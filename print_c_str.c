/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:18:30 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/21 14:16:31 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int	ft_printf_write_c_str(const char *str, t_parameters *parameters, int len)
{
	int	printf_len;

	printf_len = 0;
	if (!(parameters->flag & FLAG_MINUS))
	{
		if (ft_printf_space(parameters->space_len) == -1)
			return (-1);
		printf_len += parameters->space_len;
	}
	if (ft_printf_zero(parameters->zero_len) == -1)
		return (-1);
	printf_len += parameters->zero_len;
	if (write(1, str, len) == -1)
		return (-1);
	printf_len += len;
	if (parameters->flag & FLAG_MINUS)
	{
		if (ft_printf_space(parameters->space_len) == -1)
			return (-1);
		printf_len += parameters->space_len;
	}
	return (printf_len);
}

int	ft_printf_str(const char *str, t_parameters *parameters)
{
	int	len;
	int	printf_len;
	int	temp_return;

	printf_len = 0;
	temp_return = 0;
	parameters->zero_len = 0;
	parameters->space_len = 0;
	if (parameters->flag & FLAG_MINUS)
		parameters->flag &= ~FLAG_ZERO;
	if (parameters->flag & FLAG_PRECISION)
		len = ft_printf_strnlen(str, parameters->precision);
	else
		len = ft_printf_strlen(str);
	if ((parameters->flag & FLAG_ZERO) && parameters->precision > len)
		parameters->zero_len = parameters->width - len;
	else if (parameters->width > len)
		parameters->space_len = parameters->width - len;
	temp_return = ft_printf_write_c_str(str, parameters, len);
	if (temp_return == -1)
		return (-1);
	return (printf_len += temp_return);
}

int	ft_printf_c(char c, t_parameters *parameters)
{
	int	printf_len;
	int	temp_return;

	printf_len = 0;
	temp_return = 0;
	parameters->zero_len = 0;
	parameters->space_len = 0;
	if (parameters->flag & FLAG_MINUS)
		parameters->flag &= ~FLAG_ZERO;
	if ((parameters->flag & FLAG_ZERO) && parameters->width > 1)
		parameters->zero_len = parameters->width - 1;
	else if (parameters->width > 1)
		parameters->space_len = parameters->width - 1;
	temp_return = ft_printf_write_c_str(&c, parameters, 1);
	if (temp_return == -1)
		return (-1);
	return (printf_len += temp_return);
}
