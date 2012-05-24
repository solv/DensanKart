//-------------------------------------------------------------
//描写管理クラス
//-------------------------------------------------------------

//二重インクルード防止
#pragma once

//ヘッダーファイル読込
#include <vector>
#include "iDrawObjectBase.h"

class cDrawManager
{
private:
	std::vector<iDrawObjectBase*> m_VectorDraw;

public:
	cDrawManager(){}
	virtual ~cDrawManager(){}

	void Draw();
	HRESULT Remove();
	HRESULT Append( iDrawObjectBase* );
};
