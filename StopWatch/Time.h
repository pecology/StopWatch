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

  //tchar��Ԃ����̕�����
  wchar_t record_time_display_format[50];

  //���Ԃ�����B
  void SetTimeDisplay();

  //int�^��n���ڂ̒l�����o��
  int ExtractDigit(int number, int digit);
};

