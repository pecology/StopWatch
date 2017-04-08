#pragma once
#include<chrono>
#include<string>

using namespace std;

typedef chrono::duration<int, milli> milliseconds;

class StopWatch
{
public:
  StopWatch();
  ~StopWatch();

  //�v�����J�n����B
  void Start();

  //�v�����I�����Atime�Ɍv�����ʂ�����B
  void Stop();

  //���Z�b�g����B
  void Reset();

  //�v�����ʂ��~���b�P�ʂŎ擾����B
  string GetTimeString();

  //�o�ߎ��Ԃ��~���b�P�ʂŎ擾����B
  int GetTime();

  wchar_t *GetTimeDisplay();

  //�X�^�[�g��ԁF1, ����ȊO:0
  int is_started;

private:
  //���Ԃ�����B
  void SetTimeDisplay(int time);

  //int�^��n���ڂ̒l�����o��
  int ExtractDigit(int number, int digit);

  milliseconds MeasureTime();

  //�v�������L�^
  milliseconds time;

  //�Ō�ɃX�g�b�v�������̋L�^
  milliseconds last_stop_time;

  //tchar��Ԃ����̕�����
  wchar_t record_time_display_format[100];

  //�v���J�n����
  chrono::time_point<chrono::system_clock> start_time_point;
};

