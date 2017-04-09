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
  milliseconds time;

  //tchar��Ԃ����̕�����
  wchar_t record_time_display_format[50];

  //���Ԃ�����B
  void SetTimeDisplay(int time);

  //int�^��n���ڂ̒l�����o��
  int ExtractDigit(int number, int digit);
};

