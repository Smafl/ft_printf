/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_proceed_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:04:55 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/13 16:43:20 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

enum e_state	ft_printf_if_state_text(char str)
{
	if (str == '%')
		return (STATE_FORMAT);
	return (STATE_TEXT);
}

enum e_state	ft_printf_if_state_format(char str, int *flag)
{
	if (ft_printf_is_flag(str))
	{
		*flag = ft_printf_get_flag(str);
		return (STATE_FLAG);
	}
	else if (str >= '1' && str <= '9')
		return (STATE_WIDTH);
	else if (str == '.')
		return (STATE_UNDEF_PRECISION);
	else if (ft_printf_is_type(str))
		return (STATE_TYPE);
	else
		return (STATE_TEXT);
	return (STATE_FORMAT);
}

enum e_state	ft_printf_if_state_flag(char str, int *flag)
{
	if (ft_printf_is_flag(str))
		*flag |= ft_printf_get_flag(str);
	else if (str >= '1' && str <= '9')
		return (STATE_WIDTH);
	else if (str == '.')
		return (STATE_UNDEF_PRECISION);
	else if (ft_printf_is_type(str))
		return (STATE_TYPE);
	else
		return (STATE_TEXT);
	return (STATE_FLAG);
}

enum e_state	ft_printf_if_state_width(char str)
{
	if (str >= '0' && str <= '9')
		;
	else if (str == '.')
		return (STATE_UNDEF_PRECISION);
	else if (ft_printf_is_type(str))
		return (STATE_TYPE);
	else
		return (STATE_TEXT);
	return (STATE_WIDTH);
}
