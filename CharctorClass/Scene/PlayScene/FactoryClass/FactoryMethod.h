//--------------------------------------------------------------
//プレイシーンコース・マシンファクトリークラス
//-------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイルの読み込み
#include "../cPlaySceneCharctor.h"
#include "../../../../_Debug/dDebug.h"

class CourseFactory
{
public:
	static cCourseCharctor* Create( int CourseNum ){
		switch( CourseNum ){
			case 0: return NEW cCourseCharctor( _T("Data/Map/Course2.crsb") );
			case 1: return NEW cCourseCharctor( _T("Data/Map/Course4.crsb") );
			case 2: return NEW cCourseCharctor( _T("Data/Map/Course5.crsb") );
			case 3:	return NEW cCourseCharctor( _T("Data/Map/Course3.crsb") );
			default: return NULL;
		}
	}
};

class CourseMaskFactory
{
public:
	static cCourseMaskCharctor* Create( int CourseNum ){
		switch( CourseNum ){
			case 0: return NEW cCourseMaskCharctor( _T("Data/Map/Course2.crsb") );
			case 1: return NEW cCourseMaskCharctor( _T("Data/Map/Course4.crsb") );
			case 2: return NEW cCourseMaskCharctor( _T("Data/Map/Course5.crsb") );
			case 3:	return NEW cCourseMaskCharctor( _T("Data/Map/Course3.crsb") );
			default: return NULL;
		}
	}
};

class CarFactory
{
public:
	static cCarCharctor* Create( int CarNum ){
		switch( CarNum ){
			case 0: return NEW cCarCharctor( _T("Data/Image/Car/Car1.img"), _T("Data/Car/CarLightWeight.prt") );
			case 1: return NEW cCarCharctor( _T("Data/Image/Car/Car2.img"), _T("Data/Car/CarMiddleWeight.prt") );
			case 2: return NEW cCarCharctor( _T("Data/Image/Car/Car3.img"), _T("Data/Car/CarHeavyWeight.prt") );
			default: return NULL;
		}
	}
};
