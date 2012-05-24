/////////////////////////////////////////////////////
// 2008/04/29
// funcsetter.h
/////////////////////////////////////////////////////

#ifndef IKD_FUNCSETTER_H
#define IKD_FUNCSETTER_H

// ステートメソッド設定テンプレート群
//
// テンプレートの説明
//
//   FuncExecutor< class CLS >
//   　登録したCLS内のメソッドを実行するexecメソッドを提供するインターフェイス
//
//   Arg0Func< class CLS >
//   　引数が無いCLS内のメソッドの管理とexecによるメソッド呼び出しを行う
//
//   Arg1Func< class CLS, ARG1 >
//   　引数が1つ(型はARG1)のメソッド及びその引数の値の管理とexecによるメソッド呼び出しを行う
//
//   FuncSetter< class CLS >
//   　ステートメソッドの設定メソッドを提供しそれを実行する
//

#include <new.h>
#include <malloc.h>

namespace Dix {
	//! メソッド実行者クラス
	template < class CLS, class EXECARG1 = unsigned int >
	class FuncExecutor {
	public:
		FuncExecutor() {}
		virtual ~FuncExecutor(){}

	public:
		//! 実行メソッド
		virtual void exec( CLS* pObj ) = 0;
		virtual void exec( CLS* pObj, EXECARG1 execArg1 ) = 0;

		//! ステート識別ID
		virtual unsigned int getFuncID(){ return 0; };
	};

	//! 引数0のメソッド管理クラス
	template< class CLS, class EXECARG1 = unsigned int >
	class Arg0Func : public FuncExecutor< CLS, EXECARG1 > {
		typedef void ( CLS::*FUNC )();
	public:
		Arg0Func() : pFunc_( 0 ) { }
		Arg0Func( FUNC func ) : pFunc_( func ) { }
		virtual ~Arg0Func() {}

		virtual void exec( CLS* pObj ) {
			if ( pFunc_ ) ( pObj->*pFunc_ )();
		}
		virtual void exec( CLS* pObj, EXECARG1 execArg1 ) {
			if ( pFunc_ ) ( pObj->*pFunc_ )();
		}

		Arg0Func& operator ()( FUNC func ) {
			pFunc_ = func;
			return *this;
		}

	protected:
		FUNC pFunc_;	//!< 関数ポインタ
	};

	// 引数1のメソッド管理クラス
	template< class CLS, class ARG1, class EXECARG1 = ARG1 >
	class Arg1Func : public FuncExecutor< CLS, EXECARG1 > {
		typedef void ( CLS::*FUNC )( ARG1 );
	public:
		Arg1Func() : pFunc_( 0 ), arg1( ARG1() ) { }
		Arg1Func( FUNC func, ARG1 arg1 ) : pFunc_( func ), arg1_( arg1 ) { }
		virtual ~Arg1Func() {}

		virtual void exec( CLS* pObj ) {
			if ( pFunc_ ) ( pObj->*pFunc_ )( arg1_ );
		}
		virtual void exec( CLS* pObj, EXECARG1 execArg1 ) {
			if ( pFunc_ ) ( pObj->*pFunc_ )( execArg1 );
		}

		Arg1Func& operator ()( FUNC func, ARG1 arg1 ) {
			arg1_ = arg1;
			pFunc_ = func;
			return *this;
		}

	private:
		FUNC pFunc_;	//!< 関数ポインタ
		ARG1 arg1_;		//!< 引数1
	};


	// 引数2のメソッド管理クラス
	template< class CLS, class ARG1, class ARG2, class EXECARG1 = ARG1 >
	class Arg2Func : public FuncExecutor< CLS, EXECARG1 > {
		typedef void ( CLS::*FUNC )( ARG1, ARG2 );
	public:
		Arg2Func() : pFunc_( 0 ), arg1_( ARG1() ), arg2_( ARG2() ) { }
		Arg2Func( FUNC func, ARG1 arg1, ARG2 arg2 ) : pFunc_( func ), arg1_( arg1 ), arg2_( arg2 ) { }
		virtual ~Arg2Func() {}

		virtual void exec( CLS* pObj ) {
			if ( pFunc_ ) ( pObj->*pFunc_ )( arg1_, arg2_ );
		}
		virtual void exec( CLS* pObj, EXECARG1 execArg1 ) {
			if ( pFunc_ ) ( pObj->*pFunc_ )( execArg1, arg2_ );
		}

		Arg2Func& operator ()( FUNC func, ARG1 arg1, ARG2 arg2 ) {
			arg1_ = arg1;
			arg2_ = arg2;
			pFunc_ = func;
			return *this;
		}

	private:
		FUNC pFunc_;	//!< 関数ポインタ
		ARG1 arg1_;		//!< 引数1
		ARG2 arg2_;		//!< 引数2
	};

	// 引数3のメソッド管理クラス
	template< class CLS, class ARG1, class ARG2, class ARG3, class EXECARG1 = ARG1 >
	class Arg3Func : public FuncExecutor< CLS, EXECARG1 > {
		typedef void ( CLS::*FUNC )( ARG1, ARG2, ARG3 );
	public:
		Arg3Func() : pFunc_( 0 ), arg1_( ARG1() ), arg2_( ARG2() ), arg3_( ARG3() ) { }
		Arg3Func( FUNC func, ARG1 arg1, ARG2 arg2, ARG3 arg3 ) : pFunc_( func ), arg1_( arg1 ), arg2_( arg2 ), arg3_( arg3 ) { }
		virtual ~Arg3Func() {}

