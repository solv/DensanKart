//ヘッダーファイル読み込み
#include "cSelectScene.h"
#include "../../CharctorClass/cCharctor.h"
#include "../../CharctorClass/Scene/SelectScene/cSelectSceneCharctor.h"
#include "../../CharctorClass/Scene/cCursorCharctor.h"
#include "../../CharctorClass/Scene/PlayScene/cTimer.h"
#include "../../_Debug/dDebug.h"
#include "../../_Debug/dComon.h"

namespace{
	enum SelectID{
		CourseSelect,
		CarSelect,
	};

	static const int FadeOutMaxCount	= 30;
	static const int FadeInMaxCount	= 30;
	static int FadeInCount		= 0;
	static int FadeOutCount		= FadeOutMaxCount;
}

cCharctor* pSelectBackGround;
cObjectCharctor* pSelectCourse[MAX_COURSE];
cObjectCharctor* pSelectCar[MAX_CAR];
cCursorCharctor* pSelectCursor;
cTimeRecord* pSelectTimeRecord;
cStringCharctor* pSelectString;

//-------------------------------------------------------------------
// 初期化
//-------------------------------------------------------------------
void cSelectScene::Init()
{
	MyOutputDebugString( _T("セレクトシーン：初期化\n") );
	stateResult_ = StateResult_Continue;
	stateFunc_.setFunc( &cSelectScene::Idle );

	pSelectBackGround = NEW cCharctor( _T("Data/Image/Back/SelectBackGround.img") );

	pSelectCourse[0] = NEW cObjectCharctor( _T("Data/Image/Course/Course2_thm.img"), 0.01 );
	pSelectCourse[1] = NEW cObjectCharctor( _T("Data/Image/Course/Course4_thm.img"), 0.01 );
	pSelectCourse[2] = NEW cObjectCharctor( _T("Data/Image/Course/Course5_thm.img"), 0.01 );
	pSelectCourse[3] = NEW cObjectCharctor( _T("Data/Image/Course/Course3_thm.img"), 0.01 );
	for( int i=0; i<MAX_COURSE; i++ )
		pSelectCourse[i]->m_spPosInfo->SetPos( 144.0f, 185.0f, 0.0f );
	for( int i=1; i<MAX_COURSE; i++ )
		pSelectCourse[i]->SetIsDraw( FALSE );

	pSelectCar[0] = NEW cObjectCharctor( _T("Data/Image/Car/Car1_thm.img"), 0.01 );
	pSelectCar[1] = NEW cObjectCharctor( _T("Data/Image/Car/Car2_thm.img"), 0.01 );
	pSelectCar[2] = NEW cObjectCharctor( _T("Data/Image/Car/Car3_thm.img"), 0.01 );
	for( int i=0; i<MAX_CAR; i++ )
		pSelectCar[i]->m_spPosInfo->SetPos( 145.0f, 345.0f, 0.0f );
	for( int i=1; i<MAX_CAR; i++ )
		pSelectCar[i]->SetIsDraw( FALSE );

	pSelectCursor = NEW cCursorCharctor( _T("Data/Image/Parts/SelectCursor.img"), 2, 0, 160 );
	pSelectCursor->m_spPosInfo->SetPos( 55.0f, 104.0f, 0.0f );
	pSelectCursor->SetFirstPos();

	pSelectTimeRecord = NEW cTimeRecord;
	pSelectTimeRecord->LoadFile();

	Device->Draw.Append( pSelectBackGround );

	for( int i=0; i<MAX_COURSE; i++ )
		Device->Draw.Append( pSelectCourse[i] );
	for( int i=0; i<MAX_CAR; i++ )
		Device->Draw.Append( pSelectCar[i] );
	Device->Draw.Append( pSelectCursor );

	pSelectString = NEW cStringCharctor( pSelectTimeRecord->GetRecordTime() );
	Device->Draw.Append( pSelectString );
	
	m_CourseNum = 0;
	m_CarNum = 0;

	Device->Sound.LoadBGM( _T("Data/Sound/Select.bgm"), 20149 );
	Device->Sound.PlayBGM();

	FadeInCount	 = 0;
	FadeOutCount = FadeOutMaxCount;
	DxLib::SetDrawBright( 0, 0, 0 );
}

static bool FadeIn()
{
	if( FadeInCount < FadeInMaxCount ){
		FadeInCount++;
		DxLib::SetDrawBright(
			FadeInCount*(255/FadeInMaxCount) , FadeInCount*(255/FadeInMaxCount), FadeInCount*(255/FadeInMaxCount)
		);
		return FALSE;
	}
	DxLib::SetDrawBright( 255, 255, 255 );
	return TRUE;
}

static bool FadeOut()
{	
	if( FadeOutCount > 0 ){
		FadeOutCount--;
		DxLib::SetDrawBright(
			FadeOutCount*(255/FadeOutMaxCount) , FadeOutCount*(255/FadeOutMaxCount), FadeOutCount*(255/FadeOutMaxCount)
		);
		return FALSE;
	}
	DxLib::SetDrawBright( 0, 0, 0 );
	return TRUE;
}

