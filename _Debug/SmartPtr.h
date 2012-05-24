// SmartPtr.h: sp クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SMARTPTR_H__4D5E5A30_6FF3_4C18_ACEC_19EA17209FC1__INCLUDED_)
#define AFX_SMARTPTR_H__4D5E5A30_6FF3_4C18_ACEC_19EA17209FC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

// spクラス（テンプレートスマートポインタクラス）
//  Created by IKD (2005. 9. 2)

// ・ 登録されたオブジェクトポインタの使用者がいなくなったら自動的にdelete
// ・ 通常のポインタ操作演算子「*」「->」「[ ]」が使える。
// ・ 異なるオブジェクトポインタが登録された状態でアップキャストができる

class void_sp;

template <class T>
class sp
{
private:
   unsigned int *m_pRefCnt;   // 参照カウンタへのポインタ
   T* m_pPtr;             // T型のオブジェクトのポインタ

private:
   /////////////////
   // 参照カウンタ増加
   /////
      void AddRef(){(*m_pRefCnt)++;}

   /////////////////
   // 参照カウンタ減少
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
   // デフォルトコンストラクタ
   /////
      explicit sp(T* src=NULL, int add=0)
      {
         m_pRefCnt = new UINT;
         *m_pRefCnt = add;
         m_pPtr = src;
         AddRef();       // 参照カウンタ増加
      }


  //////////////////////////////////////
   // コピーコンストラクタ（同型コピー）
   /////
      sp(const sp<T> &src)
      {
         // 相手のポインタをコピー
         m_pRefCnt = src.m_pRefCnt;
         m_pPtr = src.m_pPtr;

         // 自分自身の参照カウンタを増加
         AddRef();
      }


   //////////////////////////////////////
   // コピーコンストラクタ（暗黙的アップキャスト）
   /////
      template<class T2> sp(sp<T2> &src)
      {
         // 相手のポインタをコピー
         m_pRefCnt = src.GetRefPtr();
         m_pPtr = src.GetPtr();

         // 自分自身の参照カウンタを増加
         AddRef();
      }


   //////////////////////////////////////
   // コピーコンストラクタ（NULL代入代用）
   /////
      sp(const int nullval)
      {
         m_pRefCnt = new UINT;
         *m_pRefCnt = add;
         m_pPtr = src;
         AddRef();       // 参照カウンタ増加
      }


   ///////////////
   // デストラクタ
   /////
     virtual ~sp()
      {
         Release();
      }


//■■■演算子のオーバーロード■■■■■■■■■■■

   /////////////////////////////////
   // =代入演算子（明示的コピー）
   /////
      sp<T>& operator =(const sp<T> &src)
      {
         // 自分自身への代入は不正で意味が無いので
         // 行わない。
         if(src.m_pPtr == m_pPtr)
            return (*this);

		  // 自分は他人になってしまうので
         // 参照カウンタを1つ減少
         Release();

         // 相手のポインタをコピー
         m_pRefCnt = src.m_pRefCnt;
         m_pPtr = src.m_pPtr;

         // 新しい自分自身の参照カウンタを増加
         AddRef();

         return (*this);
      }


   /////////////////////////////////
   // =代入演算子（明示的アップキャスト）
   /////
      template<class T2> sp<T>& operator =(sp<T2> &src)
      {
         // 自分自身への代入は不正で意味が無いので
         // 行わない。
         if(src.GetPtr() == m_pPtr)
            return (*this);

		  // 自分は他人になってしまうので
         // 参照カウンタを1つ減少
         Release();

         // 相手のポインタをコピー
         m_pRefCnt = src.GetRefPtr();
         m_pPtr = src.GetPtr();

         // 新しい自分自身の参照カウンタを増加
         AddRef();

         return (*this);
      }


   /////////////////////////////////
   // =代入演算子(NULL代入によるリセット）
   /////
      sp<T>& operator =(const int nullval)
      {
		  // 自分は空な人になってしまうので
          // 参照カウンタを1つ減少
          Release();

          // 新規に自分自身を作る
          m_pRefCnt = new UINT;
          m_pPtr = NULL;
          AddRef();			// 参照カウンタを初期設定値に

         return (*this);
      }

   
   ///////////////
   // *間接演算子
   /////
      T& operator *(){ return *m_pPtr;}

   //////////////////////
   // ->メンバ選択演算子
   /////
      T* operator ->(){ return m_pPtr;}

   //////////////////
   // []配列参照演算子
   /////
      T& operator [](int n){ return m_pPtr[n];}

   /////////////////
   // ==比較演算子
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
   // !=比較演算子
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

//■■■ メンバ関数 ■■■■■■■■■■■

public:
   //////////////////////////
   // ポインタの明示的な登録
   /////
      void SetPtr(T* src = NULL, int add=0)
      {
         // 参照カウンタを減らした後に再初期化
            Release();
            m_pRefCnt = new UINT;
            *m_pRefCnt = add;
            m_pPtr = src;
            AddRef();
      }

   /////////////////////
   // ポインタの貸し出し
   /////
      T* GetPtr(){return m_pPtr;}


   ///////////////////////////////
   // 参照カウンタへのポインタを取得
   /////
      unsigned int* GetRefPtr(){return m_pRefCnt;}

   //////////////////////////
   // ダウンキャストコピー
   /////
	template <class T2> bool DownCast(sp<T2> &src)
	{
		// 引数のスマートポインタの持つポインタが、
		// 自分の登録しているポインタに
		// ダウンキャスト可能な場合はダウンキャストコピーを実行
		T* castPtr = dynamic_cast<T*>(src.GetPtr());
		if(castPtr){
			// ダウンキャスト成功
			// 既存の参照カウンタを1つ減少
			Release();
			// 新しいポインタと参照カウンタを共有
			m_pPtr = castPtr;
			m_pRefCnt = src.GetRefPtr();
			// 参照カウンタ増加
			AddRef();
			return true;
		}

		return false;
	}
};



#endif // !defined(AFX_SMARTPTR_H__4D5E5A30_6FF3_4C18_ACEC_19EA17209FC1__INCLUDED_)
