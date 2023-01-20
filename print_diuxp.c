/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_diuxp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:02:36 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/20 19:42:35 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int	ft_printf_diuxp(long nbr, int flag, t_parameters *parameters)
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
	space_len = 0;
	if (flag & FLAG_PRECISION)
		flag &= ~FLAG_ZERO;
	if (nbr == 0 && (flag & FLAG_PRECISION) && parameters->precision == 0)
		len = 0;
	else if (flag & FLAG_BASE_DEC)
		len = ft_printf_dec_itoa(nbr, flag, array);
	else
		len = ft_printf_hex_itoa((unsigned long)nbr, flag, array);
	len_with_precision = ft_printf_get_max(parameters->precision, len);
	sign = ft_printf_get_sign(nbr, flag, &sign_len);
	fill_len = ft_printf_get_max(parameters->width - sign_len - len_with_precision, 0);
	if (flag & FLAG_ZERO && !(flag & FLAG_MINUS))
		zero_len = fill_len + (len_with_precision - len);
	else
	{
		zero_len = len_with_precision - len;
		space_len = fill_len;
	}
	if (!(flag & FLAG_MINUS))
	{
		if (ft_printf_space(space_len) == -1)
			return (-1);
		else
			printf_len += space_len;
	}
	if (write(1, &sign, sign_len) == -1)
		return (-1);
	else
		printf_len += sign_len;
	if (ft_printf_zero(zero_len) == -1)
		return (-1);
	else
		printf_len += zero_len;
	if (write(1, array, len) == -1)
		return (-1);
	else
		printf_len += len;
	if (flag & FLAG_MINUS)
	{
		if (ft_printf_space(space_len) == -1)
			return (-1);
		else
			printf_len += space_len;
	}
	return (printf_len);
}
