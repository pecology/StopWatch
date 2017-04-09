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

  //tchar��Ԃ����̕�����
  wchar_t record_time_display_format[50];

  //���Ԃ�����B
  void SetTimeDisplay();

  //int�^��n���ڂ̒l�����o��
  int ExtractDigit(int number, int digit);
};

