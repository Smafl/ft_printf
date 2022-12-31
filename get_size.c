
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
	// printf("size %d\n", size);
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
