#pragma once
#include"GameFrame.h"
#include"CStageInfo.h"
#include"CMap.h"
#include"CPlayer.h"
#include"CUI.h"
#include"CBattleScene.h"
#include"CScene.h"
class CGameWork:public GameFrame
{
private:
	CStageInfo Stage;
	CScene* Scene;
	CBattleScene* BattleScene;
	CPlayer* Player;
	CMap* Map;
	CUI* Ui;

	virtual void SceneInit();
	virtual void SceneUpdate();
	virtual void SceneRender();
	virtual void SceneRelease();

public:
	CGameWork(void);
	~CGameWork(void);
};

