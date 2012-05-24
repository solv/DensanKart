//--------------------------------------------------------------
//セレクトシーンキャラクタクラス
//-------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイルの読み込み
#include "../../cCharctor.h"

//-------------------------------------------------------------------
// 回転してるキャラクタークラス
//-------------------------------------------------------------------
class cObjectCharctor : public cCharctor
{
private:
	double m_Angle;
	const double m_AngleVel;

public:
	cObjectCharctor( LPCTSTR FileName, double inAngleVel ):
		cCharctor(FileName),m_Angle(0),m_AngleVel(inAngleVel){}
	virtual ~cObjectCharctor(){}

	virtual void Draw();
	virtual void Updata();
};

//-------------------------------------------------------------------
// 文字列キャラクタークラス
//-------------------------------------------------------------------
class cStringCharctor : public cCharctor
{
private:
	int m_StringColor;
	TCHAR m_String[4][256];

public:
	cStringCharctor( int* CourseTime );
	virtual ~cStringCharctor(){}

	void SetCourse( int CourseNum, int* CourseTime );
	void SetCar( int CarNum );

	virtual void Draw();
	virtual void Updata( int CourseNum, int CarNum, int* CourseTime );
};