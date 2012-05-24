//ヘッダーファイル読み込み
#include "cCursorCharctor.h"
#include "DxLib.h"

namespace{
	static int FirstCursorX;
	static int FirstCursorY;
}

//-------------------------------------------------------------------
// 画像の描画
//-------------------------------------------------------------------
void cCursorCharctor::Draw()
{
	if( m_DisplayFlag ){
		DxLib::DrawGraphF( m_spPosInfo->GetPosX(), m_spPosInfo->GetPosY(), GetImage(), TRUE );
	}
}

//-------------------------------------------------------------------
// 更新
//-------------------------------------------------------------------
void cCursorCharctor::Updata()
{
	m_DisplayCount++;
	if( !(m_DisplayCount % m_CursorTurnNum ) ){
		m_DisplayFlag = !m_DisplayFlag;
		m_DisplayCount = 0;
	}
}

//-------------------------------------------------------------------
// カーソルの移動
//-------------------------------------------------------------------
void cCursorCharctor::Move()
{
	D3DXVECTOR3 Pos;
	m_spPosInfo->GetPos( &Pos );

	this->m_spPosInfo->SetPosY( FirstCursorY + (this->m_CursorMoveY  * this->m_SelectNum) );
}

//-------------------------------------------------------------------
// 上に移動
//-------------------------------------------------------------------
void cCursorCharctor::Up()
{
	m_SelectNum--;
	if( m_SelectNum < 0 )	m_SelectNum = m_MaxSelectNum - 1;

	this->Move();
}

//-------------------------------------------------------------------
// 下に移動
//-------------------------------------------------------------------
void cCursorCharctor::Down()
{
	m_SelectNum++;
	if( m_MaxSelectNum <= m_SelectNum )	m_SelectNum = 0;

	this->Move();
}

//-------------------------------------------------------------------
// 初期位置の設定
//-------------------------------------------------------------------
void cCursorCharctor::SetFirstPos()
{
	 FirstCursorX = (int)this->m_spPosInfo->GetPosX();
	 FirstCursorY = (int)this->m_spPosInfo->GetPosY();
}