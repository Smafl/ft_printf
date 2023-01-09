
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

unsigned short	get_sign(long nbr, int flag, int base, int *sign_len)
{
	if (base == 10)
	{
		if (nbr >= 0)
		{	
			if ((flag & FLAG_SPACE) && !(flag & FLAG_PLUS))
			{
				*sign_len = 1;
				return (' ');
			}
			else if (flag & FLAG_PLUS)
			{
				*sign_len = 1;
				return ('+');
			}
		}
		else if (nbr < 0)
		{
			*sign_len = 1;
			return ('-');
		}
	}
	else if (base == 16)
	{
		if (nbr == 0 && !(flag & FLAG_POINTER))
			;
		else if (flag & FLAG_POINTER)
		{
			*sign_len = 2;
			return ((unsigned short)'x' << 8 | '0');
		}
		else if (flag & FLAG_HASH)
		{
			*sign_len = 2;
			if (flag & FLAG_UPPERCASE)
				return ((unsigned short)'X' << 8 | '0');
			else
				return ((unsigned short)'x' << 8 | '0');
		}
	}
	*sign_len = 0;
	return (0);
}

int	get_max(int precision, int len)
{
	if (precision <= len)
		return (len);
	return (precision);
}
