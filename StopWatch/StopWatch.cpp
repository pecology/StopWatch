#include "StopWatch.h"

using namespace std;

StopWatch::StopWatch()
{
  start_time = chrono::time_point<chrono::system_clock>::min();
  record = record.zero();
}


StopWatch::~StopWatch()
{
}


void StopWatch::Start()
{
  this->is_started = 1;
  this->start_time = chrono::system_clock::now();
}

void StopWatch::Stop()
{
  record = GetElapsedTimeDuration();
  this->is_started = 0;
}

void StopWatch::Reset()
{
  is_started = 0;
  record = record.zero();
  start_time = chrono::time_point<chrono::system_clock>::min();
}

int StopWatch::GetRecord()
{
  return this->record.count();
}

string StopWatch::GetRecordString()
{
  return to_string(record.count());
}

int StopWatch::GetElapsedTime()
{
  milliseconds elapsedTime = GetElapsedTimeDuration();
  return elapsedTime.count();
}

wchar_t *StopWatch::GetElapsedTimeDisplay()
{
  int elapsedTime = GetElapsedTime();
  SetRecordTimeDisplayFormat(elapsedTime);
  return record_time_display_format;
}

void StopWatch::SetRecordTimeDisplayFormat(int time)
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


milliseconds StopWatch::GetElapsedTimeDuration()
{
  chrono::time_point<chrono::system_clock> now_time = chrono::system_clock::now();
  auto diff = now_time - start_time;
  milliseconds elapsedTime = chrono::duration_cast<milliseconds>(diff + record);
  return elapsedTime;
}

string StopWatch::GetElapsedTimeString()
{
  int elapsed_time = GetElapsedTime();
  return to_string(elapsed_time);
}