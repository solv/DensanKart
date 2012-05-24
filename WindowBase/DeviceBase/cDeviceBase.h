//--------------------------------------------------------------
//デバイスクラス
//-------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイルの読み込み
#include "InputDevice/cInput.h"
#include "DrawDevice/cDrawManager.h"
#include "SoundDevice/cSoundManager.h"

class cDeviceBase
{
public:
	cVirtualJoyPad	Pad;
	cDrawManager	Draw;
	cSoundManager	Sound;
};