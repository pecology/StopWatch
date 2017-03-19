
#include "stdafx.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	int nCmdShow) 
{
	HWND window_handle = CreateWindow(
		TEXT("STATIC"),    //ウィンドウクラス
		TEXT("ウィンドウだよ"), //ウィンドウ名
		WS_CAPTION,       //ウィンドウのスタイル(CAPTIONは、タイトルバーを持つやつ)
		500,              //初期位置(x軸)
		100,              //初期位置(y軸)
		100,              //ウィンドウの幅(x軸)
		1000,              //ウィンドウの幅(y軸)
		NULL,             //親ウィンドウのハンドル
		NULL,             //メニューのハンドル
		hInstance,         //インスタンスハンドル(メインの引数で受け取る、プログラムのハンドル)
		NULL              //メッセージに渡されるパラメータ
	);

	if (window_handle == NULL)
	{
		return 0; //エラーチェック。ハンドルがNULLだったらエラーなので、プログラム終了。
	}

	ShowWindow(window_handle, SW_SHOW);
	MessageBox(NULL, TEXT("Kitty on your lap"),
		TEXT("メッセージボックス"), MB_OK);
	return 0;
}