
#include "ft_printf.h"

int		get_size_dec(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		size = 1;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

int		get_size_unsigned_dec(unsigned long n)
{
	int	size;

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

int		get_size_hex(long long n)
{
	int	size;

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

void	get_sign(int nbr, int flag)
{
	if (nbr >= 0)
	{	
		if ((flag & FLAG_SPACE) && !(flag & FLAG_PLUS))
			write(1, " ", 1);
		else if (flag & FLAG_PLUS)
			write(1, "+", 1);
	}
	else if (nbr < 0)
		write(1, "-", 1);
}
