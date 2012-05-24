//--------------------------------------------------------------
//位置情報インターフェースクラス
//--------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイルの読み込み
#include <d3dx9.h>

class iPosInfo
{
protected:
	D3DXVECTOR3 m_Pos;		//位置
	D3DXVECTOR3 m_Direct;	//向き

public:
	iPosInfo(){
		m_Pos.x=0; m_Pos.y=0; m_Pos.z=0;
		m_Direct.x=1; m_Direct.y=0; m_Direct.z=0;
	}

	virtual void SetPos( float x, float y, float z ) = 0;
	virtual void SetPosX( float x ) = 0;
	virtual void SetPosY( float y ) = 0;
	virtual void SetPos( D3DXVECTOR3 *Pos ) = 0;
	virtual float GetPosX() = 0;
	virtual float GetPosY() = 0;
	virtual D3DXVECTOR3& GetPos( D3DXVECTOR3* pPos ) = 0;

	virtual void SetDirect( float dx, float dy, float dz ) = 0;
	virtual void SetDirectX( float dx ) = 0;
	virtual void SetDirectY( float dy ) = 0;
	virtual void SetDirect( D3DXVECTOR3 *Direct ) = 0;
	virtual float GetDirectX() = 0;
	virtual float GetDirectY() = 0;
	virtual D3DXVECTOR3& GetDirect( D3DXVECTOR3* pDirect ) = 0;
};