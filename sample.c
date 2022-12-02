
#include <stdio.h>

int print_parse_str(int state_number);
int parse_str(const char *str);

enum e_State
{
	STATE_TEXT,
	STATE_FORMAT,
	STATE_WIDTH
};

int parse_str(const char *str)
{
	int i = 0;
	int len = 0;
	int ii = 0;
	int width;
	char *width_start;

	enum e_State state = STATE_TEXT;
	enum e_State new_state = state;
	while (str[i])
	{
// text
		if (state == STATE_TEXT)
		{
			if (str[i] == '%')
			{
				new_state = STATE_FORMAT;
			}
			else
			{
				len++;
			}
			i++;
		}
		if (state != new_state)
		{
			print_parse_str(state);
			while (len != ii)
			{
				printf("%c", str[ii]);
				ii++;
			}
			printf("\n");
			len = 0;
			ii = 0;
			state = new_state;
		}

// format
		if (state == STATE_FORMAT)
		{
			if (str[i] >= '1' && str[i] <= '9')
			{
				new_state = STATE_WIDTH;
			}
			else
			{
				new_state = STATE_TEXT;
			}
			i++;
		}
		if (state != new_state)
		{
			
		}

// width
		if (state == STATE_WIDTH)
		{
			if (str[i] == '%')
			{
				new_state = STATE_FORMAT;
			}
			else if (str[i] >= '1' && str[i] <= '9')
			{
				len++;
			}
			else
			{
				new_state = STATE_TEXT;
			}
			i++;
		}
	}
	return 0;
}

int print_parse_str(int state_number)
{
	if (state_number == STATE_TEXT)
		printf("text: ");
	else if (state_number == STATE_FORMAT)
		printf("format:");
	else if (state_number == STATE_WIDTH)
		printf("	width: ");
	return (0);
}

int main(void)
{
	parse_str("hello%10 smafl");
	return 0;
}
