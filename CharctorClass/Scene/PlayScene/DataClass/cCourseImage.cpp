//�w�b�_�[�t�@�C���ǂݍ���
#include "DxLib.h"
#include "cCourseImage.h"
#include "../../../../_Debug/dDebug.h"

const int CHIP_WIDTH  = 4;
const int CHIP_HEIGHT = 25;
const int CHIP_SIZE	  = 32;

//-------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------
cCourseImage::cCourseImage(){
}

//-------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------
cCourseImage::~cCourseImage(){
}

//-------------------------------------------------------------------
// �\�摜�̃R�[�X�摜����
//-------------------------------------------------------------------
bool cCourseImage::CreateCourseImageFace()
{
	Image bufCourseChipImageFace	= DxLib::LoadSoftImage( this->m_ImageFileName[Face] );
	Image bufCourseImageFace		= DxLib::MakeXRGB8ColorSoftImage( m_Width*CHIP_SIZE, m_Height*CHIP_SIZE );
	MyOutputDebugString( _T("�R�[�X�t�F�C�X�C���[�W�쐬�J�n\n") );

	//�R�[�X�摜�̍쐬
	for(int height=0; height<m_Height; height++){
		for(int width=0; width<m_Width; width++){
			//�\���p�摜�̓]��
			DxLib::BltSoftImage( (m_CourseData[(height*m_Width)+width] % CHIP_WIDTH) * CHIP_SIZE,
								 (m_CourseData[(height*m_Width)+width] / CHIP_WIDTH) * CHIP_SIZE,				 
								 CHIP_SIZE, CHIP_SIZE, bufCourseChipImageFace,
								 width * CHIP_SIZE, height*CHIP_SIZE, bufCourseImageFace
							    );
		}
	}

	this->m_CourseImage = DxLib::CreateGraphFromSoftImage( bufCourseImageFace );
	DxLib::DeleteSoftImage( bufCourseChipImageFace );
	DxLib::DeleteSoftImage( bufCourseImageFace );

	MyOutputDebugString( _T("�R�[�X�t�F�C�X�C���[�W�쐬����\n") );

	return TRUE;
}

//-------------------------------------------------------------------
// ���摜�̃R�[�X�C���[�W����
//-------------------------------------------------------------------
bool cCourseImage::CreateCourseImageMask()
{
	Image bufCourseChipImageMask	= DxLib::LoadSoftImage( this->m_ImageFileName[Mask] );
	Image bufCourseImageMask		= DxLib::MakeXRGB8ColorSoftImage( m_Width*CHIP_SIZE, m_Height*CHIP_SIZE );
	Image bufCourseGoalCheckPointMask = DxLib::LoadSoftImage( _T("Data/Image/Course/GoalWallCheckPoint.img") );
	
	MyOutputDebugString( _T("�R�[�X�}�X�N�C���[�W�쐬�J�n\n") );

	//�R�[�X�摜�̍쐬
	for(int height=0; height<m_Height; height++){
		for(int width=0; width<m_Width; width++){
			//�����蔻��p�摜�̓]��
			DxLib::BltSoftImage( (m_CourseData[(height*m_Width)+width] % CHIP_WIDTH) * CHIP_SIZE,
								 (m_CourseData[(height*m_Width)+width] / CHIP_WIDTH) * CHIP_SIZE,				 
								 CHIP_SIZE, CHIP_SIZE, bufCourseChipImageMask,
								 width * CHIP_SIZE, height*CHIP_SIZE, bufCourseImageMask
							    );
		}
	}
	
	//�`�F�b�N�|�C���g�̂Ƃ���ǔ���̍쐬�B
	for( int i=0; i<4; i++ ){
		DxLib::BltSoftImage( m_CourseGoalCheckPoint[i] * CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, bufCourseGoalCheckPointMask,
							 m_CourseGoalCheckPoint[i+4] * CHIP_SIZE, m_CourseGoalCheckPoint[i+8] * CHIP_SIZE,
							 bufCourseImageMask
							);
	}
	
	this->m_CourseImage = bufCourseImageMask;
	DxLib::DeleteSoftImage( bufCourseChipImageMask );
	DxLib::DeleteSoftImage( bufCourseGoalCheckPointMask );

	MyOutputDebugString( _T("�R�[�X�}�X�N�C���[�W�쐬����\n") );

	return TRUE;
}