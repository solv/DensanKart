//--------------------------------------------------------------
//マシン・コースセレクトシーンクラス
//-------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイル読込
#include "../iFuncSetter.h"
#include "../iSceneBase.h"
#include "../../WindowBase/DeviceBase/cDeviceBase.h"

class cSelectScene : public iSceneBase
{
public:
	int SelectNum;
	cDeviceBase* Device;

	enum Select{
		Select_None,
		Select_GoPlaying,
		Select_GoTitle,
		Select_Exit,
	};

private:
	Dix::FuncSetter<cSelectScene> stateFunc_;
	StateResult stateResult_;
	Select select_;

	int m_CourseNum;
	int m_CarNum;

	void Init();
	void Idle();
	void End();

public:
	cSelectScene():stateResult_( StateResult_Continue ){
		stateFunc_.setFunc( &cSelectScene::Init );
	}

	virtual ~cSelectScene(){}

	//更新
	virtual StateResult Update(){
		stateFunc_.exec( this );
		return stateResult_;
	}

	//タイトルの選択結果取得
	Select getSelectResult(){ return select_; }

	//コース番号の取得
	int GetCourseNumber();
	//マシン番号の取得
	int GetCarNumber();
};