		virtual void exec( CLS* pObj ) {
			if ( pFunc_ ) ( pObj->*pFunc_ )( arg1_, arg2_, arg3_ );
		}
		virtual void exec( CLS* pObj, EXECARG1 execArg1 ) {
			if ( pFunc_ ) ( pObj->*pFunc_ )( execArg1, arg2_, arg3_ );
		}

		Arg3Func& operator ()( FUNC func, ARG1 arg1, ARG2 arg2, ARG3 arg3 ) {
			arg1_ = arg1;
			arg2_ = arg2;
			arg3_ = arg3;
			pFunc_ = func;
			return *this;
		}

	private:
		FUNC pFunc_;	//!< 関数ポインタ
		ARG1 arg1_;		//!< 引数1
		ARG2 arg2_;		//!< 引数2
		ARG3 arg3_;		//!< 引数3
	};

	// ステートメソッド設定クラス
	template< class CLS, class EXECARG1 = unsigned int >
	class FuncSetter {
	public:
		FuncSetter() : ptr_( 0 ), allocSize_( 0 ), isUseOuterHeap_( false ) { }
		FuncSetter( void* heap ) : ptr_( (FuncExecutor< CLS, EXECARG1 >*)heap ), allocSize_( 0 ), isUseOuterHeap_( true ) {
			// 外部のヒープ領域にオブジェクトをプレースメントする
			// サイズは外部依存
		}

		~FuncSetter() {
			if ( ptr_ ) {
				ptr_->~FuncExecutor();
			}

			if ( isUseOuterHeap_ == false && ptr_ ) {
				free( ptr_ );
				ptr_ = 0;
			}
		}

		//! ステート実行
		void exec( CLS *pObj ) {
			if ( ptr_ ) {
				isStateChange_ = false;
				ptr_->exec( pObj );
			}
		}

		//! ステート実行
		void exec( CLS *pObj, EXECARG1 execArg1 ) {
			if ( ptr_ ) {
				isStateChange_ = false;
				ptr_->exec( pObj, execArg1 );
			}
		}

		//! メソッド変更？
		bool isStateChange() {
			return isStateChange_;
		}

		//! 引数0のメソッド設定
		template< class FUNC >
		FuncExecutor<CLS>* setFunc( FUNC func ) {
			if( ptr_ ) ptr_->~FuncExecutor();
			ReallocMem ( sizeof( Arg0Func< CLS > ) );
			return new( ptr_ ) Arg0Func< CLS, EXECARG1 >( func );
		}

		//! 引数1のメソッド設定
		template< class FUNC, class ARG1 >
		FuncExecutor<CLS>* setFunc( FUNC func, ARG1 arg1 ) {
			if( ptr_ ) ptr_->~FuncExecutor();
			ReallocMem( sizeof( Arg1Func< CLS, ARG1> ) );
			return new( ptr_ ) Arg1Func< CLS, ARG1, EXECARG1 >( func, arg1 );	
		}

		//! 引数2のメソッド設定
		template< class FUNC, class ARG1, class ARG2 >
		FuncExecutor<CLS>* setFunc( FUNC func, ARG1 arg1, ARG2 arg2 ) {
			if( ptr_ ) ptr_->~FuncExecutor();
			ReallocMem( sizeof( Arg2Func< CLS, ARG1, ARG2, EXECARG1 > ) );
			return new( ptr_ ) Arg2Func< CLS, ARG1, ARG2, EXECARG1 >( func, arg1, arg2 );	
		}

		//! 引数3のメソッド設定
		template< class FUNC, class ARG1, class ARG2, class ARG3 >
		FuncExecutor<CLS>* setFunc( FUNC func, ARG1 arg1, ARG2 arg2, ARG3 arg3 ) {
			ReallocMem( sizeof( Arg3Func< CLS, ARG1, ARG2, ARG3, EXECARG1 > ) );
			return new( ptr_ ) Arg3Func< CLS, ARG1, ARG2, ARG3, EXECARG1 >( func, arg1, arg2, arg3 );	
		}

	private:
		//! メモリを再確保
		void ReallocMem( unsigned int size ) {
			// ステート変更フラグを立てる
			isStateChange_ = true;

			// 外部ヒープがある時は無視される
			if ( isUseOuterHeap_ == false && allocSize_ < size ) {
				ptr_ = (FuncExecutor< CLS >*)realloc( ptr_, size );
				allocSize_ = size;
			}
		}

	private:
		unsigned int allocSize_;	//!< 確保しているメモリサイズ
		FuncExecutor< CLS, EXECARG1 >* ptr_;	//!< 確保しているメモリへの先頭ポインタ
		bool isUseOuterHeap_;		//!< 外部提供のヒープを使う？
		bool isStateChange_;		//!< ステート変更があった？
	};


} // end namespace Dix


#endif // IKD_FUNCSETTER_H
