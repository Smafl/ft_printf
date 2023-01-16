/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_ft_printf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:06:12 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/16 14:41:43 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private.h"

int	ft_printf_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	if (*str == '-')
	{
		sign = sign * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (sign * (*str - '0') + (result * 10));
		str++;
	}
	return (result);
}

int	ft_printf_dec_itoa(long n, int flag, char *result)
{
	int		i;
	int		size;

	size = ft_printf_get_size_dec(n);
	i = size;
	if (n < 0)
		n *= -1;
	result[i--] = '\0';
	while (n >= 0)
	{
		result[i--] = ft_printf_get_hex_digit(n % 10, flag);
		n /= 10;
		if (n == 0)
			break ;
	}
	return (size);
}

int	ft_printf_hex_itoa(unsigned long n, int flag, char *result)
{
	int				i;
	int				size;

	size = ft_printf_get_size_hex(n);
	i = size;
	result[i--] = '\0';
	while (n >= 0)
	{
		result[i--] = ft_printf_get_hex_digit(n % 16, flag);
		n /= 16;
		if (n == 0)
			break ;
	}
	return (size);
}

int	ft_printf_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_printf_strnlen(const char *str, int max_len)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && i < max_len)
	{
		i++;
	}
	return (i);
}
