//------------------------------------------------------
//
//		�f�o�b�N�@�\�̎���
//
//------------------------------------------------------

//��d�C���N���[�h�h�~
#pragma once

//�w�b�_�[�t�@�C���Ǎ�
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <crtdbg.h>

/*********************
�����t���f�o�b�J�o��
**********************/
#ifdef _DEBUG
#define MyOutputDebugString( str, ... ) \
      { \
        TCHAR c[256]; \
        _stprintf_s( c, 256, str, __VA_ARGS__ ); \
        OutputDebugString( c ); \
      }
#else
#define MyOutputDebugString( str, ... ) // �����
#endif

/*********************
_ASSERT�}�N��
**********************/
#define _ASSERT_EXPR(expr, msg) \
(void) ((!!(expr)) || \
(1 != _CrtDbgReportW(_CRT_ASSERT, _CRT_WIDE(__FILE__), __LINE__, NULL, msg)) || \
(_CrtDbgBreak(), 0))

#ifndef _ASSERT
#define _ASSERT(expr) _ASSERT_EXPR((expr), NULL)
#endif

#ifndef _ASSERTE
#define _ASSERTE(expr) _ASSERT_EXPR((expr), _CRT_WIDE(#expr))
#endif

/*********************
���������[�N���o NEW
*********************/
#if defined(_DEBUG)// && defined(_CRTDBG_MAP_ALLOC_)
#define NEW  new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define NEW  new
#endif

/********************
���������[�N���m��
********************/
#if defined(_DEBUG)// && defined(_MEMORY_LEAKS_CHECKER_)
#define MemoryLeaksChecker _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#else
#define MemoryLeaksChecker
#endif
