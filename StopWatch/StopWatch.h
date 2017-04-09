#pragma once
#include"Time.h"

using namespace std;

class StopWatch
{
public:
  StopWatch();
  ~StopWatch();

  //計測を開始する。
  void Start();

  //計測を終了し、timeに計測結果を入れる。
  void Stop();

  //リセットする。
  void Reset();

  //スタート状態：1, それ以外:0
  int is_started;

  void MeasureTime();

  //計測した記録
  Time time;
private:

  //最後にストップした時の記録
  milliseconds last_stop_time;

  //計測開始時間
  chrono::time_point<chrono::system_clock> start_time_point;
};

