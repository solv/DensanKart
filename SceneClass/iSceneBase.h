//--------------------------------------------------------------
//シーンベースクラス
//-------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイル読込

//状態遷移基本クラス
class iSceneBase
{
public:
	enum StateResult{
		StateResult_Finish,		// 状態終了
		StateResult_Continue	// 状態継続中
	};

public:
	iSceneBase(){}
	virtual ~iSceneBase(){}

	//更新
	virtual StateResult Update() = 0;
};