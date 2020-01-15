#include "GameFrame.h"

GameFrame::GameFrame(void)
{
	m_bIsFullMode = TRUE; // �⺻�� Ǯ���
	m_nFPSCount = 0;
	m_nFPS = 0;
}

GameFrame::~GameFrame(void)
{
}

void GameFrame::ChangeScreenMode(BOOL bIsFullMode)
{
	RECT rect;
	m_bIsFullMode = bIsFullMode;
	if (bIsFullMode)
	{
		SetWindowLong(m_hWnd, GWL_STYLE, WS_POPUP);
		SetWindowPos(m_hWnd, 0, 0, 0, m_nWidth, m_nHeight, SWP_SHOWWINDOW);
		FullScreenModeChange();
	}
	else {
		// ChangeDisplaySettings(NULL, 0);
		SetWindowLong(m_hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);

		// ������ ũ�� ����
		SetRect(&rect, 0, 0, m_nWidth, m_nHeight);
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(m_hWnd, 0, 100, 100, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);
	}
}

void GameFrame::FullScreenModeChange()
{
	DEVMODE sDevMode;
	sDevMode.dmSize = sizeof(DEVMODE);
	sDevMode.dmPelsWidth = m_nWidth;
	sDevMode.dmPelsHeight = m_nHeight;
	sDevMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
	ChangeDisplaySettings(&sDevMode, CDS_FULLSCREEN);
}

void GameFrame::Init(HWND hWnd, int nWidth, int nHeight, BOOL bIsFullMode)
{
	HBITMAP hBitmap;
	HDC hdc;
	RECT rect;

	m_hWnd = hWnd;
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_bIsFullMode = bIsFullMode;

	hdc = GetDC(m_hWnd);
	m_hBackBuffer = CreateCompatibleDC(hdc);
	hBitmap = CreateCompatibleBitmap(hdc, m_nWidth, m_nHeight);
	SelectObject(m_hBackBuffer, (HBITMAP)hBitmap);
	DeleteObject(hBitmap);
	ReleaseDC(m_hWnd, hdc);

	ChangeScreenMode(bIsFullMode);

	SceneInit();

	m_dwOldFPSTime = GetTickCount();

	keyState = None;
}

void GameFrame::Update()
{
	m_dwCurTime = GetTickCount();
	if (m_dwCurTime - m_dwOldFPSTime >= 1000)
	{
		m_dwOldFPSTime = m_dwCurTime;
		m_nFPS = m_nFPSCount;
		m_nFPSCount = 0;
	}
	else {
		m_nFPSCount++;
	}

	SceneUpdate();
}

void GameFrame::Render()
{
	HDC hdc = GetDC(m_hWnd);
	PatBlt(m_hBackBuffer, 0, 0, m_nWidth, m_nHeight, BLACKNESS);
	// ������ �̹��� ���

	SceneRender();

	BitBlt(hdc, 0, 0, m_nWidth, m_nHeight, m_hBackBuffer, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hdc);
}

void GameFrame::Release()
{
	DeleteDC(m_hBackBuffer);

	SceneRelease();
}
