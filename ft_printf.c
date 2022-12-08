
#include <stdio.h>

int parse_str(const char *str);
int print_parse_str(int state, int len, const char *start);
int print_parse_nbr(int state, int nbr);
int	ft_atoi(const char *str);

enum e_State
{
	STATE_TEXT,
	STATE_FORMAT,
	STATE_FLAG,
	STATE_WIDTH,
	STATE_UNDEF_PRECISION,
	STATE_PRECISION,
	STATE_TYPE,
	STATE_END
};

int parse_str(const char *str)
{
	int len;
	int width;
	int precision;
	const char *start = str;

	enum e_State state = STATE_TEXT;
	enum e_State new_state = state;
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
			if (*str == '-' || *str == '0')
				new_state = STATE_FLAG;
			else if (*str == '#' || *str == ' ' || *str == '+')
				new_state = STATE_FLAG;
			else if (*str >= '1' && *str <= '9')
			{
				width = ft_atoi(str);
				new_state = STATE_WIDTH;
			}
			else if (*str == '.')
				new_state = STATE_UNDEF_PRECISION;
			else if (*str == 'c' || *str == 's'
					|| *str == 'p' || *str == 'd'
					|| *str == 'i' || *str == 'u'
					|| *str == 'x' || *str == 'X')
				new_state = STATE_TYPE;
			else
				new_state = STATE_TEXT;
		}

// flag
		else if (state == STATE_FLAG)
		{
			if (*str == '-' || *str == '0')
				state = STATE_FLAG;
			else if (*str == '#' || *str == ' ' || *str == '+')
				state = STATE_FLAG;
			else if (*str >= '1' && *str <= '9')
			{
				width = ft_atoi(str);
				new_state = STATE_WIDTH;
			}
			else if (*str == '.')
				new_state = STATE_UNDEF_PRECISION;
			else if (*str == 'c' || *str == 's'
					|| *str == 'p' || *str == 'd'
					|| *str == 'i' || *str == 'u'
					|| *str == 'x' || *str == 'X')
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
				state = STATE_WIDTH;
			else if (*str == '.')
				new_state = STATE_UNDEF_PRECISION;
			else if (*str == 'c' || *str == 's'
					|| *str == 'p' || *str == 'd'
					|| *str == 'i' || *str == 'u'
					|| *str == 'x' || *str == 'X')
				state = STATE_TYPE;
			else
				new_state = STATE_TEXT;
		}

// undef_precision
		else if (state == STATE_UNDEF_PRECISION)
		{
			if (*str == '%')
				new_state = STATE_FORMAT;
			else if (*str == '-')
			{
				precision = ft_atoi(str);
				new_state = STATE_PRECISION;
			}

			else if (*str >= '0' && *str <= '9')
			{
				precision = ft_atoi(str);
				new_state = STATE_PRECISION;
			}

			else if (*str == 'c' || *str == 's'
					|| *str == 'p' || *str == 'd'
					|| *str == 'i' || *str == 'u'
					|| *str == 'x' || *str == 'X')
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
				state = STATE_PRECISION;
			else if (*str == 'c' || *str == 's'
					|| *str == 'p' || *str == 'd'
					|| *str == 'i' || *str == 'u'
					|| *str == 'x' || *str == 'X')
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
			if (state == STATE_WIDTH)
			{
				print_parse_nbr(state, width);
				start = str;
				state = new_state;
			}
			else if (state == STATE_PRECISION)
			{
				print_parse_nbr(state, precision);
				start = str;
				state = new_state;
			}
			else
			{
				len = str - start;
				print_parse_str(state, len, start);
				start = str;
				state = new_state;
			}
		}
		str++;
	}
	return (0);
}

int print_parse_str(int state, int len, const char *start)
{
	if (state == STATE_TEXT)
		printf("text: %.*s\n", len, start);
	else if (state == STATE_FORMAT)
		return (0);
	else if (state == STATE_FLAG)
		printf("flag: %.*s\n", len, start);
	else if (state == STATE_TYPE)
		printf("type: %.*s\n", len, start);
	else if (state == STATE_UNDEF_PRECISION)
		return (0);
	return (0);
}

int print_parse_nbr(int state, int nbr)
{
	if (state == STATE_WIDTH)
		printf("width: %d\n", nbr);
	else if (state == STATE_PRECISION)
		printf("precision: %d\n", nbr);
	return (0);
}

int	ft_atoi(const char *str)
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

int main(void)
{
	// parse_str("%.15d color %s");
	// parse_str("dd%c");
	// parse_str("%.5-8d");
	// parse_str("% -s");
	// parse_str("a%10dx");
	// parse_str("d%0.-");
	parse_str("hello%22dsmafl"); // -
	// parse_str("h%5.12"); // +
	return (0);
}
