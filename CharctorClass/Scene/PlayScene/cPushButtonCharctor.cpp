//ヘッダーファイル読み込み
#include "cPlaySceneCharctor.h"

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
cPushButtonCharctor::cPushButtonCharctor(LPCTSTR ImageName, int Count = 0 ):cGoalSignalCharctor(ImageName,Count)
{
	this->m_ExRate = 1.0;
	this->m_spPosInfo->SetPos( 320.0f, 500.0f, 0.0f );
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void cPushButtonCharctor::Updata()
{
	D3DXVECTOR3 Pos;
	this->m_spPosInfo->GetPos( &Pos );
	Pos.y <= 360.0f ? Pos.y : Pos.y -= 5.0f;
	this->m_spPosInfo->SetPos( &Pos );
}