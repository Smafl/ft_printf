/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:02:26 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/13 21:05:19 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "private.h"
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>

// ft_printf.c
int				ft_printf(const char *str, ...);

// get_size.c norm+
int				ft_printf_get_size_dec(long n);
int				ft_printf_get_size_ul(unsigned long n);

// is_type_flag.c norm+
bool			ft_printf_is_type(char c);
bool			ft_printf_is_flag(char c);
int				ft_printf_get_flag(char c);

// libft_ft_printf.c norm+
int				ft_printf_atoi(const char *str);
int				ft_printf_dec_itoa(long n, int flag, char *result);
int				ft_printf_hex_itoa(unsigned long n, int flag, char *result);
int				ft_printf_strlen(const char *str);
int				ft_printf_strnlen(const char *str, int max_len);

// new_state.c
int				ft_printf_if_is_str(
					const char *args_str, int flag, int width, int precision);
int				ft_printf_if_is_hex(
					const char *str, unsigned long args, int flag, int width,
					int precision);
int				ft_printf_if_is_pointer(
					unsigned long args, int flag, int width, int precision);

// print_c_str.c
int				ft_printf_str_print(
					const char *str, int flag, int width, int precision);
int				ft_printf_c_print(char c, int flag, int width);

// print_dec_hex_p.c
int				ft_printf_dec_hex_print(
					long nbr, int flag, int width, int precision);

// print_zero_space.c norm+
int				ft_printf_zero_print(int width);
int				ft_printf_space_print(int width);

// states_proceed_1.c norm+
enum e_state	ft_printf_if_state_text(char str);
enum e_state	ft_printf_if_state_format(char str, int *flag);
enum e_state	ft_printf_if_state_flag(char str, int *flag);
enum e_state	ft_printf_if_state_width(char str);

// states_proceed_2.c norm+
enum e_state	ft_printf_if_state_undef_precision(char str);
enum e_state	ft_printf_if_state_precision(char str);
enum e_state	ft_printf_if_state_type(char str);

// utils.c norm+
int				ft_printf_get_max(int precision, int len);
char			ft_printf_get_hex_digit(int digit, int flag);
unsigned short	ft_printf_get_sign(long nbr, int flag, int *has_sign);
unsigned short	ft_printf_get_sign_base_10(long nbr, int flag, int *sign_len);
unsigned short	ft_printf_get_sign_base_16(long nbr, int flag, int *sign_len);

#endif
