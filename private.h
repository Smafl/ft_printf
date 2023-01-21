/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:52 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/21 21:38:42 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVATE_H
# define PRIVATE_H

# include "ft_printf.h"
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>

# define FLAG_MINUS 	0b0000000001
# define FLAG_ZERO 		0b0000000010
# define FLAG_HASH 		0b0000000100
# define FLAG_SPACE 	0b0000001000
# define FLAG_PLUS 		0b0000010000
# define FLAG_WIDTH 	0b0000100000
# define FLAG_PRECISION 0b0001000000
# define FLAG_UPPERCASE 0b0010000000
# define FLAG_POINTER 	0b0100000000
# define FLAG_BASE_DEC	0b1000000000

typedef enum e_state
{
	STATE_TEXT,
	STATE_FORMAT,
	STATE_FLAG,
	STATE_WIDTH,
	STATE_UNDEF_PRECISION,
	STATE_PRECISION,
	STATE_TYPE,
	STATE_END
}	t_state;

typedef struct s_params
{
	int				flag;
	int				width;
	int				precision;
	int				zero_len;
	int				space_len;
	int				len;
	int				sign_len;
	int				fill_len;
	int				len_with_precision;
	char			array[18];
	const char		*text_start;
	unsigned short	sign;
	t_state			state;
	t_state			new_state;
}	t_params;

/*
In ft_printf.c, parsing.c, and pars_utils.c we assign values to some variables,
define states, take args and set parameters (like find width and precision)
*/

// parsing.c
void			ftp_init(
					const char *str, t_params *params,
					int *len, int *temp_return);
enum e_state	ftp_get_new_state(char c, t_params *params);
int				ftp_ev(
					const char *str, va_list args, t_params *params, int *len);
int				ftp_param_set(const char *str, t_params *param, int *temp_len);

// pars_utils.c
int				ftp_set_flag(va_list args, t_params *params);
int				ftp_if_is_str(const char *args_str, t_params *params);
int				ftp_if_is_hex(
					const char *str, unsigned long args, t_params *params);
int				ftp_if_is_pointer(unsigned long args, t_params *params);

/*
In state_proceed.c (1 and 2) we manage flags,
width, precision, and types with functins from is_type_flag.c
*/

// states_proceed_1.c
enum e_state	ftp_if_state_text(char str);
enum e_state	ftp_if_state_format(char c, t_params *params);
enum e_state	ftp_if_state_flag(char str, t_params *params);
enum e_state	ftp_if_state_width(char str);

// states_proceed_2.c
enum e_state	ftp_if_state_undef_precision(char str);
enum e_state	ftp_if_state_precision(char str);
enum e_state	ftp_if_state_type(char str);

// is_type_flag.c
bool			ftp_is_type(char c);
bool			ftp_is_flag(char c);
int				ftp_get_flag(char c);

/*
In print_c_str.c we manage string and char with flags, count zero
and spaces if need, and print them
*/

// print_c_str.c
int				ftp_write_c_str(const char *str, t_params *params, int len);
int				ftp_str(const char *str, t_params *params);
int				ftp_c(char c, t_params *params);

/*
In print_dec_hex_p.c we manage diuxp with flags, count zero
and spaces if need, and print them
*/

// print_dec_hex_p.c
void			ftp_diuxp_param_count(long nbr, t_params *param);
int				ftp_write_diuxp(t_params *params, int sign_len, int len);
int				ftp_diuxp(long nbr, t_params *params);

// Additional functions:
// print_zero_space.c
int				ftp_zero(int width);
int				ftp_space(int width);

// get_size.c
int				ftp_get_size_dec(long n);
int				ftp_get_size_hex(unsigned long n);

// libft_ft_printf.c
int				ftp_atoi(const char *str);
int				ftp_dec_itoa(long n, int flag, char *result);
int				ftp_hex_itoa(unsigned long n, int flag, char *result);
int				ftp_strlen(const char *str);
int				ftp_strnlen(const char *str, int max_len);

// utils.c
int				ftp_get_max(int precision, int len);
char			ftp_get_hex_digit(int digit, int flag);
unsigned short	ftp_get_sign(long nbr, int flag, int *has_sign);
unsigned short	ftp_get_sign_base_10(long nbr, int flag, int *sign_len);
unsigned short	ftp_get_sign_base_16(long nbr, int flag, int *sign_len);

#endif