//-------------------------------------------------------------------
// 実行中
//-------------------------------------------------------------------
void cSelectScene::Idle()
{	
	if( !FadeIn() ) return;

	if( DxLib::GetWindowUserCloseFlag( TRUE ) && (MessageBox( DxLib::GetMainWindowHandle(),WindowText, WindowTitleText, MB_YESNO|MB_ICONQUESTION ) == IDYES) ){
		select_ = Select_Exit;
		stateFunc_.setFunc( &cSelectScene::End );
	}

	if(InputButton(Up) == 1){
		Device->Sound.PlaySE(0);
		pSelectCursor->Up();
	}
	if( InputButton(Down) == 1 ){
		Device->Sound.PlaySE(0);
		pSelectCursor->Down();
	}

	if( InputButton(Left) == 1 ){
		if( pSelectCursor->GetSelectID() == CourseSelect ){
			pSelectCourse[m_CourseNum]->SetIsDraw( FALSE );
			--m_CourseNum >= 0 ? m_CourseNum,Device->Sound.PlaySE(1) : m_CourseNum = 0;
			pSelectCourse[m_CourseNum]->SetIsDraw( TRUE );
		}
		if( pSelectCursor->GetSelectID() == CarSelect ){
			pSelectCar[m_CarNum]->SetIsDraw( FALSE );
			--m_CarNum >= 0 ? m_CarNum,Device->Sound.PlaySE(1) : m_CarNum = 0;
			pSelectCar[m_CarNum]->SetIsDraw( TRUE );
		}
	}
	if( InputButton(Right) == 1 ){
		if( pSelectCursor->GetSelectID() == CourseSelect ){
			pSelectCourse[m_CourseNum]->SetIsDraw( FALSE );
			++m_CourseNum < MAX_COURSE ? m_CourseNum,Device->Sound.PlaySE(1) : m_CourseNum = MAX_COURSE-1; 
			pSelectCourse[m_CourseNum]->SetIsDraw( TRUE );
		}
		if( pSelectCursor->GetSelectID() == CarSelect ){
			pSelectCar[m_CarNum]->SetIsDraw( FALSE );
			++m_CarNum < MAX_CAR ? m_CarNum,Device->Sound.PlaySE(1) : m_CarNum = MAX_CAR-1;
			pSelectCar[m_CarNum]->SetIsDraw( TRUE );
		}
	}
	
	//ゲームスタート
	if( InputButton(Button1) == 1 ){
		Device->Sound.PlaySE(3);
		select_ = Select_GoPlaying;
		stateFunc_.setFunc( &cSelectScene::End );
		MyOutputDebugString( _T("セレクトシーン：アイドル終了\nプレイシーンへ移行します\n") )
	}
	//キャンセル、タイトルに戻る
	if( InputButton(Button2) == 1 ){
		Device->Sound.PlaySE(2);
		select_ = Select_GoTitle;
		stateFunc_.setFunc( &cSelectScene::End );
		MyOutputDebugString( _T("セレクトシーン：アイドル終了\nタイトルシーンへ移行します\n") )
	}

	pSelectCourse[m_CourseNum]->Updata();
	pSelectCar[m_CarNum]->Updata();
	pSelectCursor->Updata();
	pSelectString->Updata( m_CourseNum, m_CarNum, pSelectTimeRecord->GetRecordTime() );
}

//-------------------------------------------------------------------
// 終了処理
//-------------------------------------------------------------------
void cSelectScene::End()
{
	if( select_ != Select_Exit && !FadeOut() ) return;

	pSelectBackGround->SetIsExit(TRUE);
	for( int i=0; i<MAX_COURSE; i++ )
		pSelectCourse[i]->SetIsExit(TRUE);
	for( int i=0; i<MAX_CAR; i++ )
		pSelectCar[i]->SetIsExit(TRUE);
	pSelectCursor->SetIsExit(TRUE);
	pSelectString->SetIsExit(TRUE);
	Device->Draw.Remove();
	SAFE_DELETE( pSelectBackGround );
	for( int i=0; i<MAX_COURSE; i++ )
		SAFE_DELETE( pSelectCourse[i] );
	for( int i=0; i<MAX_CAR; i++ )
		SAFE_DELETE( pSelectCar[i] );
	SAFE_DELETE( pSelectCursor );
	SAFE_DELETE( pSelectTimeRecord );
	SAFE_DELETE( pSelectString );
	Device->Sound.StopBGM();
	
	MyOutputDebugString( _T("セレクトシーン：終了\n\n") );
	stateResult_ = StateResult_Finish;
	stateFunc_.setFunc( &cSelectScene::Init );
}

//-------------------------------------------------------------------
// コース番号の取得
//-------------------------------------------------------------------
int cSelectScene::GetCourseNumber()
{
	return this->m_CourseNum;
}

//-------------------------------------------------------------------
// マシン番号の取得
//-------------------------------------------------------------------
int cSelectScene::GetCarNumber()
{
	return this->m_CarNum;
}