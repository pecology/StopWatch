#pragma once
#include<chrono>
#include<string>

using namespace std;

typedef chrono::duration<int, milli> milliseconds;

class StopWatch
{
public:
  StopWatch();
  ~StopWatch();

  //計測を開始する
  void Start();

  //計測を終了し、recordに計測結果を入れる。
  void Stop();

  //計測結果を1ミリ秒単位で取得する。
  int GetRecord();

  //リセットする。
  void Reset();

  //計測結果をミリ秒単位で取得する。
  string GetRecordString();

  //経過時間をミリ秒単位で取得する。
  int GetElapsedTime();

  //経過時間をミリ秒単位で取得する。
  string GetElapsedTimeString();

  wchar_t *GetElapsedTimeDisplay();

  //スタート状態：1, それ以外:0
  int is_started;

private:
  //時間を入れる。
  void SetRecordTimeDisplayFormat(int time);

  //int型のn桁目の値を取り出す
  int ExtractDigit(int number, int digit);

  milliseconds GetElapsedTimeDuration();

  //計測した記録
  milliseconds record;

  //tcharを返す時の文字列
  wchar_t record_time_display_format[100];

  //計測開始時間
  chrono::time_point<chrono::system_clock> start_time;
};

