/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   private.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:57:52 by ekulichk          #+#    #+#             */
/*   Updated: 2023/01/21 16:07:24 by ekulichk         ###   ########.fr       */
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

typedef struct s_parameters
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
}	t_parameters;

// get_size.c
int				ft_printf_get_size_dec(long n);
int				ft_printf_get_size_hex(unsigned long n);

// is_type_flag.c
bool			ft_printf_is_type(char c);
bool			ft_printf_is_flag(char c);
int				ft_printf_get_flag(char c);

// libft_ft_printf.c
int				ft_printf_atoi(const char *str);
int				ft_printf_dec_itoa(long n, int flag, char *result);
int				ft_printf_hex_itoa(unsigned long n, int flag, char *result);
int				ft_printf_strlen(const char *str);
int				ft_printf_strnlen(const char *str, int max_len);

// new_state.c
int				ft_printf_param_set(
					const char *str, t_parameters *param);
enum e_state	get_new_state(char c, t_parameters *parameters);
int				ft_printf_if_is_str(
					const char *args_str, t_parameters *parameters);
int				ft_printf_if_is_hex(
					const char *str, unsigned long args,
					t_parameters *parameters);
int				ft_printf_if_is_pointer(
					unsigned long args, t_parameters *parameters);

// print_c_str.c
int				ft_printf_write_c_str(
					const char *str, t_parameters *parameters, int len);
int				ft_printf_str(
					const char *str, t_parameters *parameters);
int				ft_printf_c(char c, t_parameters *parameters);

// print_dec_hex_p.c
void			ft_printf_diuxp_param_count(long nbr, t_parameters *param);
int				ft_printf_write_diuxp(
					t_parameters *parameters, int sign_len, int len);
int				ft_printf_diuxp(long nbr, t_parameters *parameters);

// print_zero_space.c
int				ft_printf_zero(int width);
int				ft_printf_space(int width);

// states_proceed_1.c
enum e_state	ft_printf_if_state_text(char str);
enum e_state	ft_printf_if_state_format(char c, t_parameters *parameters);
enum e_state	ft_printf_if_state_flag(char str, t_parameters *parameters);
enum e_state	ft_printf_if_state_width(char str);

// states_proceed_2.c
enum e_state	ft_printf_if_state_undef_precision(char str);
enum e_state	ft_printf_if_state_precision(char str);
enum e_state	ft_printf_if_state_type(char str);

// utils.c
int				ft_printf_get_max(int precision, int len);
char			ft_printf_get_hex_digit(int digit, int flag);
unsigned short	ft_printf_get_sign(long nbr, int flag, int *has_sign);
unsigned short	ft_printf_get_sign_base_10(long nbr, int flag, int *sign_len);
unsigned short	ft_printf_get_sign_base_16(long nbr, int flag, int *sign_len);

#endif
