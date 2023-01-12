/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:04:55 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/12 17:22:03 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

enum e_state	state_text(const char *str)
{
	if (*str == '%')
		return (STATE_FORMAT);
	return (STATE_TEXT);
}

enum e_state	state_format(const char *str, int *flag)
{
	if (is_flag(*str))
	{
		*flag = get_flag(*str);
		return (STATE_FLAG);
	}
	else if (*str >= '1' && *str <= '9')
		return (STATE_WIDTH);
	else if (*str == '.')
		return (STATE_UNDEF_PRECISION);
	else if (is_type(*str))
		return (STATE_TYPE);
	else
		return (STATE_TEXT);
	return (STATE_FORMAT);
}

enum e_state	state_flag(const char *str, int *flag)
{
	if (is_flag(*str))
		*flag |= get_flag(*str);
	else if (*str >= '1' && *str <= '9')
		return (STATE_WIDTH);
	else if (*str == '.')
		return (STATE_UNDEF_PRECISION);
	else if (is_type(*str))
		return (STATE_TYPE);
	else
		return (STATE_TEXT);
	return (STATE_FLAG);
}

enum e_state	state_width(const char *str)
{
	if (*str >= '0' && *str <= '9')
		;
	else if (*str == '.')
		return (STATE_UNDEF_PRECISION);
	else if (is_type(*str))
		return (STATE_TYPE);
	else
		return (STATE_TEXT);
	return (STATE_WIDTH);
}

enum e_state	state_undef_precision(const char *str)
{
	if (*str == '-')
		return (STATE_PRECISION);
	else if (*str >= '0' && *str <= '9')
		return (STATE_PRECISION);
	else if (is_type(*str))
		return (STATE_TYPE);
	else
		return (STATE_TEXT);
	return (STATE_UNDEF_PRECISION);
}
