//--------------------------------------------------------------
//カーソルキャラクタクラス
//-------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイルの読み込み
#include "../cCharctor.h"

class cCursorCharctor : public cCharctor
{
private:
	int m_DisplayCount;
	int m_SelectNum;
	int m_CursorTurnNum;
	bool m_DisplayFlag;

	int m_CursorMoveX;
	int m_CursorMoveY;

	const int m_MaxSelectNum;
	virtual void Move();

public:
	cCursorCharctor( LPCTSTR ImageName, int MaxSelectNum, int inMoveX, int inMoveY, int TurnNum = 5 ):
		cCharctor(ImageName),m_MaxSelectNum(MaxSelectNum),m_SelectNum(0)
	{
		m_CursorMoveX   = inMoveX;
		m_CursorMoveY   = inMoveY;
		m_DisplayCount  = 0;
		m_CursorTurnNum = TurnNum;
	}
	cCursorCharctor( Image inImage, int MaxSelectNum, int inMoveX, int inMoveY, int TurnNum = 5 ):
		cCharctor(inImage),m_MaxSelectNum(MaxSelectNum),m_SelectNum(0)
	{
		m_CursorMoveX   = inMoveX;
		m_CursorMoveY   = inMoveY;
		m_DisplayCount  = 0;
		
		m_CursorTurnNum = TurnNum;
	}
	virtual ~cCursorCharctor(){}

	virtual void Draw();
	virtual void Updata();	
	
	void Up();
	void Down();
	void Left();
	void Right();
	int GetSelectID(){ return m_SelectNum; }
	void SetTurnNum( int inTurnNum ){ this->m_CursorTurnNum = inTurnNum; }

	void SetFirstPos();
};