
#include "ft_printf.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>

// print_c_str.c
static void print_s(const char *str, int flag, int width, int precision);
static void print_c(char c, int flag, int width, int precision);

// print_dec_hex_p.c
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

int ft_printf(const char *str, ...)
{
	int flag;
	int width;
	int precision;
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
				// char *printf_core(char type, va_list args, size_t *out_len);
				if (str[-1] == '%')
					write(1, "%", 1);
				else if (str[-1] == 's')
					print_s(va_arg(args, char *), flag, width, precision);
				else if (str[-1] == 'c')
					print_c(va_arg(args, int), flag, width, precision);
				else if (str[-1] == 'd' || str[-1] == 'i')
					print_s(ft_itoa(va_arg(args, int)), flag, width, precision);
				else if (str[-1] == 'u')
					print_unsigned_dec(va_arg(args, int));
				else if (str[-1] == 'x')
					print_unsigned_x_hex(va_arg(args, int), flag, width, precision);
				else if (str[-1] == 'X')
					print_unsigned_X_hex(va_arg(args, int));
				else if (str[-1] == 'p')
					print_p(va_arg(args, void *), flag, width, precision);
			}
			state = new_state;
		}
		str++;
	}
	va_end(args);
	return (0);
}

/*
вынести в отдельную ф-ю заполнение массива
сразу убрать флаг 0, если - и 0
считать возвращаемое значение (кол-во печатаемых символов)
*/

int checker(void)
{

	// int a = 10;

	// ft_printf("print %%: %%\n\n");
	// printf("print %%: %10%\n");

	// ft_printf("1 ft_print s: %-15.5s\n\n", "string");

	// printf("1 st_print s: %-15.5s\n", "string");

	// ft_printf("1 print c: %10c\n", 'c');
	// ft_printf("2 print c: %010c\n", 'c');
	// ft_printf("3 print c: %-10c\n", 'c');
	// ft_printf("4 print c: %-010c\n\n", 'c');

	// printf("1 print c: %10c\n", 'c');
	// printf("2 print c: %010c\n", 'c');
	// printf("3 print c: %-10c\n", 'c');
	// printf("4 print c: %-010c\n", 'c');

	// ft_printf("1 ft_print d: %-20d\n", INT_MIN);
	// ft_printf("2 ft_print i: %-20i\n", INT_MIN);

	// printf("1 st_print d: %-20d\n", INT_MIN);
	// printf("2 st_print i: %-20i\n", INT_MIN);
	// ft_printf("print u: %u\n", INT_MIN);
	ft_printf("ft print x: %#x\n", 376237); // 5bdad
	printf("st print x: %#x\n", 376237); // 5bdad
	// ft_printf("print X: %X\n", 376237);
	// ft_printf("ft print addr [%.2p]\n", &a);
	// printf("st print addr [%.2p]\n", &a);

	// ft_printf("print %c and %% and %p\n", 'r', &a);
	return (0);
}

int main()
{
	checker();
	// system("leaks a.out");
}
