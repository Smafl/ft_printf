
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
	int printf_len;
	int temp_return;
	const char *text_start;
	const char *args_str;

	text_start = str;
	va_list args;
	va_start(args, str);

	width = 0;
	precision = 0;
	printf_len = 0;
	temp_return = 0;
	enum e_state state = STATE_TEXT;
	enum e_state new_state = state;
	while (state != STATE_END)
	{
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
			if (*str >= '0' && *str <= '9')
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
			if (*str == '-')
				new_state = STATE_PRECISION;
			else if (*str >= '0' && *str <= '9')
				new_state = STATE_PRECISION;
			else if (is_type(*str))
				new_state = STATE_TYPE;
			else
				new_state = STATE_TEXT;
		}

// precision %23%%d
		else if (state == STATE_PRECISION)
		{
			if (*str >= '0' && *str <= '9')
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
// print state
		if (state != new_state)
		{
			if (state == STATE_TYPE)
			{
				if (str[-1] == '%')
				{
					temp_return = print_c('%', flag, width);
				}
				else if (str[-1] == 's')
				{
					args_str = va_arg(args, char *);
					if (args_str == NULL)
						temp_return = print_str("(null)", flag, width, precision);
					else
						temp_return = print_str(args_str, flag, width, precision);
				}
				else if (str[-1] == 'c')
					temp_return = print_c(va_arg(args, int), flag, width);
				else if (str[-1] == 'd' || str[-1] == 'i')
					temp_return = print_dec_int(va_arg(args, int), flag, width, precision);
				else if (str[-1] == 'u')
					temp_return = print_dec_int(va_arg(args, unsigned int), flag & ~FLAG_PLUS & ~FLAG_SPACE, width, precision);
				else if (str[-1] == 'x' || str[-1] == 'X' || str[-1] == 'p')
				{
					if (str[-1] == 'X')
						flag |= FLAG_UPPERCASE;
					if (str[-1] == 'x' || str[-1] == 'X')
						temp_return = print_unsigned_hex((unsigned long)va_arg(args, unsigned int), flag, width, precision);
					if (str[-1] == 'p')
					{
						flag |= FLAG_POINTER;
						temp_return = print_unsigned_hex((unsigned long)va_arg(args, void *), flag, width, precision);
					}
				}
				if (temp_return == -1)
					return (-1);
				else
				{
					printf_len += temp_return;
					temp_return = 0;
				}
			}
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
			{
				if (write(1, text_start, str - text_start) == -1)
					return (-1);
				else
					printf_len += str - text_start;
			}
			state = new_state;
		}
		str++;
	}
	va_end(args);
	return (printf_len);
}

/*
вынести в отдельную ф-ю заполнение массива
сразу убрать флаг 0, если - и 0
*/
