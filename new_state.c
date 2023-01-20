/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:39:08 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/20 19:40:38 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int	ft_printf_if_is_str(
	const char *args_str, int flag, t_parameters *parameters)
{
	int	printf_len;

	printf_len = 0;
	if (args_str == NULL)
		printf_len = ft_printf_str("(null)", flag, parameters);
	else
		printf_len = ft_printf_str(args_str, flag, parameters);
	if (printf_len == -1)
		return (-1);
	return (printf_len);
}

int	ft_printf_if_is_hex(
	const char *str, unsigned long args, int flag, t_parameters *parameters)
{
	int	printf_len;

	printf_len = 0;
	if (str[-1] == 'X')
		flag |= FLAG_UPPERCASE;
	printf_len = ft_printf_diuxp(args, flag, parameters);
	if (printf_len == -1)
		return (-1);
	return (printf_len);
}

int	ft_printf_if_is_pointer(
	unsigned long args, int flag, t_parameters *parameters)
{
	int	printf_len;

	printf_len = 0;
	flag |= FLAG_POINTER;
	printf_len = ft_printf_diuxp(args, flag, parameters);
	if (printf_len == -1)
		return (-1);
	return (printf_len);
}
