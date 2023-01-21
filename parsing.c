/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:27:54 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/21 21:30:59 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

void	ftp_init(
	const char *str, t_params *params, int *len, int *temp_return)
{
	params->width = 0;
	params->precision = 0;
	params->text_start = str;
	params->state = STATE_TEXT;
	*len = 0;
	*temp_return = 0;
}

enum e_state	ftp_get_new_state(char c, t_params *params)
{
	if (params->state == STATE_TEXT)
		return (ftp_if_state_text(c));
	if (params->state == STATE_FORMAT)
		return (ftp_if_state_format(c, params));
	if (params->state == STATE_FLAG)
		return (ftp_if_state_flag(c, params));
	if (params->state == STATE_WIDTH)
		return (ftp_if_state_width(c));
	if (params->state == STATE_UNDEF_PRECISION)
		return (ftp_if_state_undef_precision(c));
	if (params->state == STATE_PRECISION)
		return (ftp_if_state_precision(c));
	if (params->state == STATE_TYPE)
		return (ftp_if_state_type(c));
	return (params->state);
}

int	ftp_ev(const char *str, va_list args, t_params *params, int *len)
{
	int	tmp;

	tmp = 0;
	if (str[-1] == '%')
		tmp = ftp_c('%', params);
	else if (str[-1] == 's')
		tmp = ftp_if_is_str(va_arg(args, char *), params);
	else if (str[-1] == 'c')
		tmp = ftp_c(va_arg(args, int), params);
	else if (str[-1] == 'd' || str[-1] == 'i')
	{
		params->flag |= FLAG_BASE_DEC;
		tmp = ftp_diuxp(va_arg(args, int), params);
	}
	else if (str[-1] == 'u')
		tmp = ftp_set_flag(args, params);
	else if (str[-1] == 'x' || str[-1] == 'X')
		tmp = ftp_if_is_hex(str, va_arg(args, unsigned int), params);
	else if (str[-1] == 'p')
		tmp = ftp_if_is_pointer(
				(unsigned long)va_arg(args, void *), params);
	if (tmp == -1)
		return (0);
	*len += tmp;
	return (1);
}

static void	ftp_set_zero(t_params *params)
{
	params->flag = 0;
	params->precision = 0;
	params->width = 0;
}

int	ftp_param_set(const char *str, t_params *params, int *temp_len)
{
	*temp_len = 0;
	if (params->state == STATE_TEXT)
	{
		if (write(1, params->text_start, str - params->text_start) == -1)
			return (-1);
		*temp_len += str - params->text_start;
	}
	if (params->new_state == STATE_WIDTH)
	{
		params->width = ftp_atoi(str);
		params->flag |= FLAG_WIDTH;
	}
	if (params->new_state == STATE_UNDEF_PRECISION)
		params->precision = !(params->flag |= FLAG_PRECISION);
	if (params->new_state == STATE_PRECISION)
		params->precision = ftp_atoi(str);
	if (params->new_state == STATE_FORMAT)
		ftp_set_zero(params);
	if (params->new_state == STATE_TEXT)
		params->text_start = str;
	return (*temp_len == -1);
}
