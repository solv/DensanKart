//--------------------------------------------------------------
//�V�[���x�[�X�N���X
//-------------------------------------------------------------

//��d�C���N���[�h�h�~
#pragma once

//�w�b�_�[�t�@�C���Ǎ�

//��ԑJ�ڊ�{�N���X
class iSceneBase
{
public:
	enum StateResult{
		StateResult_Finish,		// ��ԏI��
		StateResult_Continue	// ��Ԍp����
	};

public:
	iSceneBase(){}
	virtual ~iSceneBase(){}

	//�X�V
	virtual StateResult Update() = 0;
};