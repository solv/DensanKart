//--------------------------------------------------------------
//�^�C�g���V�[���L�����N�^�N���X
//-------------------------------------------------------------

//��d�C���N���[�h�h�~
#pragma once

//�w�b�_�[�t�@�C���̓ǂݍ���
#include "../../cCharctor.h"

//-------------------------------------------------------------------
// �R���t�B�O���̃L�����N�^�[�N���X
//-------------------------------------------------------------------
class cConfigCharctor : public cCharctor
{
private:
	int m_StringColor[2];
	int m_KeyNum;
	TCHAR m_PushKeyString[7][64];

public:
	cConfigCharctor();
	virtual ~cConfigCharctor();

	virtual void Draw();
	virtual void Updata();
};