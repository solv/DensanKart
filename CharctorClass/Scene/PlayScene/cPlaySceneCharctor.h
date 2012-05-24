//--------------------------------------------------------------
//プレイシーンキャラクタクラス
//--------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイルの読み込み
#include "../../cCharctor.h"
#include "DataClass/cCourseImage.h"

//--------------------------------------------------------------
// コースキャラクタークラス
//--------------------------------------------------------------
class cCourseCharctor : public cCharctor
{
private:
	float m_Yaw;
	cCourseImage* m_CourseImage;

public:
	cCourseCharctor( LPCTSTR CourseFileName );
	virtual ~cCourseCharctor(){}

	virtual void Draw();
	virtual void Move( float Vel );
	virtual void WallHitMove( int HitWall );
	void Updata( float inYaw, float inVel, int HitWall );

	D3DXVECTOR3 GetMapPos();
};

//--------------------------------------------------------------
// コースマスクキャラクタークラス
//--------------------------------------------------------------
class cCourseMaskCharctor : public cCharctor
{
private:
	cCourseImage* m_CourseImage;

public:
	cCourseMaskCharctor( LPCTSTR CourseFileName );
	virtual ~cCourseMaskCharctor(){
		DxLib::DeleteSoftImage( this->m_Image );
	}

	virtual void Draw(){}
	virtual void Move(){}

	int IsHitGoalAndCar( float* CarHitTire, D3DXVECTOR3 inPos );
	int IsHitWallAndCar( float* CarHitTire, float Yaw, D3DXVECTOR3 inPos );
	bool IsHitGroundAndCar( float* CarHitTire, D3DXVECTOR3 inPos );
};

//--------------------------------------------------------------
// マシンキャラクタークラス
//--------------------------------------------------------------
class cCarCharctor : public cCharctor
{
public:
	enum CarMoveState{
		AccelOn,
		AccelOff,
		BrakeOn,
		BrakeOff,
		SteeringLeft,
		SteeringRight,
		AutoSteering,
	};

private:
	typedef struct _tagCarParameter{
		float kREV_MAX;
		float kSLOWDOWN_C;
		float kSTATIC_FRICTION;
		float kOnRESISTANCE_C;
		float kOffRESISTANCE_C;
		float kRESISTANCE_C;
		float kCAR_WEIGHT;
		float kCAR_LENGTH;
		float kWHEEL_UNIT;
		float kWHELL_MAX;
		float kREV_UNIT;
		float kBRAKE_UNIT;
		float kBRAKE_MAX;
		float kAUTO_HANDLE;
	}CarParameter;

	float Vel;
	float Rev;
	float Brake;
	float wheelAngle;
	float Yaw;

	float CarHit[10];

	CarParameter* carParameter;

	bool GetCarParameter( CarParameter* carParameter_, LPCTSTR ParameterName );
	virtual void Move();
	void CheckFloatRange( float *aFloat ,const float aRange);

public:
	cCarCharctor( LPCTSTR ImageName, LPCTSTR ParameterName );
	virtual ~cCarCharctor();

	virtual void Draw();
	void Updata( bool ResistanceFlag );

	void Acceleration( CarMoveState state_ );
	void Deceleration( CarMoveState state_ );
	void Steering( CarMoveState state_ );

	float GetVel(){ return this->Vel; }
	float GetYaw(){ return this->Yaw; }

	void SetResistance( bool ResistanceFlag );
	void SetCarHitTire();
	float* GetCarHitTire();
};

//--------------------------------------------------------------
// シグナルキャラクタークラス
//--------------------------------------------------------------
class cSignalCharctor : public cCharctor
{
protected:
	int m_SignalCount;
	double m_ExRate;

public:
	cSignalCharctor( LPCTSTR FileName, int Count );
	virtual ~cSignalCharctor(){}

	virtual void Draw();
	virtual void Updata();

	int GetSignalCount();
};

//--------------------------------------------------------------
// ゴールシグナルキャラクタークラス
//--------------------------------------------------------------
class cGoalSignalCharctor : public cSignalCharctor
{
private:
	
public:
	cGoalSignalCharctor( LPCTSTR ImageName, int Count );
	virtual ~cGoalSignalCharctor(){}

	virtual void Draw();
	virtual void Updata();

	double GetExRate(){ return this->m_ExRate; }
};

//--------------------------------------------------------------
// ニューレコードキャラクタークラス
//--------------------------------------------------------------
class cNewRecordCharctor : public cGoalSignalCharctor
{
private:

public:
	cNewRecordCharctor( LPCTSTR ImageName, int Count );
	virtual ~cNewRecordCharctor(){}
	
};

//--------------------------------------------------------------
// プッシュボタンキャラクタークラス
//--------------------------------------------------------------
class cPushButtonCharctor : public cGoalSignalCharctor
{
public:
	cPushButtonCharctor( LPCTSTR ImageName, int Count );
	virtual ~cPushButtonCharctor(){}

	void Updata();
};

//--------------------------------------------------------------
// スピードメーターキャラクタークラス
//--------------------------------------------------------------
class cSpeedoMeterCharctor : public cCharctor
{
private:

public:
	cSpeedoMeterCharctor( LPCTSTR ImageName ):cCharctor(ImageName){
		m_spPosInfo->SetPos( 475.0f, 315.0f, 0.0f );
	}
	virtual ~cSpeedoMeterCharctor(){}

	virtual void Draw();
};

//--------------------------------------------------------------
// スピードメーターのニードルキャラクタークラス
//--------------------------------------------------------------
class cSpeedoMeterNeedleCharctor : public cCharctor
{
private:
	double m_Angle;

private:
	float ChangeVelToSpeed( float Vel );

public:
	cSpeedoMeterNeedleCharctor( LPCTSTR ImageName );
	virtual ~cSpeedoMeterNeedleCharctor(){}

	void Updata( float Vel );
	virtual void Draw();
};