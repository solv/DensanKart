//ヘッダーファイル読み込み
#include "DxLib.h"
#include "cSelectSceneCharctor.h"

//-------------------------------------------------------------------
// 画像の描画
//-------------------------------------------------------------------
void cObjectCharctor::Draw()
{
	DxLib::DrawRotaGraphF( m_spPosInfo->GetPosX(), m_spPosInfo->GetPosY(), 1.0, m_Angle, GetImage(), TRUE );
}

//-------------------------------------------------------------------
// 更新処理
//-------------------------------------------------------------------
void cObjectCharctor::Updata()
{
	m_Angle += m_AngleVel;
}