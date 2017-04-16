
#include <windows.h>
#include "main.h"
#include "StopWatch.h"
#include "stdlib.h"

#pragma warning(disable : 4996)

//ウィンドウハンドル
HWND main_window_handle;
//インスタンスハンドル
HINSTANCE instance_handle;
//スレッド終了フラグ
int thread_end_flg = 0;
//ストップウォッチクラス
StopWatch stop_watch;
//表示タイム
LPCWSTR display_time;
//経過時間再描画の範囲
RECT elapsed_time_rect;
//経過時間のフォント
HFONT font_handle;
//元々のボタンのウィンドウプロシージャハンドル
WNDPROC default_button_window_proc_handle;

//経過時間を描画するスレッド。計測中に常に動いている。
DWORD WINAPI PaintElapsedTime()
{
  while (!thread_end_flg)
  {
    display_time = (LPCWSTR)stop_watch.MeasureTime().ToWCharArray();

    InvalidateRect(main_window_handle, &elapsed_time_rect, TRUE);  //領域無効化

    Sleep(87);
  }
  ExitThread(0);
}

//ボタンの拡張プロシージャ。ボタンに対して送られたWM_CHAR(キー入力)をメインウィンドウに送る
LRESULT CALLBACK CustomButtonProc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_wapam)
{
  if (message == WM_CHAR)
  {
    // メインウィンドウプロシージャに送る。
    SendMessage(main_window_handle, message, w_param, l_wapam);
  }
  //　もともとのプロシージャにも送る。
  return CallWindowProc(default_button_window_proc_handle, hwnd, message, w_param, l_wapam);
}

