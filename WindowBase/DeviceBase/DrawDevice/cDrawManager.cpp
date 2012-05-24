//�w�b�_�[�t�@�C���ǂݍ���
#include "DxLib.h"
#include "cDrawManager.h"

//-------------------------------------------------------------------
// �摜�̕`��
//-------------------------------------------------------------------
void cDrawManager::Draw()
{
	std::vector<iDrawObjectBase*>::iterator itr = m_VectorDraw.begin();
	for(; itr != m_VectorDraw.end(); itr++ ){
		if( (*itr)->GetIsDraw() )
			(*itr)->Draw();
	}
}

//-------------------------------------------------------------------
// �摜�̒ǉ�
//-------------------------------------------------------------------
HRESULT cDrawManager::Append( iDrawObjectBase* inDrawObject )
{
	m_VectorDraw.push_back( inDrawObject );
	return( S_OK );
}

//-------------------------------------------------------------------
// �摜�̍폜
//-------------------------------------------------------------------
HRESULT cDrawManager::Remove()
{
	std::vector<iDrawObjectBase*>::iterator itr = m_VectorDraw.begin();
	while( itr != m_VectorDraw.end() ){
		if( (*itr)->GetIsExit() ){
			DxLib::DeleteGraph( (*itr)->GetImage() );
			itr = m_VectorDraw.erase(itr);
			continue;
		}
		itr++;
	}
	return( S_OK );
}