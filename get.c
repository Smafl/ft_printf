
#include "ft_printf.h"

size_t	get_size(int n)
{
	size_t	size;

	size = 0;
	if (n <= 0)
		size = 1;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

size_t get_size_t(size_t n)
{
	size_t	size;

	size = 0;
	if (n <= 0)
		size = 1;
	while (n)
	{
		n /= 16;
		size++;
	}
	return (size);
}

char	get_hex_digit(int digit)
{
	char c;

	if (digit < 10)
	{
		c = '0' + digit;
	}
	else
	{
		c = 'a' + digit - 10;
	}
	return (c);
}
