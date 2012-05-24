//--------------------------------------------------------------
//タイトルシーンキャラクタクラス
//-------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイルの読み込み
#include "../../cCharctor.h"

//-------------------------------------------------------------------
// コンフィグ時のキャラクタークラス
//-------------------------------------------------------------------
class cConfigCharctor : public cCharctor
{
private:
	int m_StringColor[2];
	int m_KeyNum;
	TCHAR m_PushKeyString[7][64];

public:
	cConfigCharctor();
	virtual ~cConfigCharctor();

	virtual void Draw();
	virtual void Updata();
};