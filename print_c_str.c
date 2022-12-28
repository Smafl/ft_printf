
#include "ft_printf.h"

static void print_s(const char *str, int flag, int width, int precision)
{
	int len;

	len = ft_strlen(str);

	// if (flag & FLAG_MINUS) printf("minus\n");
	// if (flag & FLAG_HASH) printf("hash\n");
	// if (flag & FLAG_ZERO) printf("zero\n");
	// if (flag & FLAG_SPACE) printf("space\n");
	// if (flag & FLAG_PLUS) printf("plus\n");
	// if (flag & HAS_PRECISION) printf("precision\n");
	// if (flag & HAS_WIDTH) printf("width\n");

	if ((flag & FLAG_ZERO) && (flag & HAS_PRECISION)
		&& (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		if (width > len) print_zero(width - precision);
		while (precision != 0)
		{
			write(1, str, 1);
			str++;
			precision--;
		}
	}
	else if ((flag & FLAG_ZERO) && (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		if (width > len) print_zero(width - len);
		while (*str)
		{
			write(1, str, 1);
			str++;
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
		}
		if (width > len) print_space(width - precision);
	}
	else if ((flag & HAS_WIDTH) && (flag & HAS_PRECISION))
	{
		if (width > len) print_space(width - precision);
		while (precision != 0)
		{
			write(1, str, 1);
			str++;
			precision--;
		}
	}
	else if ((flag & HAS_WIDTH) && (flag & FLAG_MINUS))
	{
		while (*str)
		{
			write(1, str, 1);
			str++;
		}
		if (width > len) print_space(width - len);
	}
	else if (flag & HAS_WIDTH)
	{
		if (width > len) print_space(width - len);
		while (*str)
		{
			write(1, str, 1);
			str++;
		}
	}
	else if (flag & HAS_PRECISION)
	{
		while (precision != 0)
		{
			write(1, str, 1);
			str++;
			precision--;
		}
	}
	else
	{
		while (*str)
		{
			write(1, str, 1);
			str++;
		}
	}
}

static void print_c(char c, int flag, int width, int precision)
{
	if ((flag & FLAG_ZERO) && (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		print_zero(width - 1);
		write(1, &c, 1);
	}
	else if ((flag & FLAG_MINUS) && (flag & HAS_WIDTH))
	{
		write(1, &c, 1);
		print_space(width - 1);
	}
	else if (flag & HAS_WIDTH)
	{	print_space(width - 1);
		write(1, &c, 1);
	}
	else
		write(1, &c, 1);
}