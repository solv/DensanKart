//ヘッダーファイル読み込み
#include "cTitleScene.h"
#include "../../CharctorClass/cCharctor.h"
#include "../../CharctorClass/Scene/TitleScene/cTitleSceneCharctor.h"
#include "../../CharctorClass/Scene/cCursorCharctor.h"
#include "../../_Debug/dComon.h"
#include "../../_Debug/dDebug.h"

#include "../../CharctorClass/Scene/PlayScene/cStageManager.h"

namespace{
	const int FadeOutMaxCount	= 30;
	const int FadeInMaxCount	= 30;
	static int FadeInCount		= 0;
	static int FadeOutCount		= FadeOutMaxCount;
}

cCharctor* pTitleBackGround;
cCursorCharctor* pTitleCursor;
cConfigCharctor* pTitleKeyConfigString;

//-------------------------------------------------------------------
// 初期化
//-------------------------------------------------------------------
void cTitleScene::Init()
{
	MyOutputDebugString( _T("タイトルシーン：初期化\n") );
	select_ = Select_None;
	stateResult_ = StateResult_Continue;
	stateFunc_.setFunc( &cTitleScene::Idle );

	pTitleBackGround = NEW cCharctor( _T("Data/Image/Back/TitleBackGround.img") );
	pTitleCursor	 = NEW cCursorCharctor( _T("Data/Image/Parts/TitleCursor.img"), 3, 0, 72 );
	pTitleCursor->m_spPosInfo->SetPos( 212.0f, 215.0f, 0.0f );
	pTitleCursor->SetFirstPos();
	Device->Draw.Append( pTitleBackGround );
	Device->Draw.Append( pTitleCursor );

	pTitleKeyConfigString = NEW cConfigCharctor;
	pTitleKeyConfigString->m_spPosInfo->SetPos( 190.0f, 255.0f, 0.0f );
	pTitleKeyConfigString->SetIsDraw(FALSE);
	Device->Draw.Append( pTitleKeyConfigString );

	Device->Sound.LoadBGM( _T("Data/Sound/Title.bgm") );
	Device->Sound.PlayBGM();

	FadeInCount = 0;
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
void cTitleScene::Idle()
{
	if( !FadeIn() ) return;

	if( InputButton(Up) == 1 ){
		Device->Sound.PlaySE(0);
		pTitleCursor->Up();
	}
	if( InputButton(Down) == 1 ){
		Device->Sound.PlaySE(0);
		pTitleCursor->Down();
	}

	if( InputButton(Button1) == 1 ){
		switch( pTitleCursor->GetSelectID() ){
			case Select_GoSelect:
				Device->Sound.PlaySE(2);
				select_ = Select_GoSelect;
				stateFunc_.setFunc( &cTitleScene::End );
				MyOutputDebugString( _T("タイトルシーン：アイドル終了\nセレクトシーンへ移行します\n") );
				break;

			case Select_Config:
				pTitleKeyConfigString->SetIsDraw(TRUE);
				select_ = Select_Config;
				stateFunc_.setFunc( &cTitleScene::KeyConfig );
				MyOutputDebugString( _T("タイトルシーン：キーコンフィグを起動します。\n") );
				break;

			case Select_Exit:
				select_ = Select_Exit;
				stateFunc_.setFunc( &cTitleScene::End );
				MyOutputDebugString( _T("タイトルシーン：アイドル終了\nアプリケーションを終了します\n") );
				break;
		}
	}

	pTitleCursor->Updata();

	if( DxLib::GetWindowUserCloseFlag( TRUE ) && (MessageBox( DxLib::GetMainWindowHandle(),WindowText, WindowTitleText, MB_YESNO|MB_ICONQUESTION ) == IDYES) ){
		select_ = Select_Exit;
		stateFunc_.setFunc( &cTitleScene::End );
	}
}

//-------------------------------------------------------------------
// キーコンフィグ中
//-------------------------------------------------------------------
void cTitleScene::KeyConfig()
{
	int PushedKeyNumber = 0;	// 現在押されたキー番号
	static int NowKeyNum = 0;	// 設定するキー番号
	
	if( NowKeyNum >= Device->Pad.VIRTUAL_MAX_BUTTON ){
		NowKeyNum = 0;
		pTitleKeyConfigString->SetIsDraw(FALSE);
		select_ = Select_None;
		stateFunc_.setFunc( &cTitleScene::Idle );
		MyOutputDebugString( _T("タイトルシーン：アイドルに移行します。\n") );
	}
	else if( (PushedKeyNumber = Device->Pad.PushedButton()) != 0 ){
		MyOutputDebugString( _T("%d,%d\n"),PushedKeyNumber,NowKeyNum );
		Device->Pad.SetConfig( PushedKeyNumber, NowKeyNum );
		++NowKeyNum;
		pTitleKeyConfigString->Updata();
	}

	if( DxLib::GetWindowUserCloseFlag( TRUE ) && (MessageBox( DxLib::GetMainWindowHandle(),WindowText, WindowTitleText, MB_YESNO|MB_ICONQUESTION ) == IDYES) ){
		select_ = Select_Exit;
		stateFunc_.setFunc( &cTitleScene::End );
	}
}

//-------------------------------------------------------------------
// 終了処理
//-------------------------------------------------------------------
void cTitleScene::End()
{
	if( select_ != Select_Exit  && !FadeOut() ) return;
	
	pTitleBackGround->SetIsExit(TRUE);
	pTitleCursor->SetIsExit(TRUE);
	pTitleKeyConfigString->SetIsExit(TRUE);
	Device->Draw.Remove();
	SAFE_DELETE( pTitleBackGround );
	SAFE_DELETE( pTitleCursor );
	SAFE_DELETE( pTitleKeyConfigString );
	
	Device->Sound.StopBGM();

	MyOutputDebugString( _T("タイトルシーン：終了\n\n") );
	stateResult_ = StateResult_Finish;
	stateFunc_.setFunc( &cTitleScene::Init );

	DxLib::SetDrawBright( 255, 255, 255 );
}