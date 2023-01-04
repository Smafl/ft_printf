
#include "ft_printf.h"

int	print_p(void *pnt, int flag, int width)
{
	int size;
	char *array;
	int i;
	int digit;
	int len;
	int printf_len;
	unsigned long long temp;

	printf_len = 0;
	size = get_size_hex_ull((unsigned long long)pnt);
	i = size - 1;
	temp = (unsigned long long)pnt;
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
			printf_len += print_zero(width - len - 2);
		write(1, array, len);
		printf_len += (len + 2);
	}
	else if ((flag & FLAG_MINUS) && (flag & HAS_WIDTH))
	{
		write(1, "0x", 2);
		write(1, array, len);
		printf_len += (len + 2);
		if (width > (len + 2))
			printf_len += print_space(width - len - 2);
	}
	else if (flag & HAS_WIDTH)
	{	
		if (width > (len + 2))
			printf_len += print_space(width - len - 2);
		write(1, "0x", 2);
		write(1, array, len);
		printf_len += (len + 2);
	}
	else
	{
		write(1, "0x", 2);
		write(1, array, len);
		printf_len += (len + 2);
	}
	free(array);
	return (printf_len);
}

int	print_unsigned_x_hex(unsigned int nbr, int flag, int width, int precision)
{
	int size;
	char array[8];
	int i;
	int digit;
	int printf_len;

	if (nbr == 0)
		flag &= ~FLAG_HASH;
	printf_len = 0;
	size = get_size_hex_ll(nbr);
	i = size - 1;
	while (i != -1)
	{
		digit = nbr % 16;
		nbr = nbr / 16;
		array[i] = get_hex_digit(digit);
		i--;
	}
	if ((flag & FLAG_ZERO) && (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		if (flag & FLAG_HASH)
		{
			if (width > (size + 2))
				printf_len += print_zero(width - size - 2);
			write(1, "0x", 2);
			printf_len += 2;
		}
		else
		{
			if (width > (size))
				printf_len += print_zero(width - size);
		}
		write(1, array, size);
		printf_len += size;
	}
	else if ((flag & HAS_WIDTH) && (flag & FLAG_MINUS))
	{
		if (flag & FLAG_HASH)
		{
			write(1, "0x", 2);
			write(1, array, size);
			printf_len += (size + 2);
			if (width > (size + 2))
				printf_len += print_space(width - size - 2);
		}
		else
		{
			write(1, array, size);
			printf_len += size;
			if (width > (size))
				printf_len += print_space(width - size);
		}
	}
	else if (flag & HAS_PRECISION)
	{
		if (precision > size)
			printf_len += print_zero(precision - size);
		write(1, array, size);
		printf_len += size;
	}
	else if (flag & HAS_WIDTH)
	{
		if (flag & FLAG_HASH)
		{
			if (width > (size + 2))
				printf_len += print_space(width - size - 2);
			write(1, "0x", 2);
			printf_len += 2;
		}
		else
		{
			if (width > (size))
				printf_len += print_space(width - size);
		}
		write(1, array, size);
		printf_len += size;
	}
	else
	{
		if (flag & FLAG_HASH)
		{
			write(1, "0x", 2);
			printf_len += 2;
		}
		write(1, array, size);
		printf_len += size;
	}
	return (printf_len);
}

int	print_unsigned_X_hex(unsigned int nbr, int flag, int width, int precision)
{
	int size;
	char *array;
	int i;
	int digit;
	int len;
	int printf_len;
	unsigned long ul_nbr;

	if (nbr == 0)
		flag &= ~FLAG_HASH;
	printf_len = 0;
	size = get_size_hex_ll(nbr);
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
		// добавить в get_hex_digit второй параметр
		i--;
	}
	len = ft_strlen(array);
	if ((flag & FLAG_ZERO) && (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		if (flag & FLAG_HASH)
		{
			if (width > (len + 2))
				printf_len += print_zero(width - len - 2);
			write(1, "0X", 2);
			printf_len += 2;
		}
		else
		{
			if (width > (len))
				printf_len += print_zero(width - len);
		}
		write(1, array, len);
		printf_len += len;
	}
	else if ((flag & HAS_WIDTH) && (flag & FLAG_MINUS))
	{
		if (flag & FLAG_HASH)
		{
			write(1, "0X", 2);
			write(1, array, len);
			printf_len += (len + 2);
			if (width > (len + 2))
				printf_len += print_space(width - len - 2);
		}
		else
		{
			write(1, array, len);
			printf_len += len;
			if (width > (len))
				printf_len += print_space(width - len);
		}
	}
	else if (flag & HAS_PRECISION)
	{
		if (precision > len)
			printf_len += print_zero(precision - len);
		write(1, array, len);
		printf_len += len;
	}
	else if (flag & HAS_WIDTH)
	{
		if (flag & FLAG_HASH)
		{
			if (width > (len + 2))
				printf_len += print_space(width - len - 2);
			write(1, "0X", 2);
			printf_len += 2;
		}
		else
		{
			if (width > (len))
				printf_len += print_space(width - len);
		}
		write(1, array, len);
		printf_len += len;
	}
	else
	{
		if (flag & FLAG_HASH)
		{
			write(1, "0X", 2);
			printf_len += 2;
		}
		write(1, array, len);
		printf_len += len;
	}
	free(array);
	return (printf_len);
}

int	print_unsigned_dec(unsigned int nbr, int flag, int width, int precision)
{
	int size;
	char array[16];
	int i;
	int digit;
	int printf_len;

	printf_len = 0;
	size = get_size_unsigned_dec(nbr);
	i = size - 1;
	while (i != -1)
	{
		digit = nbr % 10;
		nbr = nbr / 10;
		array[i] = get_hex_digit(digit);
		i--;
	}
	if ((flag & FLAG_ZERO) && (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		if (width > size)
			printf_len += print_zero(width - size);
		write(1, array, size);
		printf_len += size;
	}
	else if ((flag & HAS_PRECISION) && (flag & HAS_WIDTH) && (flag & FLAG_MINUS))
	{
		if (precision >= width)
		{
			if (precision > size)
				printf_len += print_zero(precision - size);
			write(1, array, size);
			printf_len += size;
		}
		else
		{
			write(1, array, size);
			printf_len += size;
			if (width > size)
				printf_len += print_space(width - size);
		}
	}
	else if ((flag & HAS_WIDTH) && (flag & FLAG_MINUS))
	{
		write(1, array, size);
		printf_len += size;
		if (width > size)
			printf_len += print_space(width - size);
	}
	else if ((flag & HAS_PRECISION) && (flag & HAS_WIDTH))
	{
		if (precision >= width)
		{
			if (precision > size)
				printf_len += print_zero(precision - size);
		}
		else
		{
			if (width > size)
				printf_len += print_space(width - size);
		}
		write(1, array, size);
		printf_len += size;
	}
	else if (flag & HAS_PRECISION)
	{
		if (precision > size)
			printf_len += print_zero(precision - size);
		write(1, array, size);
		printf_len += size;
	}
	else if (flag & HAS_WIDTH)
	{
		if (width > size)
			printf_len += print_space(width - size);
		write(1, array, size);
		printf_len += size;
	}
	else
	{
		write(1, array, size);
		printf_len += size;
	}
	return (printf_len);
}

int print_dec_int(int nbr, int flag, int width, int precision)
{
	int len;
	int has_sign;
	int printf_len;
	char sign;
	char array[16];

	printf_len = 0;
	len = ft_itoa(nbr, array);
	sign = get_sign(nbr, flag, &has_sign);
	if ((flag & FLAG_ZERO) && (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		if (has_sign)
		{
			write(1, &sign, 1);
			printf_len += 1;
		}
		printf_len += print_zero(get_zero_space_len(flag, (len + has_sign), width, precision));
		write(1, array, len);
		printf_len += len;
	}
	else if ((flag & HAS_PRECISION) && (flag & HAS_WIDTH) && (flag & FLAG_MINUS))
	{
		if (precision >= width)
		{
			if (has_sign)
			{
				write(1, &sign, 1);
				printf_len += 1;
			}
			printf_len += print_zero(get_zero_space_len(flag, (len + has_sign), width, precision));
			write(1, array, len);
			printf_len += len;
		}
		else
		{
			if (has_sign)
			{
				write(1, &sign, 1);
				printf_len += 1;
			}
			write(1, array, len);
			printf_len += len;
			printf_len += print_space(get_zero_space_len(flag, (len + has_sign), width, precision));
		}
	}
	else if ((flag & HAS_WIDTH) && (flag & FLAG_MINUS))
	{
		if (has_sign)
		{
			write(1, &sign, 1);
			printf_len += 1;
		}
		write(1, array, len);
		printf_len += len;
		printf_len += print_space(get_zero_space_len(flag, (len + has_sign), width, precision));
	}
	else if ((flag & HAS_PRECISION) && (flag & HAS_WIDTH))
	{
		if (precision >= width)
		{
			if (has_sign)
			{
				write(1, &sign, 1);
				printf_len += 1;
			}
			printf_len += print_zero(get_zero_space_len(flag, (len + has_sign), width, precision));
		}
		else
		{
			printf_len += print_space(get_zero_space_len(flag, (len + has_sign), width, precision));
			if (has_sign)
			{
				write(1, &sign, 1);
				printf_len += 1;
			}
		}
		write(1, array, len);
		printf_len += len;
	}
	else if (flag & HAS_PRECISION)
	{
		if (has_sign)
		{
			write(1, &sign, 1);
			printf_len += 1;
		}
		if (precision > len)
			printf_len += print_zero(precision - len);
		write(1, array, len);
		printf_len += len;
	}
	else if (flag & HAS_WIDTH)
	{
		printf_len += print_space(get_zero_space_len(flag, (len + has_sign), width, precision));
		if (has_sign)
		{
			write(1, &sign, 1);
			printf_len += 1;
		}
		write(1, array, len);
		printf_len += len;
	}
	else
	{
		if (has_sign)
		{
			write(1, &sign, 1);
			printf_len += 1;
		}
		write(1, array, len);
		printf_len += len;
	}
	return (printf_len);
}
