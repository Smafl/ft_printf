
#include "ft_printf.h"

int print_str(const char *str, int flag, int width, int precision)
{
	int len;
	int printf_len;

	len = ft_strlen(str);
	printf_len = 0;

	if ((flag & FLAG_ZERO) && (flag & HAS_PRECISION)
		&& (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		if (width > len)
			printf_len += print_zero(width - precision);
		while (precision != 0)
		{
			write(1, str, 1);
			str++;
			precision--;
			printf_len++;
		}
	}
	else if ((flag & FLAG_ZERO) && (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		if (width > len)
			printf_len += print_zero(width - len);
		while (*str)
		{
			write(1, str, 1);
			str++;
			printf_len++;
		}
	}
// 	else func() 
// func() :if ((flag & HAS_WIDTH) && (flag & HAS_PRECISION) && (flag & FLAG_MINUS))
	else if ((flag & HAS_WIDTH) && (flag & HAS_PRECISION) && (flag & FLAG_MINUS))
	{
		while (precision != 0)
		{
			write(1, str, 1);
			str++;
			precision--;
			printf_len++;
		}
		if (width > len)
			printf_len += print_space(width - precision);
	}
	else if ((flag & HAS_WIDTH) && (flag & HAS_PRECISION))
	{
		if (width > len)
			printf_len += print_space(width - precision);
		while (precision != 0)
		{
			write(1, str, 1);
			str++;
			precision--;
			printf_len++;
		}
	}
	else if ((flag & HAS_WIDTH) && (flag & FLAG_MINUS))
	{
		while (*str)
		{
			write(1, str, 1);
			str++;
			printf_len++;
		}
		if (width > len)
			printf_len += print_space(width - len);
	}
	else if (flag & HAS_WIDTH)
	{
		if (width > len)
			printf_len += print_space(width - len);
		while (*str)
		{
			write(1, str, 1);
			str++;
			printf_len++;
		}
	}
	else if (flag & HAS_PRECISION)
	{
		while (precision != 0)
		{
			write(1, str, 1);
			str++;
			precision--;
			printf_len++;
		}
	}
	else
	{
		while (*str)
		{
			write(1, str, 1);
			str++;
			printf_len++;
		}
	}
	return (printf_len);
}

int print_c(char c, int flag, int width)
{
	int printf_len;

	printf_len = 0;
	if ((flag & FLAG_ZERO) && (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		printf_len = print_zero(width - 1) + 1;
		write(1, &c, 1);
	}
	else if ((flag & FLAG_MINUS) && (flag & HAS_WIDTH))
	{
		write(1, &c, 1);
		printf_len = print_space(width - 1) + 1;
	}
	else if (flag & HAS_WIDTH)
	{	
		printf_len = print_space(width - 1) + 1;
		write(1, &c, 1);
	}
	else
	{
		write(1, &c, 1);
		printf_len++;
	}
	return (printf_len);
}
