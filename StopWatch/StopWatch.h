#pragma once
#include"Time.h"

using namespace std;

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

  //�X�^�[�g��ԁF1, ����ȊO:0
  int is_started;

  void MeasureTime();

  //�v�������L�^
  Time time;
private:

  //�Ō�ɃX�g�b�v�������̋L�^
  milliseconds last_stop_time;

  //�v���J�n����
  chrono::time_point<chrono::system_clock> start_time_point;
};

