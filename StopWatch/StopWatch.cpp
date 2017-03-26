#include "stdafx.h"
#include "StopWatch.h"

using namespace std::chrono;
using namespace std;

StopWatch::StopWatch()
{
  start_time = time_point<system_clock>::min();
  stop_time = time_point<system_clock>::min();
  record = record.zero();
}


StopWatch::~StopWatch()
{
}


void StopWatch::Start()
{
  this->is_started = 1;
  this->start_time = system_clock::now();
}

void StopWatch::Stop()
{
  stop_time = system_clock::now();
  auto diff = stop_time - start_time;
  record = duration_cast<milliseconds>(diff + record);
  this->is_started = 0;
}

void StopWatch::Reset()
{
  is_started = 0;
  record = record.zero();
  start_time = time_point<system_clock>::min();
}

int StopWatch::GetRecord()
{
  return this->record.count();
}

string StopWatch::GetRecordString()
{
  return to_string(record.count());
}

int StopWatch::GetElapsedTime()
{
  time_point<system_clock> now_time = system_clock::now();
  auto diff = now_time - start_time;
  milliseconds elapsedTime = duration_cast<milliseconds>(diff + record);
  return elapsedTime.count();
}

string StopWatch::GetElapsedTimeString()
{
  int elapsed_time = GetElapsedTime();
  return to_string(elapsed_time);
}

