//--------------------------------------------------------------
//�}�V���E�R�[�X�Z���N�g�V�[���N���X
//-------------------------------------------------------------

//��d�C���N���[�h�h�~
#pragma once

//�w�b�_�[�t�@�C���Ǎ�
#include "../iFuncSetter.h"
#include "../iSceneBase.h"
#include "../../WindowBase/DeviceBase/cDeviceBase.h"

class cSelectScene : public iSceneBase
{
public:
	int SelectNum;
	cDeviceBase* Device;

	enum Select{
		Select_None,
		Select_GoPlaying,
		Select_GoTitle,
		Select_Exit,
	};

private:
	Dix::FuncSetter<cSelectScene> stateFunc_;
	StateResult stateResult_;
	Select select_;

	int m_CourseNum;
	int m_CarNum;

	void Init();
	void Idle();
	void End();

public:
	cSelectScene():stateResult_( StateResult_Continue ){
		stateFunc_.setFunc( &cSelectScene::Init );
	}

	virtual ~cSelectScene(){}

	//�X�V
	virtual StateResult Update(){
		stateFunc_.exec( this );
		return stateResult_;
	}

	//�^�C�g���̑I�����ʎ擾
	Select getSelectResult(){ return select_; }

	//�R�[�X�ԍ��̎擾
	int GetCourseNumber();
	//�}�V���ԍ��̎擾
	int GetCarNumber();
};