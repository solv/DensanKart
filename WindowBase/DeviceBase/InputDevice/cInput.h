//-------------------------------------------------------------
//ゲームパッド、キーボードの入力クラス
//-------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイル読込
#include "DxLib.h"

//定数
const int MAX_BUTTON = 14;

// 全部入力含めたジョイパッド（使い捨て）
class cJoyPad
{
protected:
	char m_KeyInputOnOffBuffer[256];			//キー入力の有無
	int  m_KeyInputLevelBuffer[256];			//キー入力レベル
	int  m_JoyPadInputLevelBuffer[MAX_BUTTON];	//ジョイパッドのキー入力レベル

protected:
	enum GamePad{
		KBack		 = KEY_INPUT_BACK,
		KTab		 = KEY_INPUT_TAB,
		KReturn		 = KEY_INPUT_RETURN,
		KLShift		 = KEY_INPUT_LSHIFT,
		KRShift		 = KEY_INPUT_RSHIFT,
		KLCtrl		 = KEY_INPUT_LCONTROL,
		KRCtrl		 = KEY_INPUT_RCONTROL,
		KEsc		 = KEY_INPUT_ESCAPE,
		KSpace		 = KEY_INPUT_SPACE,
		KPageUp		 = KEY_INPUT_PGUP,
		KPageDown	 = KEY_INPUT_PGDN,
		KEnd		 = KEY_INPUT_END,
		KHome		 = KEY_INPUT_HOME,
		KLeft		 = KEY_INPUT_LEFT,
		KUp			 = KEY_INPUT_UP,
		KRight		 = KEY_INPUT_RIGHT,
		KDown		 = KEY_INPUT_DOWN,
		KInsert	 	 = KEY_INPUT_INSERT,
		KDelete		 = KEY_INPUT_DELETE,
		KMinus		 = KEY_INPUT_MINUS,
		KYen		 = KEY_INPUT_YEN,
		KPrevtrack	 = KEY_INPUT_PREVTRACK,
		KPeriod		 = KEY_INPUT_PERIOD,
		KSlash		 = KEY_INPUT_SLASH,
		KLAlt		 = KEY_INPUT_LALT,
		KRAlt		 = KEY_INPUT_RALT,
		KScroll		 = KEY_INPUT_SCROLL,
		KSemicolon	 = KEY_INPUT_SEMICOLON,
		KColon		 = KEY_INPUT_COLON,
		KLBracket	 = KEY_INPUT_LBRACKET,
		KRBracket	 = KEY_INPUT_RBRACKET,
		KAt			 = KEY_INPUT_AT,
		KBackSlash	 = KEY_INPUT_BACKSLASH,
		KComma		 = KEY_INPUT_COMMA,
		KCapslock	 = KEY_INPUT_CAPSLOCK,
		KPause		 = KEY_INPUT_PAUSE,
		KNumPad0	 = KEY_INPUT_NUMPAD0,
		KNumPad1	 = KEY_INPUT_NUMPAD1,
		KNumPad2	 = KEY_INPUT_NUMPAD2,
		KNumPad3	 = KEY_INPUT_NUMPAD3,
		KNumPad4	 = KEY_INPUT_NUMPAD4,
		KNumPad5	 = KEY_INPUT_NUMPAD5,
		KNumPad6	 = KEY_INPUT_NUMPAD6,
		KNumPad7	 = KEY_INPUT_NUMPAD7,
		KNumPad8	 = KEY_INPUT_NUMPAD8,
		KNumPad9	 = KEY_INPUT_NUMPAD9,
		KMultiply	 = KEY_INPUT_MULTIPLY,
		KAdd		 = KEY_INPUT_ADD,
		KSubtract	 = KEY_INPUT_SUBTRACT,
		KDecimal	 = KEY_INPUT_DECIMAL,
		KDivide		 = KEY_INPUT_DIVIDE,
		KNumPadEnter = KEY_INPUT_NUMPADENTER,
		KF1	 = KEY_INPUT_F1,
		KF2	 = KEY_INPUT_F2,
		KF3	 = KEY_INPUT_F3,
		KF4	 = KEY_INPUT_F4,
		KF5	 = KEY_INPUT_F5,
		KF6	 = KEY_INPUT_F6,
		KF7	 = KEY_INPUT_F7,
		KF8	 = KEY_INPUT_F8,
		KF9	 = KEY_INPUT_F9,
		KF10 = KEY_INPUT_F10,
		KF11 = KEY_INPUT_F11,
		KF12 = KEY_INPUT_F12,
		KA	 = KEY_INPUT_A,
		KB	 = KEY_INPUT_B,
		KC	 = KEY_INPUT_C,
		KD	 = KEY_INPUT_D,
		KE	 = KEY_INPUT_E,
		KF	 = KEY_INPUT_F,
		KG	 = KEY_INPUT_G,
		KH	 = KEY_INPUT_H,
		KI	 = KEY_INPUT_I,
		KJ	 = KEY_INPUT_J,
		KK	 = KEY_INPUT_K,
		KL	 = KEY_INPUT_L,
		KM	 = KEY_INPUT_M,
		KN	 = KEY_INPUT_N,
		KO	 = KEY_INPUT_O,
		KP	 = KEY_INPUT_P,
		KQ	 = KEY_INPUT_Q,
		KR	 = KEY_INPUT_R,
		KS	 = KEY_INPUT_S,
		KT	 = KEY_INPUT_T,
		KU	 = KEY_INPUT_U,
		KV	 = KEY_INPUT_V,
		KW	 = KEY_INPUT_W,
		KX	 = KEY_INPUT_X,
		KY	 = KEY_INPUT_Y,
		KZ	 = KEY_INPUT_Z,
		K0	 = KEY_INPUT_0,
		K1	 = KEY_INPUT_1,
		K2	 = KEY_INPUT_2,
		K3	 = KEY_INPUT_3,
		K4	 = KEY_INPUT_4,
		K5	 = KEY_INPUT_5,
		K6	 = KEY_INPUT_6,
		K7	 = KEY_INPUT_7,
		K8	 = KEY_INPUT_8,
		K9	 = KEY_INPUT_9,
		PDown		= 300,
		PLeft		= 301,
		PRight		= 302,
		PUp			= 303, 
		PButton1	= 304, 
		PButton2	= 305,
		PButton3	= 306, 
		PButton4	= 307, 
		PButton5	= 308,
		PButton6	= 309,
		PButton7	= 310, 
		PButton8	= 311, 
		PButton9	= 312, 
		PButton11	= 313,
	};

public:
	cJoyPad();
	~cJoyPad();

	// 入力状況の更新
	void UpdateJoyPad();
	void UpdateKeyBord();
	void Update();

	// 入力レベル取得
	int Button( int gamePad );
};

//-------------------------------------------------------------------
// キーコンフィグ付きパッド
//-------------------------------------------------------------------
class cVirtualJoyPad : public cJoyPad
{
public:
	const static int VIRTUAL_MAX_BUTTON = 7;

	enum ButtonName{
		Down = 0,
		Left,
		Right,
		Up,
		Button1,
		Button2,
		Button3
	};
	int m_Button[VIRTUAL_MAX_BUTTON];

	cVirtualJoyPad();
	~cVirtualJoyPad();

	// ボタンの変更
	void SetConfig( int PushedKeyNumber,  int NowKeyNum );

	// 入力されたボタンを返す
	int PushedButton();
};