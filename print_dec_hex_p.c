
#include "ft_printf.h"

int print_dec_int(long nbr, int flag, int width, int precision, int base)
{
	int len;
	int sign_len;
	int zero_len;
	int space_len;
	int fill_len;
	int len_with_precision;
	int printf_len;
	unsigned short sign;
	char array[16];

	if (nbr == LONG_MIN && !(flag & FLAG_POINTER))
		flag &= ~FLAG_HASH;
	if (flag & HAS_PRECISION)
		flag &= ~FLAG_ZERO;
	printf_len = 0;
	if (nbr == 0 && (flag & HAS_PRECISION) && precision == 0)
		len = 0;
	else if (flag & FLAG_POINTER)
		len = ft_pointer_itoa((unsigned long)nbr, flag, array);
	else
		len = ft_itoa(nbr, base, flag,  array);
	len_with_precision = get_max(precision, len);
	sign = get_sign(nbr, flag, base, &sign_len);
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

// int print_dec_int(long nbr, int flag, int width, int precision)
// {
// 	int len;
// 	int sign_len;
// 	int zero_len;
// 	int space_len;
// 	int fill_len;
// 	int len_with_precision;
// 	int printf_len;
// 	char sign;
// 	char array[16];

// 	if (flag & HAS_PRECISION)
// 		flag &= ~FLAG_ZERO;
// 	printf_len = 0;
// 	if (nbr == 0 && (flag & HAS_PRECISION) && precision == 0)
// 		len = 0;
// 	else
// 		len = ft_itoa(nbr, array);
// 	len_with_precision = get_max(precision, len);
// 	sign = get_sign(nbr, flag, &sign_len);
// 	fill_len = get_max(width - sign_len - len_with_precision, 0);
// 	if (flag & FLAG_ZERO && !(flag & FLAG_MINUS))
// 	{
// 		zero_len = fill_len + (len_with_precision - len);
// 		space_len = 0;
// 	}
// 	else
// 	{
// 		zero_len = len_with_precision - len;
// 		space_len = fill_len;
// 	}
// 	if (!(flag & FLAG_MINUS))
// 			printf_len += print_space(space_len); // add return
// 	if (write(1, &sign, sign_len) == -1)
// 		return (-1);
// 	else
// 		printf_len += sign_len;
// 	printf_len += print_zero(zero_len);
// 	printf_len += write(1, array, len);
// 	if (flag & FLAG_MINUS)
// 		printf_len += print_space(space_len);

// 	return (printf_len);
// }
