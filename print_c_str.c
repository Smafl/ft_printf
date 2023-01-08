
#include "ft_printf.h"

int print_str(const char *str, int flag, int width, int precision)
{
	int len;
	int printf_len;

	printf_len = 0;
	if (flag & HAS_PRECISION)
		len = ft_strnlen(str, precision);
	else
		len = ft_strlen(str);
	if ((flag & FLAG_ZERO) && (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		if (width > len)
		{
			if (print_zero(width - len) == -1)
				return (-1);
			else
				printf_len += width - len;
		}
		if (write(1, str, len) == -1)
			return (-1);
		else
			printf_len += len;
	}
	else if ((flag & HAS_WIDTH) && (flag & FLAG_MINUS))
	{
		if (write(1, str, len) == -1)
			return (-1);
		else
			printf_len += len;
		if (width > len)
		{
			if (print_space(width - len) == -1)
				return (-1);
			else
				printf_len += width - len;
		}
	}
	else if (flag & HAS_WIDTH)
	{
		if (width > len)
		{
			if (print_space(width - len) == -1)
				return (-1);
			else
				printf_len += width - len;
		}
		if (write(1, str, len) == -1)
			return (-1);
		else
			printf_len += len;
	}
	else
	{
		if (write(1, str, len) == -1)
			return (-1);
		else
			printf_len += len;
	}
	return (printf_len);
}

int print_c(char c, int flag, int width)
{
	int printf_len;

	printf_len = 0;
	if ((flag & FLAG_ZERO) && (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		if (print_zero(width - 1) == -1)
			return (-1);
		else
			printf_len += width -1;
		if (write(1, &c, 1) == -1)
			return (-1);
		else
			printf_len += 1;
	}
	else if ((flag & FLAG_MINUS) && (flag & HAS_WIDTH))
	{
		if (write(1, &c, 1) == -1)
			return (-1);
		else
			printf_len += 1;
		if (print_space(width - 1) == -1)
			return (-1);
		else
			printf_len += width -1;
	}
	else if (flag & HAS_WIDTH)
	{	
		if (print_space(width - 1) == -1)
			return (-1);
		else
			printf_len += width -1;
		if (write(1, &c, 1) == -1)
			return (-1);
		else
			printf_len += 1;
	}
	else
	{
		if (write(1, &c, 1) == -1)
			return (-1);
		else
			printf_len += 1;
	}
	return (printf_len);
}
