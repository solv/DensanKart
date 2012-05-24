//�w�b�_�[�t�@�C���ǂݍ���
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
// �R���X�g���N�^
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
// �f�X�g���N�^
//-------------------------------------------------------------------
cCourseFile::~cCourseFile()
{
	if( m_CourseData ){
		delete m_CourseData;
		m_CourseData = NULL;
	}
}

//-------------------------------------------------------------------
// �R�[�X�t�@�C���̓ǂݍ���
//-------------------------------------------------------------------
bool cCourseFile::LoadCourseFile( LPCTSTR FileName )
{
	TCHAR* ext = PathFindExtension( FileName );

	MyOutputDebugString( _T("�R�[�X�t�@�C���Ǎ��J�n\n"));
	if( _tcscmp(ext,_T(".crst")) == 0 ){
		MyOutputDebugString( _T("�e�L�X�g�t�@�C���Ǎ��J�n\n"));
		if( !this->LoadTextFile(FileName) ){
			MyOutputDebugString( _T("�e�L�X�g�t�@�C���ǂݍ��ݎ��s\n"));
			return FALSE;
		}
	}else if( _tcscmp(ext,_T(".crsb")) == 0 ){
		MyOutputDebugString( _T("�o�C�i���t�@�C���Ǎ��J�n\n"));
		if( !this->LoadBinaryFile(FileName) ){
			MyOutputDebugString( _T("�o�C�i���t�@�C���Ǎ����s\n"));
			return FALSE;
		}
	}else{
		MyOutputDebugString( _T("�t�@�C����������܂���\n"));
		return FALSE;
	}
	MyOutputDebugString( _T("�R�[�X�t�@�C���Ǎ��I��\n"));

	return TRUE;
}

//-------------------------------------------------------------------
// �e�L�X�g�̃R�[�X�t�@�C���ǂݍ���
//-------------------------------------------------------------------
bool cCourseFile::LoadTextFile( LPCTSTR FileName )
{
	ifstream ifs;
	TCHAR buffer[255];

	ifs.open( FileName, ios_base::in );
	if( !ifs ){
		MyOutputDebugString( _T("�ǂݍ��ݎ��s:%s\n"), FileName );
		return FALSE;
	}

	//���A�c�̒����擾
	ifs.getline( buffer, 10, ',' );
	this->m_Width = boost::lexical_cast<int>( buffer );
	MyOutputDebugString( _T("���F%d\n"), m_Width );

	ifs.getline( buffer, 10, ',' );
	this->m_Height = boost::lexical_cast<int>( buffer );
	MyOutputDebugString( _T("�c�F%d\n"), m_Height );

	//�\�A���̉摜�t�@�C�����擾
	ifs.getline( buffer, 256, ',');
	_tcscpy_s( this->m_ImageFileName[Face], 256, buffer );
	MyOutputDebugString( _T("�\�摜�F%s\n"), m_ImageFileName[Face] );
	
	ifs.getline( buffer, 256, ',');
	_tcscpy_s( this->m_ImageFileName[Mask], 256, buffer );
	MyOutputDebugString( _T("�}�X�N�摜�F%s\n"), m_ImageFileName[Mask] );

	//�`�b�v�l�i�[�̔z��𐶐�
	m_CourseData = NEW int[ m_Width * m_Height ];

	//�`�b�v�l���擾
	for(int height=0; height<m_Height; height++){
		for(int width=0; width<m_Width; width++){
			ifs.getline( buffer, 10, ',' );
			this->m_CourseData[(height*m_Width)+width]= boost::lexical_cast<int>( buffer );
		}
	}

	//�R�[�XX,Y�̏����ʒu�擾
	ifs.getline( buffer, 256, ',' );
	this->m_FirstPosX = boost::lexical_cast<int>( buffer );
	ifs.getline( buffer, 256, ',' );
	this->m_FirstPosY = boost::lexical_cast<int>( buffer );

	//�ǂ̃S�[���`�F�b�N�|�C���g�ʒu�̎擾
	for( int i=0; i<10; i++ ){
		ifs.getline( buffer, 256, ',' );
		this->m_CourseGoalCheckPoint[i] = boost::lexical_cast<int>( buffer );
	}
	
	ifs.close();

	return TRUE;
}

//-------------------------------------------------------------------
// �o�C�i���̃R�[�X�t�@�C���ǂݍ���
//-------------------------------------------------------------------
bool cCourseFile::LoadBinaryFile( LPCTSTR FileName )
{
	ifstream ifs;

	ifs.open( FileName, ios_base::binary );
	if( !ifs ){
		MyOutputDebugString( _T("�ǂݍ��ݎ��s:%s\n"), FileName );
		return FALSE;
	}
	
	//���A�c�̒����擾
	ifs.read( (char*)&this->m_Width, sizeof(int) );
	ifs.read( (char*)&this->m_Height, sizeof(int) );
	MyOutputDebugString( _T("��:%d\n�c:%d\n"), m_Width, m_Height );

	//�\�A���̉摜�t�@�C�����擾
	ifs.read( (char*)this->m_ImageFileName[Face], sizeof(char) * 64 );
	ifs.read( (char*)this->m_ImageFileName[Mask], sizeof(char) * 64 );
	MyOutputDebugString( _T("�\�摜�F%s\n�}�X�N�摜�F%s\n"), m_ImageFileName[Face], m_ImageFileName[Mask] );
	
	//�`�b�v�l�i�[�̔z��𐶐�
	this->m_CourseData = NEW int[ m_Width * m_Height ];
	//�`�b�v�l���擾
	ifs.read( (char*)this->m_CourseData, sizeof(this->m_CourseData) * (this->m_Width * this->m_Height) );

	//�R�[�XX,Y�̏����ʒu�擾
	ifs.read( (char*)&this->m_FirstPosX, sizeof(this->m_FirstPosX) );
	ifs.read( (char*)&this->m_FirstPosY, sizeof(this->m_FirstPosY) );

	//�ǂ̃S�[���`�F�b�N�|�C���g�ʒu�̎擾
	ifs.read( (char*)&this->m_CourseGoalCheckPoint, sizeof(this->m_CourseGoalCheckPoint) );
	
	ifs.close();
	
	return TRUE;
}