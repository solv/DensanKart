//�w�b�_�[�t�@�C���ǂݍ���
#include "cPlaySceneCharctor.h"

//--------------------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------------------
cNewRecordCharctor::cNewRecordCharctor(LPCTSTR ImageName, int Count):cGoalSignalCharctor(ImageName,Count)
{
	this->m_spPosInfo->SetPos( 320.0f, 130.0f, 0.0f );
}