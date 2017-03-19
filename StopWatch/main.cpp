
#include "stdafx.h"

//ウィンドウプロシージャ。ウィンドウクラスのlpfnWndProcにこの関数のポインタを入れておかないと、有効にならない。
LRESULT CALLBACK MyWndProc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_wapam)
{
  if (message == WM_DESTROY)
  { //ウィンドウ右上の×が押されたときに、WM_DESTROYがポストされるので、そのとき。
    MessageBox(hwnd, TEXT("終わるにゃん"),
      TEXT("Kitty"), MB_ICONINFORMATION);
    PostQuitMessage(21);     //これが実行されると、メッセージキューにVM_QUITメッセージがポストされる。
                            //引数の0は、VM_QUITメッセージのwPARAMの値になる。
    return 0;
  }
  return DefWindowProc(hwnd, message, w_param, l_wapam);
}

int WINAPI WinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  PSTR lpCmdLine,
  int nCmdShow) 
{
  //ウィンドウクラス作成
  WNDCLASS window_class;
  window_class.style = CS_HREDRAW | CS_VREDRAW;  //ウィンドウが拡大縮小されると再描画される。
  window_class.lpfnWndProc = MyWndProc;      //ウィンドウプロシージャを設定。
  window_class.cbClsExtra = 0;                   //ウィンドウクラスの追加領域をバイト単位で指定
  window_class.cbWndExtra = 0;                   //同じ
  window_class.hInstance = hInstance;             //インスタンスハンドル
  window_class.hIcon = LoadIcon(NULL, IDI_ERROR);  //アイコンの設定（下のバーに出るやつ）
  window_class.hCursor = LoadCursor(NULL, IDC_HELP); //マウスカーソルのハンドルを指定
                                                      //第一引数にNULLで第二引数に定数を入れることにより、
                                                      //システムで定義されているカーソルを指定できる。IDC_ARROWは標準のやつ
                                                      //矢印を十字にしたり砂時計にしたりできる。
  window_class.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //クライアントエリアの背景色を指定。
  //ブラシのハンドルを渡す。すでにあるブラシのハンドルは、GetStockObjectで取得できる。
  window_class.lpszMenuName = NULL;              //メニューを渡す。メニューはないのでNULL
  window_class.lpszClassName = TEXT("ウィンドウクラス名です");  //ウィンドウクラスの名前を指定

  //作成したウィンドウクラスを登録
  ATOM atom = RegisterClass(&window_class);
  if (atom == NULL)
  {
    return 0; //エラーチェック。atomがNULLだったらウィンドウクラス登録失敗なので、プログラム終了。
  }

  HWND window_handle = CreateWindow(
    TEXT("ウィンドウクラス名です"),  //ウィンドウクラス名。lpsxClssNameの文字列を指定
    TEXT("ウィンドウだよ"),      //ウィンドウ名
    WS_OVERLAPPEDWINDOW | WS_VISIBLE, //ウィンドウのスタイル。枠とタイトルを持つウィンドウ
    100, 100, 200, 200,          //表示する座標と幅を指定
    NULL, NULL,                    //親ウィンドウとメニューはないので、NULL
    hInstance,                   //インスタンスハンドル
    NULL                         //メッセージのパラメータ。ないのでNULL
  );

  if (window_handle == NULL)
  {
    return 0; //エラーチェック。window_handleがNULLだったらウィンドウクラス作成失敗なので、プログラム終了。
  }

  MSG msg;
  int result;
  while (TRUE)
  {
    //メッセージを受け取る
    result = GetMessage(
      &msg,    // 受け取ったメッセージを格納する変数のアドレス
      NULL,     // メッセージを受け取るウィンドウのハンドルを指定
               // NULLを指定すると、アプリケーションを構成する
               // すべてのウィンドウのメッセージを取得する。)
      0,       // 受け取るメッセージの最小値。0は制限なし
      0        // 受け取るメッセージの最大値。0は制限なし。
    );
    if (result == 0)
    {
      //GetMessageがWM_QUITを受け取ると戻り値が0になるので、そのとき。
      //メイン関数に、wPARAMの値を戻して、プログラムを終了する。
      return msg.wParam;
    }
    //ディスパッチ後、上のウィンドウプロシージャが実行される。
    DispatchMessage(&msg);
  }

  return 0;
}