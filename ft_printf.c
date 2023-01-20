/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:43:18 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/20 20:37:19 by ekulichk         ###   ########.fr       */
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
	va_list			args;
	t_state			state;
	t_state			new_state;
	t_parameters	parameters;

	va_start(args, str);
	parameters.width = 0;
	parameters.precision = 0;
	parameters.printf_len = 0;
	parameters.temp_return = 0;
	parameters.text_start = str;
	state = STATE_TEXT;
	while (state != STATE_END)
	{
		new_state = get_new_state(state, *str, &parameters);
		if (*str == '\0')
			new_state = STATE_END;
		if (state != new_state)
		{
			if (state == STATE_TYPE)
			{
				if (str[-1] == '%')
					parameters.temp_return = ft_printf_c('%', &parameters);
				else if (str[-1] == 's')
					parameters.temp_return = ft_printf_if_is_str(
							va_arg(args, char *), &parameters);
				else if (str[-1] == 'c')
					parameters.temp_return = ft_printf_c(
							va_arg(args, int), &parameters);
				else if (str[-1] == 'd' || str[-1] == 'i')
				{
					parameters.flag |= FLAG_BASE_DEC;
					parameters.temp_return = ft_printf_diuxp(
							va_arg(args, int), &parameters);
				}
				else if (str[-1] == 'u')
				{
					parameters.flag |= FLAG_BASE_DEC;
					parameters.flag &= ~FLAG_PLUS;
					parameters.flag &= ~FLAG_SPACE;
					parameters.temp_return = ft_printf_diuxp(
							va_arg(args, unsigned int), &parameters);
				}
				else if (str[-1] == 'x' || str[-1] == 'X')
					parameters.temp_return = ft_printf_if_is_hex(
							str, (unsigned long)va_arg
							(args, unsigned int), &parameters);
				else if (str[-1] == 'p')
					parameters.temp_return = ft_printf_if_is_pointer(
							(unsigned long)va_arg(args, void *), &parameters);
				if (parameters.temp_return == -1)
					return (-1);
				else
				{
					parameters.printf_len += parameters.temp_return;
					parameters.temp_return = 0;
				}
			}
			if (state == STATE_TEXT)
			{
				if (write(1, parameters.text_start,
						str - parameters.text_start) == -1)
					return (-1);
				else
					parameters.printf_len += str - parameters.text_start;
			}
			if (new_state == STATE_WIDTH)
			{
				parameters.width = ft_printf_atoi(str);
				parameters.flag |= FLAG_WIDTH;
			}
			if (new_state == STATE_UNDEF_PRECISION)
			{
				parameters.precision = 0;
				parameters.flag |= FLAG_PRECISION;
			}
			if (new_state == STATE_PRECISION)
				parameters.precision = ft_printf_atoi(str);
			if (new_state == STATE_FORMAT)
			{
				parameters.flag = 0;
				parameters.precision = 0;
				parameters.width = 0;
			}
			if (new_state == STATE_TEXT)
				parameters.text_start = str;
			state = new_state;
		}
		str++;
	}
	va_end(args);
	return (parameters.printf_len);
}
