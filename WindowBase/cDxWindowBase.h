//--------------------------------------------------------------
//�A�v���P�[�V���������N���X
//-------------------------------------------------------------

//��d�C���N���[�h�h�~
#pragma once

//�w�b�_�[�t�@�C���Ǎ�
#include <windows.h>
#include <tchar.h>
#include "DeviceBase/cDeviceBase.h"
#include "../SceneClass/cGameSceneBase.h"
#include "../_Debug/dDebug.h"
#include "../_Debug/dComon.h"

//�S�Ă̓����N���X
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