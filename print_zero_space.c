/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_zero_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:05:31 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/20 19:43:26 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int	ft_printf_zero(t_parameters *parameters)
{
	int	printf_len;

	printf_len = 0;
	while (parameters->width != 0)
	{
		if (write(1, "0", 1) == -1)
			return (-1);
		parameters->width--;
		printf_len++;
	}
	return (printf_len);
}

int	ft_printf_space(t_parameters *parameters)
{
	int	printf_len;

	printf_len = 0;
	while (parameters->width != 0)
	{
		if (write(1, " ", 1) == -1)
			return (-1);
		parameters->width--;
		printf_len++;
	}
	return (printf_len);
}
