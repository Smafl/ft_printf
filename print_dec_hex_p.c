
#include "ft_printf.h"

int	print_unsigned_hex(unsigned long nbr, int flag, int width, int precision)
{
	int size;
	char array[16];
	int i;
	int digit;
	int printf_len;

	if (nbr == 0 || (long)nbr == LONG_MIN)
		flag &= ~FLAG_HASH;
	printf_len = 0;
	if (flag & FLAG_POINTER)
		size = get_size_hex_ul(nbr);
	else
		size = get_size_hex_uint((unsigned int)nbr);
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
	int len;
	int sign_len;
	int zero_len;
	int space_len;
	int fill_len;
	int len_with_precision;
	int printf_len;
	char sign;
	char array[16];

	if (flag & HAS_PRECISION)
		flag &= ~FLAG_ZERO;
	printf_len = 0;
	if (nbr == 0 && (flag & HAS_PRECISION) && precision == 0)
		len = 0;
	else
		len = ft_itoa(nbr, array);
	len_with_precision = get_max(precision, len);
	sign = get_sign(nbr, flag, &sign_len);
	fill_len = get_max(width - sign_len - len_with_precision, 0);
	if (flag & FLAG_ZERO && !(flag & FLAG_MINUS))
	{
		zero_len = fill_len + (len_with_precision - len);
		space_len = 0;
	}
	else
	{
		zero_len = len_with_precision - len;
		space_len = fill_len;
	}
	if (!(flag & FLAG_MINUS))
			printf_len += print_space(space_len); // add return
	if (write(1, &sign, sign_len) == -1)
		return (-1);
	else
		printf_len += sign_len;
	printf_len += print_zero(zero_len);
	printf_len += write(1, array, len);
	if (flag & FLAG_MINUS)
		printf_len += print_space(space_len);

	return (printf_len);
}
