/////////////////////////////////////////////////////
// 2008/04/29
// funcsetter.h
/////////////////////////////////////////////////////

#ifndef IKD_FUNCSETTER_H
#define IKD_FUNCSETTER_H

// �X�e�[�g���\�b�h�ݒ�e���v���[�g�Q
//
// �e���v���[�g�̐���
//
//   FuncExecutor< class CLS >
//   �@�o�^����CLS���̃��\�b�h�����s����exec���\�b�h��񋟂���C���^�[�t�F�C�X
//
//   Arg0Func< class CLS >
//   �@����������CLS���̃��\�b�h�̊Ǘ���exec�ɂ�郁�\�b�h�Ăяo�����s��
//
//   Arg1Func< class CLS, ARG1 >
//   �@������1��(�^��ARG1)�̃��\�b�h�y�т��̈����̒l�̊Ǘ���exec�ɂ�郁�\�b�h�Ăяo�����s��
//
//   FuncSetter< class CLS >
//   �@�X�e�[�g���\�b�h�̐ݒ胁�\�b�h��񋟂���������s����
//

#include <new.h>
#include <malloc.h>

namespace Dix {
	//! ���\�b�h���s�҃N���X
	template < class CLS, class EXECARG1 = unsigned int >
	class FuncExecutor {
	public:
		FuncExecutor() {}
		virtual ~FuncExecutor(){}

	public:
		//! ���s���\�b�h
		virtual void exec( CLS* pObj ) = 0;
		virtual void exec( CLS* pObj, EXECARG1 execArg1 ) = 0;

		//! �X�e�[�g����ID
		virtual unsigned int getFuncID(){ return 0; };
	};

	//! ����0�̃��\�b�h�Ǘ��N���X
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
		FUNC pFunc_;	//!< �֐��|�C���^
	};

	// ����1�̃��\�b�h�Ǘ��N���X
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
		FUNC pFunc_;	//!< �֐��|�C���^
		ARG1 arg1_;		//!< ����1
	};


	// ����2�̃��\�b�h�Ǘ��N���X
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
		FUNC pFunc_;	//!< �֐��|�C���^
		ARG1 arg1_;		//!< ����1
		ARG2 arg2_;		//!< ����2
	};

	// ����3�̃��\�b�h�Ǘ��N���X
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
		FUNC pFunc_;	//!< �֐��|�C���^
		ARG1 arg1_;		//!< ����1
		ARG2 arg2_;		//!< ����2
		ARG3 arg3_;		//!< ����3
	};

	// �X�e�[�g���\�b�h�ݒ�N���X
	template< class CLS, class EXECARG1 = unsigned int >
	class FuncSetter {
	public:
		FuncSetter() : ptr_( 0 ), allocSize_( 0 ), isUseOuterHeap_( false ) { }
		FuncSetter( void* heap ) : ptr_( (FuncExecutor< CLS, EXECARG1 >*)heap ), allocSize_( 0 ), isUseOuterHeap_( true ) {
			// �O���̃q�[�v�̈�ɃI�u�W�F�N�g���v���[�X�����g����
			// �T�C�Y�͊O���ˑ�
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

		//! �X�e�[�g���s
		void exec( CLS *pObj ) {
			if ( ptr_ ) {
				isStateChange_ = false;
				ptr_->exec( pObj );
			}
		}

		//! �X�e�[�g���s
		void exec( CLS *pObj, EXECARG1 execArg1 ) {
			if ( ptr_ ) {
				isStateChange_ = false;
				ptr_->exec( pObj, execArg1 );
			}
		}

		//! ���\�b�h�ύX�H
		bool isStateChange() {
			return isStateChange_;
		}

		//! ����0�̃��\�b�h�ݒ�
		template< class FUNC >
		FuncExecutor<CLS>* setFunc( FUNC func ) {
			if( ptr_ ) ptr_->~FuncExecutor();
			ReallocMem ( sizeof( Arg0Func< CLS > ) );
			return new( ptr_ ) Arg0Func< CLS, EXECARG1 >( func );
		}

		//! ����1�̃��\�b�h�ݒ�
		template< class FUNC, class ARG1 >
		FuncExecutor<CLS>* setFunc( FUNC func, ARG1 arg1 ) {
			if( ptr_ ) ptr_->~FuncExecutor();
			ReallocMem( sizeof( Arg1Func< CLS, ARG1> ) );
			return new( ptr_ ) Arg1Func< CLS, ARG1, EXECARG1 >( func, arg1 );	
		}

		//! ����2�̃��\�b�h�ݒ�
		template< class FUNC, class ARG1, class ARG2 >
		FuncExecutor<CLS>* setFunc( FUNC func, ARG1 arg1, ARG2 arg2 ) {
			if( ptr_ ) ptr_->~FuncExecutor();
			ReallocMem( sizeof( Arg2Func< CLS, ARG1, ARG2, EXECARG1 > ) );
			return new( ptr_ ) Arg2Func< CLS, ARG1, ARG2, EXECARG1 >( func, arg1, arg2 );	
		}

		//! ����3�̃��\�b�h�ݒ�
		template< class FUNC, class ARG1, class ARG2, class ARG3 >
		FuncExecutor<CLS>* setFunc( FUNC func, ARG1 arg1, ARG2 arg2, ARG3 arg3 ) {
			ReallocMem( sizeof( Arg3Func< CLS, ARG1, ARG2, ARG3, EXECARG1 > ) );
			return new( ptr_ ) Arg3Func< CLS, ARG1, ARG2, ARG3, EXECARG1 >( func, arg1, arg2, arg3 );	
		}

	private:
		//! ���������Ċm��
		void ReallocMem( unsigned int size ) {
			// �X�e�[�g�ύX�t���O�𗧂Ă�
			isStateChange_ = true;

			// �O���q�[�v�����鎞�͖��������
			if ( isUseOuterHeap_ == false && allocSize_ < size ) {
				ptr_ = (FuncExecutor< CLS >*)realloc( ptr_, size );
				allocSize_ = size;
			}
		}

	private:
		unsigned int allocSize_;	//!< �m�ۂ��Ă��郁�����T�C�Y
		FuncExecutor< CLS, EXECARG1 >* ptr_;	//!< �m�ۂ��Ă��郁�����ւ̐擪�|�C���^
		bool isUseOuterHeap_;		//!< �O���񋟂̃q�[�v���g���H
		bool isStateChange_;		//!< �X�e�[�g�ύX���������H
	};


} // end namespace Dix


#endif // IKD_FUNCSETTER_H
