
#include "ft_printf.h"

int		get_size_dec(long n, int base)
{
	int	size;

	size = 0;
	if (n == 0)
		size = 1;
	while (n)
	{
		n /= base;
		size++;
	}
	return (size);
}

int		get_size_ul(unsigned long n, int base)
{
	int	size;

	size = 0;
	if (n <= 0)
		size = 1;
	while (n)
	{
		n /= base;
		size++;
	}
	return (size);
}
