/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:39:08 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/21 21:06:45 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int	ftp_set_flag(va_list args, t_params *params)
{
	params->flag |= FLAG_BASE_DEC;
	params->flag &= ~FLAG_PLUS;
	params->flag &= ~FLAG_SPACE;
	return (ftp_diuxp(va_arg(args, unsigned int), params));
}

int	ftp_if_is_str(const char *args_str, t_params *params)
{
	int	printf_len;

	printf_len = 0;
	if (args_str == NULL)
		printf_len = ftp_str("(null)", params);
	else
		printf_len = ftp_str(args_str, params);
	if (printf_len == -1)
		return (-1);
	return (printf_len);
}

int	ftp_if_is_hex(
	const char *str, unsigned long args, t_params *params)
{
	int	printf_len;

	printf_len = 0;
	if (str[-1] == 'X')
		params->flag |= FLAG_UPPERCASE;
	printf_len = ftp_diuxp(args, params);
	if (printf_len == -1)
		return (-1);
	return (printf_len);
}

int	ftp_if_is_pointer(unsigned long args, t_params *params)
{
	int	printf_len;

	printf_len = 0;
	params->flag |= FLAG_POINTER;
	printf_len = ftp_diuxp(args, params);
	if (printf_len == -1)
		return (-1);
	return (printf_len);
}
