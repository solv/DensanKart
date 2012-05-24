//ヘッダーファイル読み込み
#include "cPlaySceneCharctor.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
cGoalSignalCharctor::cGoalSignalCharctor( LPCTSTR ImageName, int Count ):cSignalCharctor(ImageName,Count)
{
	this->SetIsDraw( FALSE );
	this->m_ExRate = 0.0;
	m_spPosInfo->SetPos( 320.0f, 240.0f, 0.0f );
}

//--------------------------------------------------------------
// 画像の描画
//--------------------------------------------------------------
void cGoalSignalCharctor::Draw()
{
	DxLib::DrawRotaGraphF( m_spPosInfo->GetPosX(), m_spPosInfo->GetPosY(), this->m_ExRate, 0.0, GetImage(), FALSE );
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void cGoalSignalCharctor::Updata()
{
	this->m_ExRate += 0.01f;
	if( this->m_ExRate >= 1.0 )	this->m_ExRate = 1.0;
}