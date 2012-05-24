//-------------------------------------------------------------
//�`�ʊ��N���X
//-------------------------------------------------------------

//��d�C���N���[�h�h�~
#pragma once

//�w�b�_�[�t�@�C���Ǎ�
#include "DxLib.h"

typedef int Image;

class iDrawObjectBase
{
protected:
	bool m_isDraw;
	bool m_isExit;
	Image m_Image;

public:
	//�����񂩂�ƃC���[�W����ǂݍ���2���
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