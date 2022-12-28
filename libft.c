
#include "ft_printf.h"

int	ft_atoi(const char *str)
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

char	*ft_itoa(int n)
{
	char	*result;
	int		size;
	long	digit;

	size = get_size(n);
	result = malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	digit = (long)n;
	if (n < 0)
	{
		digit *= -1;
		*result = '-';
	}
	result[size--] = '\0';
	while (digit >= 0)
	{
		result[size--] = (digit % 10) + '0';
		digit /= 10;
		if (digit == 0)
			break ;
	}
	return (result);
}

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		c = c - ('a' - 'A');
		return (c);
	}
	else
		return (c);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
