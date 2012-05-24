//ヘッダーファイル読み込み
#include <fstream>
#include <boost/lexical_cast.hpp>
#include "cPlaySceneCharctor.h"
#include "../../../_Debug/dComon.h"
#include "../../../_Debug/dDebug.h"
#include "../../../WindowBase/FPSCounter.h"

using namespace std;

namespace{
	static const float kDIV_UNIT	 = 60;
	static const float CAR_HIT_LENGTH = 33.0f;
}

CFPSCounter FPS(10);

//--------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------
cCarCharctor::cCarCharctor(LPCTSTR ImageName, LPCTSTR ParameterName ):
	cCharctor(ImageName),
	Vel(0.0f),
	Rev(0.0f),
	Brake(0.0f),
	wheelAngle(0.0f),
	Yaw(0.0f)
{
	carParameter = NEW CarParameter;
	GetCarParameter( carParameter, ParameterName );

	m_spPosInfo->SetPos( CAR_SCREEN_X, CAR_SCREEN_Y, 0.0f );

	DxLib::SetFontSize(15);
}

//--------------------------------------------------------------
// デストラクタ
//--------------------------------------------------------------
cCarCharctor::~cCarCharctor()
{
	SAFE_DELETE( carParameter );
}

//--------------------------------------------------------------
// マシンパラメータの取得
//--------------------------------------------------------------
bool cCarCharctor::GetCarParameter( CarParameter* carParameter_, LPCTSTR ParameterName )
{
	CarParameter* bufCarParameter = NEW CarParameter;

	ifstream ifs;
	TCHAR buffer[255];

	ifs.open( ParameterName, ios_base::in );
	
	ifs.getline( buffer, 10, '\n' );
	bufCarParameter->kREV_MAX			= boost::lexical_cast<float>( buffer );

	ifs.getline( buffer, 10, '\n' );
	bufCarParameter->kSLOWDOWN_C		= boost::lexical_cast<float>( buffer );

	bufCarParameter->kSTATIC_FRICTION	= 0.9f;
	bufCarParameter->kOnRESISTANCE_C	= 0.1f;
	bufCarParameter->kOffRESISTANCE_C	= 0.2f;
	
	ifs.getline( buffer, 10, '\n' );
	bufCarParameter->kCAR_WEIGHT		= boost::lexical_cast<float>( buffer );
	ifs.getline( buffer, 10, '\n' );
	bufCarParameter->kCAR_LENGTH		= boost::lexical_cast<float>( buffer );
	
	ifs.getline( buffer, 10, '\n' );
	bufCarParameter->kWHEEL_UNIT		= ( boost::lexical_cast<float>( buffer ) * kDEG_TO_RAD );
	ifs.getline( buffer, 10, '\n' );
	bufCarParameter->kWHELL_MAX			= ( boost::lexical_cast<float>( buffer ) * kDEG_TO_RAD );

	bufCarParameter->kREV_UNIT			= (bufCarParameter->kREV_MAX / kDIV_UNIT);

	ifs.getline( buffer, 10, '\n' );
	bufCarParameter->kBRAKE_UNIT		= boost::lexical_cast<float>( buffer );
	ifs.getline( buffer, 10, '\n' );
	bufCarParameter->kBRAKE_MAX			= boost::lexical_cast<float>( buffer );

	bufCarParameter->kAUTO_HANDLE		= 4.0f;
	bufCarParameter->kRESISTANCE_C		= bufCarParameter->kOnRESISTANCE_C;

	ifs.close();

	*carParameter_ = *bufCarParameter;
	SAFE_DELETE( bufCarParameter );

	return TRUE;
}

//--------------------------------------------------------------
// アクセル
//--------------------------------------------------------------
void cCarCharctor::Acceleration( CarMoveState state_ )
{
	if( state_ == AccelOn ){
		Rev += carParameter->kREV_UNIT;
		if( Rev > carParameter->kREV_MAX ){ Rev = carParameter->kREV_MAX; }
	}
	else if( state_ == AccelOff ){
		if( Rev > 0.0f ){
			//エンジン回転数減らし処理
			Rev -= Rev * carParameter->kSLOWDOWN_C;
			if( Rev < 0 ){ Rev = 0; }
		}
	}
}

//--------------------------------------------------------------
// ブレーキ
//--------------------------------------------------------------
void cCarCharctor::Deceleration( CarMoveState state_ )
{
	if( state_ == BrakeOn ){
		Brake += carParameter->kBRAKE_UNIT;
		if( Brake > carParameter->kBRAKE_MAX ){ Brake = carParameter->kBRAKE_MAX; }
	}
	else if( state_ == BrakeOff ){
		if( Brake > 0.0f ){
			Brake -= carParameter->kBRAKE_UNIT * 2.5f;
			if( Brake < 0.0f ){ Brake = 0.0f; }
		}
	}
}

