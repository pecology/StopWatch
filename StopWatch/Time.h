#pragma once
#include<chrono>
#include<string>

//StopWatch�N���X�Ōv���������Ԃ�\���N���X�B
class Time
{
public:
  Time();
  Time(std::chrono::milliseconds time);
  ~Time();

  //���Ԃ�string�^�Ŏ擾����B
  std::string ToString();

  //���Ԃ�wchar_t�̃|�C���^�Ŏ擾����B
  //�`���́u����2��:��2��:�b2��:�R���}�b�ȉ�3���v
  wchar_t* ToWCharArray();

  //���Ԃ�int�^�Ŏ擾����B
  int ToInt();

  //���Ԃ�milliseconds�^�Ŏ擾����B
  std::chrono::milliseconds ToMilliseconds();

  //������milliseconds���Z�b�g����B
  void SetTime(std::chrono::milliseconds time);

  void Clear();

private:
  //�L�^�̍��v
  std::chrono::milliseconds sum_time;

  //�~���b���i�[����B(���ʂ�2����56��45�b234�̏ꍇ�́A234�~���b������B)
  std::chrono::milliseconds milli_seconds;

  //�b���i�[����B(���ʂ�2����56��45�b234�̏ꍇ�́A45�b������B)
  std::chrono::seconds seconds;

  //�����i�[����B(���ʂ�2����56��45�b234�̏ꍇ�́A56��������B)
  std::chrono::minutes minutes;

  //���Ԃ��i�[����B(���ʂ�2����56��45�b234�̏ꍇ�́A2���Ԃ�����B)
  std::chrono::hours hours;

  //tchar��Ԃ����̕�����
  wchar_t wchar_array[30];

  //���Ԃ�����B
  void SetWcharArray();

  //number��disit���ڂ̒l�����o���B
  int ExtractDigit(int number, int digit);
};

