//�w�b�_�[�t�@�C���ǂݍ���
#include "cPlaySceneCharctor.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
cSignalCharctor::cSignalCharctor( LPCTSTR FileName, int Count ):cCharctor(FileName),m_SignalCount(Count),m_ExRate(2.0)
{
	m_spPosInfo->SetPos( 320.0f, 200.0f, 0.0f );
}

//--------------------------------------------------------------
// �摜�̕`��
//--------------------------------------------------------------
void cSignalCharctor::Draw()
{
	DxLib::DrawRotaGraphF( m_spPosInfo->GetPosX(), m_spPosInfo->GetPosY(), m_ExRate, 0.0, GetImage(), TRUE );
}

//--------------------------------------------------------------
// �X�V����
//--------------------------------------------------------------
void cSignalCharctor::Updata()
{
	this->SetIsDraw( TRUE );
	this->m_ExRate -= 0.033;
	this->m_SignalCount--;
	if( this->m_SignalCount <= 0 ){
		this->SetIsDraw( FALSE );
	}
}

//--------------------------------------------------------------
// �S�[���J�E���g�̎擾
//--------------------------------------------------------------
int cSignalCharctor::GetSignalCount()
{
	return this->m_SignalCount;
}