//ヘッダーファイル読み込み
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include "cTimer.h"
#include "../../../_Debug/dDebug.h"

using namespace std;

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
cTimer::cTimer():
	m_Time(-1),
	m_TimerFlag(TRUE),
	m_TimeMinute(0),
	m_TimeSecond(0),
	m_TimeMilliSecond(0)
{
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
void cTimer::TimerStart()
{
	m_TimerFlag = TRUE;
}

//--------------------------------------------------------------
// タイマーの停止
//--------------------------------------------------------------
void cTimer::TimerStop()
{
	m_TimerFlag = FALSE;
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void cTimer::Updata()
{
	if( m_TimerFlag )	m_Time += 1;
	SetChangeTime();
}

//--------------------------------------------------------------
// 時間の変換
//--------------------------------------------------------------
void cTimer::SetChangeTime()
{
	//分
	if( m_TimeMinute >= 99 && m_TimeSecond >= 59 ){
		m_TimeMinute = 99;
	}else if( (m_TimeSecond / 60 ) == 1 ){
		m_TimeSecond = 0;
		m_TimeMinute++;
	}
	
	//秒
	if( m_TimeMinute >= 99 && m_TimeSecond >= 59 ){
		m_TimeSecond = 59;
	}else if( (m_Time / 60 ) == 1 ){
		m_TimeSecond++;
	}
	
	//ミリ秒
	if( m_TimeMinute >= 99 && m_TimeSecond >= 59 ){
		m_TimeMilliSecond = 99;
	}else{
		m_TimeMilliSecond = (int)(m_Time * 1.6);
	}

	if( m_Time >= 60 ){
		m_Time = 0;
	}
}

//--------------------------------------------------------------
// 画像の描画
//--------------------------------------------------------------
void cTimer::Draw()
{
	DrawFormatString( m_spPosInfo->GetPosX(), m_spPosInfo->GetPosY(), GetColor(255,255,255), _T("TIME:%02d\"%02d'%02d"),m_TimeMinute,m_TimeSecond,m_TimeMilliSecond );
}

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
cTimeRecord::cTimeRecord()
{
	int TimeInit[MAX_COURSE*3];
	struct _tstat stat_buf;
	ofstream ofs;

	if( _tstat( _T("Data/Score/Score.btb"), &stat_buf ) == 0 )	return;

	for( int i=0; i<MAX_COURSE*3; i++ )
		TimeInit[i] = 99;

	ofs.open( _T("Data/Score/Score.btb"), ios_base::out | ios_base::trunc | ios_base::binary );	
	ofs.write( (char*)TimeInit, sizeof(TimeInit) );
	
	ofs.close();
}

//--------------------------------------------------------------
// タイムの比較
//--------------------------------------------------------------
bool cTimeRecord::ComparisonTime( int CourseNum, int* NowRecordTime )
{
	int OldRecord = 0;
	int NowRecord = 0;

	this->LoadFile();

	MyOutputDebugString( _T("%d:%d:%d\n"),*(NowRecordTime),*(NowRecordTime+1),*(NowRecordTime+2));
	MyOutputDebugString( _T("%d:%d:%d\n"), m_RecordTime[0+(CourseNum*3)], m_RecordTime[1+(CourseNum*3)], m_RecordTime[2+(CourseNum*3)])

	for( int i=0, mul=10000; i<3; i++,mul/=100 ){
		OldRecord += m_RecordTime[i+(CourseNum*3)] * mul;
		NowRecord += *(NowRecordTime+i) * mul;
	}

	for( int i=0; i<3; i++ )
		this->m_RecordTime[i+(CourseNum*3)] = *(NowRecordTime+i);

	if( OldRecord < NowRecord ){
		MyOutputDebugString( _T("記録更新していません。") );
		return FALSE;
	}
	
	return TRUE;
}

//--------------------------------------------------------------
// タイムの書き込み
//--------------------------------------------------------------
bool cTimeRecord::WriteFile()
{
	ofstream ofs;
	ofs.open( _T("Data/Score/Score.btb"), ios_base::out | ios_base::binary | ios_base::trunc );

	MyOutputDebugString( _T("書き込み[0] %02d:%02d:%02d\n"),m_RecordTime[0],m_RecordTime[1],m_RecordTime[2] );
	MyOutputDebugString( _T("書き込み[1] %02d:%02d:%02d\n"),m_RecordTime[3],m_RecordTime[4],m_RecordTime[5] );

	ofs.write( (char*)this->m_RecordTime, sizeof(this->m_RecordTime) );

	ofs.close();	
	return TRUE;
}

//--------------------------------------------------------------
// タイムの読み込み
//--------------------------------------------------------------
bool cTimeRecord::LoadFile()
{
	ifstream ifs;
	ifs.open( _T("Data/Score/Score.btb"), ios_base::binary );

	ifs.read( (char*)this->m_RecordTime, sizeof(this->m_RecordTime) );

	MyOutputDebugString( _T("読み込み[0] %2d:%2d:%2d\n"),m_RecordTime[0],m_RecordTime[1],m_RecordTime[2] );
	MyOutputDebugString( _T("読み込み[1] %2d:%2d:%2d\n"),m_RecordTime[3],m_RecordTime[4],m_RecordTime[5] );

	ifs.close();
	return TRUE;
}