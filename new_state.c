/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:39:08 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/12 21:46:21 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_str(const char *args_str, int flag, int width, int precision)
{
	int	printf_len;
	int	temp_return;

	printf_len = 0;
	if (args_str == NULL)
		temp_return = print_str("(null)", flag, width, precision);
	else
		temp_return = print_str(args_str, flag, width, precision);
	if (temp_return == -1)
		return (-1);
	else
	{
		printf_len += temp_return;
		temp_return = 0;
	}
	return (printf_len);
}

int	is_hex(const char *str, unsigned long args, int flag, int width, int precision)
{
	int	printf_len;
	int	temp_return;

	printf_len = 0;
	if (str[-1] == 'X')
		flag |= FLAG_UPPERCASE;
	temp_return = print_dec_int(args, flag, width, precision, 16);
	if (temp_return == -1)
		return (-1);
	else
		printf_len += temp_return;
	return (printf_len);
}

int	is_pointer(const char *str, unsigned long args, int flag, int width, int precision)
{
	int	printf_len;
	int	temp_return;

	printf_len = 0;
	if (str[-1] == 'p')
		flag |= FLAG_POINTER;
	temp_return = print_dec_int(args, flag, width, precision, 16);
	if (temp_return == -1)
		return (-1);
	else
		printf_len += temp_return;
	return (printf_len);
}

// void	new_state(int new_state, int *flag, int *width, int *precision)
// {
// 	;
// }
