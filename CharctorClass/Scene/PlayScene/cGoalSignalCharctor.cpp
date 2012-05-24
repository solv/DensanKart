//�w�b�_�[�t�@�C���ǂݍ���
#include "cPlaySceneCharctor.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
cGoalSignalCharctor::cGoalSignalCharctor( LPCTSTR ImageName, int Count ):cSignalCharctor(ImageName,Count)
{
	this->SetIsDraw( FALSE );
	this->m_ExRate = 0.0;
	m_spPosInfo->SetPos( 320.0f, 240.0f, 0.0f );
}

//--------------------------------------------------------------
// �摜�̕`��
//--------------------------------------------------------------
void cGoalSignalCharctor::Draw()
{
	DxLib::DrawRotaGraphF( m_spPosInfo->GetPosX(), m_spPosInfo->GetPosY(), this->m_ExRate, 0.0, GetImage(), FALSE );
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void cGoalSignalCharctor::Updata()
{
	this->m_ExRate += 0.01f;
	if( this->m_ExRate >= 1.0 )	this->m_ExRate = 1.0;
}