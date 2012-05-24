//ヘッダーファイル読み込み
#include "cTitleSceneCharctor.h"

#include "../../../_Debug/dDebug.h"
#include "../../../_Debug/dComon.h"

static const int WidthLength = 270;
static const int HeightLength = 100;

//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
cConfigCharctor::cConfigCharctor(){
	TCHAR* KeyName[] = { _T("Down"), _T("Left"), _T("Right"), _T("Up"), _T("Button1"), _T("Button2"), _T("Button3") };
	for( int i=0; i<7; ++i ){
		_stprintf_s( m_PushKeyString[i], 64, _T("Pushed Key - %s\0"), KeyName[i] );
	}

	this->m_KeyNum = 0;

	this->m_StringColor[0] = DxLib::GetColor( 0, 0, 128 );
	this->m_StringColor[1] = DxLib::GetColor( 255, 255, 255 );

	DxLib::SetFontSize(22);
}

//-------------------------------------------------------------------
// デストラクタ
//-------------------------------------------------------------------
cConfigCharctor::~cConfigCharctor(){
}

//-------------------------------------------------------------------
// 更新処理
//-------------------------------------------------------------------
void cConfigCharctor::Updata(){
	this->m_KeyNum >= 6 ? this->m_KeyNum = 0 : ++this->m_KeyNum;
}

//-------------------------------------------------------------------
// 描画
//-------------------------------------------------------------------
void cConfigCharctor::Draw(){
	DxLib::DrawBox( this->m_spPosInfo->GetPosX(), this->m_spPosInfo->GetPosY(),
					this->m_spPosInfo->GetPosX()+WidthLength, this->m_spPosInfo->GetPosY()+HeightLength,
					this->m_StringColor[0], TRUE
				);
	DxLib::DrawBox( this->m_spPosInfo->GetPosX(), this->m_spPosInfo->GetPosY(),
					this->m_spPosInfo->GetPosX()+WidthLength, this->m_spPosInfo->GetPosY()+HeightLength,
					this->m_StringColor[1], FALSE
				);
	DxLib::DrawFormatString( this->m_spPosInfo->GetPosX()+70, this->m_spPosInfo->GetPosY()+10,
							 this->m_StringColor[1], _T("Key Config")
							);
 	DxLib::DrawFormatString( this->m_spPosInfo->GetPosX()+20, this->m_spPosInfo->GetPosY()+60,
							 this->m_StringColor[1], this->m_PushKeyString[this->m_KeyNum]
							);
}