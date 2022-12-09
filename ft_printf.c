
#include <stdio.h>

int parse_str(const char *str);
int print_str(int state, int len, const char *text_start);
int print_nbr(int state, int nbr);
int print_flag(int flag);
int	ft_atoi(const char *str);

#define FLAG_MINUS (1 << 0)
#define FLAG_ZERO (1 << 1)
#define FLAG_HASH (1 << 2)
#define FLAG_SPACE (1 << 3)
#define FLAG_PLUS (1 << 4)

enum e_State
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

int parse_str(const char *str)
{
	int len;
	int flag;
	int width;
	int precision;
	const char *text_start = str;

	enum e_State state = STATE_TEXT;
	enum e_State new_state = state;
	while (state != STATE_END)
	{
		printf("begin while state: %d\n", state);
		printf("char: %c\n", *str);
		printf("text start: %s\n", text_start);
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
			if (*str == '-' || *str == '0' || *str == '#' || *str == ' ' || *str == '+')
			{
				if (*str == '-')
					flag = FLAG_MINUS;
				else if (*str == '0')
					flag = FLAG_ZERO;
				else if (*str == '#')
					flag = FLAG_HASH;
				else if (*str == ' ')
					flag = FLAG_SPACE;
				else if (*str == '+')
					flag = FLAG_PLUS;
				new_state = STATE_FLAG;
			}
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
			if (*str == '-' || *str == '0' || *str == '#' || *str == ' ' || *str == '+')
			{
				if (*str == '-')
					flag = FLAG_MINUS;
				else if (*str == '0')
					flag = FLAG_ZERO;
				else if (*str == '#')
					flag = FLAG_HASH;
				else if (*str == ' ')
					flag = FLAG_SPACE;
				else if (*str == '+')
					flag = FLAG_PLUS;
				new_state = STATE_FLAG;
			}
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
		printf("new state: %d\n", new_state);
// print state
		if (state != new_state)
		{
			if (state == STATE_WIDTH)
			{
				print_nbr(state, width);
				text_start = str;
				state = new_state;
			}
			else if (state == STATE_PRECISION)
			{
				print_nbr(state, precision);
				text_start = str;
				state = new_state;
			}
			else if (state == STATE_FLAG)
			{
				print_flag(flag);
				text_start = str;
				state = new_state;
			}
			else
			{
				len = str - text_start;
				print_str(state, len, text_start);
				text_start = str;
				state = new_state;
			}
		}
		str++;
	}
	return (0);
}

int print_flag(int flag)
{
	if (flag & FLAG_MINUS) printf("	flag: minus\n");
	if (flag & FLAG_ZERO) printf("	flag: zero\n");
	if (flag & FLAG_HASH) printf("	flag: hash\n");
	if (flag & FLAG_SPACE) printf("	flag: space\n");
	if (flag & FLAG_PLUS) printf("	flag: plus\n");
	return (0);
}

int print_str(int state, int len, const char *text_start)
{
	if (state == STATE_TEXT)
		printf("text: %.*s\n", len, text_start);
	else if (state == STATE_FORMAT)
		printf("format:\n");
	else if (state == STATE_TYPE)
		printf("	type: %.*s\n", len, text_start);
	else if (state == STATE_UNDEF_PRECISION)
		return (0);
	return (0);
}

int print_nbr(int state, int nbr)
{
	if (state == STATE_WIDTH)
		printf("	width: %d\n", nbr);
	else if (state == STATE_PRECISION)
		printf("	precision: %d\n", nbr);
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
	parse_str("%-0%0-% %+%#%0%-");
	// parse_str("dd%c");
	// parse_str("%.5-8d"); // - (remove text at first line)
	// parse_str("% -s"); // - (remove text at first line)
	// parse_str("a%10dx");
	// parse_str("d%0.-"); // - (flags)
	// parse_str("hello%25dsmafl");
	// parse_str("h%5.12");
	return (0);
}

/*
text
format
flag minus
flag zero
format
flag zero
flag minus
format
flag space
format
flag plus
format
flag hash
format
flag zero
format
flag minus
*/