//ヘッダーファイル読み込み
#include "cGameSceneBase.h"

//-------------------------------------------------------------------
// 更新
//-------------------------------------------------------------------
iSceneBase::StateResult cGameSceneBase::Update()
{
	stateFunc_.exec( this );
	return stateResult_;
}

//-------------------------------------------------------------------
// タイトルシーン
//-------------------------------------------------------------------
void cGameSceneBase::Title()
{
	if( titleScene_.Update() == StateResult_Finish ){
		switch( titleScene_.getSelectResult() ){
			case cTitleScene::Select_GoSelect:
				stateFunc_.setFunc( &cGameSceneBase::Select );
				break;

			case cTitleScene::Select_Exit:
				stateFunc_.setFunc( &cGameSceneBase::Title );
				stateResult_ = StateResult_Finish;
				break;
		}
	}
}

//-------------------------------------------------------------------
// セレクトシーン
//-------------------------------------------------------------------
void cGameSceneBase::Select()
{
	if( selectScene_.Update() == StateResult_Finish ){
		switch( selectScene_.getSelectResult() ){
			case cSelectScene::Select_GoPlaying:
				stateFunc_.setFunc( &cGameSceneBase::Playing );			
				break;

			case cSelectScene::Select_GoTitle:
				stateFunc_.setFunc( &cGameSceneBase::Title );
				break;

			case cSelectScene::Select_Exit:
				stateFunc_.setFunc( &cGameSceneBase::Title );
				stateResult_ = StateResult_Finish;
				break;
		}
	}
}

//-------------------------------------------------------------------
// プレイシーン
//-------------------------------------------------------------------
void cGameSceneBase::Playing()
{
	playScene_.SetCourseNumber( selectScene_.GetCourseNumber() );
	playScene_.SetCarNumber( selectScene_.GetCarNumber() );

	if( playScene_.Update() == StateResult_Finish ){
		switch( playScene_.getSelectResult() ){
			case cPlayScene::Select_GoSelect:
				stateFunc_.setFunc( &cGameSceneBase::Select );
				break;

			case cPlayScene::Select_GoTitle:
				stateFunc_.setFunc( &cGameSceneBase::Title );
				break;

			case cPlayScene::Select_Exit:
				stateFunc_.setFunc( &cGameSceneBase::Title );
				stateResult_ = StateResult_Finish;
				break;

			case cPlayScene::Select_GoPlaying:
				stateFunc_.setFunc( &cGameSceneBase::Playing );
				break;
		}
	}
}