//�w�b�_�[�t�@�C���ǂݍ���
#include "cDxWindowBase.h"
#include "DxLib.h"

namespace{
	BOOL WindowScreenMode = TRUE;
	const LPTSTR  MessageBoxText	= _T("�E�C���h�E���[�h�ŋN�����܂����H");
	const int	  WindowWidth		= 640;
	const int	  WindowHeight		= 480;
	const int	  WindowColorBit	= 16;
}

//-------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------
cDxWindowBase::cDxWindowBase():m_isEnd(TRUE)
{
	MyOutputDebugString( _T("\nDX���C�u�����������J�n\n\n") );

	if( MessageBox( DxLib::GetMainWindowHandle(), MessageBoxText, WindowTitleText, MB_YESNO | MB_ICONQUESTION ) == IDNO )
		WindowScreenMode = FALSE;

	DxLib::ChangeWindowMode( WindowScreenMode );
	DxLib::SetGraphMode( WindowWidth, WindowHeight, WindowColorBit );
	DxLib::SetMainWindowText( WindowTitleText );
	DxLib::SetOutApplicationLogValidFlag( FALSE );
	DxLib::SetWindowUserCloseEnableFlag( FALSE );

	if(  DxLib::DxLib_Init() == -1 )
	{
		this->m_isEnd = FALSE;
		MyOutputDebugString( _T("\nDX���C�u�������������s\n\n") )
	}
	else
	{
		DxLib::SetDrawScreen( DX_SCREEN_BACK );
		MyOutputDebugString( _T("\nDX���C�u��������������\n\n") )
	}

	//�V�[���x�[�X�N���X����
	gameScene = NEW cGameSceneBase( &deviceBase );

	//���ʉ��ǂݍ���
	deviceBase.Sound.LoadSE();
}

//-------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------
cDxWindowBase::~cDxWindowBase()
{
	SAFE_DELETE( gameScene );
	DxLib::DxLib_End();
	MyOutputDebugString( _T("�A�v���P�[�V�����I����������\n") );
}

//-------------------------------------------------------------------
// �Q�[�����[�v
//-------------------------------------------------------------------
bool cDxWindowBase::Run()
{
	while( !DxLib::ProcessMessage() && m_isEnd )
	{
		//����ʂ̏���
		DxLib::ClearDrawScreen();
		//����
		deviceBase.Pad.Update();
		//�X�V
		if( !cGameSceneBase::StateResult_Continue == gameScene->Update() )	this->m_isEnd = FALSE;
		//�`��
		deviceBase.Draw.Draw();
		//��
		deviceBase.Sound.Play();
		//����ʂ̕\��
		DxLib::ScreenFlip();
	}

	return TRUE;
}