//ヘッダーファイル読み込み
#include "cPlaySceneCharctor.h"
#include "../../../_Debug/dComon.h"

//--------------------------------------------------------------
// 画像の描画
//--------------------------------------------------------------
void cSpeedoMeterCharctor::Draw()
{
	DxLib::DrawGraphF( m_spPosInfo->GetPosX(), m_spPosInfo->GetPosY(), GetImage(), TRUE );
}

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
cSpeedoMeterNeedleCharctor::cSpeedoMeterNeedleCharctor(LPCTSTR ImageName):cCharctor(ImageName),m_Angle(0.0)
{
	m_spPosInfo->SetPos( 554.0f, 395.0f, 0.0f );
}

//--------------------------------------------------------------
// 画像の描画
//--------------------------------------------------------------
void cSpeedoMeterNeedleCharctor::Draw()
{
	DxLib::DrawRotaGraphF( m_spPosInfo->GetPosX(), m_spPosInfo->GetPosY(), 1.0, this->m_Angle, GetImage(), TRUE );
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void cSpeedoMeterNeedleCharctor::Updata( float Vel )
{
	m_Angle = DEG_TO_RAD( ChangeVelToSpeed( Vel ) ) - 2.63;
}

//--------------------------------------------------------------
// 速度の変換
//--------------------------------------------------------------
float cSpeedoMeterNeedleCharctor::ChangeVelToSpeed( float Vel )
{
	return Vel * 18;
}