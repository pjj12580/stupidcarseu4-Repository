#include "init.h"

void init()
{
    //��ʼ�����򿪹�
    gpio_init(B26 ,GPI,0,GPIO_PIN_CONFIG);
    gpio_init(B27 ,GPI,0,GPIO_PIN_CONFIG);
    gpio_init(B28 ,GPI,0,GPIO_PIN_CONFIG);
    gpio_init(B29 ,GPI,0,GPIO_PIN_CONFIG);
    gpio_init(B30 ,GPI,0,GPIO_PIN_CONFIG);
    
    //��ʼ����������
    uart_init (USART_1, 115200,UART1_TX_B12,UART1_RX_B13);
    //NVIC_SetPriority(LPUART1_IRQn,1);         //���ô����ж����ȼ� ��Χ0-15 ԽС���ȼ�Խ�� 38400
    //uart_rx_irq(USART_1,1);
    
    //��ʼ�����
    pwm_init(PWM4_MODULE3_CHA_C31,50,mid_steer_duty);
    
    //��ʼ�����
    pwm_init(PWM1_MODULE3_CHB_D1 , 12000, 0);//��ת
    pwm_init(PWM1_MODULE3_CHA_D0 , 12000, 0);//��ת
    
    //��ʼ��������
    qtimer_quad_init(QTIMER_1,QTIMER1_TIMER0_C0,QTIMER1_TIMER1_C1);
    
    //��ʼ��AD
    adc_init(ADC_1,ADC1_CH3_B14,ADC_8BIT);
    adc_init(ADC_1,ADC1_CH4_B15,ADC_8BIT);
    adc_init(ADC_1,ADC1_CH5_B16,ADC_8BIT);
    adc_init(ADC_1,ADC1_CH6_B17,ADC_8BIT);
    adc_init(ADC_1,ADC1_CH7_B18,ADC_8BIT);
    adc_init(ADC_1,ADC1_CH8_B19,ADC_8BIT);
    adc_init(ADC_1,ADC1_CH9_B20,ADC_8BIT);
    adc_init(ADC_1,ADC1_CH10_B21,ADC_8BIT);
    adc_init(ADC_1,ADC1_CH11_B22,ADC_8BIT);
    adc_init(ADC_1,ADC1_CH12_B23,ADC_8BIT);
    adc_init(ADC_1,ADC1_CH13_B24,ADC_8BIT);
    adc_init(ADC_1,ADC1_CH14_B25,ADC_8BIT);
    
    systick_delay_ms(100);
    
    //��ʼ���ж�
    pit_init();
    pit_interrupt_ms(PIT_CH0,3);//3
    NVIC_SetPriority(PIT_IRQn,0);//�����ж����ȼ� ��Χ0-15 ԽС���ȼ�Խ�� 
	
	//LCD
	lcd_init();
	
}