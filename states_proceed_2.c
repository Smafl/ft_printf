/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_proceed_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:26:29 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/14 17:25:00 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

enum e_state	ft_printf_if_state_undef_precision(char c)
{
	if (c == '-')
		return (STATE_PRECISION);
	else if (c >= '0' && c <= '9')
		return (STATE_PRECISION);
	else if (ft_printf_is_type(c))
		return (STATE_TYPE);
	else
		return (STATE_TEXT);
	return (STATE_UNDEF_PRECISION);
}

enum e_state	ft_printf_if_state_precision(char c)
{
	if (c >= '0' && c <= '9')
		;
	else if (ft_printf_is_type(c))
		return (STATE_TYPE);
	else
		return (STATE_TEXT);
	return (STATE_PRECISION);
}

enum e_state	ft_printf_if_state_type(char c)
{
	if (c == '%')
		return (STATE_FORMAT);
	else
		return (STATE_TEXT);
	return (STATE_TYPE);
}
