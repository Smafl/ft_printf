/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_diuxp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:02:36 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/21 21:07:15 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

void	ftp_diuxp_param_count(long nbr, t_params *param)
{
	param->zero_len = 0;
	param->space_len = 0;
	if (param->flag & FLAG_PRECISION)
		param->flag &= ~FLAG_ZERO;
	if (nbr == 0 && (param->flag & FLAG_PRECISION) && param->precision == 0)
		param->len = 0;
	else if (param->flag & FLAG_BASE_DEC)
		param->len = ftp_dec_itoa(nbr, param->flag, param->array);
	else
		param->len = ftp_hex_itoa(
				(unsigned long)nbr, param->flag, param->array);
	param->len_with_precision = ftp_get_max(param->precision, param->len);
	param->sign = ftp_get_sign(nbr, param->flag, &param->sign_len);
	param->fill_len = ftp_get_max(
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

int	ftp_write_diuxp(t_params *params, int sign_len, int len)
{
	int	printf_len;

	printf_len = 0;
	if (!(params->flag & FLAG_MINUS))
	{
		if (ftp_space(params->space_len) == -1)
			return (-1);
		printf_len += params->space_len;
	}
	if (write(1, &params->sign, sign_len) == -1)
		return (-1);
	printf_len += sign_len;
	if (ftp_zero(params->zero_len) == -1)
		return (-1);
	printf_len += params->zero_len;
	if (write(1, params-> array, len) == -1)
		return (-1);
	printf_len += len;
	if (params->flag & FLAG_MINUS)
	{
		if (ftp_space(params->space_len) == -1)
			return (-1);
		printf_len += params->space_len;
	}
	return (printf_len);
}

int	ftp_diuxp(long nbr, t_params *params)
{
	int	printf_len;
	int	temp_return;

	printf_len = 0;
	temp_return = 0;
	ftp_diuxp_param_count(nbr, params);
	temp_return = ftp_write_diuxp(
			params, params->sign_len, params->len);
	if (temp_return == -1)
		return (-1);
	return (printf_len += temp_return);
}
