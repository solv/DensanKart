//--------------------------------------------------------------
//プレイシーンマネージャクラス
//-------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイルの読み込み
#include "../../cCharctor.h"
#include "cTimer.h"

class cStageManager : public cCharctor
{
private:
	bool m_GoalFlag;
	int m_Lap;

public:
	cTimer* m_pTimer;

public:
	cStageManager();
	virtual ~cStageManager();

	void Updata( int RunningFlag );

	virtual void Draw();
	virtual void Move(){}

	void SetLap( int RunningFlag );
	int GetLap();
	bool GetGoalFlag();
};