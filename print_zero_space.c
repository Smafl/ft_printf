
#include "ft_printf.h"

int print_zero(int width)
{
	int printf_len;

	printf_len = 0;
	while (width != 0)
		{
			write(1, "0", 1);
			width--;
			printf_len++;
		}
	return (printf_len);
}

int print_space(int width)
{
	int printf_len;

	printf_len = 0;
	while (width != 0)
		{
			write(1, " ", 1);
			width--;
			printf_len++;
		}
	return (printf_len);
}
