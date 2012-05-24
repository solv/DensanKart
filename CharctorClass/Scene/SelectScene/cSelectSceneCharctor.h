//--------------------------------------------------------------
//�Z���N�g�V�[���L�����N�^�N���X
//-------------------------------------------------------------

//��d�C���N���[�h�h�~
#pragma once

//�w�b�_�[�t�@�C���̓ǂݍ���
#include "../../cCharctor.h"

//-------------------------------------------------------------------
// ��]���Ă�L�����N�^�[�N���X
//-------------------------------------------------------------------
class cObjectCharctor : public cCharctor
{
private:
	double m_Angle;
	const double m_AngleVel;

public:
	cObjectCharctor( LPCTSTR FileName, double inAngleVel ):
		cCharctor(FileName),m_Angle(0),m_AngleVel(inAngleVel){}
	virtual ~cObjectCharctor(){}

	virtual void Draw();
	virtual void Updata();
};

//-------------------------------------------------------------------
// ������L�����N�^�[�N���X
//-------------------------------------------------------------------
class cStringCharctor : public cCharctor
{
private:
	int m_StringColor;
	TCHAR m_String[4][256];

public:
	cStringCharctor( int* CourseTime );
	virtual ~cStringCharctor(){}

	void SetCourse( int CourseNum, int* CourseTime );
	void SetCar( int CarNum );

	virtual void Draw();
	virtual void Updata( int CourseNum, int CarNum, int* CourseTime );
};