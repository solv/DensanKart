//ヘッダーファイル読み込み
#include "cStageManager.h"
#include "../../../_Debug/dDebug.h"
#include "../../../_Debug/dComon.h"

namespace{
	static const int MAX_LAP = 2;
	int DrawLap = 1;
}

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
cStageManager::cStageManager():m_Lap(0),m_GoalFlag(FALSE)
{
	m_pTimer = NEW cTimer;
	m_spPosInfo->SetPos( 540.0f, 0.0f, 0.0f );
	
	DrawLap = 1;

	DxLib::SetFontSize(25);
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
cStageManager::~cStageManager()
{
	SAFE_DELETE( m_pTimer );
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void cStageManager::Updata( int RunningFlag )
{
	this->SetLap( RunningFlag );

	m_pTimer->Updata();
	if( m_Lap > MAX_LAP ){
		m_pTimer->TimerStop();
		m_GoalFlag = TRUE;
	}

}

//--------------------------------------------------------------
// 画像の描画
//--------------------------------------------------------------
void cStageManager::Draw()
{
	m_pTimer->Draw();
	DxLib::DrawFormatString( m_spPosInfo->GetPosX(), m_spPosInfo->GetPosY(), GetColor(0,255,255), _T("Lap:%d/%d"),DrawLap ,MAX_LAP );
}

//--------------------------------------------------------------
// ラップ数の設定
//--------------------------------------------------------------
void cStageManager::SetLap( int RunningFlag )
{
	if( RunningFlag == 1 )	++m_Lap < DrawLap ?  DrawLap : m_Lap <= MAX_LAP ? DrawLap = m_Lap : DrawLap;
	if( RunningFlag == 2 )	--m_Lap;
}

//--------------------------------------------------------------
// ラップ数の取得
//--------------------------------------------------------------
int cStageManager::GetLap()
{
	return this->m_Lap;
}

//--------------------------------------------------------------
// ゴールしたかどうか
//--------------------------------------------------------------
bool cStageManager::GetGoalFlag()
{
	return this->m_GoalFlag;
}