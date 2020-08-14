/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/


//整套推荐IO查看Projecct文件夹下的TXT文本

//打开新的工程或者工程移动了位置务必执行以下操作
//第一步 关闭上面所有打开的文件
//第二步 project  clean  等待下方进度条走完

//下载代码前请根据自己使用的下载器在工程里设置下载器为自己所使用的

#include "headfile.h"
#include <stdio.h>//用于sprintf函数

uint16 AD_value;

int main(void)
{
    DisableGlobalIRQ();
    board_init();//务必保留，本函数用于初始化MPU 时钟 调试串口
    
	//此处编写用户代码(例如：外设初始化代码等)
    init();
	//int steer = 0;
	//总中断最后开启
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
        //此处编写需要循环执行的代码
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
            collection_success = 0;     //是否收集状态位清零，以备重新收集
			
			//前两个字节为时间，如果程序结构里面有时间变量可以将时间变量输出，这样我们接受到数据后
			//可以根据时间来判断包是否是连续的，是否有丢包
            send_buff[0] = 0;
            send_buff[1] = 0;
            
			send_buff[2] = ad1;
            send_buff[3] = ad2;
            send_buff[4] = ad3;
					
					
            send_buff[5] = ad4;
            send_buff[6] = ad5;
            send_buff[7] = ad6;
            send_buff[8] = ad7;
			//新加入几个电感
			/*
			send_buff[9] = ad8;
			send_buff[10] = ad9;
			*/
            
			//将舵机数值转换为-128至+127  因为舵机转角被限制在-400至+400之间，
			//因此舵机转角除以420之后绝对值必定是小于1的，
			//然后在乘以128数据范围也就一定被限制在了-128至+127之间了。
            send_buff[9] = (int32)(steer - mid_steer_duty)*128/1400;
			
			//固定字节，可以用于校验或者方便肉眼可辨每一个包是否正确
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





