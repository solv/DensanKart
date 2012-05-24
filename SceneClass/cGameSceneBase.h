//--------------------------------------------------------------
//ゲームシーンベースクラス
//-------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイル読込
#include <windows.h>
#include "iSceneBase.h"
#include "iFuncSetter.h"
#include "../WindowBase/DeviceBase/cDeviceBase.h"
#include "SceneBase/cTitleScene.h"
#include "SceneBase/cSelectScene.h"
#include "SceneBase/cPlayScene.h"

class cGameSceneBase : public iSceneBase
{
private:
	Dix::FuncSetter<cGameSceneBase> stateFunc_;	//実行ステート
	StateResult stateResult_;					//状態の結果

	//各種シーン
	cTitleScene		titleScene_;
	cSelectScene	selectScene_;
	cPlayScene		playScene_;

public:
	cGameSceneBase( cDeviceBase* dev ):stateResult_( StateResult_Continue ){
		titleScene_.Device	 = dev;
		selectScene_.Device  = dev;
		playScene_.Device    = dev;
		stateFunc_.setFunc( &cGameSceneBase::Title );
	}
	virtual ~cGameSceneBase(){}

	//更新
	virtual StateResult Update();

	//ステートメソッド
	void Title();	//タイトル
	void Select();	//マシン・コース選択
	void Playing();	//プレイ中
};