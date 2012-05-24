//-------------------------------------------------------------
//描写基底クラス
//-------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイル読込
#include "DxLib.h"

typedef int Image;

class iDrawObjectBase
{
protected:
	bool m_isDraw;
	bool m_isExit;
	Image m_Image;

public:
	//文字列からとイメージから読み込む2種類
	iDrawObjectBase():m_isDraw(TRUE),m_isExit(FALSE),m_Image(0){}
	iDrawObjectBase( LPCTSTR ImageName ):m_isDraw(TRUE),m_isExit(FALSE){
		LoadImage( ImageName );
	}
	iDrawObjectBase( Image inImage ):m_isDraw(TRUE),m_isExit(FALSE){
		LoadImage( inImage );
	}
	virtual ~iDrawObjectBase(){}

	HRESULT LoadImage( Image inImage ){
		m_Image = inImage;
		return( S_OK );
	}
	HRESULT LoadImage( LPCTSTR ImageName ){
		if( (m_Image = DxLib::LoadGraph( ImageName )) == -1 )
			return( E_FAIL );
		return( S_OK );
	}

	inline bool GetIsDraw(){ return m_isDraw; }
	inline bool GetIsExit(){ return m_isExit; }
	inline void SetIsDraw( bool flag ){ m_isDraw = flag; }
	inline void SetIsExit( bool flag ){ m_isExit = flag; }

	inline Image GetImage(){ return m_Image; }
	virtual void Draw() = 0;
};