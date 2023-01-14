/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 18:21:05 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/14 16:18:51 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

bool	ft_printf_is_type(char c)
{
	return (c == 'c' || c == 's'
		|| c == 'p' || c == 'd'
		|| c == 'i' || c == 'u'
		|| c == 'x' || c == 'X'
		|| c == '%');
}

bool	ft_printf_is_flag(char c)
{
	return (c == '-' || c == '0' || c == '#' || c == ' ' || c == '+');
}

int	ft_printf_get_flag(char c)
{
	if (c == '-')
		return (FLAG_MINUS);
	else if (c == '0')
		return (FLAG_ZERO);
	else if (c == '#')
		return (FLAG_HASH);
	else if (c == ' ')
		return (FLAG_SPACE);
	else if (c == '+')
		return (FLAG_PLUS);
	return (0);
}
