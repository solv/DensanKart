//-------------------------------------------------------------
//�`�ʊǗ��N���X
//-------------------------------------------------------------

//��d�C���N���[�h�h�~
#pragma once

//�w�b�_�[�t�@�C���Ǎ�
#include <vector>
#include "iDrawObjectBase.h"

class cDrawManager
{
private:
	std::vector<iDrawObjectBase*> m_VectorDraw;

public:
	cDrawManager(){}
	virtual ~cDrawManager(){}

	void Draw();
	HRESULT Remove();
	HRESULT Append( iDrawObjectBase* );
};
