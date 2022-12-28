
#include "ft_printf.h"

static int print_p(void *pnt, int flag, int width, int precision)
{
	size_t size;
	char *array;
	int i;
	int digit;
	int len;
	size_t temp;

	size = get_size_t((size_t)pnt);
	i = size - 1;
	temp = (size_t)pnt;
	array = malloc(sizeof(char) * size);
	if (array == NULL)
		return (0);
	while (i != -1)
	{
		digit = temp % 16;
		temp = temp / 16;
		array[i] = get_hex_digit(digit);
		i--;
	}
	len = ft_strlen(array);
	if ((flag & FLAG_ZERO) && (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		write(1, "0x", 2);
		if (width > (len + 2))
			print_zero(width - len - 2);
		write(1, array, len);
	}
	else if ((flag & FLAG_MINUS) && (flag & HAS_WIDTH))
	{
		write(1, "0x", 2);
		write(1, array, len);
		if (width > (len + 2))
			print_space(width - len - 2);
	}
	else if (flag & HAS_WIDTH)
	{	
		if (width > (len + 2))
			print_space(width - len - 2);
		write(1, "0x", 2);
		write(1, array, len);
	}
	else
	{
		write(1, "0x", 2);
		write(1, array, len);
	}
	free(array);
	return (0);
}

static int print_unsigned_x_hex(int nbr, int flag, int width, int precision)
{
	size_t size;
	char *array;
	int i;
	int digit;
	int len;
	size_t ul_nbr;

	size = get_size_t((size_t)nbr);
	i = size - 1;
	ul_nbr = (size_t)nbr;
	array = malloc(sizeof(char) * size);
	if (array == NULL)
		return (0);
	while (i != -1)
	{
		digit = ul_nbr % 16;
		ul_nbr = ul_nbr / 16;
		array[i] = get_hex_digit(digit);
		i--;
	}
	len = ft_strlen(array);
	if ((flag & FLAG_ZERO) && (flag & HAS_PRECISION)
		&& (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		if (flag & FLAG_HASH)
			write(1, "0x", 2);
		if (width > (len + 2))
			print_zero(width - len - 2);
		write(1, array, size);
	}
	else if ((flag & FLAG_ZERO) && (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		if (flag & FLAG_HASH)
			write(1, "0x", 2);
		if (width > (len + 2))
			print_zero(width - len - 2);
		write(1, array, len);
	}
	// else if ((flag & HAS_WIDTH) && (flag & HAS_PRECISION) && (flag & FLAG_MINUS))
	// {

	// }
	// else if ((flag & HAS_WIDTH) && (flag & HAS_PRECISION))
	// {

	// }
	// else if ((flag & HAS_WIDTH) && (flag & FLAG_MINUS))
	// {

	// }
	// else if (flag & HAS_WIDTH)
	// {

	// }
	// else if (flag & HAS_PRECISION)
	// {

	// }
	else
	{
		if (flag & FLAG_HASH)
			write(1, "0x", 2);
		write(1, array, size);
	}
	// write(1, array, size);
	free(array);
	return (0);
}

static void print_unsigned_X_hex(int nbr)
{
	int size = (int)get_size(nbr);
	char array[size];
	int i;
	int digit;
	unsigned long ul_nbr;

	i = size - 1;
	ul_nbr = (unsigned long)nbr;
	while (i != -1)
	{
		digit = ul_nbr % 16;
		ul_nbr = ul_nbr / 16;
		array[i] = ft_toupper(get_hex_digit(digit));
		i--;
	}
	write(1, array, size);
}

static void print_unsigned_dec(int nbr)
{
	char *str_nbr = ft_itoa(nbr);
	while (*str_nbr)
	{
		if (*str_nbr != '-')
			write(1, str_nbr, 1);
		str_nbr++;
	}
}
