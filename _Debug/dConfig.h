//------------------------------------------------------
//
//		デバック機能の有効・無効の設定
//
//------------------------------------------------------

//二重インクルード防止
#pragma once

//--------------------------------------
//無効にしたいデバッグ項目をコメントアウトにする
//--------------------------------------

//全てのデバッグ項目を無効にする
//全ての項目より優先される
//#define _DEBUG_NOTHING_

//全てのデバッグ項目を有効にする
//_DEBUG_NOTHING_の次に優先される
#define _DEBUG_ALL_

//メモリリーク検出NEW
#define _CRTDBG_MAP_ALLOC_

//メモリリーク検出器
#define _MEMORY_LEAKS_CHECKER_


//全てのデバッグ項目を有効にする
#ifdef _DEBUG_ALL_
	#define _CRTDBG_MAP_ALLOC_
	#define _MEMORY_LEAKS_CHECKER_
#endif /* _DEBUG_ALL */

//全てのデバッグ項目を無効にする
#ifdef _DEBUG_NOTHING_
	#undef _CRTDBG_MAP_ALLOC_
	#undef _MEMORY_LEAKS_CHECKER_
#endif /* _DEBUG_NOTHING_ */

//デバッカ読み込み
#include "dDebug.h"