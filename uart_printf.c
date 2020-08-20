#include "uart.h"

bit busy;

 c8 wptr;
 c8 rptr;
 c8 buffer[16];
 
 

void UartIsr() interrupt 4
{
    if (TI)
    {
        TI = 0;
        busy = 0;
    }
    if (RI)
    {
        RI = 0;
        buffer[wptr++] = SBUF;
        wptr &= 0x0f;
    }
}

void UartInit()
{
	SCON = 0x50;		//8位数据，可变波特率
	AUXR |= 0x40;		//定时器1时钟为FOSE，即1T
	AUXR &= 0xFE;		//串口1定时器1为波特率发生器
	TMOD &= 0x0F;		//设定定时器1位16位重装载方式
	TL1 = 0xCC;			//设定定时器初值
	TH1 = 0xFF;			//设定定时器初值
	ET1 = 0;				//禁止定时器1中断
	TR1 = 1;				//启动定时器1
	
    wptr = 0x00;
    rptr = 0x00;
    busy = 0;
	   
	ES = 1;
	EA = 1;

}

void UartSend(char dat)
{
    while (busy);
    busy = 1;
    SBUF = dat;
}

void UartSendStr(char *p)
{
    while (*p)
    {
        UartSend(*p++);
    }
}

void Delay50ms()		//@24.000MHz
{
	u8 i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 144;
	k = 71;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void UartSendHandel()
{
		
	//	Delay50ms();
    
		/*if (rptr != wptr)
    {
     UartSend(buffer[rptr++]);
     rptr &= 0x0f;
			
     }
	*/
		/*if(buffer[0] == 01)
		{
			to_led_flag = 1;
		}*/


}


void UartPrintf(char *fmt,...)
{
	char *ap;
	char xdata string[128];
	va_start(ap,fmt);
	vsprintf(string,fmt,ap);
	UartSendStr(string);
	va_end(ap);

}

