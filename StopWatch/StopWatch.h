#pragma once
#include<chrono>
#include<string>

using namespace std::chrono;
using namespace std;
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

  //計測結果をミリ秒単位で取得する。
  string GetRecordString();

  //経過時間をミリ秒単位で取得する。
  int GetElapsedTime();

  //経過時間をミリ秒単位で取得する。
  string GetElapsedTimeString();

private:
  //計測した記録
  milliseconds record;

  //スタート状態：1, それ以外:0
  int is_started;

  //計測開始時間
  time_point<system_clock> start_time;
};

