
#include <windows.h>
#include "main.h"
#include "StopWatch.h"
#include "stdlib.h"

#pragma warning(disable : 4996)

//�E�B���h�E�n���h��
HWND main_window_handle;
//�C���X�^���X�n���h��
HINSTANCE instance_handle;
//�X���b�h�I���t���O
int thread_end_flg = 0;
//�X�g�b�v�E�H�b�`�N���X
StopWatch stop_watch;
//�\���^�C��
LPCWSTR display_time;
//�o�ߎ��ԍĕ`��͈̔�
RECT elapsed_time_rect;
//�o�ߎ��Ԃ̃t�H���g
HFONT font_handle;
//���X�̃{�^���̃E�B���h�E�v���V�[�W���n���h��
WNDPROC default_button_window_proc_handle;

//�o�ߎ��Ԃ�`�悷��X���b�h�B�v�����ɏ�ɓ����Ă���B
DWORD WINAPI PaintElapsedTime()
{
  while (!thread_end_flg)
  {
    display_time = (LPCWSTR)stop_watch.MeasureTime().ToWCharArray();

    InvalidateRect(main_window_handle, &elapsed_time_rect, TRUE);  //�̈斳����

    Sleep(87);
  }
  ExitThread(0);
}

//�{�^���̊g���v���V�[�W���B�{�^���ɑ΂��đ���ꂽWM_CHAR(�L�[����)�����C���E�B���h�E�ɑ���
LRESULT CALLBACK CustomButtonProc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_wapam)
{
  if (message == WM_CHAR)
  {
    // ���C���E�B���h�E�v���V�[�W���ɑ���B
    SendMessage(main_window_handle, message, w_param, l_wapam);
  }
  //�@���Ƃ��Ƃ̃v���V�[�W���ɂ�����B
  return CallWindowProc(default_button_window_proc_handle, hwnd, message, w_param, l_wapam);
}

