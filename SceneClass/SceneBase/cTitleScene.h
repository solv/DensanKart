//--------------------------------------------------------------
//�^�C�g���V�[���N���X
//-------------------------------------------------------------

//��d�C���N���[�h�h�~
#pragma once

//�w�b�_�[�t�@�C���Ǎ�
#include "../iFuncSetter.h"
#include "../iSceneBase.h"
#include "../../WindowBase/DeviceBase/cDeviceBase.h"

class cTitleScene : public iSceneBase
{
public:
	cDeviceBase* Device;

	enum Select{
		Select_GoSelect,
		Select_Config,
		Select_Exit,
		Select_None,
	};

private:
	Dix::FuncSetter<cTitleScene> stateFunc_;
	StateResult stateResult_;
	Select select_;

	void Init();
	void Idle();
	void KeyConfig();
	void End();

public:
	cTitleScene():stateResult_( StateResult_Continue ),select_( Select_None ){
		stateFunc_.setFunc( &cTitleScene::Init );
	}

	virtual ~cTitleScene(){}

	//�X�V
	virtual StateResult Update(){
		stateFunc_.exec( this );
		return stateResult_;
	}

	//�^�C�g���̑I�����ʎ擾
	Select getSelectResult(){ return select_; }
};