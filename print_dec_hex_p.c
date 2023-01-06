
#include "ft_printf.h"

int	print_p(void *pnt, int flag, int width)
{
	int size;
	char array[16];
	int i;
	int digit;
	int printf_len;
	unsigned long long temp;

	printf_len = 0;
	size = get_size_hex_ull((unsigned long long)pnt);
	i = size - 1;
	temp = (unsigned long long)pnt;
	while (i != -1)
	{
		digit = temp % 16;
		temp = temp / 16;
		array[i] = get_hex_digit(digit, flag);
		i--;
	}
	if ((flag & FLAG_ZERO) && (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		printf_len += print_prefix(flag);
		if (width > (size + 2))
			printf_len += print_zero(width - size - 2);
		write(1, array, size);
		printf_len += size;
	}
	else if ((flag & FLAG_MINUS) && (flag & HAS_WIDTH))
	{
		printf_len += print_prefix(flag);
		write(1, array, size);
		printf_len += size;
		if (width > (size + 2))
			printf_len += print_space(width - size - 2);
	}
	else if (flag & HAS_WIDTH)
	{	
		if (width > (size + 2))
			printf_len += print_space(width - size - 2);
		printf_len += print_prefix(flag);
		write(1, array, size);
		printf_len += size;
	}
	else
	{
		printf_len += print_prefix(flag);
		write(1, array, size);
		printf_len += size;
	}
	return (printf_len);
}

int	print_unsigned_hex(unsigned long nbr, int flag, int width, int precision)
{
	int size;
	char array[16];
	int i;
	int digit;
	int printf_len;

	if (nbr == 0) // && !(flag & FLAG_POINTER)
		flag &= ~FLAG_HASH;
	printf_len = 0;
	if (flag & FLAG_POINTER)
		size = get_size_hex_ull(nbr);
	else
		size = get_size_hex_ll((unsigned int)nbr);
	i = size - 1;
	while (i != -1)
	{
		digit = nbr % 16;
		nbr = nbr / 16;
		array[i] = get_hex_digit(digit, flag);
		i--;
	}
	if ((flag & FLAG_ZERO) && (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		if (flag & FLAG_HASH || flag & FLAG_POINTER)
		{
			if (width > (size + 2))
			{
				if (print_zero(width - size - 2) == -1)
					return (-1);
				else
					printf_len += width - size - 2;
			}
			if (print_prefix(flag) == -1)
				return (-1);
			else
				printf_len += 2;
		}
		else
		{
			if (width > (size))
			{
				if (print_zero(width - size) == -1)
					return (-1);
				else
					printf_len += width - size;
			}
		}
		if (write(1, array, size) == -1)
			return (-1);
		else
			printf_len += size;
	}
	else if ((flag & HAS_WIDTH) && (flag & FLAG_MINUS))
	{
		if (flag & FLAG_HASH || flag & FLAG_POINTER)
		{
			if (print_prefix(flag) == -1)
				return (-1);
			else
				printf_len += 2;
			if (write(1, array, size) == -1)
				return (-1);
			else
				printf_len += size;
			if (width > (size + 2))
			{
				if (print_space(width - size - 2) == -1)
					return (-1);
				else
					printf_len += width - size - 2;
			}
		}
		else
		{
			if (write(1, array, size) == -1)
				return (-1);
			else
				printf_len += size;
			if (width > (size))
			{
				if (print_space(width - size) == -1)
					return (-1);
				else
					printf_len += width - size;
			};
		}
	}
	else if (flag & HAS_PRECISION)
	{
		if (precision > size)
		{
			if (print_zero(precision - size) == -1)
				return (-1);
			else
				printf_len += precision - size;
		}
		if (write(1, array, size) == -1)
			return (-1);
		else
			printf_len += size;
	}
	else if (flag & HAS_WIDTH)
	{
		if (flag & FLAG_HASH || flag & FLAG_POINTER)
		{
			if (width > (size + 2))
			{
				if (print_space(width - size - 2) == -1)
					return (-1);
				else
					printf_len += width - size - 2;
			}
			if (print_prefix(flag) == -1)
				return (-1);
			else
				printf_len += 2;
		}
		else
		{
			if (width > (size))
			{
				if (print_space(width - size) == -1)
					return (-1);
				else
					printf_len += width - size;
			}
		}
		if (write(1, array, size) == -1)
			return (-1);
		else
			printf_len += size;
	}
	else
	{
		if (flag & FLAG_HASH || flag & FLAG_POINTER)
		{
			if (print_prefix(flag) == -1)
				return (-1);
			else
				printf_len += 2;
		}
		if (write(1, array, size) == -1)
			return (-1);
		else
			printf_len += size;
	}
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
		array[i] = get_hex_digit(digit, flag);
		i--;
	}
	if ((flag & FLAG_ZERO) && (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		if (width > size)
		{
			if (print_zero(width - size) == -1)
				return (-1);
			else
				printf_len += width - size;
		}
		if (write(1, array, size) == -1)
			return (-1);
		else
			printf_len += size;
	}
	else if ((flag & HAS_PRECISION) && (flag & HAS_WIDTH) && (flag & FLAG_MINUS))
	{
		if (precision >= width)
		{
			if (precision > size)
			{
				if (print_zero(precision - size) == -1)
					return (-1);
				else
					printf_len += precision - size;
			}
			if (write(1, array, size) == -1)
				return (-1);
			else
				printf_len += size;
		}
		else
		{
			if (write(1, array, size) == -1)
				return (-1);
			else
				printf_len += size;
			if (width > size)
			{
				if (print_space(width - size) == -1)
					return (-1);
				else
					printf_len += width - size;
			}
		}
	}
	else if ((flag & HAS_WIDTH) && (flag & FLAG_MINUS))
	{
		if (write(1, array, size) == -1)
			return (-1);
		else
			printf_len += size;
		if (width > size)
		{
			if (print_space(width - size) == -1)
				return (-1);
			else
				printf_len += width - size;
		}
	}
	else if ((flag & HAS_PRECISION) && (flag & HAS_WIDTH))
	{
		if (precision >= width)
		{
			if (precision > size)
			{
				if (print_zero(precision - size) == -1)
					return (-1);
				else
					printf_len += precision - size;
			}
		}
		else
		{
			if (width > size)
			{
				if (print_space(width - size) == -1)
					return (-1);
				else
					printf_len += width - size;
			}
		}
		if (write(1, array, size) == -1)
			return (-1);
		else
			printf_len += size;
	}
	else if (flag & HAS_PRECISION)
	{
		if (precision > size)
		{
			if (print_zero(precision - size) == -1)
				return (-1);
			else
				printf_len += precision - size;
		}
		if (write(1, array, size) == -1)
			return (-1);
		else
			printf_len += size;
	}
	else if (flag & HAS_WIDTH)
	{
		if (width > size)
		{
			if (print_space(width - size) == -1)
				return (-1);
			else
				printf_len += width - size;
		}
		if (write(1, array, size) == -1)
			return (-1);
		else
			printf_len += size;
	}
	else
	{
		if (write(1, array, size) == -1)
			return (-1);
		else
			printf_len += size;
	}
	return (printf_len);
}

int print_dec_int(int nbr, int flag, int width, int precision)
{
	int size;
	int has_sign;
	int printf_len;
	char sign;
	char array[16];

	printf_len = 0;
	size = ft_itoa(nbr, array);
	sign = get_sign(nbr, flag, &has_sign);
	if ((flag & FLAG_ZERO) && (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		if (has_sign)
		{
			if (write(1, &sign, 1) == -1)
				return (-1);
			else
				printf_len += 1;
		}
		if (print_zero(get_zero_space_len(flag, (size + has_sign), width, precision)) == -1)
			return (-1);
		else
			printf_len += get_zero_space_len(flag, (size + has_sign), width, precision);
		if (write(1, array, size) == -1)
			return (-1);
		else
			printf_len += size;
	}
	else if ((flag & HAS_PRECISION) && (flag & HAS_WIDTH) && (flag & FLAG_MINUS))
	{
		if (precision >= width)
		{
			if (has_sign)
			{
				if (write(1, &sign, 1) == -1)
					return (-1);
				else
					printf_len += 1;
			}
			if (print_zero(get_zero_space_len(flag, (size + has_sign), width, precision)) == -1)
				return (-1);
			else
				printf_len += get_zero_space_len(flag, (size + has_sign), width, precision);
			if (write(1, array, size) == -1)
				return (-1);
			else
				printf_len += size;
		}
		else
		{
			if (has_sign)
			{
				if (write(1, &sign, 1) == -1)
					return (-1);
				else
					printf_len += 1;
			}
			if (write(1, array, size) == -1)
				return (-1);
			else
				printf_len += size;
			if (print_space(get_zero_space_len(flag, (size + has_sign), width, precision)) == -1)
				return (-1);
			else
				printf_len += get_zero_space_len(flag, (size + has_sign), width, precision);
		}
	}
	else if ((flag & HAS_WIDTH) && (flag & FLAG_MINUS))
	{
		if (has_sign)
		{
			if (write(1, &sign, 1) == -1)
				return (-1);
			else
				printf_len += 1;
		}
		if (write(1, array, size) == -1)
			return (-1);
		else
			printf_len += size;
		if (print_space(get_zero_space_len(flag, (size + has_sign), width, precision)) == -1)
			return (-1);
		else
			printf_len += get_zero_space_len(flag, (size + has_sign), width, precision);
	}
	else if ((flag & HAS_PRECISION) && (flag & HAS_WIDTH))
	{
		if (precision >= width)
		{
			if (has_sign)
			{
				if (write(1, &sign, 1) == -1)
					return (-1);
				else
					printf_len += 1;
			}
			if (print_zero(get_zero_space_len(flag, (size + has_sign), width, precision)) == -1)
				return (-1);
			else
				printf_len += get_zero_space_len(flag, (size + has_sign), width, precision);
		}
		else
		{
			if (print_space(get_zero_space_len(flag, (size + has_sign), width, precision)) == -1)
				return (-1);
			else
				printf_len += get_zero_space_len(flag, (size + has_sign), width, precision);
			if (has_sign)
			{
				if (write(1, &sign, 1) == -1)
					return (-1);
				else
					printf_len += 1;
			}
		}
		if (write(1, array, size) == -1)
			return (-1);
		else
			printf_len += size;
	}
	else if (flag & HAS_PRECISION)
	{
		if (has_sign)
		{
			if (write(1, &sign, 1) == -1)
				return (-1);
			else
				printf_len += 1;
		}
		if (precision > size)
		{
			if (print_zero(precision - size) == -1)
				return (-1);
			else
				printf_len += precision - size;
		}
		if (write(1, array, size) == -1)
			return (-1);
		else
			printf_len += size;
	}
	else if (flag & HAS_WIDTH)
	{
		if (print_space(get_zero_space_len(flag, (size + has_sign), width, precision)) == -1)
			return (-1);
		else
			printf_len += get_zero_space_len(flag, (size + has_sign), width, precision);
		if (has_sign)
		{
			if (write(1, &sign, 1) == -1)
				return (-1);
			else
				printf_len += 1;
		}
		if (write(1, array, size) == -1)
			return (-1);
		else
			printf_len += size;
	}
	else
	{
		if (has_sign)
		{
			if (write(1, &sign, 1) == -1)
				return (-1);
			else
				printf_len += 1;
		}
		if (write(1, array, size) == -1)
			return (-1);
		else
			printf_len += size;
	}
	return (printf_len);
}
