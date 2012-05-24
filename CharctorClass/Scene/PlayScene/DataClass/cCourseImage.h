//--------------------------------------------------------------
//�R�[�X�C���[�W�쐬�N���X
//-------------------------------------------------------------

//��d�C���N���[�h�h�~
#pragma once

//�w�b�_�[�t�@�C���Ǎ�
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