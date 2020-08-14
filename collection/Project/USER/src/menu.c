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

uint8 KEY_check( void )                                 /*������� */
{
	uint8	key_lable = 0;
	uint8	temp1, temp2;

	/* �ó��ĸ������µı�ǩλ */
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

	/* ��ǩλΪ0��û�м����� */
	if ( key_lable == 0 )                           /* û�а������� */
	{
		if ( key_temp != 0 )                    /* ֮ǰ�а������� */
		{
			temp1		= key_counter;  /*���µļ�����(���¼��Σ�) */
			temp2		= key_temp;     /* ֮ǰ�İ����ı�� */
			key_counter	= 0;
			key_temp	= 0;
			if ( temp1 > 0 )                /* ���� */
			{
				return(temp2);
			}else  {
				return(0);
			}
		}else return(0);
	}
	/* ��ǩλ��Ϊ0���м����� */
	else{ /*�а������� */
		if ( key_temp == 0 ) /* ֮ǰû�м�⵽�������� */
		{
			key_temp = key_lable;
		}
		key_counter++;

		return(0);
	}
}