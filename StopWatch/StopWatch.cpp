#include "StopWatch.h"

using namespace std;
using namespace std::chrono;

StopWatch::StopWatch()
{
  start_time_point = chrono::time_point<chrono::system_clock>::min();
  time.Clear();
  last_stop_time = last_stop_time.zero();
}

StopWatch::~StopWatch()
{
}


void StopWatch::Start()
{
  this->is_started = 1;
  this->start_time_point = chrono::system_clock::now();
}

void StopWatch::Stop()
{
  MeasureTime();
  last_stop_time = time.ToMilliseconds();
  this->is_started = 0;
}

void StopWatch::Reset()
{
  is_started = 0;
  time.Clear();
  last_stop_time = last_stop_time.zero();
  start_time_point = chrono::time_point<chrono::system_clock>::min();
}

void StopWatch::MeasureTime()
{
  //���ݎ������擾
  chrono::time_point<chrono::system_clock> now_time_point = chrono::system_clock::now();

  //�X�^�[�g���Ă���o�߂������Ԃ��v�Z
  auto time_after_start = now_time_point - start_time_point;

  //�ȑO�ɒ�~���������Ƃ��̋L�^ + �X�^�[�g���Ă���o�߂�������
  milliseconds time = last_stop_time +  chrono::duration_cast<milliseconds>(time_after_start);

  this->time.SetTime(time);
}