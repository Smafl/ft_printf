
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

static int parse_str(const char *str);
static void print_flags(int flag);
static int	ft_atoi(const char *str);
static bool is_type(char c);
static bool is_flag(char c);
static int get_flag(char c);

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

static int parse_str(const char *str)
{
	int flag;
	int width;
	int precision;
	bool has_width;
	bool has_precision;
	const char *text_start = str;

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
				// write(1, text_start, str - text_start);
				printf("text: %.*s\n", (int)(str - text_start), text_start);
			}
			if (state == STATE_TYPE)
			{
				printf("format:\n");
				if (flag) print_flags(flag);
				if (has_width) printf("\twidth: %d\n", width);
				if (has_precision) printf("\tprecision: %d\n", precision);
				printf("\ttype: %c\n", str[-1]);

			}
			state = new_state;
		}
		str++;
	}
	return (0);
}

static void print_flags(int flag)
{
	printf("\tflag: ");
	if (flag & FLAG_MINUS) printf("minus ");
	if (flag & FLAG_ZERO) printf("zero ");
	if (flag & FLAG_HASH) printf("hash ");
	if (flag & FLAG_SPACE) printf("space ");
	if (flag & FLAG_PLUS) printf("plus ");
	printf("\n");
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
	// parse_str("%.15d color %s");
	// parse_str("%-0%0-% %+%#%0%-");
	// parse_str("dd%c");
	// parse_str("%.5-8d");
	// parse_str("% -s");
	// parse_str("a%10dx");
	// parse_str("d%0.-"); // - (flags)
	// parse_str("hello%25dsmafl");
	// parse_str("h%5.12");
	parse_str("smafl%0-y123");
	return (0);
}
