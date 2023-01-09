
#include "ft_printf.h"

int		print_zero(int width)
{
	int printf_len;

	printf_len = 0;
	while (width != 0)
	{
		if (write(1, "0", 1) == -1)
			return (-1);
		else
		{
			printf_len += 1;
			width--;
		}
	}
	return (printf_len);
}

int		print_space(int width)
{
	int printf_len;

	printf_len = 0;
	while (width != 0)
	{
		if (write(1, " ", 1) == -1)
			return (-1);
		else
		{
			printf_len += 1;
			width--;
		}
	}
	return (printf_len);
}
