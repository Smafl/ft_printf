// 
#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

int checker(void)
{
	// ft_printf(" %20d %-50d %020d %d %d %d %d\n", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	// ft_printf(" %x %x %x %x %x %x %x\n", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	// ft_printf(" %X %X %X %X %X %X %X\n", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	// printf("\n");
	// printf(" %u %u %u %u %u %u %u\n", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	// printf(" %x %x %x %x %x %x %x\n", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	// printf(" %X %X %X %X %X %X %X\n", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	printf("%llx\n", 9223372036854775807);
	// ft_printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%", 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
	// printf("\n");
	// printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%", 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
	return (0);
}

int main()
{
	checker();
	// system("leaks a.out");
	return (0);
}

/*
%[flags][width][.precision]type

flags:
- -- left-align the output
if - and 0 (zero) are used, then 0 (zero) have to be override
If a precision is given with a numeric conversion (d, i, o, u, i, x, and X), the 0 flag is ignored;
+ -- add sign for number
if space and + are used, space have to be override;
space -- add sign before negative number and a space before positive number;
0 (zero) -- add zeros before numeric types when the 'width' option specified
(the defoult prepends spaces);
# -- for x, X, p in our ft_printf (For x and X conversions, a non-zero result
has the string `0x' (or `0X' for X conversions) prepended to it);

width: numeric integer value (minimum number of characters)
f.e.: printf("%5d", 10) --> <___10>

precision: dot and numeric integer value (maximum limit on the output)
f.e.: printf("%.*s", 3, "abcde") --> <abc>
if the precision is given as just '.', the precision is taken as zero
if the pricision is given as negative integer, the precision is omitted

type:
%c Prints a single character.
%s Prints a string (as defined by the common C convention).
%p The void * pointer argument has to be printed in hexadecimal format.
%d Prints a decimal (base 10) number.
%i Prints an integer in base 10.
%u Prints an unsigned decimal (base 10) number.
%x Prints a number in hexadecimal (base 16) lowercase format.
%X Prints a number in hexadecimal (base 16) uppercase format.
%% Prints a percent sign.

functions return the number of characters printed
(excluding the null byte used to end output to strings)
*/
