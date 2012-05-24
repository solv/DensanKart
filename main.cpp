#include "WindowBase/cDxWindowBase.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//_DEBUGならば有効
	MemoryLeaksChecker;
	
	//アプリケーション起動
	cDxWindowBase cDxWnd;

	//アプリケーション実行
	cDxWnd.Run();

	return 0;
}