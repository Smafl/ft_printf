
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>

int ft_printf(const char *str, ...);
static void print_flags(int flag);
static int	ft_atoi(const char *str);
static bool is_type(char c);
static bool is_flag(char c);
static int get_flag(char c);
static void print_s(const char *str);
static void print_c(char c);
static char get_hex_lo_digit(int digit);
static char get_hex_up_digit(int digit);
static char	*ft_itoa(int n);
static size_t	get_size(int n);
static void print_usigned_dec(int nbr);
static void print_usigned_hex(int nbr, const char up_lo);
static void print_p(void *pnt);

#define FLAG_MINUS (1 << 0)
#define FLAG_ZERO (1 << 1)
#define FLAG_HASH (1 << 2)
#define FLAG_SPACE (1 << 3)
#define FLAG_PLUS (1 << 4)

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

int ft_printf(const char *str, ...)
{
	int flag;
	int width;
	int precision;
	bool has_width;
	bool has_precision;
	const char *text_start = str;

	va_list args;
	va_start(args, str);

	enum e_state state = STATE_TEXT;
	enum e_state new_state = state;
	while (state != STATE_END)
	{
		// printf("begin while state: %d\n", state);
		// printf("char: %c\n", *str);
		// printf("text start: %s\n", text_start);
// text
		if (state == STATE_TEXT)
		{
			if (*str == '%')
			{
				new_state = STATE_FORMAT;
			}
		}

// format
		else if (state == STATE_FORMAT)
		{
			if (is_flag(*str))
			{
				flag = get_flag(*str);
				new_state = STATE_FLAG;
			}
			else if (*str >= '1' && *str <= '9')
				new_state = STATE_WIDTH;
			else if (*str == '.')
				new_state = STATE_UNDEF_PRECISION;
			else if (is_type(*str))
				new_state = STATE_TYPE;
			else
				new_state = STATE_TEXT;
		}

// flag
		else if (state == STATE_FLAG)
		{
			if (is_flag(*str))
				flag |= get_flag(*str);
			else if (*str >= '1' && *str <= '9')
				new_state = STATE_WIDTH;
			else if (*str == '.')
				new_state = STATE_UNDEF_PRECISION;
			else if (is_type(*str))
				new_state = STATE_TYPE;
			else
				new_state = STATE_TEXT;
		}

// width
		else if (state == STATE_WIDTH)
		{
			if (*str == '%')
				new_state = STATE_FORMAT;
			else if (*str >= '0' && *str <= '9')
				; // ok
			else if (*str == '.')
				new_state = STATE_UNDEF_PRECISION;
			else if (is_type(*str))
				new_state = STATE_TYPE;
			else
				new_state = STATE_TEXT;
		}

// undef_precision
		else if (state == STATE_UNDEF_PRECISION)
		{
			if (*str == '%')
				new_state = STATE_FORMAT;
			else if (*str == '-')
				new_state = STATE_PRECISION;
			else if (*str >= '0' && *str <= '9')
				new_state = STATE_PRECISION;
			else if (is_type(*str))
				new_state = STATE_TYPE;
			else
				new_state = STATE_TEXT;
		}

// precision
		else if (state == STATE_PRECISION)
		{
			if (*str == '%')
				new_state = STATE_FORMAT;
			else if (*str >= '0' && *str <= '9')
				;
			else if (is_type(*str))
				new_state = STATE_TYPE;
			else
				new_state = STATE_TEXT;
		}

// type
		else if (state == STATE_TYPE)
		{
			if (*str == '%')
				new_state = STATE_FORMAT;
			else
				new_state = STATE_TEXT;
		}

// end
		if (*str == '\0')
			new_state = STATE_END;
		// printf("new state: %d\n", new_state);

// print state
		if (state != new_state)
		{
			if (new_state == STATE_WIDTH)
			{
				width = ft_atoi(str);
				has_width = true;
			}
			if (new_state == STATE_UNDEF_PRECISION)
			{
				precision = 0;
				has_precision = true;
			}
			if (new_state == STATE_PRECISION)
				precision = ft_atoi(str);

			if (new_state == STATE_FORMAT)
			{
				has_precision = false;
				has_width = false;
			}
			if (new_state == STATE_TEXT)
			{
				text_start = str;
			}
			if (state == STATE_TEXT)
			{
				write(1, text_start, str - text_start);
				// printf("%.*s", (int)(str - text_start), text_start);
			}
			if (state == STATE_TYPE)
			{
				if (str[-1] == '%')
					write(1, "%", 1);
					// printf("%%");
				else if (str[-1] == 's')
					print_s(va_arg(args, char *));
				else if (str[-1] == 'c')
					print_c(va_arg(args, int));
				else if (str[-1] == 'd' || str[-1] == 'i')
					print_s(ft_itoa(va_arg(args, int)));
				else if (str[-1] == 'u')
					print_usigned_dec(va_arg(args, int));
				else if (str[-1] == 'x' || str[-1] == 'X')
					print_usigned_hex(va_arg(args, int), str[-1]);
				else if (str[-1] == 'p')
					print_p(va_arg(args, void *));
			}
			state = new_state;
		}
		str++;
	}
	va_end(args);
	return (0);
}

