//--------------------------------------------------------------
//�Q�[���V�[���x�[�X�N���X
//-------------------------------------------------------------

//��d�C���N���[�h�h�~
#pragma once

//�w�b�_�[�t�@�C���Ǎ�
#include <windows.h>
#include "iSceneBase.h"
#include "iFuncSetter.h"
#include "../WindowBase/DeviceBase/cDeviceBase.h"
#include "SceneBase/cTitleScene.h"
#include "SceneBase/cSelectScene.h"
#include "SceneBase/cPlayScene.h"

class cGameSceneBase : public iSceneBase
{
private:
	Dix::FuncSetter<cGameSceneBase> stateFunc_;	//���s�X�e�[�g
	StateResult stateResult_;					//��Ԃ̌���

	//�e��V�[��
	cTitleScene		titleScene_;
	cSelectScene	selectScene_;
	cPlayScene		playScene_;

public:
	cGameSceneBase( cDeviceBase* dev ):stateResult_( StateResult_Continue ){
		titleScene_.Device	 = dev;
		selectScene_.Device  = dev;
		playScene_.Device    = dev;
		stateFunc_.setFunc( &cGameSceneBase::Title );
	}
	virtual ~cGameSceneBase(){}

	//�X�V
	virtual StateResult Update();

	//�X�e�[�g���\�b�h
	void Title();	//�^�C�g��
	void Select();	//�}�V���E�R�[�X�I��
	void Playing();	//�v���C��
};