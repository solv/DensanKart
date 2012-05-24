//--------------------------------------------------------------
//�L�����N�^�N���X
//-------------------------------------------------------------

//��d�C���N���[�h�h�~
#pragma once

//�w�b�_�[�t�@�C���̓ǂݍ���
#include "DxLib.h"
#include "Interface/iCharctor.h"
#include "cPosInfo.h"

class cCharctor : public iCharctor
{
public:
	// �����Ȃ��A�摜����A�摜�p�X����ǂݍ���
	cCharctor(){
		m_spPosInfo.SetPtr( new cPosInfo );
		m_spPosInfo->SetPos(0,1,0);
	}
	cCharctor( LPCTSTR ImageName ):iCharctor(ImageName){
		m_spPosInfo.SetPtr( new cPosInfo );
		m_spPosInfo->SetPos(0,1,0);
	}
	cCharctor( Image inImage ):iCharctor(inImage){
		m_spPosInfo.SetPtr( new cPosInfo );
		m_spPosInfo->SetPos(0,1,0);
	}

	virtual ~cCharctor(){}

	inline virtual void Draw(){
		DxLib::DrawGraphF( m_spPosInfo->GetPosX(), m_spPosInfo->GetPosY(), GetImage(), FALSE );
	}
	virtual void Move(){}
};