/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 23:02:26 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/12 17:37:03 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>

# define FLAG_MINUS 	0b000000001
# define FLAG_ZERO 		0b000000010
# define FLAG_HASH 		0b000000100
# define FLAG_SPACE 	0b000001000
# define FLAG_PLUS 		0b000010000
# define HAS_WIDTH 		0b000100000
# define HAS_PRECISION 	0b001000000
# define FLAG_UPPERCASE 0b010000000
# define FLAG_POINTER 	0b100000000

enum e_state
{
	STATE_TEXT,
	STATE_FORMAT,
	STATE_FLAG,
	STATE_WIDTH,
	STATE_UNDEF_PRECISION,
	STATE_PRECISION,
	STATE_TYPE,
	STATE_END
};

// ft_printf.c
int				ft_printf(const char *str, ...);

// get_size.c norm+
int				get_size_dec(long n, int base);
int				get_size_ul(unsigned long n, int base);

// is_type_flag.c norm+
bool			is_type(char c);
bool			is_flag(char c);
int				get_flag(char c);

// libft.c norm+
int				ft_itoa(long n, int base, int flag, char *result);
int				ft_pointer_itoa(unsigned long n, int flag, char *result);
int				ft_atoi(const char *str);
int				ft_strlen(const char *str);
int				ft_strnlen(const char *str, int max_len);

// print_c_str.c
int				print_str(const char *str, int flag, int width, int precision);
int				print_c(char c, int flag, int width);

// print_dec_hex_p.c
int				print_dec_int(long nbr, int flag, int width, int precision, int base);

// print_zero_space.c norm+
int				print_zero(int width);
int				print_space(int width);

// states_enter.c
enum e_state	state_text(const char *str);
enum e_state	state_format(const char *str, int *flag);
enum e_state	state_flag(const char *str, int *flag);
enum e_state	state_width(const char *str);
enum e_state	state_undef_precision(const char *str);

// states_exit.c
enum e_state	state_precision(const char *str);
enum e_state	state_type(const char *str);

// utils.c norm+
int				get_max(int precision, int len);
char			get_hex_digit(int digit, int flag);
unsigned short	get_sign(long nbr, int flag, int base, int *has_sign);
unsigned short	get_sign_base_10(long nbr, int flag, int *sign_len);
unsigned short	get_sign_base_16(long nbr, int flag, int *sign_len);

#endif
