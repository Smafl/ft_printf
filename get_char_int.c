
#include "ft_printf.h"

char	get_hex_digit(int digit, int flag)
{
	char c;

	if (digit < 10)
	{
		c = '0' + digit;
	}
	else
	{
		if (flag & FLAG_UPPERCASE)
			c = 'A' + digit - 10;
		else
			c = 'a' + digit - 10;
	}
	return (c);
}

char	get_sign(int nbr, int flag, int *has_sign)
{
	if (nbr >= 0)
	{	
		if ((flag & FLAG_SPACE) && !(flag & FLAG_PLUS))
		{
			*has_sign = 1;
			return (' ');
		}
		else if (flag & FLAG_PLUS)
		{
			*has_sign = 1;
			return ('+');
		}
	}
	else if (nbr < 0)
	{
		*has_sign = 1;
		return ('-');
	}
	*has_sign = 0;
	return (0);
}

int		get_zero_space_len(int flag, int len, int width, int precision)
{
	if ((flag & FLAG_ZERO) && (flag & HAS_WIDTH) && !(flag & FLAG_MINUS))
	{
		if (width > len)
			return (width - len);
	}
	else if (precision >= width)
	{
		if (precision > len)
			return (precision - len);
	}
	else if (precision < width)
	{
		if (width > len)
			return (width - len);
	}
	return (0);
}
