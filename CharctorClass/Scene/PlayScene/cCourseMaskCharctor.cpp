//�w�b�_�[�t�@�C���ǂݍ���
#include "cPlaySceneCharctor.h"
#include "../../../_Debug/dComon.h"
#include "../../../_Debug/dDebug.h"

namespace{
	enum RoadType{
		Out				 = -1,
		OffRoad			 = 0,
		Wall			 = 384,	
		OnGoalBefor		 = 255,
		OffGoalWallBefor = 287,
		OffGoalBefor	 = 319,
		OnGoalAfter		 = 510,
		OffGoalWallAfter = 574,
		OffGoalAfter	 = 638,
		OnRoad			 = 765,
	};

	enum CarHitWall{
		DownWall  = 4,
		RightWall = 3,
		UpWall    = 2,
		LeftWall  = 1,
	};

	//�S�[�����Ƀt���O�Ǘ�
	int RunningFlag,OldRunningFlag;
}

//-------------------------------------------------------------------
//����������
//-------------------------------------------------------------------
cCourseMaskCharctor::cCourseMaskCharctor( LPCTSTR CourseFileName )
{
	//�R�[�X�}�X�N�C���[�W�̍쐬
	m_CourseImage = NEW cCourseImage;
	m_CourseImage->LoadCourseFile( CourseFileName );
	m_CourseImage->CreateCourseImageMask();

	this->LoadImage( m_CourseImage->GetImage() );
	SAFE_DELETE( m_CourseImage );

	RunningFlag = 0;
	OldRunningFlag = 0;
}

//-------------------------------------------------------------------
//�}�V���ƃS�[���̔���
//-------------------------------------------------------------------
int cCourseMaskCharctor::IsHitGoalAndCar( float* CarHitTire, D3DXVECTOR3 inPos )
{
	int a,r,g,b;
	int CarHit;
	D3DXVECTOR3 Map = inPos;

	//�ԑ̑O���̍��W�̐F���擾
	DxLib::GetPixelSoftImage( this->GetImage(), Map.x+CarHitTire[8], Map.y+CarHitTire[9], &r, &g, &b, &a );
	CarHit = r+g+b;

	//�S�[����O�̂���ꍇ
	if( CarHit == OnGoalBefor || CarHit == OffGoalBefor || CarHit == OffGoalWallBefor ){
		RunningFlag = 1;
	//�S�[�����ɂ���ꍇ
	}else if( CarHit == OnGoalAfter || CarHit == OffGoalAfter || CarHit == OffGoalWallAfter ){
		RunningFlag = 2;
	}//�S�[�����ɂ���ꍇ
	else{
		RunningFlag = 0;
		OldRunningFlag = 0;
	}

	if( RunningFlag != OldRunningFlag && OldRunningFlag != 0 ){
		OldRunningFlag = RunningFlag;
		return (RunningFlag % 2)+1;
	}

	OldRunningFlag = RunningFlag;
	
	return 0;
}

//-------------------------------------------------------------------
//�}�V���ƕǂ̔���
//-------------------------------------------------------------------
int cCourseMaskCharctor::IsHitWallAndCar( float* CarHitTire, float Yaw, D3DXVECTOR3 inPos )
{
	//�F�X�ϐ�
	int a,r[2],g[2],b[2];
	int RightCarHit;
	int LeftCarHit;
	D3DXVECTOR3 Map = inPos;

	//��[2�̍��W�_�̐F���擾
	for( int i=0; i<2; i++ )
		DxLib::GetPixelSoftImage( this->GetImage(), Map.x+CarHitTire[i], Map.y+CarHitTire[i+4], &r[i], &g[i], &b[i], &a );

	RightCarHit = r[0]+g[0]+b[0];
	LeftCarHit  = r[1]+g[1]+b[1];

	//���p���Փ˂����ꍇ
	if( (LeftCarHit == Wall && RightCarHit == Wall)							||
		(LeftCarHit == Wall && RightCarHit == OffGoalWallBefor)				||
		(LeftCarHit == Wall && RightCarHit == OffGoalWallAfter )			||
		(LeftCarHit == OffGoalWallBefor && RightCarHit == OffGoalWallAfter)	||
		(LeftCarHit == OffGoalWallBefor && RightCarHit == Wall)				||
		(LeftCarHit == OffGoalWallAfter && RightCarHit == Wall)				||
		(LeftCarHit == Wall && RightCarHit == OffGoalWallAfter)				||
		(LeftCarHit == Wall && RightCarHit == OffGoalWallBefor)				||
		(LeftCarHit == OffGoalWallAfter && RightCarHit == OffGoalWallBefor) ||
		(LeftCarHit == OffGoalWallAfter && RightCarHit == Wall)				||
		(LeftCarHit == OffGoalWallBefor && LeftCarHit == Wall)			
	){
		if( -0.785f <= Yaw && Yaw <= 0.785f )	return DownWall;
		if( -2.355f <= Yaw && Yaw < -0.785 )	return LeftWall;
		if( 2.355f <= Yaw || Yaw < -2.355f )	return UpWall;
		if( 2.355f > Yaw && Yaw >= 0.785f )		return RightWall;
	}
	//���p�������Փ˂����ꍇ
	else if( LeftCarHit == Wall || LeftCarHit == OffGoalWallBefor || LeftCarHit == OffGoalWallAfter ){
		if( -1.57f <= Yaw && Yaw <= 0.00f  )	return DownWall;
		if( -3.14f <= Yaw &&  Yaw < -1.57f )	return LeftWall;
		if( 3.14f >= Yaw && Yaw > 1.57f )		return UpWall;
		if( 1.57f >= Yaw && Yaw > 0.00f )		return RightWall;
	}
	//�E�p�������ǂɏՓ˂����ꍇ
	else if( RightCarHit == Wall || RightCarHit == OffGoalWallBefor || RightCarHit == OffGoalWallAfter ){
		if( -1.57f <= Yaw && Yaw <= 0.0f  )		return LeftWall;
		if( -3.14f <= Yaw &&  Yaw < -1.57f )	return UpWall;
		if( 3.14f >= Yaw && Yaw > 1.57f )		return RightWall;
		if( 1.57f >= Yaw && Yaw > 0.00f )		return DownWall;
	}

	//�Փ˂��Ă��Ȃ��ꍇ
	return 0;
}

//-------------------------------------------------------------------
//�}�V���ƘH�ʂ̔���
//-------------------------------------------------------------------
bool cCourseMaskCharctor::IsHitGroundAndCar( float* CarHitTire, D3DXVECTOR3 inPos )
{
	int a,r,g,b,CarHit,AreaOut;
	D3DXVECTOR3 Map = inPos;

	//�H���܂��̓G���A�O�̎��AFALSE��Ԃ�
	for(int i=0; i<4; i++){
		AreaOut = DxLib::GetPixelSoftImage( this->GetImage(), Map.x+CarHitTire[i], Map.y+CarHitTire[i+4], &r, &g, &b, &a );
		CarHit = r+g+b;
		if( CarHit == OffRoad || CarHit == OffGoalBefor || CarHit == OffGoalAfter || AreaOut == Out ){
			return FALSE;
		}
	}

	return TRUE;
}