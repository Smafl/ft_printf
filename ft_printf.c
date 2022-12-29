
#include "ft_printf.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>

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
				if (str[-1] == '%')
					write(1, "%", 1);
				else if (str[-1] == 's')
					print_s(va_arg(args, char *), flag, width, precision);
				else if (str[-1] == 'c')
					print_c(va_arg(args, int), flag, width);
				else if (str[-1] == 'd' || str[-1] == 'i')
					print_s(ft_itoa(va_arg(args, int)), flag, width, precision);
				else if (str[-1] == 'u')
					print_unsigned_dec(va_arg(args, int));
				else if (str[-1] == 'x')
					print_unsigned_x_hex(va_arg(args, unsigned long), flag, width);
				else if (str[-1] == 'X')
					print_unsigned_X_hex(va_arg(args, unsigned long), flag, width);
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
