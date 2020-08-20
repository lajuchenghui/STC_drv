#ifndef __UART_H__
#define __UART_H__

#include "main.h"

void UartInit();
void UartSend(char dat);
void UartSendStr(char *p);
void Delay50ms();		//@24.000MHz
void UartSendHandel();
void UartPrintf(char *fmt,...);


#endif
