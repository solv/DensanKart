//--------------------------------------------------------------
//プレイシーンクラス
//-------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイル読込
#include "../iFuncSetter.h"
#include "../iSceneBase.h"
#include "../../WindowBase/DeviceBase/cDeviceBase.h"

class cPlayScene : public iSceneBase
{
public:
	cDeviceBase* Device;

	enum Select{
		Select_None,
		Select_GoSelect,
		Select_GoTitle,
		Select_Exit,
		Select_GoPlaying,
	};

private:
	Dix::FuncSetter<cPlayScene> stateFunc_;
	StateResult stateResult_;
	Select select_;

	int m_CourseNum;
	int m_CarNum;

	void Init();
	void Start();
	void Idle();
	void PlayEnd();
	void End();
	
public:
	cPlayScene():stateResult_( StateResult_Continue ){
		stateFunc_.setFunc( &cPlayScene::Init );
	}

	virtual ~cPlayScene(){}

	//更新
	virtual StateResult Update(){
		stateFunc_.exec( this );
		return stateResult_;
	}

	//タイトルの選択結果取得
	Select getSelectResult(){ return select_; }

	//コース番号をセット
	void SetCourseNumber( int num ){ m_CourseNum = num; }
	//マシン番号をセット
	void SetCarNumber( int num ){ m_CarNum = num; }
};