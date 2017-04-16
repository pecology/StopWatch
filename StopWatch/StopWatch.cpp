#include "StopWatch.h"

using namespace std;
using namespace std::chrono;

StopWatch::StopWatch()
{
  //�X�^�[�g���̎���������������B
  start_time_point = chrono::time_point<chrono::system_clock>::min();

  //�v�����ʂ̕ϐ�������������B
  time.Clear();

  //�ȑO�̌v�����ʂ�����������B
  last_stop_time = last_stop_time.zero();
}

StopWatch::~StopWatch()
{
}

void StopWatch::Start()
{
  //�v�����łȂ��Ƃ�
  if (!is_measuring_flg)
  {
    //�X�^�[�g�J�n���̎�����ۑ�����B
    start_time_point = chrono::system_clock::now();
    is_measuring_flg = 1;
  }
}

Time& StopWatch::Stop()
{
  //�v�����̎�
  if (is_measuring_flg)
  {
    //�v�����ʂ��擾����B
    MeasureTime();

    //�v�����ʂ�ۑ�����B
    last_stop_time = time.ToMilliseconds();

    //�v�����łȂ���Ԃɂ���B
    this->is_measuring_flg = 0;
  }

  return time;
}

void StopWatch::Reset()
{
  //�v�����łȂ���Ԃɂ���B
  is_measuring_flg = 0;

  //�v�����ʂ����Z�b�g����B
  time.Clear();
  last_stop_time = last_stop_time.zero();
  //�v���J�n���������Z�b�g����B
  start_time_point = chrono::time_point<chrono::system_clock>::min();
}

int StopWatch::is_measuring()
{
  return is_measuring_flg;
}

Time& StopWatch::MeasureTime()
{
  //���ݎ������擾
  chrono::time_point<chrono::system_clock> now_time_point = chrono::system_clock::now();

  //�X�^�[�g���Ă���o�߂������Ԃ��v�Z
  auto time_after_start = now_time_point - start_time_point;

  //�ȑO�ɃX�g�b�v�����Ƃ��̋L�^ + �X�^�[�g���Ă���o�߂�������
  milliseconds time = last_stop_time +  chrono::duration_cast<milliseconds>(time_after_start);

  //���ʂ������o�ϐ��ɃZ�b�g����B
  this->time.SetTime(time);

  return this->time;
}