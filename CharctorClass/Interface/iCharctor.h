//--------------------------------------------------------------
//キャラクタインターフェースクラス
//--------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイルの読み込み
#include <d3dx9.h>
#include "../WindowBase/DeviceBase/DrawDevice/iDrawObjectBase.h"
#include "iPosInfo.h"
#include "../_Debug/SmartPtr.h"

typedef sp<iPosInfo> SPIPosInfo;

class iCharctor : public iDrawObjectBase
{
public:
	SPIPosInfo m_spPosInfo; //位置情報

public:
	iCharctor(){}
	iCharctor( LPCTSTR ImageName ):iDrawObjectBase(ImageName){}
	iCharctor( Image inImage ):iDrawObjectBase(inImage){}

	SPIPosInfo GetPosInfo(){ return m_spPosInfo; }
	virtual void Draw() = 0;
	virtual void Move() = 0;
};