/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:43:18 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/21 16:13:18 by ekulichk         ###   ########.fr       */
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
	int				printf_len;
	int				temp_return;
	va_list			args;
	t_parameters	parameters;

	printf_len = 0;
	temp_return = 0;
	va_start(args, str);
	parameters.width = 0;
	parameters.precision = 0;
	parameters.text_start = str;
	parameters.state = STATE_TEXT;
	while (parameters.state != STATE_END)
	{
		parameters.new_state = get_new_state(*str, &parameters);
		if (*str == '\0')
			parameters.new_state = STATE_END;
		if (parameters.state != parameters.new_state)
		{
			if (parameters.state == STATE_TYPE)
			{
				if (str[-1] == '%')
					temp_return = ft_printf_c('%', &parameters);
				else if (str[-1] == 's')
					temp_return = ft_printf_if_is_str(
							va_arg(args, char *), &parameters);
				else if (str[-1] == 'c')
					temp_return = ft_printf_c(
							va_arg(args, int), &parameters);
				else if (str[-1] == 'd' || str[-1] == 'i')
				{
					parameters.flag |= FLAG_BASE_DEC;
					temp_return = ft_printf_diuxp(
							va_arg(args, int), &parameters);
				}
				else if (str[-1] == 'u')
				{
					parameters.flag |= FLAG_BASE_DEC;
					parameters.flag &= ~FLAG_PLUS;
					parameters.flag &= ~FLAG_SPACE;
					temp_return = ft_printf_diuxp(
							va_arg(args, unsigned int), &parameters);
				}
				else if (str[-1] == 'x' || str[-1] == 'X')
					temp_return = ft_printf_if_is_hex(
							str, (unsigned long)va_arg
							(args, unsigned int), &parameters);
				else if (str[-1] == 'p')
					temp_return = ft_printf_if_is_pointer(
							(unsigned long)va_arg(args, void *), &parameters);
				if (temp_return == -1)
					return (-1);
				else
				{
					printf_len += temp_return;
					temp_return = 0;
				}
			}
			temp_return = ft_printf_param_set(str, &parameters);
			if (temp_return == -1)
				return (-1);
			printf_len += temp_return;
			parameters.state = parameters.new_state;
		}
		str++;
	}
	va_end(args);
	return (printf_len);
}
