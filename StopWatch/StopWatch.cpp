#include "stdafx.h"
#include "StopWatch.h"

using namespace std::chrono;
using namespace std;

StopWatch::StopWatch()
{
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
  time_point<system_clock> stop_time = system_clock::now();
  auto diff = stop_time - start_time;
  record = duration_cast<milliseconds>(diff);
  this->is_started = 0;
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
  time_point<system_clock> stop_time = system_clock::now();
  auto diff = stop_time - start_time;
  milliseconds elapsedTime = duration_cast<milliseconds>(diff);
  return elapsedTime.count();
}

string StopWatch::GetElapsedTimeString()
{
  int elapsed_time = GetElapsedTime();
  return to_string(elapsed_time);
}

