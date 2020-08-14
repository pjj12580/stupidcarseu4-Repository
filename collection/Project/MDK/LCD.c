#include "LCD.h"
#include "stdio.h"

void display() 
{

        char Left[10];
        char Middle[10];
        char Right[10];

        sprintf(Left, "L:%04d", AD_read[0]);     //水平左电感
        sprintf(Middle, "R:%04d", AD_read[1]);   //水平中电感
        sprintf(Right, "LM:%04d", AD_read[2]);   //水平右电感

        lcd_showstr(0, 0, Left);
        lcd_showstr(80, 0, Middle);
        lcd_showstr(0, 1, Right);

}