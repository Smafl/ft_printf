#include <stdio.h>

#define FLAG_A (1 << 0)
#define FLAG_B (1 << 1)
#define FLAG_C (1 << 2)
#define FLAG_D (1 << 3)
 
void print_flags(int flags) {
	if (flags & FLAG_A) printf("Flag A is set\n");
	if (flags & FLAG_B) printf("Flag B is set\n");
	if (flags & FLAG_C) printf("Flag C is set\n");
	if (flags & FLAG_D) printf("Flag D is set\n");
}

int main(void)
{
	// int flags = FLAG_A | FLAG_C;
 
	// print_flags(flags);
 
	// flags |= FLAG_B;
	// printf("\n\n");
	// print_flags(flags);
 
	// flags &= ~FLAG_A;
	// printf("\n\n");
	// print_flags(flags);

	char *pnt = "hi";

	// printf("Flag -:\n");
	// printf("Color %25s\n", "red");
	// printf("Color %-25s\n", "red");
	// printf("Flag + and space:\n");
	// printf("%+d, %+d, % d, % d\n", 5, -5, 10, -10);
	// printf("% s\n", "Color");
	// printf("%+f\n", 3.3);
	// printf("Flag 0:\n");
	// printf("%05d\n", 7);
	// printf("%02d\n", 7);
	// printf("Flag #:\n");
	// printf("%x, %X, %#x, %#X\n", 10, 10, 10, 10);
	// printf("%x, %X, %#x, %#X\n", 16, 16, 16, 16);
	// printf("If no format specification after after per cent:\n");
	// printf("Color%ye;;ow\n");
	// printf("[.precision]:\n");
	// printf("%.10s\n", "Color");
	// printf("%.s\n", "Color");
	// printf("%.-10s\n", "Color");
	// printf("%.-0s\n", "Color");
	// printf("%.Krampus\n");
	// printf("%.shhh\n");
	// printf("Width:\n");
	// printf("%5d\n", 10);
	// printf("smafl%0-y123\n");

	// printf("pointer: %p\n", pnt);

	// printf("%x\n", 34764);
	// printf("%#x\n", 34764);

	// printf("color is %.2s\n", "yellow");
	// printf("color is %0-5d", 55);
	
	// printf("hi %10c\n", 'k');
	// printf("hi %-10c\n", 'g');
	// printf("hi %-c\n", 'g');
	// printf("hi %10c\n", 'g');
	// printf("hi %-010c\n", 'g');
	// printf("hi %.c\n", 'l');
	// printf("hi %.0c\n", 'g');

	// printf("hi %.s\n", "smafl");

	printf("[%8s]\n", "hihi");
	printf("[%3.8s]\n", "hihi");
	printf("[%8.3s]\n", "hihi");
	printf("[%8d]\n", 9);
	printf("[%3.8d]\n", 9);
	printf("[%8.3d]\n", 1234);
	printf("[%-3.8d]\n", 9);
	printf("[%-8.3d]\n", 9);
	printf("[%-10s]\n", "text");
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