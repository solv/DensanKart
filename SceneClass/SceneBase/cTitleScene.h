//--------------------------------------------------------------
//タイトルシーンクラス
//-------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイル読込
#include "../iFuncSetter.h"
#include "../iSceneBase.h"
#include "../../WindowBase/DeviceBase/cDeviceBase.h"

class cTitleScene : public iSceneBase
{
public:
	cDeviceBase* Device;

	enum Select{
		Select_GoSelect,
		Select_Config,
		Select_Exit,
		Select_None,
	};

private:
	Dix::FuncSetter<cTitleScene> stateFunc_;
	StateResult stateResult_;
	Select select_;

	void Init();
	void Idle();
	void KeyConfig();
	void End();

public:
	cTitleScene():stateResult_( StateResult_Continue ),select_( Select_None ){
		stateFunc_.setFunc( &cTitleScene::Init );
	}

	virtual ~cTitleScene(){}

	//更新
	virtual StateResult Update(){
		stateFunc_.exec( this );
		return stateResult_;
	}

	//タイトルの選択結果取得
	Select getSelectResult(){ return select_; }
};