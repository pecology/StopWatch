
#include "stdafx.h"

//�E�B���h�E�v���V�[�W���B�E�B���h�E�N���X��lpfnWndProc�ɂ��̊֐��̃|�C���^�����Ă����Ȃ��ƁA�L���ɂȂ�Ȃ��B
LRESULT CALLBACK MyWndProc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_wapam)
{
  if (message == WM_DESTROY)
  { //�E�B���h�E�E��́~�������ꂽ�Ƃ��ɁAWM_DESTROY���|�X�g�����̂ŁA���̂Ƃ��B
    MessageBox(hwnd, TEXT("�I���ɂ��"),
      TEXT("Kitty"), MB_ICONINFORMATION);
    PostQuitMessage(21);     //���ꂪ���s�����ƁA���b�Z�[�W�L���[��VM_QUIT���b�Z�[�W���|�X�g�����B
                            //������0�́AVM_QUIT���b�Z�[�W��wPARAM�̒l�ɂȂ�B
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
  window_class.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //�N���C�A���g�G���A�̔w�i�F���w��B
  //�u���V�̃n���h����n���B���łɂ���u���V�̃n���h���́AGetStockObject�Ŏ擾�ł���B
  window_class.lpszMenuName = NULL;              //���j���[��n���B���j���[�͂Ȃ��̂�NULL
  window_class.lpszClassName = TEXT("�E�B���h�E�N���X���ł�");  //�E�B���h�E�N���X�̖��O���w��

  //�쐬�����E�B���h�E�N���X��o�^
  ATOM atom = RegisterClass(&window_class);
  if (atom == NULL)
  {
    return 0; //�G���[�`�F�b�N�Batom��NULL��������E�B���h�E�N���X�o�^���s�Ȃ̂ŁA�v���O�����I���B
  }

  HWND window_handle = CreateWindow(
    TEXT("�E�B���h�E�N���X���ł�"),  //�E�B���h�E�N���X���BlpsxClssName�̕�������w��
    TEXT("�E�B���h�E����"),      //�E�B���h�E��
    WS_OVERLAPPEDWINDOW | WS_VISIBLE, //�E�B���h�E�̃X�^�C���B�g�ƃ^�C�g�������E�B���h�E
    100, 100, 200, 200,          //�\��������W�ƕ����w��
    NULL, NULL,                    //�e�E�B���h�E�ƃ��j���[�͂Ȃ��̂ŁANULL
    hInstance,                   //�C���X�^���X�n���h��
    NULL                         //���b�Z�[�W�̃p�����[�^�B�Ȃ��̂�NULL
  );

  if (window_handle == NULL)
  {
    return 0; //�G���[�`�F�b�N�Bwindow_handle��NULL��������E�B���h�E�N���X�쐬���s�Ȃ̂ŁA�v���O�����I���B
  }

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