
#include "libftprintf.h"

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
