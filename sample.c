
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
	int len_text = 0;

	enum e_State state = STATE_TEXT;
	enum e_State new_state = state;
	while (str[i])
	{
// text
		while (state == STATE_TEXT)
		{
			if (str[i] == '%')
			{
				new_state = STATE_FORMAT;
			}
			else
			{
				len_text++;
			}
			i++;
		}
		if (state != new_state)
		{
			print_parse_str(state);
			while (len_text != 0)
			{
				
				len_text--;
			}
			printf("\n");
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

// width
		if (state == STATE_WIDTH)
		{
			if (str[i] == '%')
			{
				new_state = STATE_FORMAT;
			}
			else
			{
				new_state = STATE_TEXT;
			}
			i++;
			continue ;
		}
	}
	return 0;
}

int print_parse_str(int state_number)
{
	if (state_number == STATE_TEXT)
		printf("text: ");
	else if (state_number == STATE_FORMAT)
		printf("format:\n");
	else if (state_number == STATE_WIDTH)
		printf("	width: ");
	return (0);
}

int main(void)
{
	parse_str("hello%10 smafl");
	return 0;
}
