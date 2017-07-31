//--------------------------------------------------------------------------------------
// File: Main.cpp
//
// ���C��
//
// ���l�F���̃v���O������DirectX11���g�p���邽�߂̍Œ�K�v�Ǝv���鏈����g�ݍ��񂾃T���v���ł�
//       �]���ȏ����͋L�q���Ă��܂���̂ŃI���W�i���t���[�����[�N�̃x�[�X�Ɏg�p���Ă�������
//
// Date: 2015.8.27
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------

// �W�����C�u����
#include <d3d11.h>
#include <Windows.h>
#include <DirectXColors.h>
#include <SimpleMath.h>
#include <ctime>
#include <memory>

// �搶�̃t���[�����[�N
#include "ImaseLib\Direct3D.h"
#include "ImaseLib\DirectXTK.h"
#include "ImaseLib\FPSTimer.h"
#include "ImaseLib\DebugCamera.h"

// ����w�b�_�t�@�C��
#include "GameSource\Game.h"

// ���O���
using namespace std;
using namespace Microsoft::WRL;
using namespace DirectX;
using namespace DirectX::SimpleMath;

//////////////////
// �萔�錾		//
//////////////////
// �E�C���h�E�X�^�C��
static const DWORD WINDOW_STYLE = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

// ��ʉ𑜓x
static const int WINDOW_W = 1280;
static const int WINDOW_H = 960;

//////////////////////////////
// �֐��̃v���g�^�C�v�錾	//
//////////////////////////////
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//////////////////////
// �O���[�o���ϐ�	//
//////////////////////
HINSTANCE g_hInst = nullptr;	// �C���X�^���X�n���h��
HWND g_hWnd = nullptr;	// �E�C���h�E�n���h��

// �Q�[��
shared_ptr<Game> game;

//--------------------------------------------------------------------------------------
// ���C��
//--------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned int)time(NULL));

	// �f�o�b�O�J����
	DebugCamera camera(WINDOW_W, WINDOW_H);

	// 1�b�Ԃ�60�t���[���ŌŒ肷��
	ImaseLib::FPSTimer fpsTimer(60);

	// �E�C���h�E�̍쐬
	if (FAILED(InitWindow(hInstance, nCmdShow)))
		return 0;

	// DirectX�f�o�C�X�̏�����
	if (FAILED(Direct3D_InitDevice(g_hWnd)))
	{
		// �������Ɏ��s
		Direct3D_CleanupDevice();
		return 0;
	}

	// DirectXTK�֌W�̏�����
	DirectXTK_Initialize();

	// ������
	game = make_shared<Game>();
	game->Initialize(WINDOW_W,WINDOW_H);

	// ���C�����[�v
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		// ���b�Z�[�W�����Ă��邩���ׂ�
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// ���b�Z�[�W�����Ă���΃E�C���h�E�v���V�[�W���֑���
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// �L�[���͂�}�E�X���̍X�V
			DirectXTK_UpdateInputState();

			// �f�o�b�O�J�����̍X�V
			camera.Update();

			// �X�V
			game->Update();

			// �o�b�N�o�b�t�@�̃N���A
			g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView.Get(), DirectX::Colors::MidnightBlue);

			// �[�x�o�b�t�@�̃N���A
			g_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

			// �r���[�s����쐬����
			Matrix view = camera.GetCameraMatrix();

			// �ˉe�s����쐬����
			Matrix proj = Matrix::CreatePerspectiveFieldOfView(XMConvertToRadians(45.0f), WINDOW_W / (float)WINDOW_H, 1.0f, 100.0f);
	
			game->Render(view,proj);

			// ��ʍX�V��҂�
			fpsTimer.WaitFrame();

			// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���
			g_pSwapChain->Present(0, 0);
		}
	}

	// �I������
	game->Finalize();

	// DirectX�f�o�C�X����̏I������
	Direct3D_CleanupDevice();

	return 0;
}

//--------------------------------------------------------------------------------------
// �E�C���h�E�̍쐬
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	// �E�C���h�E�N���X��o�^����
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

	// �E�C���h�E���쐬����
	g_hInst = hInstance;
	RECT rc = { 0, 0, WINDOW_W, WINDOW_H };	// ���E�C���h�E�T�C�Y
	AdjustWindowRect(&rc, WINDOW_STYLE, FALSE);
	g_hWnd = CreateWindow(L"WindowClass", L"avoiding", WINDOW_STYLE,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);
	if (!g_hWnd)
		return E_FAIL;

	// �E�C���h�E�̕\��
	ShowWindow(g_hWnd, nCmdShow);

	return S_OK;
}

//--------------------------------------------------------------------------------------
// �E�C���h�E�v���V�[�W���[
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:		// �E�C���h�E���j�����ꂽ���b�Z�[�W
		PostQuitMessage(0);	// WM_QUIT���b�Z�[�W�𑗏o����i���C�����[�v�𔲂���j
		break;

	case WM_ACTIVATEAPP:	// �E�C���h�E���A�N�e�B�u���A��A�N�e�B�u�����鎞�ɗ��郁�b�Z�[�W
		Keyboard::ProcessMessage(message, wParam, lParam);
		Mouse::ProcessMessage(message, wParam, lParam);
		break;

	case WM_KEYDOWN:		// �L�[���͊֌W�̃��b�Z�[�W
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard::ProcessMessage(message, wParam, lParam);
		break;

	case WM_INPUT:			// �}�E�X�֌W�̃��b�Z�[�W
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
		// �����ŏ������Ȃ����b�Z�[�W��DefWindowProc�֐��ɔC����
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
