/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:39:08 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/13 19:19:10 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_if_is_str(const char *args_str, int flag, int width, int precision)
{
	int	printf_len;

	printf_len = 0;
	if (args_str == NULL)
		printf_len = ft_printf_str_print("(null)", flag, width, precision);
	else
		printf_len = ft_printf_str_print(args_str, flag, width, precision);
	if (printf_len == -1)
		return (-1);
	return (printf_len);
}

int	ft_printf_if_is_hex(const char *str, unsigned long args, int flag, int width, int precision)
{
	int	printf_len;

	printf_len = 0;
	if (str[-1] == 'X')
		flag |= FLAG_UPPERCASE;
	printf_len = ft_printf_dec_hex_print(args, flag, width, precision);
	if (printf_len == -1)
		return (-1);
	return (printf_len);
}

int	ft_printf_if_is_pointer(unsigned long args, int flag, int width, int precision)
{
	int	printf_len;

	printf_len = 0;
	flag |= FLAG_POINTER;
	printf_len = ft_printf_dec_hex_print(args, flag, width, precision);
	if (printf_len == -1)
		return (-1);
	return (printf_len);
}

// void	new_state(int new_state, int *flag, int *width, int *precision)
// {
// 	;
// }
