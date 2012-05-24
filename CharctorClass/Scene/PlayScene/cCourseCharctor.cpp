//�w�b�_�[�t�@�C���ǂݍ���
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
//����������
//-------------------------------------------------------------------
cCourseCharctor::cCourseCharctor( LPCTSTR CourseFileName )
{
	//�R�[�X�C���[�W�̍쐬
	m_CourseImage = NEW cCourseImage;
	m_CourseImage->LoadCourseFile( CourseFileName );
	m_CourseImage->CreateCourseImageFace();

	m_spPosInfo->SetPos( (float)m_CourseImage->GetFirstPosX(), (float)m_CourseImage->GetFirstPosY(), 0.0f );

	LoadImage( m_CourseImage->GetImage() );
	SAFE_DELETE( m_CourseImage );
}

//-------------------------------------------------------------------
//�`�揈��
//-------------------------------------------------------------------
void cCourseCharctor::Draw()
{
	DxLib::DrawRotaGraph2F(
		CAR_SCREEN_X, CAR_SCREEN_Y, m_spPosInfo->GetPosX()+CAR_SCREEN_X, m_spPosInfo->GetPosY()+CAR_SCREEN_Y,
		1.0f, (double)m_Yaw, GetImage(), FALSE
	);
}

//-------------------------------------------------------------------
//�ړ�����
//-------------------------------------------------------------------
void cCourseCharctor::Move( float Vel )
{
	//�ʒu���W�擾
	D3DXVECTOR3 Pos;
	m_spPosInfo->GetPos( &Pos );

	//�ړ�����
	Pos.x -= sinf( m_Yaw ) * Vel;
	Pos.y -= cosf( m_Yaw ) * Vel;

	//�ʒu���W���X�V����
	m_spPosInfo->SetPos( &Pos );
}

//-------------------------------------------------------------------
//�}�V�����ǂɏՓ˂������̕␳
//-------------------------------------------------------------------
void cCourseCharctor::WallHitMove( const int HitWall )
{
	//�Փ˂��ĂȂ�������X���[����
	if( HitWall == 0 ) return;

	//�ʒu���W�擾
	D3DXVECTOR3 Pos;
	m_spPosInfo->GetPos( &Pos );

	//�������������ɖ߂�
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

	//�ʒu���W���X�V����
	m_spPosInfo->SetPos( &Pos );
}

//-------------------------------------------------------------------
//�X�V����
//-------------------------------------------------------------------
void cCourseCharctor::Updata( const float inYaw, const float inVel, const int HitWall )
{
	this->m_Yaw = inYaw;
	this->Move( inVel );
	this->WallHitMove( HitWall );
}

//-------------------------------------------------------------------
//�[�����W�̎擾
//-------------------------------------------------------------------
D3DXVECTOR3 cCourseCharctor::GetMapPos()
{
	D3DXVECTOR3 Pos;
	m_spPosInfo->GetPos( &Pos );

	return Pos;
}