
#include "stdafx.h"
#include "main.h"

//�E�B���h�E�n���h��
HWND window_handle;
//�C���X�^���X�n���h��
HINSTANCE instance_handle;
//�X���b�h���̃t���O
int flg = 1;

//�X���b�h
DWORD WINAPI MyThread(LPVOID *data)
{
  int count = 0;
  TCHAR buf[1000] = TEXT("");
  PAINTSTRUCT paint_struct;
  HFONT font_handle;
  while (flg)
  {
    InvalidateRect(window_handle, NULL, TRUE);  //�̈斳����
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
      device_context_handle,      //�f�o�C�X�R���e�L�X�g�n���h��
      10,                         //�\�������̈ʒux
      20,                         //�\�������̈ʒuy
      buf,                        //�\������
      lstrlen(buf)                //�\�������̕�����
    );
    SelectObject(device_context_handle, GetStockObject(SYSTEM_FONT));
    DeleteObject(font_handle);
    EndPaint(window_handle, &paint_struct);
    count++;
    Sleep(100);
  }
  ExitThread(0);
}


//�E�B���h�E�v���V�[�W���B�E�B���h�E�N���X��lpfnWndProc�ɂ��̊֐��̃|�C���^�����Ă����Ȃ��ƁA�L���ɂȂ�Ȃ��B
LRESULT CALLBACK MyWndProc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_wapam)
{
  static HANDLE thread;
  switch (message)
  {
  case WM_CREATE:
  {
    thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MyThread, (LPVOID)TEXT("�J�E���g:"), 0, NULL);
  }
  case WM_COMMAND:
  {
    switch (LOWORD(w_param))
    {
    case START_STOP_BUTTON:
    {
      MessageBox(hwnd, TEXT("�X�^�[�g/�X�g�b�v�{�^��"), TEXT("Kitty"), MB_OK);
      break;
    }
    case RESET_BUTTON:
    {
      MessageBox(hwnd, TEXT("���Z�b�g�{�^��"), TEXT("Kitty"), MB_OK);
      break;
    }
    case RECORD_BUTTON:
    {
      MessageBox(hwnd, TEXT("�L�^�{�^��"), TEXT("Kitty"), MB_OK);
      break;
    }
    }
    return 0;
  }

  case WM_LBUTTONUP:
  {
    thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MyThread, (LPVOID)TEXT("�J�E���g:"), 0, NULL);
    HDC device_context_handle;
    LPCTSTR str = TEXT("����ɂ���!!");
    device_context_handle = GetDC(hwnd);
    TextOut(
      device_context_handle,      //�f�o�C�X�R���e�L�X�g�n���h��
      10,                         //�\�������̈ʒux
      10,                         //�\�������̈ʒuy
      str,                        //�\������
      lstrlen(str)                //�\�������̕�����
    );
    ReleaseDC(hwnd, device_context_handle);
    return 0;
  }

  case WM_DESTROY:
  {
    MessageBox(hwnd, TEXT("�I���ɂ��"),
      TEXT("Kitty"), MB_ICONINFORMATION);
    PostQuitMessage(21);     //���ꂪ���s�����ƁA���b�Z�[�W�L���[��VM_QUIT���b�Z�[�W���|�X�g�����B
                             //������0�́AVM_QUIT���b�Z�[�W��wPARAM�̒l�ɂȂ�B
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

  //�E�B���h�E�N���X�쐬
  WNDCLASS window_class;
  window_class.style = CS_HREDRAW | CS_VREDRAW;  //�E�B���h�E���g��k�������ƍĕ`�悳���B
  window_class.lpfnWndProc = MyWndProc;      //�E�B���h�E�v���V�[�W����ݒ�B
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

  window_handle = CreateWindow(
    TEXT("�E�B���h�E�N���X���ł�"),  //�E�B���h�E�N���X���BlpsxClssName�̕�������w��
    TEXT("�E�B���h�E����"),      //�E�B���h�E��
    WS_OVERLAPPEDWINDOW | WS_VISIBLE, //�E�B���h�E�̃X�^�C���B�g�ƃ^�C�g�������E�B���h�E
    100, 100, 400, 140,          //�\��������W�ƕ����w��
    NULL, NULL,                    //�e�E�B���h�E�ƃ��j���[�͂Ȃ��̂ŁANULL
    hInstance,                   //�C���X�^���X�n���h��
    NULL                         //���b�Z�[�W�̃p�����[�^�B�Ȃ��̂�NULL
  );

  if (window_handle == NULL)
  {
    return 0; //�G���[�`�F�b�N�Bwindow_handle��NULL��������E�B���h�E�N���X�쐬���s�Ȃ̂ŁA�v���O�����I���B
  }

  HWND start_button_handle = CreateWindow(
    TEXT("BUTTON"),         //�E�B���h�E�N���X���B�p�ӂ���Ă���{�^�����g���B
    TEXT("�X�^�[�g/�X�g�b�v"),       //�E�B���h�E��
    WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, //�q�ɂ��邽�߁AWS_CHILD�BBS_PUSHBUTTON
    220, 10, 150, 40,
    window_handle,           //�e�E�B���h�E�̃n���h���w��
    (HMENU)START_STOP_BUTTON,        //���j���[�ł͂Ȃ��A�{�^���E�B���h�E��ID�����߂�B
    hInstance,              //�C���X�^���X�n���h��
    NULL                    //���j���[(�Ȃ�)
  );

  HWND reset_button_handle = CreateWindow(
    TEXT("BUTTON"),         //�E�B���h�E�N���X���B�p�ӂ���Ă���{�^�����g���B
    TEXT("���Z�b�g"),       //�E�B���h�E��
    WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, //�q�ɂ��邽�߁AWS_CHILD�BBS_PUSHBUTTON
    220, 60, 70, 30,
    window_handle,           //�e�E�B���h�E�̃n���h���w��
    (HMENU)RESET_BUTTON,      //���j���[�ł͂Ȃ��A�{�^���E�B���h�E��ID�����߂�B
    hInstance,              //�C���X�^���X�n���h��
    NULL                    //���j���[(�Ȃ�)
  );

  HWND record_button_handle = CreateWindow(
    TEXT("BUTTON"),         //�E�B���h�E�N���X���B�p�ӂ���Ă���{�^�����g���B
    TEXT("�L�^"),       //�E�B���h�E��
    WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, //�q�ɂ��邽�߁AWS_CHILD�BBS_PUSHBUTTON
    300, 60, 70, 30,
    window_handle,           //�e�E�B���h�E�̃n���h���w��
    (HMENU)RECORD_BUTTON,           //���j���[�ł͂Ȃ��A�{�^���E�B���h�E��ID�����߂�B
    hInstance,              //�C���X�^���X�n���h��
    NULL                    //���j���[(�Ȃ�)
  );

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
    //�f�B�X�p�b�`��A��̃E�B���h�E�v���V�[�W�������s�����B
    DispatchMessage(&msg);
  }

  return 0;
}