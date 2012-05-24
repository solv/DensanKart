//ヘッダーファイル読み込み
#include "cPlayScene.h"
#include "../../CharctorClass/Scene/PlayScene/FactoryClass/FactoryMethod.h"
#include "../../CharctorClass/cCharctor.h"
#include "../../CharctorClass/Scene/cCursorCharctor.h"
#include "../../CharctorClass/Scene/PlayScene/cPlaySceneCharctor.h"
#include "../../CharctorClass/Scene/PlayScene/cStageManager.h"
#include "../../_Debug/dDebug.h"
#include "../../_Debug/dComon.h"

static void Updata();

namespace{
	const int FadeOutMaxCount	= 30;
	const int FadeInMaxCount	= 30;
	static int FadeInCount		= 0;
	static int FadeOutCount		= FadeOutMaxCount;

	static int SignalDispCount  = 3;

	static bool EndPlayFlag	   = FALSE;
	static bool NewRecordFlag  = FALSE;
	static bool PlaySelectFlag = FALSE;
	static bool PushButtonFlag = FALSE;
}

cCourseCharctor* pPlayCourse;
cCourseMaskCharctor* pPlayCourseMask;
cCarCharctor* pPlayCar;
cStageManager* pPlayManager;
cSignalCharctor* pPlaySignal[4];
cGoalSignalCharctor* pPlayGoalSignal;
cSpeedoMeterCharctor* pPlaySpeedoMeter;
cSpeedoMeterNeedleCharctor* pPlaySpeedoMeterNeedle;
cNewRecordCharctor* pPlayNewRecord;
cPushButtonCharctor* pPlayPushButton;
cCursorCharctor* pPlayCursor;
cCharctor* pPlaySelect;
cCharctor* pPlayMap;

