#pragma once
#include"framework.h"
enum KeyState
{
	None,Left,Up,Right,Down,Z
};

class GameFrame
{
protected:
	HWND m_hWnd;
	HDC	m_hBackBuffer;
	int m_nWidth, m_nHeight;
	BOOL m_bIsFullMode;
	int m_nFPS;
	DWORD m_dwOldFPSTime;
	DWORD m_dwCurTime;

	virtual void SceneInit() = 0;
	virtual void SceneUpdate() = 0;
	virtual void SceneRender() = 0;
	virtual void SceneRelease() = 0;
	void ChangeScreenMode(BOOL bIsFullMode);

	bool keyCheack = false;

private:
	int m_nFPSCount;
	void FullScreenModeChange();

public:
	void Init(HWND hWnd, int nWidth, int nHeight, BOOL bIsFullMode);
	void Update();
	void Render();
	void Release();

	void ZkeyProgress()
	{

		if (keyCheack == false)
		{
			keyState = Z;
		}

	}

	void ZkeyUp()
	{
		keyCheack = false;
	}

	KeyState keyState;
public:
	GameFrame(void);
	~GameFrame(void);
};

