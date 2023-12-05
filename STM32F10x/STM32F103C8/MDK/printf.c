#include "stm32f10x.h"                  // Device header

#if 1

#include <stdio.h>

__asm(".global __use_no_semihosting");

//struct __FILE { int handle;} ;

FILE __stdout;
FILE __stdin;
FILE __stderr;

void _sys_exit(int x)
{
    x = x;
}
 
 

 
/*  */
int fputc(int ch, FILE *stream)
{

    while((USART1->SR & 0X40) == 0);

			USART1->DR = (uint8_t) ch;
 
    return ch;
}
 
char *_sys_command_string(char *cmd, int len){

return 0;
}

void _ttywrch(int ch){
	putchar(ch);
};

void __rt_raise(int signal, int type){
	printf("program stop:%d\r\n",signal);
while(1);
}

#endif
