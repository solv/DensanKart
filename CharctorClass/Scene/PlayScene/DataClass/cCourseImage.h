//--------------------------------------------------------------
//コースイメージ作成クラス
//-------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイル読込
#include "cCourseFile.h"
#include "../../../../_Debug/dComon.h"

class cCourseImage : public cCourseFile
{
private:
	Image m_CourseImage;

public:
	cCourseImage();
	virtual ~cCourseImage();

	bool CreateCourseImageFace();
	bool CreateCourseImageMask();

	Image GetImage(){ return this->m_CourseImage; }
};