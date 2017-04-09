#pragma once
#include<chrono>
#include<string>

using namespace std;

class Time
{
public:
  Time();
  Time(chrono::milliseconds time);
  ~Time();

  string ToString();

  wchar_t* ToWCharArray();

  int ToInt();

  chrono::milliseconds ToMilliseconds();

  void SetTime(chrono::milliseconds time);

  void Clear();

private:
  chrono::milliseconds sum_time;

  chrono::milliseconds milli_seconds;

  chrono::seconds seconds;

  chrono::minutes minutes;

  chrono::hours hours;

  //tcharを返す時の文字列
  wchar_t record_time_display_format[50];

  //時間を入れる。
  void SetTimeDisplay();

  //int型のn桁目の値を取り出す
  int ExtractDigit(int number, int digit);
};