static void print_p(void *pnt)
{
	;
}

static void print_usigned_hex(int nbr, const char up_lo)
{
	int size = (int)get_size(nbr);
	char array[size];
	int i;
	int digit;
	unsigned long ul_nbr;

	i = size - 1;
	ul_nbr = (unsigned long)nbr;
	if (up_lo == 'x')
	{
		while (i != -1)
		{
			digit = ul_nbr % 16;
			ul_nbr = ul_nbr / 16;
			array[i] = get_hex_lo_digit(digit);
			i--;
		}
	}
	else if (up_lo == 'X')
	{
		while (i != -1)
		{
			digit = ul_nbr % 16;
			ul_nbr = ul_nbr / 16;
			array[i] = get_hex_up_digit(digit);
			i--;
		}
	}
	write(1, array, size);
}

static void print_usigned_dec(int nbr)
{
	char *str_nbr = ft_itoa(nbr);
	while (*str_nbr)
	{
		if (*str_nbr != '-')
			write(1, str_nbr, 1);
		str_nbr++;
	}
}

static void print_s(const char *str)
{
	// size_t len = ft_strlen(str);
	// write(1, str, len);
	while (*str)
		{
			write(1, str, 1);
			str++;
		}
}

static void print_c(char c)
{
	write(1, &c, 1);
}

static void print_flags(int flag)
{
	// printf("\tflag: ");
	// if (flag & FLAG_MINUS) printf("minus ");
	// if (flag & FLAG_ZERO) printf("zero ");
	// if (flag & FLAG_HASH) printf("hash ");
	// if (flag & FLAG_SPACE) printf("space ");
	// if (flag & FLAG_PLUS) printf("plus ");
	// printf("\n");
	return ;
}

static size_t	get_size(int n)
{
	size_t	size;

	size = 0;
	if (n <= 0)
		size = 1;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static char	*ft_itoa(int n)
{
	char	*result;
	int		size;
	long	digit;

	size = get_size(n);
	result = malloc((size + 1) * sizeof(char));
	if (!result)
		return (NULL);
	digit = (long)n;
	if (n < 0)
	{
		digit *= -1;
		*result = '-';
	}
	result[size--] = '\0';
	while (digit >= 0)
	{
		result[size--] = (digit % 10) + '0';
		digit /= 10;
		if (digit == 0)
			break ;
	}
	return (result);
}

static char	get_hex_lo_digit(int digit)
{
	char c;

	if (digit < 10)
	{
		c = '0' + digit;
	}
	else
	{
		c = 'a' + digit - 10;
	}
	return c;
}

static char	get_hex_up_digit(int digit)
{
	char c;

	if (digit < 10)
	{
		c = '0' + digit;
	}
	else
	{
		c = 'A' + digit - 10;
	}
	return c;
}

static int	ft_atoi(const char *str)
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

static bool is_type(char c)
{
	return (c == 'c' || c == 's'
			|| c == 'p' || c == 'd'
			|| c == 'i' || c == 'u'
			|| c == 'x' || c == 'X'
			|| c == '%');
}

static bool is_flag(char c)
{
	return (c == '-' || c == '0' || c == '#' || c == ' ' || c == '+');
}

static int get_flag(char c)
{
	if (c == '-')
		return (FLAG_MINUS);
	else if (c == '0')
		return (FLAG_ZERO);
	else if (c == '#')
		return (FLAG_HASH);
	else if (c == ' ')
		return (FLAG_SPACE);
	else if (c == '+')
		return (FLAG_PLUS);
	return (0);
}

int main(void)
{
	ft_printf("print %%\n");
	ft_printf("print %s\n", "string");
	ft_printf("print %char\n", 'c');
	ft_printf("print d: %d\n", INT_MIN);
	ft_printf("print i: %i\n", INT_MIN);
	ft_printf("print u: %u\n", INT_MIN);
	ft_printf("print x: %x\n", 376237); // 5bdad
	ft_printf("print X: %X\n", 376237);
	// ft_printf("print addr %p\n", &a);
	return (0);
}
