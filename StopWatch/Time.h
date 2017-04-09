#pragma once
#include<chrono>
#include<string>

class Time
{
public:
  Time();
  Time(std::chrono::milliseconds time);
  ~Time();

  std::string ToString();

  wchar_t* ToWCharArray();

  int ToInt();

  std::chrono::milliseconds ToMilliseconds();

  void SetTime(std::chrono::milliseconds time);

  void Clear();

private:
  std::chrono::milliseconds sum_time;

  std::chrono::milliseconds milli_seconds;

  std::chrono::seconds seconds;

  std::chrono::minutes minutes;

  std::chrono::hours hours;

  //tcharを返す時の文字列
  wchar_t record_time_display_format[50];

  //時間を入れる。
  void SetTimeDisplay();

  //int型のn桁目の値を取り出す
  int ExtractDigit(int number, int digit);
};

