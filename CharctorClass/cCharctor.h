//--------------------------------------------------------------
//キャラクタクラス
//-------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイルの読み込み
#include "DxLib.h"
#include "Interface/iCharctor.h"
#include "cPosInfo.h"

class cCharctor : public iCharctor
{
public:
	// 何もなし、画像から、画像パスから読み込む
	cCharctor(){
		m_spPosInfo.SetPtr( new cPosInfo );
		m_spPosInfo->SetPos(0,1,0);
	}
	cCharctor( LPCTSTR ImageName ):iCharctor(ImageName){
		m_spPosInfo.SetPtr( new cPosInfo );
		m_spPosInfo->SetPos(0,1,0);
	}
	cCharctor( Image inImage ):iCharctor(inImage){
		m_spPosInfo.SetPtr( new cPosInfo );
		m_spPosInfo->SetPos(0,1,0);
	}

	virtual ~cCharctor(){}

	inline virtual void Draw(){
		DxLib::DrawGraphF( m_spPosInfo->GetPosX(), m_spPosInfo->GetPosY(), GetImage(), FALSE );
	}
	virtual void Move(){}
};