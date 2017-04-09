#pragma once
#include<chrono>
#include<string>

using namespace std;

typedef chrono::duration<int, milli> milliseconds;

class Time
{
public:
  Time();
  Time(milliseconds time);
  ~Time();

  string ToString();

  wchar_t* ToWCharArray();

  int ToInt();

  milliseconds ToMilliseconds();

  void SetTime(milliseconds time);

  void Clear();

private:
  milliseconds milli_seconds;

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

