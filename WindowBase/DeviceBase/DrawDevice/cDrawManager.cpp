//ヘッダーファイル読み込み
#include "DxLib.h"
#include "cDrawManager.h"

//-------------------------------------------------------------------
// 画像の描画
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
// 画像の追加
//-------------------------------------------------------------------
HRESULT cDrawManager::Append( iDrawObjectBase* inDrawObject )
{
	m_VectorDraw.push_back( inDrawObject );
	return( S_OK );
}

//-------------------------------------------------------------------
// 画像の削除
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