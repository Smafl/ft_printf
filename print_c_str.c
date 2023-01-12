
#include "ft_printf.h"

int	print_str(const char *str, int flag, int width, int precision)
{
	int	len;
	int	printf_len;
	int	zero_len;
	int	space_len;
	int	temp_len;

	printf_len = 0;
	if (flag & FLAG_MINUS)
		flag &= ~FLAG_ZERO;
	if (flag & HAS_PRECISION)
		len = ft_strnlen(str, precision);
	else
		len = ft_strlen(str);
	if ((flag & FLAG_ZERO) && width > len)
	{
		zero_len = width - len;
		space_len = 0;
	}
	else if (width > len)
	{
		zero_len = 0;
		space_len = width - len;
	}
	else
	{
		zero_len = 0;
		space_len = 0;
	}
	if (!(flag & FLAG_MINUS))
	{
		if (print_space(space_len) == -1)
			return (-1);
		else
			printf_len += space_len;
	}
	if (print_zero(zero_len) == -1)
		return (-1);
	else
		printf_len += zero_len;
	if (write(1, str, len) == -1)
		return (-1);
	else
		printf_len += len;
	if (flag & FLAG_MINUS)
	{
		if (print_space(space_len) == -1)
			return (-1);
		else
			printf_len += space_len;
	}
	return (printf_len);
}

int	print_c(char c, int flag, int width)
{
	int	printf_len;
	int	zero_len;
	int	space_len;

	printf_len = 0;
	if (flag & FLAG_MINUS)
		flag &= ~FLAG_ZERO;
	if ((flag & FLAG_ZERO) && width > 1)
	{
		zero_len = width - 1;
		space_len = 0;
	}
	else if (width > 1)
	{
		zero_len = 0;
		space_len = width - 1;
	}
	else
	{
		zero_len = 0;
		space_len = 0;
	}
	if (!(flag & FLAG_MINUS))
	{
		if (print_space(space_len) == -1)
			return (-1);
		else
			printf_len += space_len;
	}
	if (print_zero(zero_len) == -1)
		return (-1);
	else
		printf_len += zero_len;
	if (write(1, &c, 1) == -1)
		return (-1);
	else
		printf_len += 1;
	if (flag & FLAG_MINUS)
	{
		if (print_space(space_len) == -1)
			return (-1);
		else
			printf_len += space_len;
	}
	return (printf_len);
}
