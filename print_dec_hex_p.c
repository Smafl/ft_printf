/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dec_hex_p.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:02:36 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/11 18:06:46 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_dec_int(long nbr, int flag, int width, int precision, int base)
{
	int				len;
	int				sign_len;
	int				zero_len;
	int				space_len;
	int				fill_len;
	int 			len_with_precision;
	int 			printf_len;
	unsigned short	sign;
	char			array[18];

	printf_len = 0;
	if (nbr == LONG_MIN && !(flag & FLAG_POINTER))
		flag &= ~FLAG_HASH;
	if (flag & HAS_PRECISION)
		flag &= ~FLAG_ZERO;
	if (nbr == 0 && (flag & HAS_PRECISION) && precision == 0)
		len = 0;
	else if (base == 16)
		len = ft_pointer_itoa((unsigned long)nbr, flag, array);
	else
		len = ft_itoa(nbr, base, flag, array);
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
	{
		if (print_space(space_len) == -1)
			return (-1);
		else
			printf_len += space_len;
	}
	if (write(1, &sign, sign_len) == -1)
		return (-1);
	else
		printf_len += sign_len;
	if (print_zero(zero_len) == -1)
		return (-1);
	else
		printf_len += zero_len;
	if (write(1, array, len) == -1)
		return (-1);
	else
		printf_len += len;
	if (flag & FLAG_MINUS)
	{
		if (print_space(space_len) == -1)
			return (-1);
		else
			printf_len += space_len;
	}
	return (printf_len);
}
