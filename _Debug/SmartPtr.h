// SmartPtr.h: sp �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SMARTPTR_H__4D5E5A30_6FF3_4C18_ACEC_19EA17209FC1__INCLUDED_)
#define AFX_SMARTPTR_H__4D5E5A30_6FF3_4C18_ACEC_19EA17209FC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

// sp�N���X�i�e���v���[�g�X�}�[�g�|�C���^�N���X�j
//  Created by IKD (2005. 9. 2)

// �E �o�^���ꂽ�I�u�W�F�N�g�|�C���^�̎g�p�҂����Ȃ��Ȃ����玩���I��delete
// �E �ʏ�̃|�C���^���쉉�Z�q�u*�v�u->�v�u[ ]�v���g����B
// �E �قȂ�I�u�W�F�N�g�|�C���^���o�^���ꂽ��ԂŃA�b�v�L���X�g���ł���

class void_sp;

template <class T>
class sp
{
private:
   unsigned int *m_pRefCnt;   // �Q�ƃJ�E���^�ւ̃|�C���^
   T* m_pPtr;             // T�^�̃I�u�W�F�N�g�̃|�C���^

private:
   /////////////////
   // �Q�ƃJ�E���^����
   /////
      void AddRef(){(*m_pRefCnt)++;}

   /////////////////
   // �Q�ƃJ�E���^����
   /////
      void Release()
      {
         if(--(*m_pRefCnt) == 0){
             delete m_pPtr;
             delete m_pRefCnt;
         }
      }

public:
  ///////////////////////
   // �f�t�H���g�R���X�g���N�^
   /////
      explicit sp(T* src=NULL, int add=0)
      {
         m_pRefCnt = new UINT;
         *m_pRefCnt = add;
         m_pPtr = src;
         AddRef();       // �Q�ƃJ�E���^����
      }


  //////////////////////////////////////
   // �R�s�[�R���X�g���N�^�i���^�R�s�[�j
   /////
      sp(const sp<T> &src)
      {
         // ����̃|�C���^���R�s�[
         m_pRefCnt = src.m_pRefCnt;
         m_pPtr = src.m_pPtr;

         // �������g�̎Q�ƃJ�E���^�𑝉�
         AddRef();
      }


   //////////////////////////////////////
   // �R�s�[�R���X�g���N�^�i�ÖٓI�A�b�v�L���X�g�j
   /////
      template<class T2> sp(sp<T2> &src)
      {
         // ����̃|�C���^���R�s�[
         m_pRefCnt = src.GetRefPtr();
         m_pPtr = src.GetPtr();

         // �������g�̎Q�ƃJ�E���^�𑝉�
         AddRef();
      }


   //////////////////////////////////////
   // �R�s�[�R���X�g���N�^�iNULL�����p�j
   /////
      sp(const int nullval)
      {
         m_pRefCnt = new UINT;
         *m_pRefCnt = add;
         m_pPtr = src;
         AddRef();       // �Q�ƃJ�E���^����
      }


   ///////////////
   // �f�X�g���N�^
   /////
     virtual ~sp()
      {
         Release();
      }


//���������Z�q�̃I�[�o�[���[�h����������������������

   /////////////////////////////////
   // =������Z�q�i�����I�R�s�[�j
   /////
      sp<T>& operator =(const sp<T> &src)
      {
         // �������g�ւ̑���͕s���ňӖ��������̂�
         // �s��Ȃ��B
         if(src.m_pPtr == m_pPtr)
            return (*this);

		  // �����͑��l�ɂȂ��Ă��܂��̂�
         // �Q�ƃJ�E���^��1����
         Release();

         // ����̃|�C���^���R�s�[
         m_pRefCnt = src.m_pRefCnt;
         m_pPtr = src.m_pPtr;

         // �V�����������g�̎Q�ƃJ�E���^�𑝉�
         AddRef();

         return (*this);
      }


