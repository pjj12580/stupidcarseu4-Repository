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
extern int steer_offsetQueue[10];//微分控制
extern int steer_currPtr;//循环队列
extern int steer_difference;
extern int steer_pre_difference;

extern double out_increment;//增量式PID输出增量 
extern int motor_duty;//电机占空比
extern int32 motor_out;//输出量 
extern int16 motor_speed;//真实速度
extern int16 motor_except;//期望速度
extern int16 ek0,ek1,ek2;//前后三次误差
extern float Motor_P;
extern float Motor_I;
extern float Motor_D;

// 下坡判定电感值
extern int16 DownAD0, DownAD1, DownAD2, DownAD3;
// 上坡判定电感值
extern int16 UpAD0, UpAD1, UpAD2, UpAD3;

extern float rat;

extern uint8 start;
extern uint8 send_buff[20];
extern int8 ad1,ad2,ad3,ad4,ad5,ad6,ad7,ad8,ad9;
extern uint8 collection_success;
/////////数学参数/////////////////////
#define PI 3.1415926535
//////////////////////////////////

//定义位置分区相关变量
#define NONE_SIT 0//初始化
#define LEFT_LEFT 1//左
#define CENTER_LEFT 2//中左
#define CENTER_RIGHT 3//中右
#define RIGHT_RIGHT 4//右
#define OUTRANGE_SIT 5//无法判断,丢线


//各分区比例系数
//此处数值无效,若要以该数值为准,需要在flash初始化中取消数值覆盖
extern float c_ad1, c_ad2, c_ad3,c_ad4,c_ad5,c_ad6,c_ad7,c_ad8;
//各分区边界偏移值
extern float offset_c12, offset_c23, offset_c34, offset_c45, offset_c56, offset_c67, offset_c78;
extern char area;//区块判断 
//最近一次的有效分区记忆(丢线判断)
extern uint8_t lastactive_area;
extern float hinder_dis_linear;
extern float offset_cal;
extern float max_offset;
extern float min_offset;
extern float offset_precal;
extern float areadiv;

//圆环
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


//电机
extern float StraightExpectSpeed;
#endif