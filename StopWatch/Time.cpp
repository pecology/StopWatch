#include "Time.h"


Time::Time()
{
}

Time::Time(milliseconds time)
{
  this->time = time;
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
  SetTimeDisplay(ToInt());
  return record_time_display_format;
}

int Time::ToInt()
{
  return time.count();
}

milliseconds Time::ToMilliseconds()
{
  return time;
}

void Time::SetTime(milliseconds time)
{
  this->time = time;
}

void Time::Clear()
{
  time = time.zero();
}

void Time::SetTimeDisplay(int time)
{
  //時間のi桁目をi番目に入れる。
  int time_number[10];
  for (int i = 1; i < 10; i++)
  {
    time_number[i] = ExtractDigit(time, i);
  }

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
