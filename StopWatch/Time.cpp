#include "Time.h"

using namespace std;
using namespace std::chrono;

Time::Time()
{
}

Time::Time(milliseconds time)
{
  this->milli_seconds = time;
}


Time::~Time()
{
}

string Time::ToString()
{
  return to_string(ToInt());
}

wchar_t * Time::ToWCharArray()
{
  SetTimeDisplay();
  return record_time_display_format;
}

int Time::ToInt()
{
  return (int)(milli_seconds.count());
}

milliseconds Time::ToMilliseconds()
{
  return sum_time;
}

void Time::SetTime(milliseconds time)
{
  this->sum_time = time;

  this->hours = chrono::duration_cast<chrono::hours>(time);
  this->minutes = chrono::duration_cast<chrono::minutes>(time) - hours;
  this->seconds = chrono::duration_cast<chrono::seconds>(time) - hours - minutes;
  this->milli_seconds = time - hours - minutes - seconds;
}

void Time::Clear()
{
  hours = hours.zero();
  minutes = minutes.zero();
  seconds = seconds.zero();
  milli_seconds = milli_seconds.zero();
}

void Time::SetTimeDisplay()
{
  //時間のi桁目をi番目に入れる。
  int time_number[10];
  time_number[1] = ExtractDigit((int)(milli_seconds.count()), 1);
  time_number[2] = ExtractDigit((int)(milli_seconds.count()), 2);
  time_number[3] = ExtractDigit((int)(milli_seconds.count()), 3);
  time_number[4] = ExtractDigit((int)(seconds.count()), 1);
  time_number[5] = ExtractDigit((int)(seconds.count()), 2);
  time_number[6] = ExtractDigit(minutes.count(), 1);
  time_number[7] = ExtractDigit(minutes.count(), 2);
  time_number[8] = ExtractDigit(hours.count(), 1);
  time_number[9] = ExtractDigit(hours.count(), 2);

  //整形してセット
  swprintf_s(this->record_time_display_format, sizeof(wchar_t[13]),
    L"%d%d:%d%d:%d%d:%d%d%d", time_number[9],
    time_number[8], time_number[7], time_number[6], time_number[5],
    time_number[4], time_number[3], time_number[2], time_number[1]);
}

int Time::ExtractDigit(int number, int digit)
{
  int divisor = (int)pow(10, digit);
  int return_num = (number % divisor) / (divisor / 10);
  return return_num;
}
