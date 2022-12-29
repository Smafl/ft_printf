
#include "ft_printf.h"
#include <stdio.h>

int checker(void)
{

	int a = 10;

	// ft_printf("print %%: %%\n\n");
	// printf("print %%: %10%\n");

	// ft_printf("1 ft_print s: %-15.5s\n\n", "string");

	// printf("1 st_print s: %-15.5s\n", "string");

	// ft_printf("1 print c: %.0c\n", 'c');
	// ft_printf("2 print c: %010c\n", 'c');
	// ft_printf("3 print c: %-10c\n", 'c');
	// ft_printf("4 print c: %-010c\n\n", 'c');

	// printf("1 print c: %.0c\n", 'c');
	// printf("2 print c: %010c\n", 'c');
	// printf("3 print c: %-10c\n", 'c');
	// printf("4 print c: %-010c\n", 'c');

	ft_printf("ft print d: % d\n", INT_MIN);
	ft_printf("ft print i: % i\n", INT_MIN);
	ft_printf("ft print 0: [% i] [%+i]\n", 0, 0);
	printf("st print 0: [% i] [%+i]\n", 0, 0);
	printf("st print d: % d\n", INT_MIN);
	printf("st print i: % i\n", INT_MIN);
	// ft_printf("ft print u: [%13.3u]\n", INT_MIN);
	// ft_printf("ft print u: [%3.13u]\n", INT_MIN);
	// ft_printf("ft print u: [%13.13u]\n", INT_MIN);
	// ft_printf("ft print u: [%-13.3u]\n", INT_MIN);
	// ft_printf("ft print u: [%-3.13u]\n\n", INT_MIN);

	// printf("st print u: [%13.3u]\n", INT_MIN);
	// printf("st print u: [%3.13u]\n", INT_MIN);
	// printf("st print u: [%13.13u]\n", INT_MIN);
	// printf("ft print u: [%-13.3u]\n", INT_MIN);
	// printf("ft print u: [%-3.13u]\n\n", INT_MIN);

	// ft_printf("ft print x: [%#-15x]\n", -376237); // 5bdad
	// printf("st print x: [%#-15x]\n", -376237); // 5bdad

	// ft_printf("ft print X: [%#-8.3X]\n", -376237);
	// printf("st print X: [%#-8.3X]\n", -376237);

	// ft_printf("ft print addr [%-30p]\n", &a);
	// printf("st print addr [%-30p]\n", &a);

	// ft_printf("print %c and %% and %p\n", 'r', &a);
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
