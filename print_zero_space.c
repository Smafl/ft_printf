
#include "ft_printf.h"

static void print_zero(int width)
{
	while (width != 0)
		{
			write(1, "0", 1);
			width--;
		}
}

static void print_space(int width)
{
	while (width != 0)
		{
			write(1, " ", 1);
			width--;
		}
}
