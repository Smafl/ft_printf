/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:06:52 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/13 16:19:45 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_get_size_dec(long n)
{
	int	size;

	size = 0;
	if (n == 0)
		size = 1;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

int	ft_printf_get_size_ul(unsigned long n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size = 1;
	while (n)
	{
		n /= 16;
		size++;
	}
	return (size);
}
