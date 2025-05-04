/*
 * 	Description: A function that implements functionality similar to the Printf function.
 *			Supports printing of characters, strings, decimal integers, 
 *			octal integers, hexadecimal integers, and addresses.
 */

#include <stdio.h>
#include <stdarg.h>
#include "as32x601.h"
#include "as32x601_usart.h"
#include "myprintf.h"
 
/* Private function prototypes -----------------------------------------------*/
static void PrintNum (unsigned long num, int base);
static void PrintDeci (int dec);
static void PrintOct (unsigned int Oct);
static void PrintHex(unsigned int Hex);
static void PrintAddr (unsigned long addr);
static void PrintStr (char* str);
static void PrintFloat (double f);

/*
 * @brief Support required by the standard library.
 */            
struct __FILE 
{ 
	int handle; 
}; 

// FILE __stdout;    

/*
 * Function:        Printf
 * Description:     Print format string.
 * Param:           S: string address containing format character.
 * 					...: variable parameter.
 * Return:          None.
 */
void Printf(char* S, ...)
{
	int i = 0;

	/* Variable parameter first step */
	va_list va_ptr;

	/* Variable the second step */
	va_start (va_ptr, S);

	/* Loops through all format strings */
	while (S[i] != '\0')
	{
		/* Normal characters are printed */
		if (S[i] != '%')
		{
			Putchar (S[i++]);
			continue;
		}

		/* Format character special handling */
		switch (S[++i]) /* i ++ first to get the format character after '%' */
		{
			/* Different functions are called depending on the format character */
			case 'd': PrintDeci (va_arg (va_ptr, int));
				break;
			case 'o': PrintOct (va_arg (va_ptr, unsigned int));
				break;
			case 'x': PrintHex (va_arg (va_ptr, unsigned int));
				break;
			case 'c': Putchar (va_arg (va_ptr, int));
				break;
			case 'p': PrintAddr (va_arg (va_ptr, unsigned long));
				break;
			case 'f': PrintFloat(va_arg(va_ptr, double));
				break;
			case 's': PrintStr (va_arg (va_ptr, char*));
				break;
			default: break;
		}

		i++; /* Next character */
	}

	/* Variable parameter last step */
	va_end (va_ptr);
}

/*
 * Function:        PrintNum
 * Description:     The universal digital print function can print integer values as
 * 					 base 10 numbers, base 8 numbers, base 2 numbers, base 16 numbers.
 * Param:           num: an integer that needs to be printed, unsigned long integers are 
 * 					 printed for compatibility with address formats.
 * 					base: the printed base.
 * Return:          None.
 */
static void PrintNum(unsigned long num, int base)
{
	/* Recursive end condition */
	if (num == 0)
	{
		return;
	}

	/* Continuing recursion */
	PrintNum (num / base, base);

	/* Print results in reverse order */
	Putchar ("0123456789abcdef"[num % base]);
}

/*
 * Function:        PrintDeci
 * Description:     Print decimal number.
 * Param:           Dec: Decimal integer to be printed.
 * Return:          None.
 */
static void PrintDeci(int Dec)
{
	/* Handles cases where signed integers are negative */
	if (Dec < 0)
	{
		Putchar ('-');
		Dec = -Dec; /* This operation has an overflow risk: the smallest negative number has no corresponding positive number */
	}

	/* Handle the case when the integer is 0 */
	if (Dec == 0)
	{
		Putchar ('0');
		return;
	}
	else
	{
		/* Print decimal number */
		PrintNum (Dec, 10);
	}
}

/*
 * Function:        PrintOct
 * Description:     Print octal integers.
 * Param:           Oct: octal integers to be printed.
 * Return:          None.
 */
static void PrintOct (unsigned int Oct)
{
	/* Handle the case of integer 0 */
	if (Oct == 0)
	{
		Putchar ('0');
		return;
	}
	else
	{
		/* Print a base-8 number */
		PrintNum (Oct, 8);
	}
}

/*
 * Function:        PrintHex
 * Description:     Print a hexadecimal integer.
 * Param:           Hex: hexadecimal integers to be printed.
 * Return:          None.
 */
static void PrintHex(unsigned int Hex)
{
	/* Handle the case of integer 0 */
	if (Hex == 0)
	{
		Putchar ('0');
		return;
	}
	else
	{
		/* Print a hexadecimal integer */
		PrintNum (Hex, 16);
	}
}

/*
 * Function:        PrintAddr
 * Description:     Print a address.
 * Param:           Addr: a address to be printed.
 * Return:          None.
 */
static void PrintAddr(unsigned long Addr)
{
	/* Print lead "0x" */
	Putchar ('0');
	Putchar ('x');

	/* Print address: format is the same as hexadecimal */
	PrintNum (Addr, 16);
}

/*
 * Function:        PrintAddr
 * Description:     Print a address.
 * Param:           Addr: a address to be printed.
 * Return:          None.
 */
__attribute__ ((weak)) void Putchar(const unsigned char ch)
{
	/* Send a character. */
	USART6->TDR = (uint8_t)ch;//lsh
	
	/* Wait for UART to be ready to send. */ 
	while(USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET);
}

/*
 * Function:        PrintStr
 * Description:     Print string.
 * Param:           Str: string address.
 * Return:          None.
 */
static void PrintStr(char* Str)
{
	int i = 0;
	while (Str[i] != '\0')
	{
		Putchar (Str[i++]);
	}
}

/*
 * Function:        PrintFloat
 * Description:     Print floating point number.
 * Param:           F: floating point number to be printed.
 * Return:          None.
 */
static void PrintFloat(double F)
{
	int temp;

	/* Print the integer part first */
	temp = (int)F;
	if(temp == 0)
		Putchar ('0');
	PrintNum (temp, 10);

	/* Decimal separator */
	Putchar ('.');

	/* Print fractional part */
	F -= temp;
	if (F == 0)
	{
		/* Floating-point data with at least six bits of precision */
		for (temp = 0; temp < 6; temp++)
		{
			Putchar ('0');
		}
		return;
	}
	else
	{
		temp = (int)(F * 1000000);
		PrintNum (temp, 10);
	}
}

/*****END OF FILE*****/
