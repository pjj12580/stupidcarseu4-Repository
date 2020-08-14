#include "ele_processing.h"

int num_f = 0;
int filter[6][5] = {0};
double linear_cf = 1;

void Read_AD( void )
{
  AD_read[0] = adc_mean_filter(ADC_1,ADC1_CH4_B15,5);
  AD_read[1] = adc_mean_filter(ADC_1,ADC1_CH3_B14,5);
  AD_read[2] = adc_mean_filter(ADC_1,ADC1_CH5_B16,5);
	AD_read[3] = adc_mean_filter(ADC_1,ADC1_CH6_B17,5);
  AD_read[4] = adc_mean_filter(ADC_1,ADC1_CH7_B18,5);
  AD_read[5] = adc_mean_filter(ADC_1,ADC1_CH8_B19,5);
  AD_read[6] = adc_mean_filter(ADC_1,ADC1_CH9_B20,5);
  AD_read[7] = adc_mean_filter(ADC_1,ADC1_CH10_B21,5);
  AD_read[8] = adc_mean_filter(ADC_1,ADC1_CH11_B22,5);
  AD_read[9] = adc_mean_filter(ADC_1,ADC1_CH12_B23,5);
	AD_read[10] = adc_mean_filter(ADC_1,ADC1_CH13_B24,5);
	AD_read[11] = adc_mean_filter(ADC_1,ADC1_CH14_B25,5);
  if(AD_read[0] <= 10 || AD_read[1] <= 10 ||AD_read[2] <= 10)
    start = 0;
  //test
  //uart_putchar(USART_1,1);
}