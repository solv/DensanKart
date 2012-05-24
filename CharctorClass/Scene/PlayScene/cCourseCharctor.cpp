//ヘッダーファイル読み込み
#include "cPlaySceneCharctor.h"
#include "../../../_Debug/dComon.h"
#include "../../../_Debug/dDebug.h"

namespace{
	const float CAR_WALL_VEL = 13.0f;

	enum CarHitWall{
		DownWall  = 4,
		RightWall = 3,
		UpWall    = 2,
		LeftWall  = 1,
	};
}

//-------------------------------------------------------------------
//初期化処理
//-------------------------------------------------------------------
cCourseCharctor::cCourseCharctor( LPCTSTR CourseFileName )
{
	//コースイメージの作成
	m_CourseImage = NEW cCourseImage;
	m_CourseImage->LoadCourseFile( CourseFileName );
	m_CourseImage->CreateCourseImageFace();

	m_spPosInfo->SetPos( (float)m_CourseImage->GetFirstPosX(), (float)m_CourseImage->GetFirstPosY(), 0.0f );

	LoadImage( m_CourseImage->GetImage() );
	SAFE_DELETE( m_CourseImage );
}

//-------------------------------------------------------------------
//描画処理
//-------------------------------------------------------------------
void cCourseCharctor::Draw()
{
	DxLib::DrawRotaGraph2F(
		CAR_SCREEN_X, CAR_SCREEN_Y, m_spPosInfo->GetPosX()+CAR_SCREEN_X, m_spPosInfo->GetPosY()+CAR_SCREEN_Y,
		1.0f, (double)m_Yaw, GetImage(), FALSE
	);
}

//-------------------------------------------------------------------
//移動処理
//-------------------------------------------------------------------
void cCourseCharctor::Move( float Vel )
{
	//位置座標取得
	D3DXVECTOR3 Pos;
	m_spPosInfo->GetPos( &Pos );

	//移動処理
	Pos.x -= sinf( m_Yaw ) * Vel;
	Pos.y -= cosf( m_Yaw ) * Vel;

	//位置座標を更新する
	m_spPosInfo->SetPos( &Pos );
}

//-------------------------------------------------------------------
//マシンが壁に衝突した時の補正
//-------------------------------------------------------------------
void cCourseCharctor::WallHitMove( const int HitWall )
{
	//衝突してなかったらスルーする
	if( HitWall == 0 ) return;

	//位置座標取得
	D3DXVECTOR3 Pos;
	m_spPosInfo->GetPos( &Pos );

	//当たった方向に戻す
	switch( HitWall ){
		case DownWall:
			Pos.y += CAR_WALL_VEL;
			break;
		case RightWall:
			Pos.x += CAR_WALL_VEL;
			break;
		case UpWall:
			Pos.y -= CAR_WALL_VEL;
			break;
		case LeftWall:
			Pos.x -= CAR_WALL_VEL;
			break;
	}

	//位置座標を更新する
	m_spPosInfo->SetPos( &Pos );
}

//-------------------------------------------------------------------
//更新処理
//-------------------------------------------------------------------
void cCourseCharctor::Updata( const float inYaw, const float inVel, const int HitWall )
{
	this->m_Yaw = inYaw;
	this->Move( inVel );
	this->WallHitMove( HitWall );
}

//-------------------------------------------------------------------
//擬似座標の取得
//-------------------------------------------------------------------
D3DXVECTOR3 cCourseCharctor::GetMapPos()
{
	D3DXVECTOR3 Pos;
	m_spPosInfo->GetPos( &Pos );

	return Pos;
}