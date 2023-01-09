
#include "ft_printf.h"

int		ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	if (*str == '-')
	{
		sign = sign * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (sign * (*str - '0') + (result * 10));
		str++;
	}
	return (result);
}

int		ft_itoa(long n, int base, int flag, char *result)
{
	int		i;
	int		size;
	long	digit;

	size = get_size_dec(n, base);
	i = size;
	digit = (long)n;
	if (n < 0)
		digit *= -1;
	result[i--] = '\0';
	while (digit >= 0)
	{
		result[i--] = get_hex_digit(digit % base, flag);
		digit /= base;
		if (digit == 0)
			break ;
	}
	return (size);
}

int		ft_pointer_itoa(unsigned long n, int flag, char *result)
{
	int		i;
	int		size;
	unsigned long	digit;

	size = get_size_ul(n, 16);
	i = size;
	digit = (unsigned long)n;
	if (n < 0)
		digit *= -1;
	result[i--] = '\0';
	while (digit >= 0)
	{
		result[i--] = get_hex_digit(digit % 16, flag);
		digit /= 16;
		if (digit == 0)
			break ;
	}
	return (size);
}

int		ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int		ft_strnlen(const char *str, int max_len)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && i < max_len)
	{
		i++;
	}
	return (i);
}
