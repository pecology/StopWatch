#pragma once
#include"Time.h"

//ストップウォッチクラス
//使い方
//  1.Start()を呼ぶ。
//  2.待つ。
//  3.Stop()を呼ぶ。Timeクラスのオブジェクトが戻るので、To何とか関数を呼ぶ。
//  4.Start()を呼んでからStop()を呼ぶまでの時間が取得できる。
//補足1.計測中に経過時間を取得したい場合、MeasureTime()関数を呼ぶと、スタートしてから経過した時間を取得できる。
//補足2.Stop()を呼んだ後も計測結果は保存されており、再びStart()を呼ぶと、以前の結果から計測が再開される。
//補足3.記録を消去したい場合は、Reset()を呼ぶ。
class StopWatch
{
public:
  StopWatch();
  ~StopWatch();

  //計測を開始する。
  //以前にStop()が呼ばれている場合、以前の経過時間から計測を再開する。
  //計測中にこの関数が呼ばれた場合、何もしない。
  void Start();

  //計測を終了し、計測結果を返す。
  //計測中でないときにこの関数が呼ばれた場合、何もしない。
  Time& Stop();

  //計測結果をリセットする。
  //計測中に呼ばれたときは、計測を中断して計測結果をリセットする。
  void Reset();

  //計測中であるかどうか。
  //0:計測中でない
  //1;計測中
  int is_measuring();

  //関数が呼ばれた時点での経過時間を返す。
  //この関数が呼ばれた後も計測は止まらない。
  Time& MeasureTime();

private:
  //計測結果を格納する変数
  Time time;

  //最後にストップした時の計測結果
  std::chrono::milliseconds last_stop_time;

  //計測開始時刻
  std::chrono::time_point<std::chrono::system_clock> start_time_point;

  //計測中であるかどうか。
  //0:計測中でない
  //1;計測中
  int is_measuring_flg;
};

