//ヘッダーファイルー読み込み
#include "cSelectSceneCharctor.h"
#include "../../../_Debug/dComon.h"

//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
cStringCharctor::cStringCharctor( int* CourseTime ):cCharctor()
{
	SetCourse(0,CourseTime);
	SetCar(0);
	DxLib::SetFontSize(30);
}

//-------------------------------------------------------------------
// コース名の初期化
//-------------------------------------------------------------------
void cStringCharctor::SetCourse( int CourseNum, int* CourseTime )
{
	
	_stprintf_s( this->m_String[0], 256, _T("CourseName:Course%d"), CourseNum+1 );
	_stprintf_s( this->m_String[1], 256, _T("BestTime:%02d\"%02d'%02d"),  *(CourseTime+(CourseNum*3)), *(CourseTime+(1+CourseNum*3)), *(CourseTime+(2+CourseNum*3)) );
}

//-------------------------------------------------------------------
// マシン名の初期化
//-------------------------------------------------------------------
void cStringCharctor::SetCar( int CarNum )
{
	LPCTSTR CarType[] = { _T("LightWeight"), _T("MiddleWeighgt"), _T("HeavyWeight") };
	LPCTSTR CarName[] = { _T("Blue Impulse"), _T("Green Arrow"), _T("Red Star") };
	_stprintf_s( this->m_String[2], 256, _T("CarName:%s"), CarName[CarNum] );
	_stprintf_s( this->m_String[3], 256, _T("CarType:%s"), CarType[CarNum]);
}

//-------------------------------------------------------------------
// 画像の描画
//-------------------------------------------------------------------
void cStringCharctor::Draw()
{
	float PosY = 100.0f;
	for( int i=0; i<4; i++, PosY+=100.0f ){
		m_spPosInfo->SetPos( 255.0f, PosY, 0.0f );
		DxLib::DrawFormatString( m_spPosInfo->GetPosX(), m_spPosInfo->GetPosY(), DxLib::GetColor(0,0,255), _T("%s"),this->m_String[i] );
	}
}

//-------------------------------------------------------------------
// 更新処理
//-------------------------------------------------------------------
void cStringCharctor::Updata( int CourseNum, int CarNum, int* CourseTime )
{
	SetCourse( CourseNum, CourseTime );
	SetCar( CarNum );
}