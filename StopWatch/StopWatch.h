#pragma once
#include<chrono>
#include<string>

using namespace std::chrono;
using namespace std;
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

  //�v�����ʂ��~���b�P�ʂŎ擾����B
  string GetRecordString();

  //�o�ߎ��Ԃ��~���b�P�ʂŎ擾����B
  int GetElapsedTime();

  //�o�ߎ��Ԃ��~���b�P�ʂŎ擾����B
  string GetElapsedTimeString();

private:
  //�v�������L�^
  milliseconds record;

  //�X�^�[�g��ԁF1, ����ȊO:0
  int is_started;

  //�v���J�n����
  time_point<system_clock> start_time;
};

