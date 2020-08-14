#include "headfile.h"
#include "control.h"

void calculate_dis()
{
	uint16_t  ad_right =AD_read[0];
	uint16_t  ad_center =AD_read[1];
	uint16_t  ad_left =AD_read[2];
	
	if(ad_left<15)
	{
		ad_left=0;
	}
	
	if(ad_center<15)
	{
		ad_center=0;
	}
	
	if(ad_right<15)
	{
		ad_right=0;
	}
	
	uint16_t max_ad = 0;

	if ( ad_left >= ad_center )
		max_ad = ad_left;
	else max_ad = ad_center;
	if ( (ad_right >= ad_center) && (ad_right >= ad_left) )
		max_ad = ad_right;
	
/*
 * NONE_SIT 0//初始化
 * LEFT_LEFT 1//左
 * CENTER_LEFT 2//中左
 * CENTER_RIGHT 3//中右
 * RIGHT_RIGHT 4//右
 * OUTRANGE_SIT 5//无法判断,丢线
*/

	/*
	 * char area;//区块判断//这是用于判断此时车位于赛道的哪一部分的
	 * 分区
		lastactive_area意为刚刚车所处的状态
	 */
	if ( (lastactive_area == 0) && (max_ad <= 10) )
		area = NONE_SIT;                                /* 初始化 */
	else if ( max_ad <= 5 )
		area = OUTRANGE_SIT;//如果收集到的数据没有超过10，则说明跑出赛道了  /*数值：5*/
	else if ( max_ad == ad_left )
		area = RIGHT_RIGHT;  //如果左值为最大值需要右转   /*数值：4 */
	else if ( max_ad == ad_right )
		area = LEFT_LEFT;    //如果右值为最大值需要左转   /*数值：1 */
	else if ( max_ad == ad_center )//如果中值为最大值那么去判断是中间偏左还是中间偏右
	{
		if ( ad_left >= ad_right )
			area = CENTER_RIGHT;                    /*数值：3 */
		else if ( ad_right > ad_left )
			area = CENTER_LEFT;                     /*数值：2 */
		else 
			area = OUTRANGE_SIT;
	}
	else 
		area = OUTRANGE_SIT;

	
	/* 偏移计算 */
	switch ( area )
	{
	case 1:   offset_cal	= c_ad1 * ( (float) (ad_right - ad_center) / (ad_right) ) + offset_c12; break;  /* 正 zuo */
	case 2:   offset_cal	= ( ( (float) (ad_center - ad_right) / (ad_center) + offset_c12) * (ad_right - ad_left) / (ad_center - ad_left) ) + ( (-(ad_right - ad_left) / (ad_center) + offset_c23) * (ad_center - ad_right) / (ad_center - ad_left) ); break;
	case 3:   offset_cal	= ( ( (float) (ad_center - ad_left) / (ad_center) + offset_c45) * (ad_left - ad_right) / (ad_center - ad_right) ) + ( (-(ad_left - ad_right) / (ad_center) + offset_c34) * (ad_center - ad_left) / (ad_center - ad_right) ); break;
	case 4:   offset_cal	= c_ad8 * ( (float) (ad_left - ad_center) / (ad_left) ) + offset_c45; break;    /* 负 you */
	case 5:   offset_cal = offset_cal; break;
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*过大或过小的处理*/
	if ( offset_cal > max_offset )
		offset_cal = max_offset;
	else if ( offset_cal < min_offset )
		offset_cal = min_offset;
	
	
/*处理可能发生的偏离赛道的问题——丢线寻线*/
	if ( area == 5 )
	{
		if ( lastactive_area == 0 )
			offset_cal = 0;         /* 初始化 */
		else if ( offset_precal <= 0 )//>=5??
			offset_cal = min_offset;
		else offset_cal = max_offset;
	}
/////////////////////////////////////////////////////////////////////////////////////////////////
/*记录刚刚处理完的数据，为下次处理做好准备*/
	lastactive_area = area;                 /*有效区域 */
	
	offset_precal = offset_cal;
	
	steer_offset	= offset_cal;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

	
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	/*基础转向代码部分*/
	if(AD_read[2]+AD_read[1]+AD_read[0]>30)//用于边界保护
	{
		if(AD_read[0] >= AD_read[2])
		{
			steer_offset = ((int)AD_read[0] - (int)AD_read[2])/((int)AD_read[0] + (int)AD_read[2] + 1.0);
			direction = -1;
		}
    
		else
		{
			steer_offset = ((int)AD_read[2] - (int)AD_read[0])/((int)AD_read[0] + (int)AD_read[2] + 1.0);
			direction = 1;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void steer_control()//舵机控制
{
  steer_currPtr++;
  steer_currPtr = steer_currPtr%10;
  steer_offsetQueue[steer_currPtr] = (int)(direction*steer_offset);
  //PD控制 
  steer_difference = (int) (Steer_D * (direction*steer_offset - steer_offsetQueue[(steer_currPtr+5)%10])); 
  steer = (int)(mid_steer_duty + direction*Steer_P*steer_offset) + 0.5*steer_difference+0.5*steer_pre_difference;
  steer_pre_difference = steer_difference;
	
  if(steer >= max_steer_duty)
    steer = max_steer_duty;
  if(steer <= min_steer_duty)
    steer = min_steer_duty;
	
  pwm_duty(PWM4_MODULE3_CHA_C31 , steer);
	
	
	/*if(steer >= 0.712*max_steer_duty || steer<= 1.245*min_steer_duty  )
		{
			motor = motor-2000;
		}*/
}

void ad_collection(void)//数据收集
{
    //ad1 = adc_mean_filter(ADC_1,ADC1_CH6_B17 ,10)-128;
    //ad2 = adc_mean_filter(ADC_1,ADC1_CH7_B18 ,10)-128;
    ad1 = adc_mean_filter(ADC_1,ADC1_CH8_B19 ,10)-128;
    ad2 = adc_mean_filter(ADC_1,ADC1_CH9_B20 ,10)-128;
    ad3 = adc_mean_filter(ADC_1,ADC1_CH10_B21,10)-128;
    ad4 = adc_mean_filter(ADC_1,ADC1_CH11_B22,10)-128;
    ad5 = adc_mean_filter(ADC_1,ADC1_CH12_B23,10)-128;
	ad6 = adc_mean_filter(ADC_1,ADC1_CH13_B24,10)-128;
	ad7 = adc_mean_filter(ADC_1,ADC1_CH14_B25,10)-128;
	
	collection_success = 1;
}
void PWM_out()//电机控制
{
		/*double out_increment;//增量式PID输出增量 
		int motor_duty;//电机占空比
		int32 motor_out;//输出量 
		int16 motor_speed;//真实速度
		int16 motor_except;//期望速度
		int16 ek0,ek1,ek2;//前后三次误差
		float Motor_P = 25;
		float Motor_I = 2;
		float Motor_D = 8 ;*/
		motor_speed = qtimer_quad_get(QTIMER_1, QTIMER1_TIMER0_C0 );   //采集编码器数据    
		qtimer_quad_clear(QTIMER_1, QTIMER1_TIMER0_C0 );         //编码器数据采集完成后务必清零    
		ek2 = ek1;//保存上上次误差    
		ek1 = ek0; //保存上次误差    
		ek0 = motor_except - motor_speed;//计算当前误差 

        //设置PID系数    

        //进行增量式PID运算    

        out_increment = (int16)(Motor_P*(ek0-ek1) + Motor_I*ek0 + Motor_D*(ek0-2*ek1+ek2));  //计算增量  

        motor_out += out_increment;       //输出增量  

        motor_out = limit(motor_out,9000);     //输出限幅 不能超过占空比最大值    

          

        motor_duty = (int32)motor_out;    //强制转换为整数后赋值给电机占空比变量  
		
		if(AD_read[0]<DownAD0 && AD_read[1]<DownAD1 && AD_read[2]<DownAD2)//检测到下坡
		{
			pwm_duty(PWM1_MODULE3_CHB_D1,3000);
			systick_delay_ms(100);//延时100ms
		}
		if(AD_read[0]>UpAD0 && AD_read[1]>UpAD1 && AD_read[2]>UpAD2)//检测到上坡
		{
			pwm_duty(PWM1_MODULE3_CHB_D1,9000);
			systick_delay_ms(200);//延时200ms
		}
		

        if(motor_duty>=0)           //前进  

        {    

            //pwm_duty(MOTORA2_CHANNEL,0);    

            pwm_duty(PWM1_MODULE3_CHB_D1,motor_duty);    

        }    

        else                        //后退  

        {    

            //pwm_duty(MOTORA1_CHANNEL,0);    

            pwm_duty(PWM1_MODULE3_CHB_D1,-motor_duty);    

        }    

            

        systick_delay_ms(5);//延时5ms    
	
		pwm_duty(PWM1_MODULE3_CHB_D1 , motor_duty);
}



/*-------------------------------------主状态机-------------------------------*/ /* 用于处理主要运行状态（正常、圆环、停车） */
/*void Main_SM( void )
{
	if()
}	*/


/*-------------------------------------圆环状态机-------------------------------*/
void Circle_SM(void)
{
	if ( circle_state == 0 )
		return;
	else if(circle_state == 1)
	{
		
	}
}