//--------------------------------------------------------------
// ステアリング
//--------------------------------------------------------------
void cCarCharctor::Steering( CarMoveState state_ )
{
	if( state_ == SteeringLeft ){
		if( wheelAngle < 0 ){
			wheelAngle += carParameter->kAUTO_HANDLE * carParameter->kWHEEL_UNIT;
		}else{
			wheelAngle += carParameter->kWHEEL_UNIT;
			if( wheelAngle > carParameter->kWHELL_MAX ){ wheelAngle = carParameter->kWHELL_MAX; }
		}
	}
	else if( state_ == SteeringRight ){
		if( wheelAngle > 0 ){
			wheelAngle -= carParameter->kAUTO_HANDLE * carParameter->kWHEEL_UNIT;
		}else{
			wheelAngle -=  carParameter->kWHEEL_UNIT;
			if( wheelAngle < -carParameter->kWHELL_MAX ){ wheelAngle = -carParameter->kWHELL_MAX; }
		}
	}
	else if( state_ == AutoSteering ){
		if( wheelAngle != 0.0f ){
			wheelAngle += ( wheelAngle > 0 ) ? -carParameter->kWHEEL_UNIT * carParameter->kAUTO_HANDLE : carParameter->kWHEEL_UNIT * carParameter->kAUTO_HANDLE;
			wheelAngle =  (fabs( wheelAngle) > carParameter->kWHEEL_UNIT * carParameter->kAUTO_HANDLE ) ? wheelAngle : 0.0f;
		}
	}
}

//--------------------------------------------------------------
// 画像の描画
//--------------------------------------------------------------
void cCarCharctor::Draw()
{
	DxLib::DrawGraphF( m_spPosInfo->GetPosX()-16, m_spPosInfo->GetPosY()-32, GetImage(), TRUE );

#ifdef _DEBUG
	DxLib::DrawFormatString( 0,25, GetColor(255,255,255), _T("Rev:%f"),Rev);
	DxLib::DrawFormatString( 0,50, GetColor(255,255,255), _T("wheelAngle:%f"),wheelAngle);
	DxLib::DrawFormatString( 0,75, GetColor(255,255,255), _T("Vel:%f"),Vel);
	DxLib::DrawFormatString( 0,100, GetColor(255,255,255), _T("RESITANCE_C:%f"),carParameter->kRESISTANCE_C);
	DxLib::DrawFormatString( 0,125, GetColor(255,255,255), _T("Brake:%f"),Brake);
	DxLib::DrawFormatString( 0,150, GetColor(255,255,255), _T("FPS:%.2f"),FPS.GetFPS());

	/*DrawOval(320,240,CAR_HIT_LENGTH,CAR_HIT_LENGTH,GetColor(255,0,0),FALSE);
	for( int Tire=0; Tire<4; Tire++ )
		DrawLine( 320, 240, CarHit[Tire], CarHit[Tire+4], GetColor(255,0,0) );*/
#endif /* _DEBUG */

}

//--------------------------------------------------------------
// 移動
//--------------------------------------------------------------
void cCarCharctor::Move()
{
	//旋回は舵角と速度に比例して、車の長さ（ホイールベース）に反比例する
	Yaw += ( wheelAngle * Vel ) / carParameter->kCAR_LENGTH;
	CheckFloatRange( &Yaw, D3DX_PI );

	//速度変化
	Vel += Rev / carParameter->kCAR_WEIGHT * carParameter->kSTATIC_FRICTION;

	//空気抵抗とかによる減速
	Vel -= Vel * carParameter->kRESISTANCE_C / carParameter->kCAR_WEIGHT;

	//ブレーキとか掛けます
	if( Brake > 0.0f ){
		Vel -= carParameter->kCAR_WEIGHT * Brake;
		if( Vel < 0.0f ){ Vel = 0.0f; }
	}
}

//--------------------------------------------------------------
// タイヤの位置
//--------------------------------------------------------------
float* cCarCharctor::GetCarHitTire()
{
	return CarHit;
}

//--------------------------------------------------------------
// タイヤの位置の設定
//--------------------------------------------------------------
void cCarCharctor::SetCarHitTire()
{
	int Deg[] = { 150,-150,30,-30 };

	for( int Tire=0; Tire<4; Tire++ ){
		CarHit[Tire]   = sinf(Yaw+DEG_TO_RAD(Deg[Tire]))  * CAR_HIT_LENGTH + CAR_SCREEN_X;
		CarHit[Tire+4] = cosf(Yaw+DEG_TO_RAD(Deg[Tire]))  * CAR_HIT_LENGTH + CAR_SCREEN_Y;
	}
	CarHit[8] = sinf(Yaw+DEG_TO_RAD(180))  * CAR_HIT_LENGTH + CAR_SCREEN_X;
	CarHit[9] = cosf(Yaw+DEG_TO_RAD(180))  * CAR_HIT_LENGTH + CAR_SCREEN_Y;
}

//--------------------------------------------------------------
// タイヤと路面状況の設定
//--------------------------------------------------------------
void cCarCharctor::SetResistance( bool ResistanceFlag )
{
	if( ResistanceFlag ){
		carParameter->kRESISTANCE_C = carParameter->kOnRESISTANCE_C;
	}else if( !ResistanceFlag ){
		carParameter->kRESISTANCE_C = carParameter->kOffRESISTANCE_C;
	}
}

//--------------------------------------------------------------
// 更新処理
//--------------------------------------------------------------
void cCarCharctor::Updata( bool ResistanceFlag )
{
	this->SetResistance( ResistanceFlag );
	this->Move();
	this->SetCarHitTire();
}

//--------------------------------------------------------------
// 限界値のチェック
//--------------------------------------------------------------
void cCarCharctor::CheckFloatRange( float *aFloat ,const float aRange)
{
	if( *aFloat >  aRange ){
		*aFloat -= 2.0f * aRange;
	}else if( *aFloat < -aRange ){
		*aFloat += 2.0f * aRange;
	}
}