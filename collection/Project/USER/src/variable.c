#include "variable.h"
/////////////////////////////////////////////
uint8 KEY_STATE=0;
uint8 AD_read[12];
double steer_offset = 0;
int steer;
int steer_record;
double motor_offset = 0;
int motor;//电机占空比
int direction;
int steer_offsetQueue[10] = {0};//微分控制
int steer_currPtr = -1;//循环队列
float rat = 0;
int steer_difference = 0;
int steer_pre_difference = 0;
float Steer_P = 1900;//default 2000
float Steer_D = 525;//default 600

double out_increment;//增量式PID输出增量 
int motor_duty;//电机占空比
int32 motor_out;//输出量 
int16 motor_speed;//真实速度
int16 motor_except = 2500;//期望速度
int16 ek0,ek1,ek2;//前后三次误差
float Motor_P = 25;
float Motor_I = 2;
float Motor_D = 8 ;

// 下坡判定电感值
int16 DownAD0 = 3, DownAD1 = 5, DownAD2 = 3;
// 上坡判定电感值
int16 UpAD0 = 3, UpAD1 = 5, UpAD2 = 3;

uint8 start = 0;
uint8 send_buff[20];
int8 ad1,ad2,ad3,ad4,ad5,ad6,ad7,ad8,ad9;
uint8 collection_success = 0;
///////////////////////////////////////////////

//各分区比例系数
//此处数值无效,若要以该数值为准,需要在flash初始化中取消数值覆盖
//float c_ad1 = 271.10, c_ad2 = 40.0, c_ad3 = 0.6,c_ad4 = 12.0,c_ad5 = -12.0,c_ad6 = -0.6,c_ad7 = -40.0,c_ad8 = -271.10;
//float c_ad1 = 271.10, c_ad2 = 40.0, c_ad3 = 0.6,c_ad4 = 12.0,c_ad5 = -12.0,c_ad6 = -0.6,c_ad7 = -40.0,c_ad8 = -271.10;
float c_ad1 = 459.28, c_ad2 = 40.0, c_ad3 = 0.6,c_ad4 = 12.0,c_ad5 = -12.0,c_ad6 = -0.6,c_ad7 = -40.0,c_ad8 = -459.28;
//各分区边界偏移值
//float offset_c12 = 50.22, offset_c23 = 46.0, offset_c34 = 5.04, offset_c45 = 0, offset_c56 = -5.04, offset_c67 = -46.0, offset_c78 = -50.22;

//各分区边界偏移值//48
float offset_c12 = 45.22, offset_c23 = 0.04, offset_c34 = -0.04, offset_c45 = -45.22;

char area = 0;//区块判断 
//最近一次的有效分区记忆(丢线判断)
uint8_t lastactive_area = 0;
float hinder_dis_linear = 0;
float areadiv = 0.68;
float offset_cal = 0;
float offset_precal = 0;
float max_offset =240;
float min_offset = -240;

//圆环
int circle_state = 0;
int circle_num = -1;
int circle_num_AI = 0;
int circle_dir = 0;
const int circle_small = 45;
const int circle_big   = 25;
int circle_dis_AI[6] = {0,0,0,0,0,0};//左+右- //30 //32 //45
int Midstandard = 5000;
int Roundin = 4800;
int Roundout = 4400;
double Round_degree =0.0;
double Round_degree_in = 0.0;
double Round_degree_out = 0.0;
double circle_dis[41] = {0.0};
int circle_dis_i = 0;
double circle_round_in = PI*0.3333;//60度
double circle_round = PI*0.3333*3;//180度
double circle_round_out_min = PI*0.3333*1.3;//60度
double circle_round_out_max = PI*0.3333*1.6;
int circle_distance = 0;
int circle_distance_out = 0;
double circle_dis_in = 50.0;

//电机
float StraightExpectSpeed;