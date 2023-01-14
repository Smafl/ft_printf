/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:10:09 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/14 16:18:13 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int	ft_printf_get_max(int precision, int len)
{
	if (precision <= len)
		return (len);
	return (precision);
}

char	ft_printf_get_hex_digit(int digit, int flag)
{
	char	c;

	if (digit < 10)
		c = '0' + digit;
	else
	{
		if (flag & FLAG_UPPERCASE)
			c = 'A' + digit - 10;
		else
			c = 'a' + digit - 10;
	}
	return (c);
}

unsigned short	ft_printf_get_sign(long nbr, int flag, int *sign_len)
{
	if (flag & FLAG_BASE_DEC)
		return (ft_printf_get_sign_base_10(nbr, flag, sign_len));
	else
		return (ft_printf_get_sign_base_16(nbr, flag, sign_len));
	*sign_len = 0;
	return (0);
}

unsigned short	ft_printf_get_sign_base_10(long nbr, int flag, int *sign_len)
{
	*sign_len = 0;
	if (nbr >= 0)
	{	
		if ((flag & FLAG_SPACE) && !(flag & FLAG_PLUS))
		{
			*sign_len = 1;
			return (' ');
		}
		else if (flag & FLAG_PLUS)
		{
			*sign_len = 1;
			return ('+');
		}
	}
	else if (nbr < 0)
	{
		*sign_len = 1;
		return ('-');
	}
	return (0);
}

unsigned short	ft_printf_get_sign_base_16(long nbr, int flag, int *sign_len)
{
	*sign_len = 0;
	if (nbr == 0 && !(flag & FLAG_POINTER))
		;
	else if (flag & FLAG_POINTER)
	{
		*sign_len = 2;
		return ((unsigned short) 'x' << 8 | '0');
	}
	else if (flag & FLAG_HASH)
	{
		*sign_len = 2;
		if (flag & FLAG_UPPERCASE)
			return ((unsigned short) 'X' << 8 | '0');
		else
			return ((unsigned short) 'x' << 8 | '0');
	}
	return (0);
}
