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
 * NONE_SIT 0//��ʼ��
 * LEFT_LEFT 1//��
 * CENTER_LEFT 2//����
 * CENTER_RIGHT 3//����
 * RIGHT_RIGHT 4//��
 * OUTRANGE_SIT 5//�޷��ж�,����
*/

	/*
	 * char area;//�����ж�//���������жϴ�ʱ��λ����������һ���ֵ�
	 * ����
		lastactive_area��Ϊ�ոճ�������״̬
	 */
	if ( (lastactive_area == 0) && (max_ad <= 10) )
		area = NONE_SIT;                                /* ��ʼ�� */
	else if ( max_ad <= 5 )
		area = OUTRANGE_SIT;//����ռ���������û�г���10����˵���ܳ�������  /*��ֵ��5*/
	else if ( max_ad == ad_left )
		area = RIGHT_RIGHT;  //�����ֵΪ���ֵ��Ҫ��ת   /*��ֵ��4 */
	else if ( max_ad == ad_right )
		area = LEFT_LEFT;    //�����ֵΪ���ֵ��Ҫ��ת   /*��ֵ��1 */
	else if ( max_ad == ad_center )//�����ֵΪ���ֵ��ôȥ�ж����м�ƫ�����м�ƫ��
	{
		if ( ad_left >= ad_right )
			area = CENTER_RIGHT;                    /*��ֵ��3 */
		else if ( ad_right > ad_left )
			area = CENTER_LEFT;                     /*��ֵ��2 */
		else 
			area = OUTRANGE_SIT;
	}
	else 
		area = OUTRANGE_SIT;

	
	/* ƫ�Ƽ��� */
	switch ( area )
	{
	case 1:   offset_cal	= c_ad1 * ( (float) (ad_right - ad_center) / (ad_right) ) + offset_c12; break;  /* �� zuo */
	case 2:   offset_cal	= ( ( (float) (ad_center - ad_right) / (ad_center) + offset_c12) * (ad_right - ad_left) / (ad_center - ad_left) ) + ( (-(ad_right - ad_left) / (ad_center) + offset_c23) * (ad_center - ad_right) / (ad_center - ad_left) ); break;
	case 3:   offset_cal	= ( ( (float) (ad_center - ad_left) / (ad_center) + offset_c45) * (ad_left - ad_right) / (ad_center - ad_right) ) + ( (-(ad_left - ad_right) / (ad_center) + offset_c34) * (ad_center - ad_left) / (ad_center - ad_right) ); break;
	case 4:   offset_cal	= c_ad8 * ( (float) (ad_left - ad_center) / (ad_left) ) + offset_c45; break;    /* �� you */
	case 5:   offset_cal = offset_cal; break;
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*������С�Ĵ���*/
	if ( offset_cal > max_offset )
		offset_cal = max_offset;
	else if ( offset_cal < min_offset )
		offset_cal = min_offset;
	
	
/*������ܷ�����ƫ�����������⡪������Ѱ��*/
	if ( area == 5 )
	{
		if ( lastactive_area == 0 )
			offset_cal = 0;         /* ��ʼ�� */
		else if ( offset_precal <= 0 )//>=5??
			offset_cal = min_offset;
		else offset_cal = max_offset;
	}
/////////////////////////////////////////////////////////////////////////////////////////////////
/*��¼�ոմ���������ݣ�Ϊ�´δ�������׼��*/
	lastactive_area = area;                 /*��Ч���� */
	
	offset_precal = offset_cal;
	
	steer_offset	= offset_cal;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// */

	
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	/*����ת����벿��*/
	if(AD_read[2]+AD_read[1]+AD_read[0]>30)//���ڱ߽籣��
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

void steer_control()//�������
{
  steer_currPtr++;
  steer_currPtr = steer_currPtr%10;
  steer_offsetQueue[steer_currPtr] = (int)(direction*steer_offset);
  //PD���� 
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

void ad_collection(void)//�����ռ�
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
void PWM_out()//�������
{
		/*double out_increment;//����ʽPID������� 
		int motor_duty;//���ռ�ձ�
		int32 motor_out;//����� 
		int16 motor_speed;//��ʵ�ٶ�
		int16 motor_except;//�����ٶ�
		int16 ek0,ek1,ek2;//ǰ���������
		float Motor_P = 25;
		float Motor_I = 2;
		float Motor_D = 8 ;*/
		motor_speed = qtimer_quad_get(QTIMER_1, QTIMER1_TIMER0_C0 );   //�ɼ�����������    
		qtimer_quad_clear(QTIMER_1, QTIMER1_TIMER0_C0 );         //���������ݲɼ���ɺ��������    
		ek2 = ek1;//�������ϴ����    
		ek1 = ek0; //�����ϴ����    
		ek0 = motor_except - motor_speed;//���㵱ǰ��� 

        //����PIDϵ��    

        //��������ʽPID����    

        out_increment = (int16)(Motor_P*(ek0-ek1) + Motor_I*ek0 + Motor_D*(ek0-2*ek1+ek2));  //��������  

        motor_out += out_increment;       //�������  

        motor_out = limit(motor_out,9000);     //����޷� ���ܳ���ռ�ձ����ֵ    

          

        motor_duty = (int32)motor_out;    //ǿ��ת��Ϊ������ֵ�����ռ�ձȱ���  
		
		if(AD_read[0]<DownAD0 && AD_read[1]<DownAD1 && AD_read[2]<DownAD2)//��⵽����
		{
			pwm_duty(PWM1_MODULE3_CHB_D1,3000);
			systick_delay_ms(100);//��ʱ100ms
		}
		if(AD_read[0]>UpAD0 && AD_read[1]>UpAD1 && AD_read[2]>UpAD2)//��⵽����
		{
			pwm_duty(PWM1_MODULE3_CHB_D1,9000);
			systick_delay_ms(200);//��ʱ200ms
		}
		

        if(motor_duty>=0)           //ǰ��  

        {    

            //pwm_duty(MOTORA2_CHANNEL,0);    

            pwm_duty(PWM1_MODULE3_CHB_D1,motor_duty);    

        }    

        else                        //����  

        {    

            //pwm_duty(MOTORA1_CHANNEL,0);    

            pwm_duty(PWM1_MODULE3_CHB_D1,-motor_duty);    

        }    

            

        systick_delay_ms(5);//��ʱ5ms    
	
		pwm_duty(PWM1_MODULE3_CHB_D1 , motor_duty);
}



/*-------------------------------------��״̬��-------------------------------*/ /* ���ڴ�����Ҫ����״̬��������Բ����ͣ���� */
/*void Main_SM( void )
{
	if()
}	*/


/*-------------------------------------Բ��״̬��-------------------------------*/
void Circle_SM(void)
{
	if ( circle_state == 0 )
		return;
	else if(circle_state == 1)
	{
		
	}
}