
#include "stdafx.h"
#include "main.h"

//ウィンドウハンドル
HWND window_handle;
//インスタンスハンドル
HINSTANCE instance_handle;
//スレッド内のフラグ
int flg = 1;

//スレッド
DWORD WINAPI MyThread(LPVOID *data)
{
  int count = 0;
  TCHAR buf[1000] = TEXT("");
  PAINTSTRUCT paint_struct;
  HFONT font_handle;
  while (flg)
  {
    InvalidateRect(window_handle, NULL, TRUE);  //領域無効化
    wsprintf(buf, TEXT("%d"), count);
    HDC device_context_handle;
    device_context_handle = BeginPaint(window_handle, &paint_struct);
    font_handle = CreateFont(
      60, 20, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
      DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
      CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
      VARIABLE_PITCH | FF_ROMAN, NULL
    );
    SelectObject(device_context_handle, font_handle);
    TextOut(
      device_context_handle,      //デバイスコンテキストハンドル
      10,                         //表示文字の位置x
      20,                         //表示文字の位置y
      buf,                        //表示文字
      lstrlen(buf)                //表示文字の文字数
    );
    SelectObject(device_context_handle, GetStockObject(SYSTEM_FONT));
    DeleteObject(font_handle);
    EndPaint(window_handle, &paint_struct);
    count++;
    Sleep(100);
  }
  ExitThread(0);
}


//ウィンドウプロシージャ。ウィンドウクラスのlpfnWndProcにこの関数のポインタを入れておかないと、有効にならない。
LRESULT CALLBACK MyWndProc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_wapam)
{
  static HANDLE thread;
  switch (message)
  {
  case WM_CREATE:
  {
    thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MyThread, (LPVOID)TEXT("カウント:"), 0, NULL);
  }
  case WM_COMMAND:
  {
    switch (LOWORD(w_param))
    {
    case START_STOP_BUTTON:
    {
      MessageBox(hwnd, TEXT("スタート/ストップボタン"), TEXT("Kitty"), MB_OK);
      break;
    }
    case RESET_BUTTON:
    {
      MessageBox(hwnd, TEXT("リセットボタン"), TEXT("Kitty"), MB_OK);
      break;
    }
    case RECORD_BUTTON:
    {
      MessageBox(hwnd, TEXT("記録ボタン"), TEXT("Kitty"), MB_OK);
      break;
    }
    }
    return 0;
  }

  case WM_LBUTTONUP:
  {
    thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MyThread, (LPVOID)TEXT("カウント:"), 0, NULL);
    HDC device_context_handle;
    LPCTSTR str = TEXT("こんにちは!!");
    device_context_handle = GetDC(hwnd);
    TextOut(
      device_context_handle,      //デバイスコンテキストハンドル
      10,                         //表示文字の位置x
      10,                         //表示文字の位置y
      str,                        //表示文字
      lstrlen(str)                //表示文字の文字数
    );
    ReleaseDC(hwnd, device_context_handle);
    return 0;
  }

  case WM_DESTROY:
  {
    MessageBox(hwnd, TEXT("終わるにゃん"),
      TEXT("Kitty"), MB_ICONINFORMATION);
    PostQuitMessage(21);     //これが実行されると、メッセージキューにVM_QUITメッセージがポストされる。
                             //引数の0は、VM_QUITメッセージのwPARAMの値になる。
    return 0;
  }

  default:
    break;
  }
  return DefWindowProc(hwnd, message, w_param, l_wapam);
}

int WINAPI WinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  PSTR lpCmdLine,
  int nCmdShow)
{
  instance_handle = hInstance;

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
  window_class.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //クライアントエリアの背景色を指定。
  //ブラシのハンドルを渡す。すでにあるブラシのハンドルは、GetStockObjectで取得できる。
  window_class.lpszMenuName = NULL;              //メニューを渡す。メニューはないのでNULL
  window_class.lpszClassName = TEXT("ウィンドウクラス名です");  //ウィンドウクラスの名前を指定

  //作成したウィンドウクラスを登録
  ATOM atom = RegisterClass(&window_class);
  if (atom == NULL)
  {
    return 0; //エラーチェック。atomがNULLだったらウィンドウクラス登録失敗なので、プログラム終了。
  }

  window_handle = CreateWindow(
    TEXT("ウィンドウクラス名です"),  //ウィンドウクラス名。lpsxClssNameの文字列を指定
    TEXT("ウィンドウだよ"),      //ウィンドウ名
    WS_OVERLAPPEDWINDOW | WS_VISIBLE, //ウィンドウのスタイル。枠とタイトルを持つウィンドウ
    100, 100, 400, 140,          //表示する座標と幅を指定
    NULL, NULL,                    //親ウィンドウとメニューはないので、NULL
    hInstance,                   //インスタンスハンドル
    NULL                         //メッセージのパラメータ。ないのでNULL
  );

  if (window_handle == NULL)
  {
    return 0; //エラーチェック。window_handleがNULLだったらウィンドウクラス作成失敗なので、プログラム終了。
  }

  HWND start_button_handle = CreateWindow(
    TEXT("BUTTON"),         //ウィンドウクラス名。用意されているボタンを使う。
    TEXT("スタート/ストップ"),       //ウィンドウ名
    WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, //子にするため、WS_CHILD。BS_PUSHBUTTON
    220, 10, 150, 40,
    window_handle,           //親ウィンドウのハンドル指定
    (HMENU)START_STOP_BUTTON,        //メニューではなく、ボタンウィンドウのIDを決める。
    hInstance,              //インスタンスハンドル
    NULL                    //メニュー(なし)
  );

  HWND reset_button_handle = CreateWindow(
    TEXT("BUTTON"),         //ウィンドウクラス名。用意されているボタンを使う。
    TEXT("リセット"),       //ウィンドウ名
    WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, //子にするため、WS_CHILD。BS_PUSHBUTTON
    220, 60, 70, 30,
    window_handle,           //親ウィンドウのハンドル指定
    (HMENU)RESET_BUTTON,      //メニューではなく、ボタンウィンドウのIDを決める。
    hInstance,              //インスタンスハンドル
    NULL                    //メニュー(なし)
  );

  HWND record_button_handle = CreateWindow(
    TEXT("BUTTON"),         //ウィンドウクラス名。用意されているボタンを使う。
    TEXT("記録"),       //ウィンドウ名
    WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, //子にするため、WS_CHILD。BS_PUSHBUTTON
    300, 60, 70, 30,
    window_handle,           //親ウィンドウのハンドル指定
    (HMENU)RECORD_BUTTON,           //メニューではなく、ボタンウィンドウのIDを決める。
    hInstance,              //インスタンスハンドル
    NULL                    //メニュー(なし)
  );

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