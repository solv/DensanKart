//ヘッダーファイル読み込み
#include <tchar.h>
#include <fstream>
#include <shlwapi.h>
#include <boost/lexical_cast.hpp>
#include "cCourseFile.h"
#include "../../../../_Debug/dDebug.h"
#include "../../../../_Debug/dComon.h"

#pragma comment(lib, "shlwapi.lib")

using namespace std;

//-------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------
cCourseFile::cCourseFile():
	m_Width(0),
	m_Height(0),
	m_FirstPosX(0),
	m_FirstPosY(0),
	m_CourseData(NULL)
{
}

//-------------------------------------------------------------------
// デストラクタ
//-------------------------------------------------------------------
cCourseFile::~cCourseFile()
{
	if( m_CourseData ){
		delete m_CourseData;
		m_CourseData = NULL;
	}
}

//-------------------------------------------------------------------
// コースファイルの読み込み
//-------------------------------------------------------------------
bool cCourseFile::LoadCourseFile( LPCTSTR FileName )
{
	TCHAR* ext = PathFindExtension( FileName );

	MyOutputDebugString( _T("コースファイル読込開始\n"));
	if( _tcscmp(ext,_T(".crst")) == 0 ){
		MyOutputDebugString( _T("テキストファイル読込開始\n"));
		if( !this->LoadTextFile(FileName) ){
			MyOutputDebugString( _T("テキストファイル読み込み失敗\n"));
			return FALSE;
		}
	}else if( _tcscmp(ext,_T(".crsb")) == 0 ){
		MyOutputDebugString( _T("バイナリファイル読込開始\n"));
		if( !this->LoadBinaryFile(FileName) ){
			MyOutputDebugString( _T("バイナリファイル読込失敗\n"));
			return FALSE;
		}
	}else{
		MyOutputDebugString( _T("ファイルが見つかりません\n"));
		return FALSE;
	}
	MyOutputDebugString( _T("コースファイル読込終了\n"));

	return TRUE;
}

//-------------------------------------------------------------------
// テキストのコースファイル読み込み
//-------------------------------------------------------------------
bool cCourseFile::LoadTextFile( LPCTSTR FileName )
{
	ifstream ifs;
	TCHAR buffer[255];

	ifs.open( FileName, ios_base::in );
	if( !ifs ){
		MyOutputDebugString( _T("読み込み失敗:%s\n"), FileName );
		return FALSE;
	}

	//横、縦の長さ取得
	ifs.getline( buffer, 10, ',' );
	this->m_Width = boost::lexical_cast<int>( buffer );
	MyOutputDebugString( _T("横：%d\n"), m_Width );

	ifs.getline( buffer, 10, ',' );
	this->m_Height = boost::lexical_cast<int>( buffer );
	MyOutputDebugString( _T("縦：%d\n"), m_Height );

	//表、裏の画像ファイル名取得
	ifs.getline( buffer, 256, ',');
	_tcscpy_s( this->m_ImageFileName[Face], 256, buffer );
	MyOutputDebugString( _T("表画像：%s\n"), m_ImageFileName[Face] );
	
	ifs.getline( buffer, 256, ',');
	_tcscpy_s( this->m_ImageFileName[Mask], 256, buffer );
	MyOutputDebugString( _T("マスク画像：%s\n"), m_ImageFileName[Mask] );

	//チップ値格納の配列を生成
	m_CourseData = NEW int[ m_Width * m_Height ];

	//チップ値を取得
	for(int height=0; height<m_Height; height++){
		for(int width=0; width<m_Width; width++){
			ifs.getline( buffer, 10, ',' );
			this->m_CourseData[(height*m_Width)+width]= boost::lexical_cast<int>( buffer );
		}
	}

	//コースX,Yの初期位置取得
	ifs.getline( buffer, 256, ',' );
	this->m_FirstPosX = boost::lexical_cast<int>( buffer );
	ifs.getline( buffer, 256, ',' );
	this->m_FirstPosY = boost::lexical_cast<int>( buffer );

	//壁のゴールチェックポイント位置の取得
	for( int i=0; i<10; i++ ){
		ifs.getline( buffer, 256, ',' );
		this->m_CourseGoalCheckPoint[i] = boost::lexical_cast<int>( buffer );
	}
	
	ifs.close();

	return TRUE;
}

//-------------------------------------------------------------------
// バイナリのコースファイル読み込み
//-------------------------------------------------------------------
bool cCourseFile::LoadBinaryFile( LPCTSTR FileName )
{
	ifstream ifs;

	ifs.open( FileName, ios_base::binary );
	if( !ifs ){
		MyOutputDebugString( _T("読み込み失敗:%s\n"), FileName );
		return FALSE;
	}
	
	//横、縦の長さ取得
	ifs.read( (char*)&this->m_Width, sizeof(int) );
	ifs.read( (char*)&this->m_Height, sizeof(int) );
	MyOutputDebugString( _T("横:%d\n縦:%d\n"), m_Width, m_Height );

	//表、裏の画像ファイル名取得
	ifs.read( (char*)this->m_ImageFileName[Face], sizeof(char) * 64 );
	ifs.read( (char*)this->m_ImageFileName[Mask], sizeof(char) * 64 );
	MyOutputDebugString( _T("表画像：%s\nマスク画像：%s\n"), m_ImageFileName[Face], m_ImageFileName[Mask] );
	
	//チップ値格納の配列を生成
	this->m_CourseData = NEW int[ m_Width * m_Height ];
	//チップ値を取得
	ifs.read( (char*)this->m_CourseData, sizeof(this->m_CourseData) * (this->m_Width * this->m_Height) );

	//コースX,Yの初期位置取得
	ifs.read( (char*)&this->m_FirstPosX, sizeof(this->m_FirstPosX) );
	ifs.read( (char*)&this->m_FirstPosY, sizeof(this->m_FirstPosY) );

	//壁のゴールチェックポイント位置の取得
	ifs.read( (char*)&this->m_CourseGoalCheckPoint, sizeof(this->m_CourseGoalCheckPoint) );
	
	ifs.close();
	
	return TRUE;
}