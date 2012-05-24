//�w�b�_�[�t�@�C���ǂݍ���
#include "DxLib.h"
#include "cSoundManager.h"

//-------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------
cSoundManager::cSoundManager(){
}

//-------------------------------------------------------------------
// SE�̓ǂݍ���
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
// BGM�̓ǂݍ���
//-------------------------------------------------------------------
void cSoundManager::LoadBGM( LPCTSTR BGMName, int LoopTime )
{
	DxLib::SetCreateSoundDataType( DX_SOUNDDATATYPE_FILE );
	this->m_BGM = DxLib::LoadSoundMem( BGMName );
	DxLib::SetLoopPosSoundMem( LoopTime, this->m_BGM );
}

//-------------------------------------------------------------------
// �G���W�����̍Đ�
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
// SE�̍Đ�
//-------------------------------------------------------------------
void cSoundManager::PlaySE( int PlaySE_Num )
{
	m_VectorIsPlay[PlaySE_Num] = TRUE;
}

//-------------------------------------------------------------------
// BGM�̍Đ�
//-------------------------------------------------------------------
void cSoundManager::PlayBGM()
{
	DxLib::PlaySoundMem( this->m_BGM, DX_PLAYTYPE_LOOP );
}

//-------------------------------------------------------------------
// SE�̒�~
//-------------------------------------------------------------------
void cSoundManager::StopSE( int PlaySE_Num )
{
	int a = DxLib::StopSoundMem( this->m_VectorSE[PlaySE_Num] );
}

//-------------------------------------------------------------------
// BGM�̒�~
//-------------------------------------------------------------------
void cSoundManager::StopBGM()
{
	DxLib::StopSoundMem( this->m_BGM );
}

//-------------------------------------------------------------------
// �폜
//-------------------------------------------------------------------
HRESULT cSoundManager::Remove()
{
	DxLib::DeleteSoundMem( this->m_BGM );
	return( S_OK );
}