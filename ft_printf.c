/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:43:18 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/13 19:20:09 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>

int	ft_printf(const char *str, ...)
{
	int				flag;
	int				width;
	int				precision;
	int				printf_len;
	int				temp_return;
	const char		*text_start;
	va_list			args;
	enum e_state	state;
	enum e_state	new_state;

	text_start = str;
	va_start(args, str);
	width = 0;
	precision = 0;
	printf_len = 0;
	temp_return = 0;
	state = STATE_TEXT;
	new_state = state;
	while (state != STATE_END)
	{
		if (state == STATE_TEXT)
			new_state = ft_printf_if_state_text(*str);
		else if (state == STATE_FORMAT)
			new_state = ft_printf_if_state_format(*str, &flag);
		else if (state == STATE_FLAG)
			new_state = ft_printf_if_state_flag(*str, &flag);
		else if (state == STATE_WIDTH)
			new_state = ft_printf_if_state_width(*str);
		else if (state == STATE_UNDEF_PRECISION)
			new_state = ft_printf_if_state_undef_precision(*str);
		else if (state == STATE_PRECISION)
			new_state = ft_printf_if_state_precision(*str);
		else if (state == STATE_TYPE)
			new_state = ft_printf_if_state_type(*str);
		if (*str == '\0')
			new_state = STATE_END;
		if (state != new_state)
		{
			if (state == STATE_TYPE)
			{
				if (str[-1] == '%')
				{
					temp_return = ft_printf_c_print('%', flag, width);
				}
				else if (str[-1] == 's')
					temp_return
						= ft_printf_if_is_str(
							va_arg(args, char *), flag, width, precision);
				else if (str[-1] == 'c')
					temp_return = ft_printf_c_print(
							va_arg(args, int), flag, width);
				else if (str[-1] == 'd' || str[-1] == 'i')
				{
					flag |= FLAG_BASE_DEC;
					temp_return = ft_printf_dec_hex_print(
							va_arg(args, int), flag, width, precision);
				}
				else if (str[-1] == 'u')
				{
					flag |= FLAG_BASE_DEC;
					temp_return = ft_printf_dec_hex_print(
							va_arg(args, unsigned int),
							flag & ~FLAG_PLUS & ~FLAG_SPACE,
							width, precision);
				}
				else if (str[-1] == 'x' || str[-1] == 'X')
					temp_return = ft_printf_if_is_hex(
							str, (unsigned long)va_arg
							(args, unsigned int), flag, width, precision);
				else if (str[-1] == 'p')
					temp_return = ft_printf_if_is_pointer(
							(unsigned long)va_arg(args, void *),
							flag, width, precision);
				if (temp_return == -1)
					return (-1);
				else
				{
					printf_len += temp_return;
					temp_return = 0;
				}
			}
			if (state == STATE_TEXT)
			{
				if (write(1, text_start, str - text_start) == -1)
					return (-1);
				else
					printf_len += str - text_start;
			}
			if (new_state == STATE_WIDTH)
			{
				width = ft_printf_atoi(str);
				flag |= FLAG_WIDTH;
			}
			if (new_state == STATE_UNDEF_PRECISION)
			{
				precision = 0;
				flag |= FLAG_PRECISION;
			}
			if (new_state == STATE_PRECISION)
				precision = ft_printf_atoi(str);
			if (new_state == STATE_FORMAT)
			{
				flag = 0;
				precision = 0;
				width = 0;
			}
			if (new_state == STATE_TEXT)
				text_start = str;
			state = new_state;
		}
		str++;
	}
	va_end(args);
	return (printf_len);
}
