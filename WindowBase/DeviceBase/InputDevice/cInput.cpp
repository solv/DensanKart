//�w�b�_�[�t�@�C���ǂݍ���
#include "cInput.h"

#include "../../../_Debug/dDebug.h"
#include "../../../_Debug/dComon.h"

//-------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------
cJoyPad::cJoyPad(){
}

//-------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------
cJoyPad::~cJoyPad(){
}

//-------------------------------------------------------------------
// ���͏󋵂̍X�V
//-------------------------------------------------------------------
void cJoyPad::Update(){
	UpdateJoyPad();
	UpdateKeyBord();
}

//-------------------------------------------------------------------
// ���̓��x���̎擾
//-------------------------------------------------------------------
int cJoyPad::Button( int gamePad ){
	if( gamePad < 300 )
		return this->m_KeyInputLevelBuffer[gamePad];
	else if( gamePad >= 300 )
		return this->m_JoyPadInputLevelBuffer[gamePad-300];

	return 0;
}

//-------------------------------------------------------------------
// �p�b�h�̓��͏󋵂̍X�V
//-------------------------------------------------------------------
void cJoyPad::UpdateJoyPad(){
	int JoyPad[] = { PAD_INPUT_DOWN, PAD_INPUT_LEFT, PAD_INPUT_RIGHT, PAD_INPUT_UP,
					 PAD_INPUT_A,	 PAD_INPUT_B,	 PAD_INPUT_C,	  PAD_INPUT_X,
					 PAD_INPUT_Y,	 PAD_INPUT_Z,	 PAD_INPUT_L,	  PAD_INPUT_R,
					 PAD_INPUT_START,PAD_INPUT_M,
				   };

	//�Ή����ꂽ�p�b�h�̓��͏󋵂𓾂�
	int InputState = DxLib::GetJoypadInputState(DX_INPUT_PAD1);

	//���͂���Ă�������Z�A����Ă��Ȃ����0�ɏ�����
	for( int i=0; i<14; ++i ){
		if( (InputState & JoyPad[i]) != 0 )	this->m_JoyPadInputLevelBuffer[i]++;
		else								this->m_JoyPadInputLevelBuffer[i] = 0;
	}
}
//-------------------------------------------------------------------
// �L�[�{�[�h�̓��͏󋵂̍X�V
//-------------------------------------------------------------------
void cJoyPad::UpdateKeyBord(){
	DxLib::GetHitKeyStateAll( this->m_KeyInputOnOffBuffer );

	for( int i=0; i<256; ++i ){
		if( this->m_KeyInputOnOffBuffer[i] )	this->m_KeyInputLevelBuffer[i]++;
		else									this->m_KeyInputLevelBuffer[i] = 0;
	}
}

//-------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------
cVirtualJoyPad::cVirtualJoyPad(){
	this->m_Button[Down]	= cJoyPad::KDown;
	this->m_Button[Right]	= cJoyPad::KRight;
	this->m_Button[Left]	= cJoyPad::KLeft;
	this->m_Button[Up]		= cJoyPad::KUp;
	this->m_Button[Button1] = cJoyPad::KZ;
	this->m_Button[Button2] = cJoyPad::KX;
	this->m_Button[Button3] = cJoyPad::KEsc;
}

//-------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------
cVirtualJoyPad::~cVirtualJoyPad(){
}

//-------------------------------------------------------------------
// �L�[�̐ݒ�
//-------------------------------------------------------------------
void cVirtualJoyPad::SetConfig( int PushedKeyNumber, int NowKeyNum ){
	this->m_Button[NowKeyNum] = PushedKeyNumber;
}

//-------------------------------------------------------------------
// ���͂��ꂽ�L�[�ԍ���Ԃ�
//-------------------------------------------------------------------
int cVirtualJoyPad::PushedButton(){
	for( int k=0; k<256; ++k )
		if( this->m_KeyInputLevelBuffer[k] == 1 ) return k; 
	for( int j=0; j<14; ++j )
		if( this->m_JoyPadInputLevelBuffer[j] == 1 ) return j+300;

	return 0;
}