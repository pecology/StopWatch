#include<windows.h>
#include "stdafx.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	int nCmdShow) {
	MessageBox(NULL, TEXT("Kitty on your lap"),
		TEXT("メッセージボックス"), MB_OK);
	return 0;
}