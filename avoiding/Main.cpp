//--------------------------------------------------------------------------------------
// File: Main.cpp
//
// メイン
//
// 備考：このプログラムはDirectX11を使用するための最低必要と思われる処理を組み込んだサンプルです
//       余分な処理は記述していませんのでオリジナルフレームワークのベースに使用してください
//
// Date: 2015.8.27
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------

// 標準ライブラリ
#include <d3d11.h>
#include <Windows.h>
#include <DirectXColors.h>
#include <SimpleMath.h>
#include <ctime>
#include <memory>

// 先生のフレームワーク
#include "ImaseLib\Direct3D.h"
#include "ImaseLib\DirectXTK.h"
#include "ImaseLib\FPSTimer.h"
#include "ImaseLib\DebugCamera.h"

// 自作ヘッダファイル
#include "GameSource\Game.h"

// 名前空間
using namespace std;
using namespace Microsoft::WRL;
using namespace DirectX;
using namespace DirectX::SimpleMath;

//////////////////
// 定数宣言		//
//////////////////
// ウインドウスタイル
static const DWORD WINDOW_STYLE = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

// 画面解像度
static const int WINDOW_W = 1280;
static const int WINDOW_H = 960;

//////////////////////////////
// 関数のプロトタイプ宣言	//
//////////////////////////////
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//////////////////////
// グローバル変数	//
//////////////////////
HINSTANCE g_hInst = nullptr;	// インスタンスハンドル
HWND g_hWnd = nullptr;	// ウインドウハンドル

// ゲーム
shared_ptr<Game> game;

//--------------------------------------------------------------------------------------
// メイン
//--------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned int)time(NULL));

	// デバッグカメラ
	DebugCamera camera(WINDOW_W, WINDOW_H);

	// 1秒間に60フレームで固定する
	ImaseLib::FPSTimer fpsTimer(60);

	// ウインドウの作成
	if (FAILED(InitWindow(hInstance, nCmdShow)))
		return 0;

	// DirectXデバイスの初期化
	if (FAILED(Direct3D_InitDevice(g_hWnd)))
	{
		// 初期化に失敗
		Direct3D_CleanupDevice();
		return 0;
	}

	// DirectXTK関係の初期化
	DirectXTK_Initialize();

	// 初期化
	game = make_shared<Game>();
	game->Initialize(WINDOW_W,WINDOW_H);

	// メインループ
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		// メッセージが来ているか調べる
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// メッセージが来ていればウインドウプロシージャへ送る
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// キー入力やマウス情報の更新
			DirectXTK_UpdateInputState();

			// デバッグカメラの更新
			camera.Update();

			// 更新
			game->Update();

			// バックバッファのクリア
			g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView.Get(), DirectX::Colors::WhiteSmoke);

			// 深度バッファのクリア
			g_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

			// ビュー行列を作成する
			Matrix view = camera.GetCameraMatrix();

			// 射影行列を作成する
			Matrix proj = Matrix::CreatePerspectiveFieldOfView(XMConvertToRadians(45.0f), WINDOW_W / (float)WINDOW_H, 1.0f, 100.0f);
	
			game->Render(view,proj);

			// 画面更新を待つ
			fpsTimer.WaitFrame();

			// バックバッファとフロントバッファを入れ替える
			g_pSwapChain->Present(0, 0);
		}
	}

	// 終了処理
	game->Finalize();

	// DirectXデバイス周りの終了処理
	Direct3D_CleanupDevice();

	return 0;
}

//--------------------------------------------------------------------------------------
// ウインドウの作成
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	// ウインドウクラスを登録する
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)NULL);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"WindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)NULL);
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	// ウインドウを作成する
	g_hInst = hInstance;
	RECT rc = { 0, 0, WINDOW_W, WINDOW_H };	// ←ウインドウサイズ
	AdjustWindowRect(&rc, WINDOW_STYLE, FALSE);
	g_hWnd = CreateWindow(L"WindowClass", L"avoiding", WINDOW_STYLE,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);
	if (!g_hWnd)
		return E_FAIL;

	// ウインドウの表示
	ShowWindow(g_hWnd, nCmdShow);

	return S_OK;
}

//--------------------------------------------------------------------------------------
// ウインドウプロシージャー
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:		// ウインドウが破棄されたメッセージ
		PostQuitMessage(0);	// WM_QUITメッセージを送出する（メインループを抜ける）
		break;

	case WM_ACTIVATEAPP:	// ウインドウがアクティブ化、非アクティブ化する時に来るメッセージ
		Keyboard::ProcessMessage(message, wParam, lParam);
		Mouse::ProcessMessage(message, wParam, lParam);
		break;

	case WM_KEYDOWN:		// キー入力関係のメッセージ
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard::ProcessMessage(message, wParam, lParam);
		break;

	case WM_INPUT:			// マウス関係のメッセージ
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		Mouse::ProcessMessage(message, wParam, lParam);
		break;

	default:
		// 自分で処理しないメッセージはDefWindowProc関数に任せる
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
