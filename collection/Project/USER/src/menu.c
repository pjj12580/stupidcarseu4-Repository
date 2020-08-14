#include "menu.h"

uint8	key_counter	= 0;
uint8	key_temp	= 0;
uint8	temp1;
uint8	temp2;
uint8	temp3;
uint8	temp4;
uint8	temp5;
uint8	temp6;
uint8	temp7;

uint8 KEY_check( void )                                 /*按键检测 */
{
	uint8	key_lable = 0;
	uint8	temp1, temp2;

	/* 得出哪个键按下的标签位 */
	if ( gpio_get( B26 ) == 0 )                      /* up */
	{
		key_lable = 1;
	}
	if ( gpio_get( B27 ) == 0 )                      /* down */
	{
		key_lable = 2;
	}
	if ( gpio_get( B28 ) == 0 )                     /* left */
	{
		key_lable = 3;
	}
	if ( gpio_get( B29 ) == 0 )                      /* right */
	{
		key_lable = 4;
	}
	if ( gpio_get( B30 ) == 0 )                      /* Mid */
	{
		key_lable = 5;
	}

	/* 标签位为0，没有键按下 */
	if ( key_lable == 0 )                           /* 没有按键按下 */
	{
		if ( key_temp != 0 )                    /* 之前有按键按下 */
		{
			temp1		= key_counter;  /*按下的计数器(按下几次？) */
			temp2		= key_temp;     /* 之前的按键的标号 */
			key_counter	= 0;
			key_temp	= 0;
			if ( temp1 > 0 )                /* 消抖 */
			{
				return(temp2);
			}else  {
				return(0);
			}
		}else return(0);
	}
	/* 标签位不为0，有键按下 */
	else{ /*有按键按下 */
		if ( key_temp == 0 ) /* 之前没有检测到按键按下 */
		{
			key_temp = key_lable;
		}
		key_counter++;

		return(0);
	}
}