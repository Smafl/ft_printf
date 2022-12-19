
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>

int ft_printf(const char *str, ...);
static void print_flags(int flag);
static void print_s(const char *str);
static void print_c(char c);
static void print_unsigned_dec(int nbr);
static void print_unsigned_x_hex(int nbr);
static void print_unsigned_X_hex(int nbr);
static void print_p(void *pnt);
static int	ft_atoi(const char *str);
static char	*ft_itoa(int n);
static bool is_type(char c);
static bool is_flag(char c);
static int get_flag(char c);
static char get_hex_digit(int digit);
static size_t get_size(int n);
static unsigned long get_ul_size(unsigned long n);
static int	ft_toupper(int c);
char *printf_core(char type, va_list args, size_t *out_len);

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

int ft_printf(const char *str, ...)
{
	int flag;
	int width;
	int precision;
	size_t out_len;
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
				new_state = STATE_FORMAT;
		}

// format
		else if (state == STATE_FORMAT)
		{
			if (is_flag(*str))
			{
				// assign a new value to int flag
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
				// add a new flag with bitwise OR operator
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
				; // ok
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
				flag |= HAS_WIDTH;
			}
			if (new_state == STATE_UNDEF_PRECISION)
			{
				precision = 0;
				flag |= HAS_PRECISION;
			}
			if (new_state == STATE_PRECISION)
				precision = ft_atoi(str);
			if (new_state == STATE_FORMAT)
				flag = 0;
			if (new_state == STATE_TEXT)
				text_start = str;
			if (state == STATE_TEXT)
				write(1, text_start, str - text_start);
			if (state == STATE_TYPE)
			{
				if ((flag & FLAG_MINUS) && (flag & FLAG_ZERO))
					flag &= ~FLAG_ZERO;
				if ((flag & FLAG_PLUS) && (flag & FLAG_SPACE))
					flag &= ~FLAG_SPACE;
				if ((flag & FLAG_ZERO) && (flag & HAS_PRECISION) && (flag & HAS_WIDTH))
					printf_core(str[-1], args, &out_len);
			}
			state = new_state;
		}
		str++;
	}
	va_end(args);
	return (0);
}

char *printf_core(char type, va_list args, size_t *out_len)
{
	;
}

static void print_p(void *pnt)
{
	unsigned long size = get_ul_size((unsigned long)pnt);
	char array[size];
	int i;
	int digit;
	unsigned long temp;

	i = size - 1;
	temp = (unsigned long)pnt;
	while (i != -1)
	{
		digit = temp % 16;
		temp = temp / 16;
		array[i] = get_hex_digit(digit);
		i--;
	}
	write(1, "0x", 2);
	write(1, array, size);
}

static void print_unsigned_x_hex(int nbr)
{
	int size = (int)get_size(nbr);
	char array[size];
	int i;
	int digit;
	unsigned long ul_nbr;

	i = size - 1;
	ul_nbr = (unsigned long)nbr;
	while (i != -1)
	{
		digit = ul_nbr % 16;
		ul_nbr = ul_nbr / 16;
		array[i] = get_hex_digit(digit);
		i--;
	}
	write(1, array, size);
}

static void print_unsigned_X_hex(int nbr)
{
	int size = (int)get_size(nbr);
	char array[size];
	int i;
	int digit;
	unsigned long ul_nbr;

	i = size - 1;
	ul_nbr = (unsigned long)nbr;
	while (i != -1)
	{
		digit = ul_nbr % 16;
		ul_nbr = ul_nbr / 16;
		array[i] = ft_toupper(get_hex_digit(digit));
		i--;
	}
	write(1, array, size);
}

static void print_unsigned_dec(int nbr)
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
	while (*str)
		{
			write(1, str, 1);
			str++;
		}
}

static int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

static void print_c(char c)
{
	write(1, &c, 1);
}

static void print_zero(int width)
{
	while (width != 0)
		{
			write(1, "0", 1);
			width--;
		}
}

static void print_space(int width)
{
	while (width != 0)
		{
			write(1, " ", 1);
			width--;
		}
}

static int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		c = c - ('a' - 'A');
		return (c);
	}
	else
		return (c);
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

static unsigned long get_ul_size(unsigned long n)
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

static char	get_hex_digit(int digit)
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
	int a = 10;

	// ft_printf("print %%: %%\n\n");
	// printf("print %%: %10%\n");

	// ft_printf("1 ft_print s: %-15.5s\n\n", "string");

	// printf("1 st_print s: %-15.5s\n", "string");

	// ft_printf("1 print c: %10c\n", 'c');
	// ft_printf("2 print c: %010c\n", 'c');
	// ft_printf("3 print c: %-10c\n", 'c');
	// ft_printf("4 print c: %-010c\n\n", 'c');


	ft_printf ("%s %d", "hello", 12);

	

	// printf("1 print c: %10c\n", 'c');
	// printf("2 print c: %010c\n", 'c');
	// printf("3 print c: %-10c\n", 'c');
	// printf("4 print c: %-010c\n", 'c');

	// ft_printf("1 ft_print d: %-20d\n", INT_MIN);
	// ft_printf("2 ft_print i: %-20i\n", INT_MIN);

	// printf("1 st_print d: %-20d\n", INT_MIN);
	// printf("2 st_print i: %-20i\n", INT_MIN);
	// ft_printf("print u: %u\n", INT_MIN);
	// ft_printf("print x: %x\n", 376237); // 5bdad
	// ft_printf("print X: %X\n", 376237);
	// ft_printf("print addr %p\n", &a);
	// ft_printf("print %c and %% and %p\n", 'r', &a);
	return (0);
}
