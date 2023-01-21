/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:18:30 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/21 21:07:12 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int	ftp_write_c_str(const char *str, t_params *params, int len)
{
	int	printf_len;

	printf_len = 0;
	if (!(params->flag & FLAG_MINUS))
	{
		if (ftp_space(params->space_len) == -1)
			return (-1);
		printf_len += params->space_len;
	}
	if (ftp_zero(params->zero_len) == -1)
		return (-1);
	printf_len += params->zero_len;
	if (write(1, str, len) == -1)
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

int	ftp_str(const char *str, t_params *params)
{
	int	len;
	int	printf_len;
	int	temp_return;

	printf_len = 0;
	temp_return = 0;
	params->zero_len = 0;
	params->space_len = 0;
	if (params->flag & FLAG_MINUS)
		params->flag &= ~FLAG_ZERO;
	if (params->flag & FLAG_PRECISION)
		len = ftp_strnlen(str, params->precision);
	else
		len = ftp_strlen(str);
	if ((params->flag & FLAG_ZERO) && params->precision > len)
		params->zero_len = params->width - len;
	else if (params->width > len)
		params->space_len = params->width - len;
	temp_return = ftp_write_c_str(str, params, len);
	if (temp_return == -1)
		return (-1);
	return (printf_len += temp_return);
}

int	ftp_c(char c, t_params *params)
{
	int	printf_len;
	int	temp_return;

	printf_len = 0;
	temp_return = 0;
	params->zero_len = 0;
	params->space_len = 0;
	if (params->flag & FLAG_MINUS)
		params->flag &= ~FLAG_ZERO;
	if ((params->flag & FLAG_ZERO) && params->width > 1)
		params->zero_len = params->width - 1;
	else if (params->width > 1)
		params->space_len = params->width - 1;
	temp_return = ftp_write_c_str(&c, params, 1);
	if (temp_return == -1)
		return (-1);
	return (printf_len += temp_return);
}
