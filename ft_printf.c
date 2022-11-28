
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
	int len_return = 0;
	int len_text = 0;
	char *text;

	enum e_State state = STATE_TEXT;
	print_parse_str(state);
	while (str[i])
	{
// text
		if (state == STATE_TEXT)
		{
			if (str[i] == '%')
			{
				state = STATE_FORMAT;
				print_parse_str(state);
			}
			else
			{
				len_text++;
			}
			i++;
			continue ;
		}

// format
		if (state == STATE_FORMAT)
		{
			if (str[i] == '-' || str[i] == '0')
			{
				printf("%c\n", str[i]);
				state = STATE_FLAG;
				print_parse_str(state);
			}
			else if (str[i] == '#' || str[i] == ' ' || str[i] == '+')
			{
				printf("%c\n", str[i]);
				state = STATE_FLAG;
				print_parse_str(state);
			}
			else if (str[i] >= '1' && str[i] <= '9')
			{
				printf("%c\n", str[i]);
				state = STATE_WIDTH;
				print_parse_str(state);
			}
			else if (str[i] == '.')
			{
				printf("%c\n", str[i]);
				state = STATE_UNDEF_PRECISION;
				print_parse_str(state);
			}
			else if (str[i] == 'c' || str[i] == 's'
					|| str[i] == 'p' || str[i] == 'd'
					|| str[i] == 'i' || str[i] == 'u'
					|| str[i] == 'x' || str[i] == 'X')
			{
				printf("%c\n", str[i]);
				state = STATE_TYPE;
				print_parse_str(state);
			}
			else
			{
				printf("%c\n", str[i]);
				state = STATE_TEXT;
				print_parse_str(state);
			}
			i++;
			continue ;
		}

// flag
		if (state == STATE_FLAG)
		{
			if (str[i] == '-' || str[i] == '0')
			{
				printf("%c\n", str[i]);
				print_parse_str(state);
			}
			else if (str[i] == '#' || str[i] == ' ' || str[i] == '+')
			{
				printf("%c\n", str[i]);
				print_parse_str(state);
			}
			else if (str[i] >= '1' && str[i] <= '9')
			{
				printf("%c\n", str[i]);
				state = STATE_WIDTH;
				print_parse_str(state);
			}
			else if (str[i] == '.')
			{
				printf("%c\n", str[i]);
				state = STATE_UNDEF_PRECISION;
				print_parse_str(state);
			}
			else if (str[i] == 'c' || str[i] == 's'
					|| str[i] == 'p' || str[i] == 'd'
					|| str[i] == 'i' || str[i] == 'u'
					|| str[i] == 'x' || str[i] == 'X')
			{
				printf("%c\n", str[i]);
				state = STATE_TYPE;
				print_parse_str(state);
			}
			else
			{
				printf("%c\n", str[i]);
				state = STATE_TEXT;
				print_parse_str(state);
			}
			i++;
			continue ;
		}

// width
		if (state == STATE_WIDTH)
		{
			if (str[i] == '%')
			{
				printf("%c\n", str[i]);
				state = STATE_FORMAT;
				print_parse_str(state);
			}
			else if (str[i] >= '0' && str[i] <= '9')
			{
				printf("%c\n", str[i]);
				state = STATE_WIDTH;
				print_parse_str(state);
			}
			else if (str[i] == '.')
			{
				printf("%c\n", str[i]);
				state = STATE_UNDEF_PRECISION;
				print_parse_str(state);
			}
			else if (str[i] == 'c' || str[i] == 's'
					|| str[i] == 'p' || str[i] == 'd'
					|| str[i] == 'i' || str[i] == 'u'
					|| str[i] == 'x' || str[i] == 'X')
			{
				printf("%c\n", str[i]);
				state = STATE_TYPE;
				print_parse_str(state);
			}
			else
			{
				printf("%c\n", str[i]);
				state = STATE_TEXT;
				print_parse_str(state);
			}
			i++;
			continue ;
		}

// undef_precision
		if (state == STATE_UNDEF_PRECISION)
		{
			if (str[i] == '%')
			{
				printf("%c\n", str[i]);
				state = STATE_FORMAT;
				print_parse_str(state);
			}
			else if (str[i] == '-')
			{
				printf("%c\n", str[i]);
				state = STATE_PRECISION;
				print_parse_str(state);
			}
			else if (str[i] >= '0' && str[i] <= '9')
			{
				printf("%c\n", str[i]);
				state = STATE_PRECISION;
				print_parse_str(state);
			}
			else if (str[i] == 'c' || str[i] == 's'
					|| str[i] == 'p' || str[i] == 'd'
					|| str[i] == 'i' || str[i] == 'u'
					|| str[i] == 'x' || str[i] == 'X')
			{
				printf("%c\n", str[i]);
				state = STATE_TYPE;
				print_parse_str(state);
			}
			else
			{
				printf("%c\n", str[i]);
				state = STATE_TEXT;
				print_parse_str(state);
			}
			i++;
			continue ;
		}

// precision
		if (state == STATE_PRECISION)
		{
			if (str[i] == '%')
			{
				printf("%c\n", str[i]);
				state = STATE_FORMAT;
				print_parse_str(state);
			}
			else if (str[i] >= '0' && str[i] <= '9')
			{
				printf("%c\n", str[i]);
				state = STATE_PRECISION;
				print_parse_str(state);
			}
			else if (str[i] == 'c' || str[i] == 's'
					|| str[i] == 'p' || str[i] == 'd'
					|| str[i] == 'i' || str[i] == 'u'
					|| str[i] == 'x' || str[i] == 'X')
			{
				printf("%c\n", str[i]);
				state = STATE_TYPE;
				print_parse_str(state);
			}
			else
			{
				printf("%c\n", str[i]);
				state = STATE_TEXT;
				print_parse_str(state);
			}
			i++;
			continue ;
		}

// type
		if (state == STATE_TYPE)
		{
			if (str[i] == '%')
			{
				state = STATE_FORMAT;
				print_parse_str(state);
			}
			else
			{
				state = STATE_TEXT;
				print_parse_str(state);
			}
			i++;
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
	parse_str("hello world %-022dsmafl");
	return (0);
}
