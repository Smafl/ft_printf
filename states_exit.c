/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:26:29 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/12 17:36:15 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

enum e_state	state_precision(const char *str)
{
	if (*str >= '0' && *str <= '9')
		;
	else if (is_type(*str))
		return (STATE_TYPE);
	else
		return (STATE_TEXT);
	return (STATE_PRECISION);
}

enum e_state	state_type(const char *str)
{
	if (*str == '%')
		return (STATE_FORMAT);
	else
		return (STATE_TEXT);
	return (STATE_TYPE);
}

