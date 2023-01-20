/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_proceed_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:04:55 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/14 16:33:22 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

enum e_state	ft_printf_if_state_text(char c)
{
	if (c == '%')
		return (STATE_FORMAT);
	return (STATE_TEXT);
}

enum e_state	ft_printf_if_state_format(char c, t_parameters *parameters)
{
	if (ft_printf_is_flag(c))
	{
		parameters->flag = ft_printf_get_flag(c);
		return (STATE_FLAG);
	}
	else if (c >= '1' && c <= '9')
		return (STATE_WIDTH);
	else if (c == '.')
		return (STATE_UNDEF_PRECISION);
	else if (ft_printf_is_type(c))
		return (STATE_TYPE);
	else
		return (STATE_TEXT);
	return (STATE_FORMAT);
}

enum e_state	ft_printf_if_state_flag(char c, t_parameters *parameters)
{
	if (ft_printf_is_flag(c))
		parameters->flag |= ft_printf_get_flag(c);
	else if (c >= '1' && c <= '9')
		return (STATE_WIDTH);
	else if (c == '.')
		return (STATE_UNDEF_PRECISION);
	else if (ft_printf_is_type(c))
		return (STATE_TYPE);
	else
		return (STATE_TEXT);
	return (STATE_FLAG);
}

enum e_state	ft_printf_if_state_width(char c)
{
	if (c >= '0' && c <= '9')
		;
	else if (c == '.')
		return (STATE_UNDEF_PRECISION);
	else if (ft_printf_is_type(c))
		return (STATE_TYPE);
	else
		return (STATE_TEXT);
	return (STATE_WIDTH);
}
