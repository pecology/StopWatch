#include "StopWatch.h"

using namespace std::chrono;
using namespace std;

StopWatch::StopWatch()
{
  start_time = time_point<system_clock>::min();
  record = record.zero();
  record_time_display_format = new wchar_t[15];
}


StopWatch::~StopWatch()
{
  delete[] record_time_display_format;
}


void StopWatch::Start()
{
  this->is_started = 1;
  this->start_time = system_clock::now();
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
  start_time = time_point<system_clock>::min();
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
  int num[10];
  for (int i = 1; i < 10; i++)
  {
    num[i] = ExtractDigit(time, i);
  }

  swprintf_s(record_time_display_format, 100,
               L"%d%d:%d%d:%d%d:%d%d%d", num[9],
    num[8], num[7], num[6], num[5], num[4], num[3], num[2], num[1]);
}

int StopWatch::ExtractDigit(int number, int digit)
{
  int divisor = pow(10, digit);
  int return_num = (number % divisor) / (divisor / 10);
  return return_num;
}


milliseconds StopWatch::GetElapsedTimeDuration()
{
  time_point<system_clock> now_time = system_clock::now();
  auto diff = now_time - start_time;
  milliseconds elapsedTime = duration_cast<milliseconds>(diff + record);
  return elapsedTime;
}

string StopWatch::GetElapsedTimeString()
{
  int elapsed_time = GetElapsedTime();
  return to_string(elapsed_time);
}