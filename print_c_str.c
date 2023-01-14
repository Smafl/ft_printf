/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:18:30 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/14 16:18:34 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int	ft_printf_str(const char *str, int flag, int width, int precision)
{
	int	len;
	int	printf_len;
	int	zero_len;
	int	space_len;

	printf_len = 0;
	zero_len = 0;
	space_len = 0;
	if (flag & FLAG_MINUS)
		flag &= ~FLAG_ZERO;
	if (flag & FLAG_PRECISION)
		len = ft_printf_strnlen(str, precision);
	else
		len = ft_printf_strlen(str);
	if ((flag & FLAG_ZERO) && width > len)
		zero_len = width - len;
	else if (width > len)
		space_len = width - len;
	if (!(flag & FLAG_MINUS))
	{
		if (ft_printf_space(space_len) == -1)
			return (-1);
		else
			printf_len += space_len;
	}
	if (ft_printf_zero(zero_len) == -1)
		return (-1);
	else
		printf_len += zero_len;
	if (write(1, str, len) == -1)
		return (-1);
	else
		printf_len += len;
	if (flag & FLAG_MINUS)
	{
		if (ft_printf_space(space_len) == -1)
			return (-1);
		else
			printf_len += space_len;
	}
	return (printf_len);
}

int	ft_printf_c(char c, int flag, int width)
{
	int	printf_len;
	int	zero_len;
	int	space_len;

	printf_len = 0;
	zero_len = 0;
	space_len = 0;
	if (flag & FLAG_MINUS)
		flag &= ~FLAG_ZERO;
	if ((flag & FLAG_ZERO) && width > 1)
		zero_len = width - 1;
	else if (width > 1)
		space_len = width - 1;
	if (!(flag & FLAG_MINUS))
	{
		if (ft_printf_space(space_len) == -1)
			return (-1);
		else
			printf_len += space_len;
	}
	if (ft_printf_zero(zero_len) == -1)
		return (-1);
	else
		printf_len += zero_len;
	if (write(1, &c, 1) == -1)
		return (-1);
	else
		printf_len += 1;
	if (flag & FLAG_MINUS)
	{
		if (ft_printf_space(space_len) == -1)
			return (-1);
		else
			printf_len += space_len;
	}
	return (printf_len);
}
