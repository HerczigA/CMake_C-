#ifndef _UART_INCLUDED_H
#define _UART_INCLUDED_H

#include <termios.h>
#include <stdint.h>


struct term
{
    termios old;
    termios term;
    int BAUD;
    int uartFD;
};



#endif