   /////////////////////////////////
   // =������Z�q�i�����I�A�b�v�L���X�g�j
   /////
      template<class T2> sp<T>& operator =(sp<T2> &src)
      {
         // �������g�ւ̑���͕s���ňӖ��������̂�
         // �s��Ȃ��B
         if(src.GetPtr() == m_pPtr)
            return (*this);

		  // �����͑��l�ɂȂ��Ă��܂��̂�
         // �Q�ƃJ�E���^��1����
         Release();

         // ����̃|�C���^���R�s�[
         m_pRefCnt = src.GetRefPtr();
         m_pPtr = src.GetPtr();

         // �V�����������g�̎Q�ƃJ�E���^�𑝉�
         AddRef();

         return (*this);
      }


   /////////////////////////////////
   // =������Z�q(NULL����ɂ�郊�Z�b�g�j
   /////
      sp<T>& operator =(const int nullval)
      {
		  // �����͋�Ȑl�ɂȂ��Ă��܂��̂�
          // �Q�ƃJ�E���^��1����
          Release();

          // �V�K�Ɏ������g�����
          m_pRefCnt = new UINT;
          m_pPtr = NULL;
          AddRef();			// �Q�ƃJ�E���^�������ݒ�l��

         return (*this);
      }

   
   ///////////////
   // *�Ԑډ��Z�q
   /////
      T& operator *(){ return *m_pPtr;}

   //////////////////////
   // ->�����o�I�����Z�q
   /////
      T* operator ->(){ return m_pPtr;}

   //////////////////
   // []�z��Q�Ɖ��Z�q
   /////
      T& operator [](int n){ return m_pPtr[n];}

   /////////////////
   // ==��r���Z�q
   /////
/*      bool operator ==(int val){
         if((int)m_pPtr == val)
            return TRUE;
         return FALSE;
      }
*/
      bool operator ==(T *val){
         if(m_pPtr == val)
            return TRUE;
         return FALSE;
      }

   /////////////////
   // !=��r���Z�q
   /////
/*      bool operator !=(int val){
         if((int)m_pPtr != val)
            return TRUE;
         return FALSE;
      }
*/
      bool operator !=(T *val){
         if(m_pPtr != val)
            return TRUE;
         return FALSE;
      }

//������ �����o�֐� ����������������������

public:
   //////////////////////////
   // �|�C���^�̖����I�ȓo�^
   /////
      void SetPtr(T* src = NULL, int add=0)
      {
         // �Q�ƃJ�E���^�����炵����ɍď�����
            Release();
            m_pRefCnt = new UINT;
            *m_pRefCnt = add;
            m_pPtr = src;
            AddRef();
      }

   /////////////////////
   // �|�C���^�݂̑��o��
   /////
      T* GetPtr(){return m_pPtr;}


   ///////////////////////////////
   // �Q�ƃJ�E���^�ւ̃|�C���^���擾
   /////
      unsigned int* GetRefPtr(){return m_pRefCnt;}

   //////////////////////////
   // �_�E���L���X�g�R�s�[
   /////
	template <class T2> bool DownCast(sp<T2> &src)
	{
		// �����̃X�}�[�g�|�C���^�̎��|�C���^���A
		// �����̓o�^���Ă���|�C���^��
		// �_�E���L���X�g�\�ȏꍇ�̓_�E���L���X�g�R�s�[�����s
		T* castPtr = dynamic_cast<T*>(src.GetPtr());
		if(castPtr){
			// �_�E���L���X�g����
			// �����̎Q�ƃJ�E���^��1����
			Release();
			// �V�����|�C���^�ƎQ�ƃJ�E���^�����L
			m_pPtr = castPtr;
			m_pRefCnt = src.GetRefPtr();
			// �Q�ƃJ�E���^����
			AddRef();
			return true;
		}

		return false;
	}
};



#endif // !defined(AFX_SMARTPTR_H__4D5E5A30_6FF3_4C18_ACEC_19EA17209FC1__INCLUDED_)
