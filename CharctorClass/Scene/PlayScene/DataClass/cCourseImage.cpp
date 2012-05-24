//ヘッダーファイル読み込み
#include "DxLib.h"
#include "cCourseImage.h"
#include "../../../../_Debug/dDebug.h"

const int CHIP_WIDTH  = 4;
const int CHIP_HEIGHT = 25;
const int CHIP_SIZE	  = 32;

//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
cCourseImage::cCourseImage(){
}

//-------------------------------------------------------------------
// デストラクタ
//-------------------------------------------------------------------
cCourseImage::~cCourseImage(){
}

//-------------------------------------------------------------------
// 表画像のコース画像生成
//-------------------------------------------------------------------
bool cCourseImage::CreateCourseImageFace()
{
	Image bufCourseChipImageFace	= DxLib::LoadSoftImage( this->m_ImageFileName[Face] );
	Image bufCourseImageFace		= DxLib::MakeXRGB8ColorSoftImage( m_Width*CHIP_SIZE, m_Height*CHIP_SIZE );
	MyOutputDebugString( _T("コースフェイスイメージ作成開始\n") );

	//コース画像の作成
	for(int height=0; height<m_Height; height++){
		for(int width=0; width<m_Width; width++){
			//表示用画像の転送
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

	MyOutputDebugString( _T("コースフェイスイメージ作成完了\n") );

	return TRUE;
}

//-------------------------------------------------------------------
// 裏画像のコースイメージ生成
//-------------------------------------------------------------------
bool cCourseImage::CreateCourseImageMask()
{
	Image bufCourseChipImageMask	= DxLib::LoadSoftImage( this->m_ImageFileName[Mask] );
	Image bufCourseImageMask		= DxLib::MakeXRGB8ColorSoftImage( m_Width*CHIP_SIZE, m_Height*CHIP_SIZE );
	Image bufCourseGoalCheckPointMask = DxLib::LoadSoftImage( _T("Data/Image/Course/GoalWallCheckPoint.img") );
	
	MyOutputDebugString( _T("コースマスクイメージ作成開始\n") );

	//コース画像の作成
	for(int height=0; height<m_Height; height++){
		for(int width=0; width<m_Width; width++){
			//当たり判定用画像の転送
			DxLib::BltSoftImage( (m_CourseData[(height*m_Width)+width] % CHIP_WIDTH) * CHIP_SIZE,
								 (m_CourseData[(height*m_Width)+width] / CHIP_WIDTH) * CHIP_SIZE,				 
								 CHIP_SIZE, CHIP_SIZE, bufCourseChipImageMask,
								 width * CHIP_SIZE, height*CHIP_SIZE, bufCourseImageMask
							    );
		}
	}
	
	//チェックポイントのところ壁判定の作成。
	for( int i=0; i<4; i++ ){
		DxLib::BltSoftImage( m_CourseGoalCheckPoint[i] * CHIP_SIZE, 0, CHIP_SIZE, CHIP_SIZE, bufCourseGoalCheckPointMask,
							 m_CourseGoalCheckPoint[i+4] * CHIP_SIZE, m_CourseGoalCheckPoint[i+8] * CHIP_SIZE,
							 bufCourseImageMask
							);
	}
	
	this->m_CourseImage = bufCourseImageMask;
	DxLib::DeleteSoftImage( bufCourseChipImageMask );
	DxLib::DeleteSoftImage( bufCourseGoalCheckPointMask );

	MyOutputDebugString( _T("コースマスクイメージ作成完了\n") );

	return TRUE;
}