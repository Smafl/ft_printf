
#include <stdio.h>

int parse_str(const char *str);
int print_parse_str(int state, int len, const char *start);

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
			// print state
			if (state != new_state)
			{
				len = str - start;
				print_parse_str(state, len, start);
				start = str;
				state = new_state;
				str++;
			}
		}
// format
		if (state == STATE_FORMAT)
		{
			if (*str == '-' || *str == '0')
				new_state = STATE_FLAG;
			else if (*str == '#' || *str == ' ' || *str == '+')
				new_state = STATE_FLAG;
			else if (*str >= '1' && *str <= '9')
				new_state = STATE_WIDTH;
			else if (*str == '.')
				new_state = STATE_UNDEF_PRECISION;
			else if (*str == 'c' || *str == 's'
					|| *str == 'p' || *str == 'd'
					|| *str == 'i' || *str == 'u'
					|| *str == 'x' || *str == 'X')
				new_state = STATE_TYPE;
			else
				new_state = STATE_TEXT;
			// print state
			if (state != new_state)
			{
				len = str - start;
				print_parse_str(state, len, start);
				start = str;
				state = new_state;
				str++;
			}
		}

// flag
		if (state == STATE_FLAG)
		{
			if (*str == '-' || *str == '0')
				new_state = STATE_FLAG;
			else if (*str == '#' || *str == ' ' || *str == '+')
				new_state = STATE_FLAG;
			else if (*str >= '1' && *str <= '9')
				new_state = STATE_WIDTH;
			else if (*str == '.')
				new_state = STATE_UNDEF_PRECISION;
			else if (*str == 'c' || *str == 's'
					|| *str == 'p' || *str == 'd'
					|| *str == 'i' || *str == 'u'
					|| *str == 'x' || *str == 'X')
				new_state = STATE_TYPE;
			else
				new_state = STATE_TEXT;
			// print state
			if (state != new_state)
			{
				len = str - start;
				print_parse_str(state, len, start);
				start = str;
				state = new_state;
				str++;
			}
		}

// width
		if (state == STATE_WIDTH)
		{
			if (*str == '%')
				new_state = STATE_FORMAT;
			else if (*str >= '0' && *str <= '9')
				new_state = STATE_WIDTH;
			else if (*str == '.')
				new_state = STATE_UNDEF_PRECISION;
			else if (*str == 'c' || *str == 's'
					|| *str == 'p' || *str == 'd'
					|| *str == 'i' || *str == 'u'
					|| *str == 'x' || *str == 'X')
				state = STATE_TYPE;
			else
				new_state = STATE_TEXT;
			// print state
			if (state != new_state)
			{
				len = str - start;
				print_parse_str(state, len, start);
				start = str;
				state = new_state;
				str++;
			}
		}

// undef_precision
		if (state == STATE_UNDEF_PRECISION)
		{
			if (*str == '%')
				new_state = STATE_FORMAT;
			else if (*str == '-')
				new_state = STATE_PRECISION;
			else if (*str >= '0' && *str <= '9')
				new_state = STATE_PRECISION;
			else if (*str == 'c' || *str == 's'
					|| *str == 'p' || *str == 'd'
					|| *str == 'i' || *str == 'u'
					|| *str == 'x' || *str == 'X')
				new_state = STATE_TYPE;
			else
				new_state = STATE_TEXT;
			// print state
			if (state != new_state)
			{
				len = str - start;
				print_parse_str(state, len, start);
				start = str;
				state = new_state;
				str++;
			}
		}

// precision
		if (state == STATE_PRECISION)
		{
			if (*str == '%')
				new_state = STATE_FORMAT;
			else if (*str >= '0' && *str <= '9')
				new_state = STATE_PRECISION;
			else if (*str == 'c' || *str == 's'
					|| *str == 'p' || *str == 'd'
					|| *str == 'i' || *str == 'u'
					|| *str == 'x' || *str == 'X')
				new_state = STATE_TYPE;
			else
				new_state = STATE_TEXT;
			// print state
			if (state != new_state)
			{
				len = str - start;
				print_parse_str(state, len, start);
				start = str;
				state = new_state;
				str++;
			}
		}

// type
		if (state == STATE_TYPE)
		{
			if (*str == '%')
				new_state = STATE_FORMAT;
			else
				new_state = STATE_TEXT;
			// print state
			if (state != new_state)
			{
				len = str - start;
				print_parse_str(state, len, start);
				start = str;
				state = new_state;
				str++;
			}
		}

// end
		if (*str == '\0')
		{
			new_state = STATE_END;
			// print state
			if (state != new_state)
			{
				len = str - start;
				print_parse_str(state, len, start);
				start = str;
				state = new_state;
				str++;
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
		printf("format:\n");
	else if (state == STATE_FLAG)
		printf("	flag: %.*s\n", len, start);
	else if (state == STATE_WIDTH)
		printf("	width: %.*s\n", len, start);
	else if (state == STATE_PRECISION)
		printf("	precision: %.*s\n", len, start);
	else if (state == STATE_TYPE)
		printf("type: %.*s\n", len, start);
	// printf("len: %d\n", len);
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
	parse_str("hello%22d");
	// parse_str("hello%12.12");
	return (0);
}
