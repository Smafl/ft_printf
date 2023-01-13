/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_ft_printf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:06:12 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/13 16:44:24 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	long	digit;

	size = ft_printf_get_size_dec(n);
	i = size;
	digit = (long)n;
	if (n < 0)
		digit *= -1;
	result[i--] = '\0';
	while (digit >= 0)
	{
		result[i--] = ft_printf_get_hex_digit(digit % 10, flag);
		digit /= 10;
		if (digit == 0)
			break ;
	}
	return (size);
}

int	ft_printf_hex_itoa(unsigned long n, int flag, char *result)
{
	int				i;
	int				size;
	unsigned long	digit;

	size = ft_printf_get_size_ul(n);
	i = size;
	digit = (unsigned long)n;
	result[i--] = '\0';
	while (digit >= 0)
	{
		result[i--] = ft_printf_get_hex_digit(digit % 16, flag);
		digit /= 16;
		if (digit == 0)
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
