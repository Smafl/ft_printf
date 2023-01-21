/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:43:18 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/21 21:02:40 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>

int	ft_printf(const char *str, ...)
{
	int				len;
	int				temp_return;
	va_list			args;
	t_params		params;

	va_start(args, str);
	ftp_init(str, &params, &len, &temp_return);
	while (params.state != STATE_END)
	{
		params.new_state = ftp_get_new_state(*str, &params);
		if (*str == '\0')
			params.new_state = STATE_END;
		if (params.state != params.new_state)
		{
			if (params.state == STATE_TYPE && !ftp_ev(str, args, &params, &len))
				return (-1);
			if (ftp_param_set(str, &params, &temp_return))
				return (-1);
			len += temp_return;
			params.state = params.new_state;
		}
		str++;
	}
	va_end(args);
	return (len);
}
