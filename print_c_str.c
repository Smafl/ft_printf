/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:18:30 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/20 18:08:02 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int	ft_printf_str(const char *str, t_parameters *parameters)
{
	int	len;
	int	printf_len;
	int	zero_len;
	int	space_len;

	printf_len = 0;
	zero_len = 0;
	space_len = 0;
	if (parameters->flag & FLAG_MINUS)
		parameters->flag &= ~FLAG_ZERO;
	if (parameters->flag & FLAG_PRECISION)
		len = ft_printf_strnlen(str, parameters->precision);
	else
		len = ft_printf_strlen(str);
	if ((parameters->flag & FLAG_ZERO) && parameters->precision > len)
		zero_len = parameters->width - len;
	else if (parameters->width > len)
		space_len = parameters->width - len;
	if (!(parameters->flag & FLAG_MINUS))
	{
		if (ft_printf_space(space_len) == -1)
			return (-1);
		printf_len += space_len;
	}
	if (ft_printf_zero(zero_len) == -1)
		return (-1);
	printf_len += zero_len;
	if (write(1, str, len) == -1)
		return (-1);
	printf_len += len;
	if (parameters->flag & FLAG_MINUS)
	{
		if (ft_printf_space(space_len) == -1)
			return (-1);
		printf_len += space_len;
	}
	return (printf_len);
}

int	ft_printf_c(char c, t_parameters *parameters)
{
	int	printf_len;
	int	zero_len;
	int	space_len;

	printf_len = 0;
	zero_len = 0;
	space_len = 0;
	if (parameters->flag & FLAG_MINUS)
		parameters->flag &= ~FLAG_ZERO;
	if ((parameters->flag & FLAG_ZERO) && parameters->width > 1)
		zero_len = parameters->width - 1;
	else if (parameters->width > 1)
		space_len = parameters->width - 1;
	if (!(parameters->flag & FLAG_MINUS))
	{
		if (ft_printf_space(space_len) == -1)
			return (-1);
		printf_len += space_len;
	}
	if (ft_printf_zero(zero_len) == -1)
		return (-1);
	printf_len += zero_len;
	if (write(1, &c, 1) == -1)
		return (-1);
	printf_len += 1;
	if (parameters->flag & FLAG_MINUS)
	{
		if (ft_printf_space(space_len) == -1)
			return (-1);
		printf_len += space_len;
	}
	return (printf_len);
}
