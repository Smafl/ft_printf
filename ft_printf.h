
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>

# define FLAG_MINUS (1 << 0)
# define FLAG_ZERO (1 << 1)
# define FLAG_HASH (1 << 2)
# define FLAG_SPACE (1 << 3)
# define FLAG_PLUS (1 << 4)
# define HAS_WIDTH (1 << 5)
# define HAS_PRECISION (1 << 6)
# define TYPE_x (1 << 7)
# define TYPE_X (1 << 8)
# define TYPE_p (1 << 9)

enum e_state
{
	STATE_TEXT, // 0
	STATE_FORMAT, // 1
	STATE_FLAG, // 2
	STATE_WIDTH, // 3
	STATE_UNDEF_PRECISION, // 4
	STATE_PRECISION, // 5
	STATE_TYPE, // 6
	STATE_END // 7
};

int		ft_printf(const char *str, ...);

// print_c_str.c
int		print_str(const char *str, int flag, int width, int precision);
int		print_c(char c, int flag, int width);

// print_dec_hex_p.c
int		print_dec_int(int nbr, int flag, int width, int precision);
int		print_unsigned_dec(unsigned int nbr, int flag, int width, int precision);
int		print_unsigned_x_hex(unsigned int nbr, int flag, int width, int precision);
int		print_unsigned_X_hex(unsigned int nbr, int flag, int width, int precision);
int		print_p(void *pnt, int flag, int width);

// print_zero_space_0x.c
int		print_zero(int width);
int		print_space(int width);
int 	print_0x(int flag);

// libft.c
int		ft_itoa(int n, char *result);
int		ft_atoi(const char *str);
int		ft_toupper(int c);
int		ft_strlen(const char *str);

// get_char_int.c
char	get_hex_digit(int digit, int flag);
char	get_sign(int nbr, int flag, int *has_sign);
int		get_zero_space_len(int flag, int len, int width, int precision);

// get_size.c
int		get_size_dec(int n);
int		get_size_unsigned_dec(unsigned long n);
int		get_size_hex_ll(long long n);
int		get_size_hex_ull(unsigned long long n);

// is_type_flag.c
bool	is_type(char c);
bool	is_flag(char c);
int		get_flag(char c);

#endif
