//--------------------------------------------------------------
//位置情報クラス
//-------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイルの読み込み
#include <d3dx9.h>
#include "INterface/iPosinfo.h"

class cPosInfo : public iPosInfo
{
public:
	virtual void SetPos( float x, float y, float z )
	{
		m_Pos.x=x; m_Pos.y=y; m_Pos.z=z;
	}
	virtual void SetPosX( float x ){ m_Pos.x=x;}
	virtual void SetPosY( float y ){ m_Pos.y=y;}
	virtual void SetPosZ( float z ){ m_Pos.z=z;}
	virtual void SetPos( D3DXVECTOR3 *Pos ){ m_Pos=*Pos;}
	virtual D3DXVECTOR3& GetPos( D3DXVECTOR3* pPos )
	{
		*pPos = m_Pos;
		return *pPos;
	}
	virtual float GetPosX(){return m_Pos.x;}
	virtual float GetPosY(){return m_Pos.y;}
	virtual float GetPosZ(){return m_Pos.z;}
	virtual void SetDirect( float dx, float dy, float dz )
	{
		m_Direct.x=dx; m_Direct.y=dy; m_Direct.z=dz;
	}
	virtual void SetDirectX( float dx ){m_Direct.x=dx;}
	virtual void SetDirectY( float dy ){m_Direct.y=dy;}
	virtual void SetDirectZ( float dz ){m_Direct.z=dz;}
	virtual void SetDirect( D3DXVECTOR3 *Direct ){m_Direct=*Direct;}
	virtual D3DXVECTOR3& GetDirect( D3DXVECTOR3* pDirect )
	{
		*pDirect = m_Direct;
		return *pDirect;
	}
	virtual float GetDirectX(){return m_Direct.x;}
	virtual float GetDirectY(){return m_Direct.y;}
	virtual float GetDirectZ(){return m_Direct.z;}
};