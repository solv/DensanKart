//-------------------------------------------------------------
//サウンド管理クラス
//-------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイル読込
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

	// 読み込み
	void LoadSE();
	void LoadBGM( LPCTSTR BGMName, int LoopPoint = 0 );
	
	// 再生と停止
	void PlayBGM();
	void StopBGM();
	void StopSE( int PlaySE_Num );
	void PlaySE( int PlaySE_Num );

	void Play();

	// 削除
	HRESULT Remove();
};