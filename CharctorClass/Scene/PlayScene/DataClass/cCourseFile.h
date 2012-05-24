//--------------------------------------------------------------
//�R�[�X�t�@�C���ǂݍ��݃N���X
//-------------------------------------------------------------

//��d�C���N���[�h�h�~
#pragma once

//�w�b�_�[�t�@�C���Ǎ�
#include <windows.h>

class cCourseFile
{
protected:
	int m_Width;
	int m_Height;
	int m_FirstPosX;
	int m_FirstPosY;
	int* m_CourseData;
	int m_CourseGoalCheckPoint[12];
	TCHAR m_ImageFileName[2][256];

private:
	bool LoadTextFile( LPCTSTR );
	bool LoadBinaryFile( LPCTSTR );

public:
	cCourseFile();
	virtual ~cCourseFile();

	bool LoadCourseFile( LPCTSTR );

	int GetWidth()		{ return m_Width;	   }
	int GetHeight()		{ return m_Height;	   }
	int* GetCourseData(){ return m_CourseData; }
	int GetFirstPosX()  { return m_FirstPosX;  }
	int GetFirstPosY()  { return m_FirstPosY;  }
};