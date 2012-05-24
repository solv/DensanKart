//--------------------------------------------------------------
//�L�����N�^�C���^�[�t�F�[�X�N���X
//--------------------------------------------------------------

//��d�C���N���[�h�h�~
#pragma once

//�w�b�_�[�t�@�C���̓ǂݍ���
#include <d3dx9.h>
#include "../WindowBase/DeviceBase/DrawDevice/iDrawObjectBase.h"
#include "iPosInfo.h"
#include "../_Debug/SmartPtr.h"

typedef sp<iPosInfo> SPIPosInfo;

class iCharctor : public iDrawObjectBase
{
public:
	SPIPosInfo m_spPosInfo; //�ʒu���

public:
	iCharctor(){}
	iCharctor( LPCTSTR ImageName ):iDrawObjectBase(ImageName){}
	iCharctor( Image inImage ):iDrawObjectBase(inImage){}

	SPIPosInfo GetPosInfo(){ return m_spPosInfo; }
	virtual void Draw() = 0;
	virtual void Move() = 0;
};