/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_zero_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:05:31 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/13 19:32:33 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_zero_print(int width)
{
	int	printf_len;

	printf_len = 0;
	while (width != 0)
	{
		if (write(1, "0", 1) == -1)
			return (-1);
		width--;
	}
	return (printf_len);
}

int	ft_printf_space_print(int width)
{
	int	printf_len;

	printf_len = 0;
	while (width != 0)
	{
		if (write(1, " ", 1) == -1)
			return (-1);
			width--;
	}
	return (printf_len);
}
