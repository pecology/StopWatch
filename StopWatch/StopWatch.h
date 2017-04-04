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

  //�v�����J�n����
  void Start();

  //�v�����I�����Arecord�Ɍv�����ʂ�����B
  void Stop();

  //�v�����ʂ�1�~���b�P�ʂŎ擾����B
  int GetRecord();

  //���Z�b�g����B
  void Reset();

  //�v�����ʂ��~���b�P�ʂŎ擾����B
  string GetRecordString();

  //�o�ߎ��Ԃ��~���b�P�ʂŎ擾����B
  int GetElapsedTime();

  //�o�ߎ��Ԃ��~���b�P�ʂŎ擾����B
  string GetElapsedTimeString();

  wchar_t *GetElapsedTimeDisplay();

  //�X�^�[�g��ԁF1, ����ȊO:0
  int is_started;

private:
  //���Ԃ�����B
  void SetRecordTimeDisplayFormat(int time);

  //int�^��n���ڂ̒l�����o��
  int ExtractDigit(int number, int digit);

  milliseconds GetElapsedTimeDuration();

  //�v�������L�^
  milliseconds record;

  //tchar��Ԃ����̕�����
  wchar_t record_time_display_format[100];

  //�v���J�n����
  chrono::time_point<chrono::system_clock> start_time;
};

