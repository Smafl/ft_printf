
#include <stdio.h>

int parse_str(const char *str);
int print_parse_str(int state_number);

enum e_State
{
	STATE_TEXT,
	STATE_FORMAT,
	STATE_FLAG,
	STATE_WIDTH,
	STATE_UNDEF_PRECISION,
	STATE_PRECISION,
	STATE_TYPE
};

int parse_str(const char *str)
{
	int i = 0;
	int len = 0;
	const char *start = str;
	const char *text;

	enum e_State state = STATE_TEXT;
	enum e_State new_state = state;
	while (*str)
	{
// text
		if (state == STATE_TEXT)
		{
			if (*str == '%')
			{
				new_state = STATE_FORMAT;
				text = str - len;

			}
			else
			{
				len++;
			}
			str++;
		}
		if (state != new_state)
		{
			print_parse_str(state);
			while (len != 0)
			{
				printf();
				len--;
			}
			printf("\n");
			state = new_state;
		}

// format
		if (state == STATE_FORMAT)
		{
			if (*str == '-' || *str == '0')
			{
				state = STATE_FLAG;
			}
			else if (*str == '#' || *str == ' ' || *str == '+')
			{
				state = STATE_FLAG;
			}
			else if (*str >= '1' && *str <= '9')
			{
				state = STATE_WIDTH;
				len++;
			}
			else if (*str == '.')
			{
				state = STATE_UNDEF_PRECISION;
			}
			else if (*str == 'c' || *str == 's'
					|| *str == 'p' || *str == 'd'
					|| *str == 'i' || *str == 'u'
					|| *str == 'x' || *str == 'X')
			{
				state = STATE_TYPE;
			}
			else
			{
				state = STATE_TEXT;
			}
			str++;
			continue ;
		}

// flag
		if (state == STATE_FLAG)
		{
			if (*str == '-' || *str == '0')
			{
				// printf("%c\n", *str);
			}
			else if (*str == '#' || *str == ' ' || *str == '+')
			{
				// printf("%c\n", *str);
			}
			else if (*str >= '1' && *str <= '9')
			{
				state = STATE_WIDTH;
			}
			else if (*str == '.')
			{
				state = STATE_UNDEF_PRECISION;
			}
			else if (*str == 'c' || *str == 's'
					|| *str == 'p' || *str == 'd'
					|| *str == 'i' || *str == 'u'
					|| *str == 'x' || *str == 'X')
			{
				state = STATE_TYPE;
			}
			else
			{
				state = STATE_TEXT;
			}
			str++;
			continue ;
		}

// width
		if (state == STATE_WIDTH)
		{
			if (*str == '%')
			{
				new_state = STATE_FORMAT;
			}
			else if (*str >= '0' && *str <= '9')
			{
				len++;
			}
			else if (*str == '.')
			{
				new_state = STATE_UNDEF_PRECISION;
			}
			else if (*str == 'c' || *str == 's'
					|| *str == 'p' || *str == 'd'
					|| *str == 'i' || *str == 'u'
					|| *str == 'x' || *str == 'X')
			{
				state = STATE_TYPE;
			}
			else
			{
				new_state = STATE_TEXT;
			}
			str++;
		}

// undef_precision
		if (state == STATE_UNDEF_PRECISION)
		{
			if (*str == '%')
			{
				state = STATE_FORMAT;
			}
			else if (*str == '-')
			{
				state = STATE_PRECISION;
			}
			else if (*str >= '0' && *str <= '9')
			{
				state = STATE_PRECISION;
			}
			else if (*str == 'c' || *str == 's'
					|| *str == 'p' || *str == 'd'
					|| *str == 'i' || *str == 'u'
					|| *str == 'x' || *str == 'X')
			{
				state = STATE_TYPE;
			}
			else
			{
				state = STATE_TEXT;
			}
			str++;
			continue ;
		}

// precision
		if (state == STATE_PRECISION)
		{
			if (*str == '%')
			{
				state = STATE_FORMAT;
			}
			else if (*str >= '0' && *str <= '9')
			{
				state = STATE_PRECISION;
			}
			else if (*str == 'c' || *str == 's'
					|| *str == 'p' || *str == 'd'
					|| *str == 'i' || *str == 'u'
					|| *str == 'x' || *str == 'X')
			{
				state = STATE_TYPE;
			}
			else
			{
				state = STATE_TEXT;
			}
			str++;
			continue ;
		}

// type
		if (state == STATE_TYPE)
		{
			if (*str == '%')
			{
				state = STATE_FORMAT;
				print_parse_str(state);
			}
			else
			{
				state = STATE_TEXT;
				print_parse_str(state);
			}
			str++;
			continue ;
		}
	}
	return (0);
}

int print_parse_str(int state_number)
{
	if (state_number == STATE_TEXT)
		printf("text: ");
	else if (state_number == STATE_FORMAT)
		printf("format:\n");
	else if (state_number == STATE_FLAG)
		printf("	flag: ");
	else if (state_number == STATE_WIDTH)
		printf("	width: ");
	else if (state_number == STATE_PRECISION)
		printf("	precision: ");
	else if (state_number == STATE_TYPE)
		printf("type: ");
	return (0);
}

int main(void)
{
	// parse_str("%.15d color %s");
	// parse_str("dd%c");
	// parse_str("%.5-8d");
	// parse_str("% -s");
	// parse_str("a%10dx");
	// parse_str("d%0.-");
	parse_str("hello%22dsmafl");
	return (0);
}
