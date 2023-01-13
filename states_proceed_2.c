/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_proceed_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:26:29 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/13 16:43:29 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

enum e_state	ft_printf_if_state_undef_precision(char str)
{
	if (str == '-')
		return (STATE_PRECISION);
	else if (str >= '0' && str <= '9')
		return (STATE_PRECISION);
	else if (ft_printf_is_type(str))
		return (STATE_TYPE);
	else
		return (STATE_TEXT);
	return (STATE_UNDEF_PRECISION);
}

enum e_state	ft_printf_if_state_precision(char str)
{
	if (str >= '0' && str <= '9')
		;
	else if (ft_printf_is_type(str))
		return (STATE_TYPE);
	else
		return (STATE_TEXT);
	return (STATE_PRECISION);
}

enum e_state	ft_printf_if_state_type(char str)
{
	if (str == '%')
		return (STATE_FORMAT);
	else
		return (STATE_TEXT);
	return (STATE_TYPE);
}
