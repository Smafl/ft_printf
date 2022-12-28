
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>

#define FLAG_MINUS (1 << 0)
#define FLAG_ZERO (1 << 1)
#define FLAG_HASH (1 << 2)
#define FLAG_SPACE (1 << 3)
#define FLAG_PLUS (1 << 4)
#define HAS_WIDTH (1 << 5)
#define HAS_PRECISION (1 << 6)

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

int ft_printf(const char *str, ...);

static void print_s(const char *str, int flag, int width, int precision);
static void print_c(char c, int flag, int width, int precision);

static void print_unsigned_dec(int nbr);
static int print_unsigned_x_hex(int nbr, int flag, int width, int precision);
static void print_unsigned_X_hex(int nbr);
static int print_p(void *pnt, int flag, int width, int precision);

// print_zero_space.c
static void print_zero(int width);
static void print_space(int width);

// libft.c
static int	ft_atoi(const char *str);
static char	*ft_itoa(int n);
static int	ft_toupper(int c);
static int	ft_strlen(const char *str);

// get.c
static char get_hex_digit(int digit);
static size_t get_size(int n);
static size_t get_size_t(size_t n);

// is_type_flag.c
static bool is_type(char c);
static bool is_flag(char c);
static int get_flag(char c);

#endif
