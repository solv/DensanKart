//--------------------------------------------------------------
//アプリケーション統括クラス
//-------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイル読込
#include <windows.h>
#include <tchar.h>
#include "DeviceBase/cDeviceBase.h"
#include "../SceneClass/cGameSceneBase.h"
#include "../_Debug/dDebug.h"
#include "../_Debug/dComon.h"

//全ての統括クラス
class cDxWindowBase
{
private:
	cDeviceBase		deviceBase;
	cGameSceneBase*	gameScene;
	bool m_isEnd;

public:
	cDxWindowBase();
   ~cDxWindowBase();

   void Init();

   virtual bool Run();
};