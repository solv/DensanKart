#include "WindowBase/cDxWindowBase.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//_DEBUG�Ȃ�ΗL��
	MemoryLeaksChecker;
	
	//�A�v���P�[�V�����N��
	cDxWindowBase cDxWnd;

	//�A�v���P�[�V�������s
	cDxWnd.Run();

	return 0;
}