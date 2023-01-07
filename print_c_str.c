
#include "ft_printf.h"

int print_str(const char *str, int flag, int width, int precision)
{
	int i;
	int len;
	int printf_len;

	printf_len = 0;
	len = ft_strlen(str);
	if ((flag & FLAG_ZERO) && (flag & HAS_PRECISION)
		&& (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		if (width > len)
		{
			if (print_zero(width - len) == -1)
				return (-1);
			else
				printf_len += width - len;
			if (write(1, str, len) == -1)
				return (-1);
			else
				printf_len += len;
		}
		else
		{
			while (precision != 0 && (len > 0))
			{
				if (write(1, str, 1) == -1)
					return (-1);
				else
					printf_len++;
				str++;
				precision--;
			}
		}
	}
	else if ((flag & FLAG_ZERO) && (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
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
// 	else func() 
// func() :if ((flag & HAS_WIDTH) && (flag & HAS_PRECISION) && (flag & FLAG_MINUS))
	else if ((flag & HAS_WIDTH) && (flag & HAS_PRECISION) && (flag & FLAG_MINUS))
	{
		if (width > len && width > precision)
		{
			i = len;
			while (i != 0)
			{
				if (write(1, str, 1) == -1)
					return (-1);
				else
					printf_len += 1;
				i--;
				str++;
			}
			if (print_space(width - len) == -1)
				return (-1);
			else
				printf_len += width - len;
		}
		else
		{
			i = precision;
			while (i != 0)
			{
				if (write(1, str, 1) == -1)
					return (-1);
				else
					printf_len += 1;
				i--;
				str++;
			}
			if (print_space(width - precision) == -1)
				return (-1);
			else
				printf_len += width - precision;
		}
	}
	else if ((flag & HAS_WIDTH) && (flag & HAS_PRECISION))
	{
		if (width > len && width > precision)
		{
			if (print_space(width - len) == -1)
				return (-1);
			else
				printf_len += width - len;
		}
		else
		{
			if (print_space(width - precision) == -1)
				return (-1);
			else
				printf_len += width - precision;
		}
		while (precision != 0)
		{
			if (write(1, str, 1) == -1)
				return (-1);
			else
				printf_len += 1;
			precision--;
			str++;
		}
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
	else if (flag & HAS_PRECISION)
	{
		if (write(1, str, get_max(precision, len)) == -1)
			return (-1);
		else
			printf_len += get_max(precision, len);
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
