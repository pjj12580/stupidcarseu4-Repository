#include "headfile.h"

void Read_AD( void );  //读AD口的值并进行滤波
void ele_linear();
extern int num_f;
extern int filter[6][5];
extern double linear_cf;