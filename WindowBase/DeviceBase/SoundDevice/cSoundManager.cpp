//ヘッダーファイル読み込み
#include "DxLib.h"
#include "cSoundManager.h"

//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
cSoundManager::cSoundManager(){
}

//-------------------------------------------------------------------
// SEの読み込み
//-------------------------------------------------------------------
void cSoundManager::LoadSE()
{
	this->m_VectorSE.push_back( DxLib::LoadSoundMem( _T("Data/Sound/Cursor1.se") ) );
	this->m_VectorSE.push_back( DxLib::LoadSoundMem( _T("Data/Sound/Cursor2.se") ) );
	this->m_VectorSE.push_back( DxLib::LoadSoundMem( _T("Data/Sound/CursorEnter1.se") ) );
	this->m_VectorSE.push_back( DxLib::LoadSoundMem( _T("Data/Sound/CursorEnter2.se") ) );
	this->m_VectorSE.push_back( DxLib::LoadSoundMem( _T("Data/Sound/Signal.se") ) );
	this->m_VectorSE.push_back( DxLib::LoadSoundMem( _T("Data/Sound/Idle.se") ) );
	this->m_VectorSE.push_back( DxLib::LoadSoundMem( _T("Data/Sound/Run.se") ) );

	DxLib::SetLoopPosSoundMem( 1000, m_VectorSE[6] );

	for( int i=0; i<(int)m_VectorSE.size(); i++ )
		this->m_VectorIsPlay.push_back( FALSE );
}

//-------------------------------------------------------------------
// BGMの読み込み
//-------------------------------------------------------------------
void cSoundManager::LoadBGM( LPCTSTR BGMName, int LoopTime )
{
	DxLib::SetCreateSoundDataType( DX_SOUNDDATATYPE_FILE );
	this->m_BGM = DxLib::LoadSoundMem( BGMName );
	DxLib::SetLoopPosSoundMem( LoopTime, this->m_BGM );
}

//-------------------------------------------------------------------
// エンジン音の再生
//-------------------------------------------------------------------
void cSoundManager::Play()
{
	std::vector<Sound>::iterator itr = m_VectorSE.begin();
	for(int i=0; itr != m_VectorSE.end(); itr++,i++ ){
		if( m_VectorIsPlay[i] ){
			if( m_VectorIsPlay[6] ){
				DxLib::PlaySoundMem( *itr, DX_PLAYTYPE_LOOP );
			}else{
				DxLib::PlaySoundMem( *itr, DX_PLAYTYPE_BACK );
			}
			m_VectorIsPlay[i] = FALSE;
		}
	}
}

//-------------------------------------------------------------------
// SEの再生
//-------------------------------------------------------------------
void cSoundManager::PlaySE( int PlaySE_Num )
{
	m_VectorIsPlay[PlaySE_Num] = TRUE;
}

//-------------------------------------------------------------------
// BGMの再生
//-------------------------------------------------------------------
void cSoundManager::PlayBGM()
{
	DxLib::PlaySoundMem( this->m_BGM, DX_PLAYTYPE_LOOP );
}

//-------------------------------------------------------------------
// SEの停止
//-------------------------------------------------------------------
void cSoundManager::StopSE( int PlaySE_Num )
{
	int a = DxLib::StopSoundMem( this->m_VectorSE[PlaySE_Num] );
}

//-------------------------------------------------------------------
// BGMの停止
//-------------------------------------------------------------------
void cSoundManager::StopBGM()
{
	DxLib::StopSoundMem( this->m_BGM );
}

//-------------------------------------------------------------------
// 削除
//-------------------------------------------------------------------
HRESULT cSoundManager::Remove()
{
	DxLib::DeleteSoundMem( this->m_BGM );
	return( S_OK );
}