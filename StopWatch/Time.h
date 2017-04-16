#pragma once
#include<chrono>
#include<string>

//StopWatchクラスで計測した時間を表すクラス。
class Time
{
public:
  Time();
  Time(std::chrono::milliseconds time);
  ~Time();

  //時間をstring型で取得する。
  std::string ToString();

  //時間をwchar_tのポインタで取得する。
  //形式は「時間2桁:分2桁:秒2桁:コンマ秒以下3桁」
  wchar_t* ToWCharArray();

  //時間をint型で取得する。
  int ToInt();

  //時間をmilliseconds型で取得する。
  std::chrono::milliseconds ToMilliseconds();

  //引数のmillisecondsをセットする。
  void SetTime(std::chrono::milliseconds time);

  void Clear();

private:
  //記録の合計
  std::chrono::milliseconds sum_time;

  //ミリ秒を格納する。(結果が2時間56分45秒234の場合は、234ミリ秒が入る。)
  std::chrono::milliseconds milli_seconds;

  //秒を格納する。(結果が2時間56分45秒234の場合は、45秒が入る。)
  std::chrono::seconds seconds;

  //分を格納する。(結果が2時間56分45秒234の場合は、56分が入る。)
  std::chrono::minutes minutes;

  //時間を格納する。(結果が2時間56分45秒234の場合は、2時間が入る。)
  std::chrono::hours hours;

  //tcharを返す時の文字列
  wchar_t wchar_array[30];

  //時間を入れる。
  void SetWcharArray();

  //numberのdisit桁目の値を取り出す。
  int ExtractDigit(int number, int digit);
};

