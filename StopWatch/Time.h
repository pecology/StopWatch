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

  //tchar‚ğ•Ô‚·‚Ì•¶š—ñ
  wchar_t record_time_display_format[50];

  //ŠÔ‚ğ“ü‚ê‚éB
  void SetTimeDisplay(int time);

  //intŒ^‚ÌnŒ…–Ú‚Ì’l‚ğæ‚èo‚·
  int ExtractDigit(int number, int digit);
};

