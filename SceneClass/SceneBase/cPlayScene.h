//--------------------------------------------------------------
//�v���C�V�[���N���X
//-------------------------------------------------------------

//��d�C���N���[�h�h�~
#pragma once

//�w�b�_�[�t�@�C���Ǎ�
#include "../iFuncSetter.h"
#include "../iSceneBase.h"
#include "../../WindowBase/DeviceBase/cDeviceBase.h"

class cPlayScene : public iSceneBase
{
public:
	cDeviceBase* Device;

	enum Select{
		Select_None,
		Select_GoSelect,
		Select_GoTitle,
		Select_Exit,
		Select_GoPlaying,
	};

private:
	Dix::FuncSetter<cPlayScene> stateFunc_;
	StateResult stateResult_;
	Select select_;

	int m_CourseNum;
	int m_CarNum;

	void Init();
	void Start();
	void Idle();
	void PlayEnd();
	void End();
	
public:
	cPlayScene():stateResult_( StateResult_Continue ){
		stateFunc_.setFunc( &cPlayScene::Init );
	}

	virtual ~cPlayScene(){}

	//�X�V
	virtual StateResult Update(){
		stateFunc_.exec( this );
		return stateResult_;
	}

	//�^�C�g���̑I�����ʎ擾
	Select getSelectResult(){ return select_; }

	//�R�[�X�ԍ����Z�b�g
	void SetCourseNumber( int num ){ m_CourseNum = num; }
	//�}�V���ԍ����Z�b�g
	void SetCarNumber( int num ){ m_CarNum = num; }
};