//-------------------------------------------------------------
//�T�E���h�Ǘ��N���X
//-------------------------------------------------------------

//��d�C���N���[�h�h�~
#pragma once

//�w�b�_�[�t�@�C���Ǎ�
#include <vector>

typedef int Sound;

class cSoundManager
{
private:
	Sound m_BGM;
	std::vector<bool> m_VectorIsPlay;
	std::vector<Sound> m_VectorSE;

public:
	cSoundManager();
	virtual ~cSoundManager(){}

	// �ǂݍ���
	void LoadSE();
	void LoadBGM( LPCTSTR BGMName, int LoopPoint = 0 );
	
	// �Đ��ƒ�~
	void PlayBGM();
	void StopBGM();
	void StopSE( int PlaySE_Num );
	void PlaySE( int PlaySE_Num );

	void Play();

	// �폜
	HRESULT Remove();
};