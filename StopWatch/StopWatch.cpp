#include "StopWatch.h"

using namespace std;
using namespace std::chrono;

StopWatch::StopWatch()
{
  //スタート時の時刻を初期化する。
  start_time_point = chrono::time_point<chrono::system_clock>::min();

  //計測結果の変数を初期化する。
  time.Clear();

  //以前の計測結果を初期化する。
  last_stop_time = last_stop_time.zero();
}

StopWatch::~StopWatch()
{
}

void StopWatch::Start()
{
  //計測中でないとき
  if (!is_measuring_flg)
  {
    //スタート開始時の時刻を保存する。
    start_time_point = chrono::system_clock::now();
    is_measuring_flg = 1;
  }
}

Time& StopWatch::Stop()
{
  //計測中の時
  if (is_measuring_flg)
  {
    //計測結果を取得する。
    MeasureTime();

    //計測結果を保存する。
    last_stop_time = time.ToMilliseconds();

    //計測中でない状態にする。
    this->is_measuring_flg = 0;
  }

  return time;
}

void StopWatch::Reset()
{
  //計測中でない状態にする。
  is_measuring_flg = 0;

  //計測結果をリセットする。
  time.Clear();
  last_stop_time = last_stop_time.zero();
  //計測開始時刻もリセットする。
  start_time_point = chrono::time_point<chrono::system_clock>::min();
}

int StopWatch::is_measuring()
{
  return is_measuring_flg;
}

Time& StopWatch::MeasureTime()
{
  //現在時刻を取得
  chrono::time_point<chrono::system_clock> now_time_point = chrono::system_clock::now();

  //スタートしてから経過した時間を計算
  auto time_after_start = now_time_point - start_time_point;

  //以前にストップしたときの記録 + スタートしてから経過した時間
  milliseconds time = last_stop_time +  chrono::duration_cast<milliseconds>(time_after_start);

  //結果をメンバ変数にセットする。
  this->time.SetTime(time);

  return this->time;
}