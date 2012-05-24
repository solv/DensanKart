//--------------------------------------------------------------
//�f�o�C�X�N���X
//-------------------------------------------------------------

//��d�C���N���[�h�h�~
#pragma once

//�w�b�_�[�t�@�C���̓ǂݍ���
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