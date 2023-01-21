/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_diuxp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:02:36 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/21 14:15:52 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

void	ft_printf_diuxp_param_count(long nbr, t_parameters *param)
{
	param->zero_len = 0;
	param->space_len = 0;
	if (param->flag & FLAG_PRECISION)
		param->flag &= ~FLAG_ZERO;
	if (nbr == 0 && (param->flag & FLAG_PRECISION) && param->precision == 0)
		param->len = 0;
	else if (param->flag & FLAG_BASE_DEC)
		param->len = ft_printf_dec_itoa(nbr, param->flag, param->array);
	else
		param->len = ft_printf_hex_itoa(
				(unsigned long)nbr, param->flag, param->array);
	param->len_with_precision = ft_printf_get_max(param->precision, param->len);
	param->sign = ft_printf_get_sign(nbr, param->flag, &param->sign_len);
	param->fill_len = ft_printf_get_max(
			param->width - param->sign_len - param->len_with_precision, 0);
	if (param->flag & FLAG_ZERO && !(param->flag & FLAG_MINUS))
		param->zero_len = param->fill_len + (
				param->len_with_precision - param->len);
	else
	{
		param->zero_len = param->len_with_precision - param->len;
		param->space_len = param->fill_len;
	}
}

int	ft_printf_write_diuxp(t_parameters *parameters, int sign_len, int len)
{
	int	printf_len;

	printf_len = 0;
	if (!(parameters->flag & FLAG_MINUS))
	{
		if (ft_printf_space(parameters->space_len) == -1)
			return (-1);
		printf_len += parameters->space_len;
	}
	if (write(1, &parameters->sign, sign_len) == -1)
		return (-1);
	printf_len += sign_len;
	if (ft_printf_zero(parameters->zero_len) == -1)
		return (-1);
	printf_len += parameters->zero_len;
	if (write(1, parameters-> array, len) == -1)
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

int	ft_printf_diuxp(long nbr, t_parameters *parameters)
{
	int	printf_len;
	int	temp_return;

	printf_len = 0;
	temp_return = 0;
	ft_printf_diuxp_param_count(nbr, parameters);
	temp_return = ft_printf_write_diuxp(
			parameters, parameters->sign_len, parameters->len);
	if (temp_return == -1)
		return (-1);
	return (printf_len += temp_return);
}
