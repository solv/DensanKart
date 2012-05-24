//--------------------------------------------------------------
//プレイシーンタイマークラス
//-------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイルの読み込み
#include "../../cCharctor.h"
#include "../../../_Debug/dComon.h"

class cTimer : public cCharctor
{
private:
	int m_Time;
	bool m_TimerFlag;

	int m_TimeMinute;
	int m_TimeSecond;
	int m_TimeMilliSecond;

	int m_NowTime[3];

public:
	cTimer();
	~cTimer(){}

	void TimerStart();
	void TimerStop();
	void SetChangeTime();
	void Updata();

	virtual void Draw();
	virtual void Move(){}

	int* GetNewTime(){
		this->m_NowTime[0] = this->m_TimeMinute;
		this->m_NowTime[1] = this->m_TimeSecond;
		this->m_NowTime[2] = this->m_TimeMilliSecond;

		return m_NowTime;
	}
};

//--------------------------------------------------------------
// タイムの記録クラス
//--------------------------------------------------------------
class cTimeRecord
{
private:
	int m_RecordTime[MAX_COURSE*3];

public:
	cTimeRecord();
	virtual ~cTimeRecord(){}

	bool ComparisonTime( int CourseNum, int* NewRecordTime );
	bool WriteFile();
	bool LoadFile();

	int* GetRecordTime(){ return m_RecordTime; }
};
