//�w�b�_�[�t�@�C���ǂݍ���
#include "DxLib.h"
#include "cSelectSceneCharctor.h"

//-------------------------------------------------------------------
// �摜�̕`��
//-------------------------------------------------------------------
void cObjectCharctor::Draw()
{
	DxLib::DrawRotaGraphF( m_spPosInfo->GetPosX(), m_spPosInfo->GetPosY(), 1.0, m_Angle, GetImage(), TRUE );
}

//-------------------------------------------------------------------
// �X�V����
//-------------------------------------------------------------------
void cObjectCharctor::Updata()
{
	m_Angle += m_AngleVel;
}