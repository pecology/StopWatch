
#include "stdafx.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	int nCmdShow) 
{
	HWND window_handle = CreateWindow(
		TEXT("STATIC"),    //�E�B���h�E�N���X
		TEXT("�E�B���h�E����"), //�E�B���h�E��
		WS_CAPTION,       //�E�B���h�E�̃X�^�C��(CAPTION�́A�^�C�g���o�[�������)
		500,              //�����ʒu(x��)
		100,              //�����ʒu(y��)
		100,              //�E�B���h�E�̕�(x��)
		1000,              //�E�B���h�E�̕�(y��)
		NULL,             //�e�E�B���h�E�̃n���h��
		NULL,             //���j���[�̃n���h��
		hInstance,         //�C���X�^���X�n���h��(���C���̈����Ŏ󂯎��A�v���O�����̃n���h��)
		NULL              //���b�Z�[�W�ɓn�����p�����[�^
	);

	if (window_handle == NULL)
	{
		return 0; //�G���[�`�F�b�N�B�n���h����NULL��������G���[�Ȃ̂ŁA�v���O�����I���B
	}

	ShowWindow(window_handle, SW_SHOW);
	MessageBox(NULL, TEXT("Kitty on your lap"),
		TEXT("���b�Z�[�W�{�b�N�X"), MB_OK);
	return 0;
}