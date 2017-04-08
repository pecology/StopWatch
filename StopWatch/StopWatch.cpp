#include "StopWatch.h"

using namespace std;

StopWatch::StopWatch()
{
  start_time_point = chrono::time_point<chrono::system_clock>::min();
  time = time.zero();
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
  time = MeasureTime();
  last_stop_time = time;
  this->is_started = 0;
}

void StopWatch::Reset()
{
  is_started = 0;
  time = time.zero();
  last_stop_time = last_stop_time.zero();
  start_time_point = chrono::time_point<chrono::system_clock>::min();
}

string StopWatch::GetTimeString()
{
  return to_string(GetTime());
}

int StopWatch::GetTime()
{
  time = MeasureTime();
  return time.count();
}

wchar_t *StopWatch::GetTimeDisplay()
{
  time = MeasureTime();
  SetTimeDisplay(time.count());
  return record_time_display_format;
}

void StopWatch::SetTimeDisplay(int time)
{
  //時間のi桁目をi番目に入れる。
  int time_number[10];
  for (int i = 1; i < 10; i++)
  {
    time_number[i] = ExtractDigit(time, i);
  }

  //整形してセット
  swprintf_s(record_time_display_format, sizeof(wchar_t[13]),
               L"%d%d:%d%d:%d%d:%d%d%d", time_number[9],
    time_number[8], time_number[7], time_number[6], time_number[5],
    time_number[4], time_number[3], time_number[2], time_number[1]);
}

int StopWatch::ExtractDigit(int number, int digit)
{
  int divisor = (int)pow(10, digit);
  int return_num = (number % divisor) / (divisor / 10);
  return return_num;
}

milliseconds StopWatch::MeasureTime()
{
  //現在時刻を取得
  chrono::time_point<chrono::system_clock> now_time_point = chrono::system_clock::now();

  //スタートしてから経過した時間を計算
  auto time_after_start = now_time_point - start_time_point;

  //以前に停止を押したときの記録 + スタートしてから経過した時間
  milliseconds time = last_stop_time + chrono::duration_cast<milliseconds>(time_after_start);
  return time;
}