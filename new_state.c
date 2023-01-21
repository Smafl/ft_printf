/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:39:08 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/21 12:33:53 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

enum e_state	get_new_state(char c, t_parameters *parameters)
{
	if (parameters->state == STATE_TEXT)
		return (ft_printf_if_state_text(c));
	if (parameters->state == STATE_FORMAT)
		return (ft_printf_if_state_format(c, parameters));
	if (parameters->state == STATE_FLAG)
		return (ft_printf_if_state_flag(c, parameters));
	if (parameters->state == STATE_WIDTH)
		return (ft_printf_if_state_width(c));
	if (parameters->state == STATE_UNDEF_PRECISION)
		return (ft_printf_if_state_undef_precision(c));
	if (parameters->state == STATE_PRECISION)
		return (ft_printf_if_state_precision(c));
	if (parameters->state == STATE_TYPE)
		return (ft_printf_if_state_type(c));
	return (parameters->state);
}

int	ft_printf_if_is_str(const char *args_str, t_parameters *parameters)
{
	int	printf_len;

	printf_len = 0;
	if (args_str == NULL)
		printf_len = ft_printf_str("(null)", parameters);
	else
		printf_len = ft_printf_str(args_str, parameters);
	if (printf_len == -1)
		return (-1);
	return (printf_len);
}

int	ft_printf_if_is_hex(
	const char *str, unsigned long args, t_parameters *parameters)
{
	int	printf_len;

	printf_len = 0;
	if (str[-1] == 'X')
		parameters->flag |= FLAG_UPPERCASE;
	printf_len = ft_printf_diuxp(args, parameters);
	if (printf_len == -1)
		return (-1);
	return (printf_len);
}

int	ft_printf_if_is_pointer(unsigned long args, t_parameters *parameters)
{
	int	printf_len;

	printf_len = 0;
	parameters->flag |= FLAG_POINTER;
	printf_len = ft_printf_diuxp(args, parameters);
	if (printf_len == -1)
		return (-1);
	return (printf_len);
}
