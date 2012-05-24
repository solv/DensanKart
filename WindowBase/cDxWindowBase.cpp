//ヘッダーファイル読み込み
#include "cDxWindowBase.h"
#include "DxLib.h"

namespace{
	BOOL WindowScreenMode = TRUE;
	const LPTSTR  MessageBoxText	= _T("ウインドウモードで起動しますか？");
	const int	  WindowWidth		= 640;
	const int	  WindowHeight		= 480;
	const int	  WindowColorBit	= 16;
}

//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
cDxWindowBase::cDxWindowBase():m_isEnd(TRUE)
{
	MyOutputDebugString( _T("\nDXライブラリ初期化開始\n\n") );

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
		MyOutputDebugString( _T("\nDXライブラリ初期化失敗\n\n") )
	}
	else
	{
		DxLib::SetDrawScreen( DX_SCREEN_BACK );
		MyOutputDebugString( _T("\nDXライブラリ初期化完了\n\n") )
	}

	//シーンベースクラス生成
	gameScene = NEW cGameSceneBase( &deviceBase );

	//効果音読み込み
	deviceBase.Sound.LoadSE();
}

//-------------------------------------------------------------------
// デストラクタ
//-------------------------------------------------------------------
cDxWindowBase::~cDxWindowBase()
{
	SAFE_DELETE( gameScene );
	DxLib::DxLib_End();
	MyOutputDebugString( _T("アプリケーション終了処理完了\n") );
}

//-------------------------------------------------------------------
// ゲームループ
//-------------------------------------------------------------------
bool cDxWindowBase::Run()
{
	while( !DxLib::ProcessMessage() && m_isEnd )
	{
		//裏画面の消去
		DxLib::ClearDrawScreen();
		//入力
		deviceBase.Pad.Update();
		//更新
		if( !cGameSceneBase::StateResult_Continue == gameScene->Update() )	this->m_isEnd = FALSE;
		//描写
		deviceBase.Draw.Draw();
		//音
		deviceBase.Sound.Play();
		//裏画面の表示
		DxLib::ScreenFlip();
	}

	return TRUE;
}