//-------------------------------------------------------------------
//初期化
//-------------------------------------------------------------------
void cPlayScene::Init()
{
	//遷移準備
	MyOutputDebugString( _T("プレイシーン：初期化\n") );
	stateResult_ = StateResult_Continue;
	stateFunc_.setFunc( &cPlayScene::Start );

	//コース
	pPlayCourse = CourseFactory::Create( m_CourseNum );
	Device->Draw.Append( pPlayCourse );

	//コースマスク
	pPlayCourseMask = CourseMaskFactory::Create( m_CourseNum );

	//マシン
	pPlayCar = CarFactory::Create( m_CarNum );
	Device->Draw.Append( pPlayCar );

	//ステージマネージャ
	pPlayManager = NEW cStageManager;
	Device->Draw.Append( pPlayManager );

	//シグナル
	pPlaySignal[0] = NEW cSignalCharctor( _T("Data/Image/Parts/SignalGO.img"), 60 );
	pPlaySignal[1] = NEW cSignalCharctor( _T("Data/Image/Parts/Signal1.img"), 60 );
	pPlaySignal[2] = NEW cSignalCharctor( _T("Data/Image/Parts/Signal2.img"), 60 );
	pPlaySignal[3] = NEW cSignalCharctor( _T("Data/Image/Parts/Signal3.img"), 60 );
	for( int i=0; i<4; i++ ){
		pPlaySignal[i]->SetIsDraw( FALSE );
		Device->Draw.Append( pPlaySignal[i] );
	}
	pPlayGoalSignal = NEW cGoalSignalCharctor( _T("Data/Image/Parts/SignalGoal.img"), 0 );
	Device->Draw.Append( pPlayGoalSignal );

	//NEW RECORD
	pPlayNewRecord = NEW cNewRecordCharctor( _T("Data/Image/Parts/NewRecord.img"), 60 );
	pPlayNewRecord->SetIsDraw(FALSE);
	Device->Draw.Append( pPlayNewRecord );

	//PushButton1
	pPlayPushButton = NEW cPushButtonCharctor( _T("Data/Image/Parts/PushButton.img"), 60 );
	Device->Draw.Append( pPlayPushButton );

	//スピードメーター
	pPlaySpeedoMeter = NEW cSpeedoMeterCharctor( _T("Data/Image/Parts/SpeedoMeter.img") );
	Device->Draw.Append( pPlaySpeedoMeter );
	pPlaySpeedoMeterNeedle = NEW cSpeedoMeterNeedleCharctor( _T("Data/Image/Parts/SpeedoMeterNeedle.img") );
	Device->Draw.Append( pPlaySpeedoMeterNeedle );

	//メニューとカーソル
	pPlaySelect = NEW cCharctor( _T("Data/Image/Back/PlayEndSelect.img") );
	pPlaySelect->m_spPosInfo->SetPos( 185.0f, 300.0f, 0.0f );
	pPlaySelect->SetIsDraw(FALSE);
	Device->Draw.Append( pPlaySelect );
	pPlayCursor = NEW cCursorCharctor( _T("Data/Image/Parts/PlayEndCursor.img"), 3, 0, 35 );
	pPlayCursor->m_spPosInfo->SetPos( 200.0f, 312.0f, 0.0f );
	pPlayCursor->SetFirstPos();
	pPlayCursor->SetIsDraw(FALSE);
	Device->Draw.Append( pPlayCursor );

	//変数初期化
	FadeInCount	 = 0;
	FadeOutCount = FadeOutMaxCount;
	SignalDispCount = 3;
	EndPlayFlag = FALSE;
	NewRecordFlag = FALSE;
	PlaySelectFlag = FALSE;
	PushButtonFlag = FALSE;

	//座標初期化
	Updata();
	pPlaySignal[0]->SetIsDraw( FALSE );

	//再生
	Device->Sound.LoadBGM( _T("Data/Sound/Play.bgm"), 12004 );
	Device->Sound.PlaySE(5);

	//画面の暗くする
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
//スタートのシグナル
//-------------------------------------------------------------------
void cPlayScene::Start()
{
	if( !FadeIn() ) return;

	if( pPlaySignal[1]->GetSignalCount() <= 0 ){
		Device->Sound.PlayBGM();
		Device->Sound.StopSE(5);
		Device->Sound.PlaySE(6);
		pPlayManager->m_pTimer->TimerStart();
		stateResult_ = StateResult_Continue;
		stateFunc_.setFunc( &cPlayScene::Idle );
		MyOutputDebugString( _T("プレイシーン：スタート\n") );
		return;
	}else if( pPlaySignal[3]->GetSignalCount() >= 60 ){
		Device->Sound.PlaySE(4);
	}else if( pPlaySignal[SignalDispCount]->GetSignalCount() <= 0.0 ){
		SignalDispCount--;
		pPlaySignal[SignalDispCount]->SetIsDraw( FALSE );
	}
	pPlaySignal[SignalDispCount]->Updata();

	if( DxLib::GetWindowUserCloseFlag( TRUE ) && (MessageBox( DxLib::GetMainWindowHandle(),WindowText, WindowTitleText, MB_YESNO|MB_ICONQUESTION ) == IDYES) ){
		select_ = Select_Exit;
		stateFunc_.setFunc( &cPlayScene::End );
	}
}

//-------------------------------------------------------------------
//更新処理
//-------------------------------------------------------------------
static void Updata()
{
	//マシンの移動処理
	pPlayCar->Updata( pPlayCourseMask->IsHitGroundAndCar( pPlayCar->GetCarHitTire(), pPlayCourse->GetMapPos() ) );
	//擬似的なコースの移動処理と壁判定
	pPlayCourse->Updata(
		pPlayCar->GetYaw(), pPlayCar->GetVel(),
		pPlayCourseMask->IsHitWallAndCar( pPlayCar->GetCarHitTire(), pPlayCar->GetYaw(), pPlayCourse->GetMapPos() )
	);
	//コースマップの移動処理
	//pPlayMapPoint->Updata( pPlayCourse->GetMapPos() );
	//マシンとゴールの判定
	pPlayManager->Updata( pPlayCourseMask->IsHitGoalAndCar( pPlayCar->GetCarHitTire(), pPlayCourse->GetMapPos() ) );
	//0シグナルでも動き出せるように
	pPlaySignal[0]->Updata();
	//スピードメーターの変化
	pPlaySpeedoMeterNeedle->Updata( pPlayCar->GetVel() );
	//ゴールの演出
	if( pPlayManager->GetGoalFlag() )
		pPlayGoalSignal->Updata();
	//NewRecordの演出
	if( NewRecordFlag )
		pPlayNewRecord->Updata();
	//NewRecordの演出が終わったら選択画面に移行させる
	if( pPlayNewRecord->GetExRate() >= 1.0 && !EndPlayFlag ){
		PushButtonFlag = TRUE;
		pPlayPushButton->SetIsDraw( TRUE );
	}
	//プレイ終了時の選択画面
	if( PlaySelectFlag )
		pPlayCursor->Updata();
	if( PushButtonFlag )
		pPlayPushButton->Updata();
}

//-------------------------------------------------------------------
//プレイ中の処理
//-------------------------------------------------------------------
void cPlayScene::Idle()
{
	if( InputButton(Button3) == 1 ){
		select_ = Select_GoTitle;
		stateFunc_.setFunc( &cPlayScene::End );
		MyOutputDebugString( _T("プレイシーン：アイドル終了\nタイトルシーンへ移行します\n") )
	}

	if( DxLib::GetWindowUserCloseFlag( TRUE ) && (MessageBox( DxLib::GetMainWindowHandle(),WindowText, WindowTitleText, MB_YESNO|MB_ICONQUESTION ) == IDYES) ){
		select_ = Select_Exit;
		stateFunc_.setFunc( &cPlayScene::End );
	}

	if( pPlayManager->GetGoalFlag() ){
		pPlayGoalSignal->SetIsDraw( TRUE );	
		pPlayManager->m_pTimer->TimerStop();
		stateResult_ = StateResult_Continue;
		stateFunc_.setFunc( &cPlayScene::PlayEnd );
	}

	if( InputButton(Button1) ){ pPlayCar->Acceleration( pPlayCar->AccelOn );  }
	else					   { pPlayCar->Acceleration( pPlayCar->AccelOff ); }
	if( InputButton(Button2) ){ pPlayCar->Deceleration( pPlayCar->BrakeOn );  }
	else					   { pPlayCar->Deceleration( pPlayCar->BrakeOff ); }

	if( InputButton(Left) || InputButton(Right) ){
		if( InputButton(Left) )
			pPlayCar->Steering( pPlayCar->SteeringLeft );
		if( InputButton(Right) )
			pPlayCar->Steering( pPlayCar->SteeringRight );
	}else{
		pPlayCar->Steering( pPlayCar->AutoSteering );
	}

	int Rap = pPlayManager->GetLap();
	Updata();
	if( !(Rap <= 0) && Rap < pPlayManager->GetLap() )	Device->Sound.PlaySE(2);
}

//-------------------------------------------------------------------
//終了時の選択画面
//-------------------------------------------------------------------
void cPlayScene::PlayEnd()
{
	if( DxLib::GetWindowUserCloseFlag( TRUE ) && (MessageBox( DxLib::GetMainWindowHandle(),WindowText, WindowTitleText, MB_YESNO|MB_ICONQUESTION ) == IDYES) ){
		select_ = Select_Exit;
		stateFunc_.setFunc( &cPlayScene::End );
	}

	// プレイ終了後のメニュー選択部分
	if( PlaySelectFlag ){
		if( InputButton(Up) == 1 ){
			Device->Sound.PlaySE(0);
			pPlayCursor->Up();
		}
		if( InputButton(Down) == 1 ){
			Device->Sound.PlaySE(0);
			pPlayCursor->Down();
		}
		if( InputButton(Button1) == 1 ){
			switch( pPlayCursor->GetSelectID() ){
				case 0:
					select_ = Select_GoPlaying;
					stateFunc_.setFunc( &cPlayScene::End );
					break;

				case Select_GoSelect:
					select_ = Select_GoSelect;
					stateFunc_.setFunc( &cPlayScene::End );
					break;

				case Select_GoTitle:
					select_ = Select_GoTitle;
					stateFunc_.setFunc( &cPlayScene::End );
					break;
			}
		}
	}
	// ゴール演出とNewRecord演出とPushButton演出
	else if( EndPlayFlag ){
		pPlayCursor->SetIsDraw( TRUE );
		pPlaySelect->SetIsDraw( TRUE );
		PlaySelectFlag = TRUE;
		pPlayPushButton->SetIsDraw( FALSE );
	}
	else if( PushButtonFlag  && InputButton(Button1) == 1 ){
		EndPlayFlag = TRUE;
	}
	else if( !PushButtonFlag && !NewRecordFlag && pPlayCar->GetVel() <= 0.0f && pPlayGoalSignal->GetExRate() >= 1.0 ){
		cTimeRecord TimeRec;
		if( TimeRec.ComparisonTime( m_CourseNum, pPlayManager->m_pTimer->GetNewTime() ) ){
			TimeRec.WriteFile();
			pPlayNewRecord->SetIsDraw( TRUE );
			NewRecordFlag = TRUE;
		}else{
			pPlayPushButton->SetIsDraw( TRUE );
			PushButtonFlag = TRUE;
		}
	}


	//マシンを止める。
	pPlayCar->Acceleration( pPlayCar->AccelOff );
	pPlayCar->Deceleration( pPlayCar->BrakeOn );

	// 更新
	Updata();
}

//-------------------------------------------------------------------
// 終了処理
//-------------------------------------------------------------------
void cPlayScene::End()
{
	if( select_ != Select_Exit && !FadeOut() ) return;
	
	Device->Sound.StopSE(6);

	pPlayCourse->SetIsExit(TRUE);
	pPlayCar->SetIsExit(TRUE);
	pPlayManager->SetIsExit(TRUE);
	for( int i=0; i<4; i++ )
		pPlaySignal[i]->SetIsExit(TRUE);
	pPlayGoalSignal->SetIsExit(TRUE);
	pPlaySpeedoMeter->SetIsExit(TRUE);
	pPlaySpeedoMeterNeedle->SetIsExit(TRUE);
	pPlayNewRecord->SetIsExit(TRUE);
	pPlayPushButton->SetIsExit(TRUE);
	pPlayCursor->SetIsExit(TRUE);
	pPlaySelect->SetIsExit(TRUE);
	Device->Draw.Remove();
	SAFE_DELETE( pPlayCourse );
	SAFE_DELETE( pPlayCourseMask );
	SAFE_DELETE( pPlayCar );
	SAFE_DELETE( pPlayManager );
	for( int i=0; i<4; i++ )
		SAFE_DELETE( pPlaySignal[i] );
	SAFE_DELETE( pPlayGoalSignal );
	SAFE_DELETE( pPlaySpeedoMeter );
	SAFE_DELETE( pPlaySpeedoMeterNeedle );
	SAFE_DELETE( pPlayNewRecord );
	SAFE_DELETE( pPlayPushButton );
	SAFE_DELETE( pPlayCursor );
	SAFE_DELETE( pPlaySelect );

	Device->Sound.StopBGM();

	MyOutputDebugString( _T("プレイシーン：終了\n\n") );
	stateResult_ = StateResult_Finish;
	stateFunc_.setFunc( &cPlayScene::Init );
}