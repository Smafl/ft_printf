
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
void	print_s(const char *str, int flag, int width, int precision);
void	print_c(char c, int flag, int width);

// print_dec_hex_p.c
int		print_dec_int(int nbr, int flag, int width, int precision);
int		print_unsigned_dec(unsigned long nbr, int flag, int width, int precision);
int		print_unsigned_x_hex(unsigned long nbr, int flag, int width);
int		print_unsigned_X_hex(unsigned long nbr, int flag, int width);
int		print_p(void *pnt, int flag, int width);

// print_zero_space.c
void	print_zero(int width);
void	print_space(int width);

// libft.c
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		ft_toupper(int c);
int		ft_strlen(const char *str);

// get.c
char	get_hex_digit(int digit);
int		get_size_dec(int n);
int		get_size_unsigned_dec(unsigned long n);
int		get_size_hex(long long n);
void	get_sign(int nbr, int flag);

// is_type_flag.c
bool	is_type(char c);
bool	is_flag(char c);
int		get_flag(char c);

#endif
