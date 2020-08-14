#ifndef VARIABLE_H
#define VARIABLE_H
#include "common.h"
#include "headfile.h"

extern uint8 KEY_STATE;
extern uint8 AD_read[12];
extern double steer_offset;

extern int direction;//left = -1 right = 1
extern int steer;
extern int steer_record;
extern float Steer_P;
extern float Steer_D;
extern int steer_offsetQueue[10];//΢�ֿ���
extern int steer_currPtr;//ѭ������
extern int steer_difference;
extern int steer_pre_difference;

extern double out_increment;//����ʽPID������� 
extern int motor_duty;//���ռ�ձ�
extern int32 motor_out;//����� 
extern int16 motor_speed;//��ʵ�ٶ�
extern int16 motor_except;//�����ٶ�
extern int16 ek0,ek1,ek2;//ǰ���������
extern float Motor_P;
extern float Motor_I;
extern float Motor_D;

// �����ж����ֵ
extern int16 DownAD0, DownAD1, DownAD2, DownAD3;
// �����ж����ֵ
extern int16 UpAD0, UpAD1, UpAD2, UpAD3;

extern float rat;

extern uint8 start;
extern uint8 send_buff[20];
extern int8 ad1,ad2,ad3,ad4,ad5,ad6,ad7,ad8,ad9;
extern uint8 collection_success;
/////////��ѧ����/////////////////////
#define PI 3.1415926535
//////////////////////////////////

//����λ�÷�����ر���
#define NONE_SIT 0//��ʼ��
#define LEFT_LEFT 1//��
#define CENTER_LEFT 2//����
#define CENTER_RIGHT 3//����
#define RIGHT_RIGHT 4//��
#define OUTRANGE_SIT 5//�޷��ж�,����


//����������ϵ��
//�˴���ֵ��Ч,��Ҫ�Ը���ֵΪ׼,��Ҫ��flash��ʼ����ȡ����ֵ����
extern float c_ad1, c_ad2, c_ad3,c_ad4,c_ad5,c_ad6,c_ad7,c_ad8;
//�������߽�ƫ��ֵ
extern float offset_c12, offset_c23, offset_c34, offset_c45, offset_c56, offset_c67, offset_c78;
extern char area;//�����ж� 
//���һ�ε���Ч��������(�����ж�)
extern uint8_t lastactive_area;
extern float hinder_dis_linear;
extern float offset_cal;
extern float max_offset;
extern float min_offset;
extern float offset_precal;
extern float areadiv;

//Բ��
extern int circle_state;
extern int circle_num;
extern int circle_dis_AI[6];
extern int circle_dir;
extern int Midstandard;
extern int Roundin;
extern int Roundout;
extern double Round_degree;
extern double Round_degree_in;
extern double Round_degree_out;
extern double circle_dis[41];
extern int circle_dis_i;
extern double circle_round_in;
extern double circle_round;
extern double circle_round_out_min;
extern double circle_round_out_max;
extern int circle_distance;
extern int circle_distance_out;
extern int circle_num_AI;
extern const int circle_small;
extern const int circle_big;
extern double circle_dis_in;


//���
extern float StraightExpectSpeed;
#endif