//メインウィンドウのプロシージャ。ウィンドウクラスのlpfnWndProcにこの関数のポインタを入れておかないと、有効にならない。
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_wapam)
{
  static PAINTSTRUCT paint_struct; 
  static HDC device_context_handle;
  switch (message)
  {
  case WM_CHAR:
  {
    if (w_param == TEXT('s'))
    { // スタート/ストップする。
      OnStartStop();
    }
    else if (w_param == TEXT('r'))
    { //リセットする
      OnReset();
    }
    break;
  }
  case WM_COMMAND:
  {
    switch (LOWORD(w_param))
    {
    case START_STOP_BUTTON:
    {
      OnStartStop();
      break;
    }
    case RESET_BUTTON:
    {
      OnReset();
      break;
    }
    case RECORD_BUTTON:
    {
      MessageBox(hwnd, TEXT("実装しましょう"), TEXT("Kitty"), MB_OK);
      break;
    }
    }
    return 0;
  }

  case WM_DESTROY:
  {
    PostQuitMessage(21);     //これが実行されると、メッセージキューにVM_QUITメッセージがポストされる。
                             //引数の0は、VM_QUITメッセージのwPARAMの値になる。
    return 0;
  }

  case WM_PAINT:
  {
    device_context_handle = BeginPaint(main_window_handle, &paint_struct);
    SelectObject(device_context_handle, font_handle);
    TextOut(
      device_context_handle,      //デバイスコンテキストハンドル
      10,                         //表示文字の位置x
      20,                         //表示文字の位置y
      (LPCWSTR)display_time,                        //表示文字
      lstrlen((LPCWSTR)display_time)                //表示文字の文字数
    );
    //SelectObject(device_context_handle, GetStockObject(SYSTEM_FONT));
    EndPaint(main_window_handle, &paint_struct);

    break;
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

  //経過時間描画の範囲を指定する。
  SetRect(&elapsed_time_rect, 10, 20, 250, 100);

  //経過時間のフォントを指定する。
  font_handle = CreateFont(
    60, 20, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
    VARIABLE_PITCH | FF_ROMAN, NULL
  );

  //ウィンドウクラス作成
  WNDCLASS window_class;
  window_class.style = CS_HREDRAW | CS_VREDRAW;  //ウィンドウが拡大縮小されると再描画される。
  window_class.lpfnWndProc = MainWndProc;      //ウィンドウプロシージャを設定。
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

  main_window_handle = CreateWindowEx(
    WS_EX_COMPOSITED,                //ちらつき防止
    TEXT("ウィンドウクラス名です"),  //ウィンドウクラス名。lpsxClssNameの文字列を指定
    TEXT("ウィンドウだよ"),      //ウィンドウ名
    WS_OVERLAPPEDWINDOW | WS_VISIBLE, //ウィンドウのスタイル。枠とタイトルを持つウィンドウ
    100, 100, 400, 140,          //表示する座標と幅を指定
    NULL, NULL,                    //親ウィンドウとメニューはないので、NULL
    hInstance,                   //インスタンスハンドル
    NULL                         //メッセージのパラメータ。ないのでNULL
  );

  if (main_window_handle == NULL)
  {
    return 0; //エラーチェック。window_handleがNULLだったらウィンドウクラス作成失敗なので、プログラム終了。
  }

  HWND start_button_handle = CreateWindow(
    TEXT("BUTTON"),         //ウィンドウクラス名。用意されているボタンを使う。
    TEXT("スタート/ストップ"),       //ウィンドウ名
    WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, //子にするため、WS_CHILD。BS_PUSHBUTTON
    250, 10, 120, 40,
    main_window_handle,           //親ウィンドウのハンドル指定
    (HMENU)START_STOP_BUTTON,        //メニューではなく、ボタンウィンドウのIDを決める。
    hInstance,              //インスタンスハンドル
    NULL                    //メニュー(なし)
  );

  HWND reset_button_handle = CreateWindow(
    TEXT("BUTTON"),         //ウィンドウクラス名。用意されているボタンを使う。
    TEXT("リセット"),       //ウィンドウ名
    WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, //子にするため、WS_CHILD。BS_PUSHBUTTON
    250, 60, 40, 30,
    main_window_handle,           //親ウィンドウのハンドル指定
    (HMENU)RESET_BUTTON,      //メニューではなく、ボタンウィンドウのIDを決める。
    hInstance,              //インスタンスハンドル
    NULL                    //メニュー(なし)
  );

  HWND record_button_handle = CreateWindow(
    TEXT("BUTTON"),         //ウィンドウクラス名。用意されているボタンを使う。
    TEXT("記録"),       //ウィンドウ名
    WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, //子にするため、WS_CHILD。BS_PUSHBUTTON
    300, 60, 70, 30,
    main_window_handle,           //親ウィンドウのハンドル指定
    (HMENU)RECORD_BUTTON,           //メニューではなく、ボタンウィンドウのIDを決める。
    hInstance,              //インスタンスハンドル
    NULL                    //メニュー(なし)
  );

  // ボタンのウィンドウプロシージャを取得(3つのボタンはすべて共通のプロシージャなのでいっこだけでよい)
  default_button_window_proc_handle = (WNDPROC)GetWindowLong(start_button_handle, GWL_WNDPROC);
  
  // ボタンのウィンドウプロシージャを差し替える。
  SetWindowLong(start_button_handle, GWL_WNDPROC, (long)CustomButtonProc);
  SetWindowLong(reset_button_handle, GWL_WNDPROC, (long)CustomButtonProc);
  SetWindowLong(record_button_handle, GWL_WNDPROC, (long)CustomButtonProc);

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
    //仮想キーコードを実際の文字に変換
    TranslateMessage(&msg);
    //ディスパッチ後、上のウィンドウプロシージャが実行される。
    DispatchMessage(&msg);
  }

  return 0;
}

void OnStartStop() 
{
  if(stop_watch.is_measuring())
  { // ストップ
    //計測終了
    stop_watch.Stop();

    //スレッドを終了させる。
    thread_end_flg = 1;
  }
  else
  { // スタート
    //スレッドを作成する。
    thread_end_flg = 0;
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)PaintElapsedTime, NULL, 0, NULL);

    //計測開始
    stop_watch.Start();
  }
}

void OnReset()
{
  //スレッドを終了させる。
  thread_end_flg = 1;

  stop_watch.Reset();
  display_time = TEXT("00:00:00:000");
  InvalidateRect(main_window_handle, NULL, TRUE);  //領域無効化
}