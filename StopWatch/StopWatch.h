#pragma once
#include"Time.h"

//�X�g�b�v�E�H�b�`�N���X
//�g����
//  1.Start()���ĂԁB
//  2.�҂B
//  3.Stop()���ĂԁBTime�N���X�̃I�u�W�F�N�g���߂�̂ŁATo���Ƃ��֐����ĂԁB
//  4.Start()���Ă�ł���Stop()���ĂԂ܂ł̎��Ԃ��擾�ł���B
//�⑫1.�v�����Ɍo�ߎ��Ԃ��擾�������ꍇ�AMeasureTime()�֐����ĂԂƁA�X�^�[�g���Ă���o�߂������Ԃ��擾�ł���B
//�⑫2.Stop()���Ă񂾌���v�����ʂ͕ۑ�����Ă���A�Ă�Start()���ĂԂƁA�ȑO�̌��ʂ���v�����ĊJ�����B
//�⑫3.�L�^�������������ꍇ�́AReset()���ĂԁB
class StopWatch
{
public:
  StopWatch();
  ~StopWatch();

  //�v�����J�n����B
  //�ȑO��Stop()���Ă΂�Ă���ꍇ�A�ȑO�̌o�ߎ��Ԃ���v�����ĊJ����B
  //�v�����ɂ��̊֐����Ă΂ꂽ�ꍇ�A�������Ȃ��B
  void Start();

  //�v�����I�����A�v�����ʂ�Ԃ��B
  //�v�����łȂ��Ƃ��ɂ��̊֐����Ă΂ꂽ�ꍇ�A�������Ȃ��B
  Time& Stop();

  //�v�����ʂ����Z�b�g����B
  //�v�����ɌĂ΂ꂽ�Ƃ��́A�v���𒆒f���Čv�����ʂ����Z�b�g����B
  void Reset();

  //�v�����ł��邩�ǂ����B
  //0:�v�����łȂ�
  //1;�v����
  int is_measuring();

  //�֐����Ă΂ꂽ���_�ł̌o�ߎ��Ԃ�Ԃ��B
  //���̊֐����Ă΂ꂽ����v���͎~�܂�Ȃ��B
  Time& MeasureTime();

private:
  //�v�����ʂ��i�[����ϐ�
  Time time;

  //�Ō�ɃX�g�b�v�������̌v������
  std::chrono::milliseconds last_stop_time;

  //�v���J�n����
  std::chrono::time_point<std::chrono::system_clock> start_time_point;

  //�v�����ł��邩�ǂ����B
  //0:�v�����łȂ�
  //1;�v����
  int is_measuring_flg;
};

