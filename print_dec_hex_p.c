
#include "ft_printf.h"

int print_p(void *pnt, int flag, int width, int precision)
{
	int size;
	char *array;
	int i;
	int digit;
	int len;
	unsigned long temp;

	size = get_size_hex((unsigned long)pnt);
	i = size - 1;
	temp = (unsigned long)pnt;
	array = malloc(sizeof(char) * (size + 1));
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
	precision = 0;
	free(array);
	return (0);
}

int print_unsigned_x_hex(unsigned long nbr, int flag, int width)
{
	int size;
	char *array;
	int i;
	int digit;
	int len;
	unsigned long ul_nbr;

	size = get_size_hex(nbr);
	i = size - 1;
	ul_nbr = nbr;
	array = malloc(sizeof(char) * (size + 1));
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
	if ((flag & FLAG_ZERO) && (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		if (flag & FLAG_HASH)
		{
			if (width > (len + 2))
				print_zero(width - len - 2);
			write(1, "0x", 2);
		}
		else
		{
			if (width > (len))
				print_zero(width - len);
		}
		write(1, array, len);
	}
	else if ((flag & HAS_WIDTH) && (flag & FLAG_MINUS))
	{
		if (flag & FLAG_HASH)
		{
			write(1, "0x", 2);
			write(1, array, len);
			if (width > (len + 2))
				print_space(width - len - 2);
		}
		else
		{
			write(1, array, len);
			if (width > (len))
				print_space(width - len);
		}
	}
	else if (flag & HAS_WIDTH)
	{
		if (flag & FLAG_HASH)
		{
			if (width > (len + 2))
				print_space(width - len - 2);
			write(1, "0x", 2);
		}
		else
		{
			if (width > (len))
				print_space(width - len);
		}
		write(1, array, len);
	}
	else
	{
		if (flag & FLAG_HASH)
			write(1, "0x", 2);
		write(1, array, len);
	}
	free(array);
	return (0);
}

int print_unsigned_X_hex(unsigned long nbr, int flag, int width)
{
	int size;
	char *array;
	int i;
	int digit;
	int len;
	unsigned long ul_nbr;

	size = get_size_hex(nbr);
	i = size - 1;
	ul_nbr = nbr;
	array = malloc(sizeof(char) * (size + 1));
	if (array == NULL)
		return (0);
	while (i != -1)
	{
		digit = ul_nbr % 16;
		ul_nbr = ul_nbr / 16;
		array[i] = ft_toupper(get_hex_digit(digit));
		i--;
	}
	len = ft_strlen(array);
	if ((flag & FLAG_ZERO) && (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		if (flag & FLAG_HASH)
		{
			if (width > (len + 2))
				print_zero(width - len - 2);
			write(1, "0X", 2);
		}
		else
		{
			if (width > (len))
				print_zero(width - len);
		}
		write(1, array, len);
	}
	else if ((flag & HAS_WIDTH) && (flag & FLAG_MINUS))
	{
		if (flag & FLAG_HASH)
		{
			write(1, "0X", 2);
			write(1, array, len);
			if (width > (len + 2))
				print_space(width - len - 2);
		}
		else
		{
			write(1, array, len);
			if (width > (len))
				print_space(width - len);
		}
	}
	else if (flag & HAS_WIDTH)
	{
		if (flag & FLAG_HASH)
		{
			if (width > (len + 2))
				print_space(width - len - 2);
			write(1, "0X", 2);
		}
		else
		{
			if (width > (len))
				print_space(width - len);
		}
		write(1, array, len);
	}
	else
	{
		if (flag & FLAG_HASH)
			write(1, "0x", 2);
		write(1, array, len);
	}
	free(array);
	return (0);
}

void print_unsigned_dec(int nbr)
{
	char *str_nbr = ft_itoa(nbr);
	while (*str_nbr)
	{
		if (*str_nbr != '-')
			write(1, str_nbr, 1);
		str_nbr++;
	}
	// free(str_nbr);
}