//���C���E�B���h�E�̃v���V�[�W���B�E�B���h�E�N���X��lpfnWndProc�ɂ��̊֐��̃|�C���^�����Ă����Ȃ��ƁA�L���ɂȂ�Ȃ��B
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_wapam)
{
  static PAINTSTRUCT paint_struct; 
  static HDC device_context_handle;
  switch (message)
  {
  case WM_CHAR:
  {
    if (w_param == TEXT('s'))
    { // �X�^�[�g/�X�g�b�v����B
      OnStartStop();
    }
    else if (w_param == TEXT('r'))
    { //���Z�b�g����
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
      MessageBox(hwnd, TEXT("�������܂��傤"), TEXT("Kitty"), MB_OK);
      break;
    }
    }
    return 0;
  }

  case WM_DESTROY:
  {
    PostQuitMessage(21);     //���ꂪ���s�����ƁA���b�Z�[�W�L���[��VM_QUIT���b�Z�[�W���|�X�g�����B
                             //������0�́AVM_QUIT���b�Z�[�W��wPARAM�̒l�ɂȂ�B
    return 0;
  }

  case WM_PAINT:
  {
    device_context_handle = BeginPaint(main_window_handle, &paint_struct);
    SelectObject(device_context_handle, font_handle);
    TextOut(
      device_context_handle,      //�f�o�C�X�R���e�L�X�g�n���h��
      10,                         //�\�������̈ʒux
      20,                         //�\�������̈ʒuy
      (LPCWSTR)display_time,                        //�\������
      lstrlen((LPCWSTR)display_time)                //�\�������̕�����
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

  //�o�ߎ��ԕ`��͈̔͂��w�肷��B
  SetRect(&elapsed_time_rect, 10, 20, 250, 100);

  //�o�ߎ��Ԃ̃t�H���g���w�肷��B
  font_handle = CreateFont(
    60, 20, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
    VARIABLE_PITCH | FF_ROMAN, NULL
  );

  //�E�B���h�E�N���X�쐬
  WNDCLASS window_class;
  window_class.style = CS_HREDRAW | CS_VREDRAW;  //�E�B���h�E���g��k�������ƍĕ`�悳���B
  window_class.lpfnWndProc = MainWndProc;      //�E�B���h�E�v���V�[�W����ݒ�B
  window_class.cbClsExtra = 0;                   //�E�B���h�E�N���X�̒ǉ��̈���o�C�g�P�ʂŎw��
  window_class.cbWndExtra = 0;                   //����
  window_class.hInstance = hInstance;             //�C���X�^���X�n���h��
  window_class.hIcon = LoadIcon(NULL, IDI_ERROR);  //�A�C�R���̐ݒ�i���̃o�[�ɏo���j
  window_class.hCursor = LoadCursor(NULL, IDC_HELP); //�}�E�X�J�[�\���̃n���h�����w��
                                                      //��������NULL�ő������ɒ萔�����邱�Ƃɂ��A
                                                      //�V�X�e���Œ�`����Ă���J�[�\�����w��ł���BIDC_ARROW�͕W���̂��
                                                      //�����\���ɂ����荻���v�ɂ�����ł���B
  window_class.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�N���C�A���g�G���A�̔w�i�F���w��B
  //�u���V�̃n���h����n���B���łɂ���u���V�̃n���h���́AGetStockObject�Ŏ擾�ł���B
  window_class.lpszMenuName = NULL;              //���j���[��n���B���j���[�͂Ȃ��̂�NULL
  window_class.lpszClassName = TEXT("�E�B���h�E�N���X���ł�");  //�E�B���h�E�N���X�̖��O���w��

  //�쐬�����E�B���h�E�N���X��o�^
  ATOM atom = RegisterClass(&window_class);
  if (atom == NULL)
  {
    return 0; //�G���[�`�F�b�N�Batom��NULL��������E�B���h�E�N���X�o�^���s�Ȃ̂ŁA�v���O�����I���B
  }

  main_window_handle = CreateWindowEx(
    WS_EX_COMPOSITED,                //������h�~
    TEXT("�E�B���h�E�N���X���ł�"),  //�E�B���h�E�N���X���BlpsxClssName�̕�������w��
    TEXT("�E�B���h�E����"),      //�E�B���h�E��
    WS_OVERLAPPEDWINDOW | WS_VISIBLE, //�E�B���h�E�̃X�^�C���B�g�ƃ^�C�g�������E�B���h�E
    100, 100, 400, 140,          //�\��������W�ƕ����w��
    NULL, NULL,                    //�e�E�B���h�E�ƃ��j���[�͂Ȃ��̂ŁANULL
    hInstance,                   //�C���X�^���X�n���h��
    NULL                         //���b�Z�[�W�̃p�����[�^�B�Ȃ��̂�NULL
  );

  if (main_window_handle == NULL)
  {
    return 0; //�G���[�`�F�b�N�Bwindow_handle��NULL��������E�B���h�E�N���X�쐬���s�Ȃ̂ŁA�v���O�����I���B
  }

  HWND start_button_handle = CreateWindow(
    TEXT("BUTTON"),         //�E�B���h�E�N���X���B�p�ӂ���Ă���{�^�����g���B
    TEXT("�X�^�[�g/�X�g�b�v"),       //�E�B���h�E��
    WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, //�q�ɂ��邽�߁AWS_CHILD�BBS_PUSHBUTTON
    250, 10, 120, 40,
    main_window_handle,           //�e�E�B���h�E�̃n���h���w��
    (HMENU)START_STOP_BUTTON,        //���j���[�ł͂Ȃ��A�{�^���E�B���h�E��ID�����߂�B
    hInstance,              //�C���X�^���X�n���h��
    NULL                    //���j���[(�Ȃ�)
  );

  HWND reset_button_handle = CreateWindow(
    TEXT("BUTTON"),         //�E�B���h�E�N���X���B�p�ӂ���Ă���{�^�����g���B
    TEXT("���Z�b�g"),       //�E�B���h�E��
    WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, //�q�ɂ��邽�߁AWS_CHILD�BBS_PUSHBUTTON
    250, 60, 40, 30,
    main_window_handle,           //�e�E�B���h�E�̃n���h���w��
    (HMENU)RESET_BUTTON,      //���j���[�ł͂Ȃ��A�{�^���E�B���h�E��ID�����߂�B
    hInstance,              //�C���X�^���X�n���h��
    NULL                    //���j���[(�Ȃ�)
  );

  HWND record_button_handle = CreateWindow(
    TEXT("BUTTON"),         //�E�B���h�E�N���X���B�p�ӂ���Ă���{�^�����g���B
    TEXT("�L�^"),       //�E�B���h�E��
    WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, //�q�ɂ��邽�߁AWS_CHILD�BBS_PUSHBUTTON
    300, 60, 70, 30,
    main_window_handle,           //�e�E�B���h�E�̃n���h���w��
    (HMENU)RECORD_BUTTON,           //���j���[�ł͂Ȃ��A�{�^���E�B���h�E��ID�����߂�B
    hInstance,              //�C���X�^���X�n���h��
    NULL                    //���j���[(�Ȃ�)
  );

  // �{�^���̃E�B���h�E�v���V�[�W�����擾(3�̃{�^���͂��ׂċ��ʂ̃v���V�[�W���Ȃ̂ł����������ł悢)
  default_button_window_proc_handle = (WNDPROC)GetWindowLong(start_button_handle, GWL_WNDPROC);
  
  // �{�^���̃E�B���h�E�v���V�[�W���������ւ���B
  SetWindowLong(start_button_handle, GWL_WNDPROC, (long)CustomButtonProc);
  SetWindowLong(reset_button_handle, GWL_WNDPROC, (long)CustomButtonProc);
  SetWindowLong(record_button_handle, GWL_WNDPROC, (long)CustomButtonProc);

  MSG msg;
  int result;
  while (TRUE)
  {
    //���b�Z�[�W���󂯎��
    result = GetMessage(
      &msg,    // �󂯎�������b�Z�[�W���i�[����ϐ��̃A�h���X
      NULL,     // ���b�Z�[�W���󂯎��E�B���h�E�̃n���h�����w��
               // NULL���w�肷��ƁA�A�v���P�[�V�������\������
               // ���ׂẴE�B���h�E�̃��b�Z�[�W���擾����B)
      0,       // �󂯎�郁�b�Z�[�W�̍ŏ��l�B0�͐����Ȃ�
      0        // �󂯎�郁�b�Z�[�W�̍ő�l�B0�͐����Ȃ��B
    );
    if (result == 0)
    {
      //GetMessage��WM_QUIT���󂯎��Ɩ߂�l��0�ɂȂ�̂ŁA���̂Ƃ��B
      //���C���֐��ɁAwPARAM�̒l��߂��āA�v���O�������I������B
      return msg.wParam;
    }
    //���z�L�[�R�[�h�����ۂ̕����ɕϊ�
    TranslateMessage(&msg);
    //�f�B�X�p�b�`��A��̃E�B���h�E�v���V�[�W�������s�����B
    DispatchMessage(&msg);
  }

  return 0;
}

void OnStartStop() 
{
  if(stop_watch.is_measuring())
  { // �X�g�b�v
    //�v���I��
    stop_watch.Stop();

    //�X���b�h���I��������B
    thread_end_flg = 1;
  }
  else
  { // �X�^�[�g
    //�X���b�h���쐬����B
    thread_end_flg = 0;
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)PaintElapsedTime, NULL, 0, NULL);

    //�v���J�n
    stop_watch.Start();
  }
}

void OnReset()
{
  //�X���b�h���I��������B
  thread_end_flg = 1;

  stop_watch.Reset();
  display_time = TEXT("00:00:00:000");
  InvalidateRect(main_window_handle, NULL, TRUE);  //�̈斳����
}