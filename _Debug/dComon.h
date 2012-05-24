//------------------------------------------------------
//
//		マクロ定義などなど
//
//------------------------------------------------------

//二重インクルード防止
#pragma once

//--------------------
//マクロ定義
//--------------------
#define SAFE_DELETE(me)			{ if(me){ delete   (me);	(me) = NULL; } }
#define SAFE_DELETE_ARRAY(me)	{ if(me){ delete[] (me);	(me) = NULL; } }
#define RAD_PI(Radian)			( (Radian) * (3.14159f/180.0f) )

#define	kDEG_TO_RAD			( D3DX_PI * 2.0f / 360.0f)
#define DEG_TO_RAD(d)		( D3DX_PI * (d) / 180.0f )

const int MAX_COURSE = 4;
const int MAX_CAR	= 3;
const float CAR_SCREEN_X = 320.0f;
const float CAR_SCREEN_Y = 240.0f;

#define InputButton(ButtonName) Device->Pad.Button(Device->Pad.m_Button[Device->Pad.ButtonName])

//--------------------
//文字列定義
//--------------------
const LPTSTR WindowTitleText = _T("DensanKart");
const LPTSTR WindowText =  _T("ゲームを終了しますか？");

//--------------------
//型宣言
//--------------------
typedef int Image;

//--------------------
//列挙型
//--------------------
enum{
	Face = 0,
	Mask
};