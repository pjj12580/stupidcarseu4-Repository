/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/


//�����Ƽ�IO�鿴Projecct�ļ����µ�TXT�ı�

//���µĹ��̻��߹����ƶ���λ�����ִ�����²���
//��һ�� �ر��������д򿪵��ļ�
//�ڶ��� project  clean  �ȴ��·�����������

//���ش���ǰ������Լ�ʹ�õ��������ڹ���������������Ϊ�Լ���ʹ�õ�

#include "headfile.h"
#include <stdio.h>//����sprintf����

uint16 AD_value;

int main(void)
{
    DisableGlobalIRQ();
    board_init();//��ر��������������ڳ�ʼ��MPU ʱ�� ���Դ���
    
	//�˴���д�û�����(���磺�����ʼ�������)
    init();
	//int steer = 0;
	//���ж������
    EnableGlobalIRQ(0);
    while (1)
    {
        /*uint8 a = adc_mean_filter(ADC_1,ADC1_CH4_B15,5);
        uint8 b = adc_mean_filter(ADC_1,ADC1_CH3_B14,5);
        uint8 c = adc_mean_filter(ADC_1,ADC1_CH5_B16,5);
        uint8 d = adc_mean_filter(ADC_1,ADC1_CH6_B17,5);
        uint8 e = adc_mean_filter(ADC_1,ADC1_CH7_B18,5);
        uint8 f = adc_mean_filter(ADC_1,ADC1_CH8_B19,5);
        uint8 g = adc_mean_filter(ADC_1,ADC1_CH9_B20,5);
        uint8 h = adc_mean_filter(ADC_1,ADC1_CH10_B21,5);
        uint8 i = adc_mean_filter(ADC_1,ADC1_CH13_B24,5);
        uint8 j = adc_mean_filter(ADC_1,ADC1_CH14_B25,5);*/
        //�˴���д��Ҫѭ��ִ�еĴ���
		display();
        KEY_STATE=KEY_check();
        if(KEY_STATE == 5)
        {
          if(start == 0)
            start = 1;
          else
            start = 0;
        }
        if(collection_success && start == 1)
        {
            collection_success = 0;     //�Ƿ��ռ�״̬λ���㣬�Ա������ռ�
			
			//ǰ�����ֽ�Ϊʱ�䣬�������ṹ������ʱ��������Խ�ʱ�����������������ǽ��ܵ����ݺ�
			//���Ը���ʱ�����жϰ��Ƿ��������ģ��Ƿ��ж���
            send_buff[0] = 0;
            send_buff[1] = 0;
            
			send_buff[2] = ad1;
            send_buff[3] = ad2;
            send_buff[4] = ad3;
					
					
            send_buff[5] = ad4;
            send_buff[6] = ad5;
            send_buff[7] = ad6;
            send_buff[8] = ad7;
			//�¼��뼸�����
			/*
			send_buff[9] = ad8;
			send_buff[10] = ad9;
			*/
            
			//�������ֵת��Ϊ-128��+127  ��Ϊ���ת�Ǳ�������-400��+400֮�䣬
			//��˶��ת�ǳ���420֮�����ֵ�ض���С��1�ģ�
			//Ȼ���ڳ���128���ݷ�ΧҲ��һ������������-128��+127֮���ˡ�
            send_buff[9] = (int32)(steer - mid_steer_duty)*128/1400;
			
			//�̶��ֽڣ���������У����߷������ۿɱ�ÿһ�����Ƿ���ȷ
            send_buff[10] = 0x5a;
            
            uart_putbuff(USART_1,&send_buff[0],11);
        }

       
        /*if(KEY_STATE == 1)
        {
          uart_putchar(USART_1,a);
          uart_putchar(USART_1,b);
          uart_putchar(USART_1,c);
          uart_putchar(USART_1,d);
          uart_putchar(USART_1,e);
          uart_putchar(USART_1,f);
          uart_putchar(USART_1,g);
          uart_putchar(USART_1,h);
          uart_putchar(USART_1,i);
          uart_putchar(USART_1,j);
          steer += 50;
          uart_putchar(USART_1,1);
          //uart_putchar(USART_1,0xA5);
          
        }
        //KEY_STATE=KEY_check();
        if(KEY_STATE == 2)
        {
          steer -= 50;
          uart_putchar(USART_1,2);
        }
        //KEY_STATE=KEY_check();
        if(KEY_STATE == 3)
        {
          //steer -= 10;
          uart_putchar(USART_1,3);
        }
        if(KEY_STATE == 4)
        {
          //steer -= 10;
          uart_putchar(USART_1,4);
        }
        if(KEY_STATE == 5)
        {
          //steer -= 10;
          uart_putchar(USART_1,5);
        }

        pwm_duty(PWM4_MODULE3_CHA_C31,3750 + steer);
        //uart_putchar(USART_1,2);
        systick_delay_ms(100);*/
        
    }
}





