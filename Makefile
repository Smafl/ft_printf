
NAME = libftprintf.a
SRC = ft_printf.c\
		get.c\
		is_type_flag.c\
		libft.c\
		print_c_str.c\
		print_dec_hex_p.c\
		print_zero_space.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME)

re: fclean all

$(NAME): $(OBJ)
	ar -rcs $(NAME)

# all - compile starter (execute other rules)

# CFLAGS is used automatically

# ar -rcs adds files in archve and replace them
# if they have already been there
# (if the library already exists)
# c creates the library if there is no one
# s creates a sorted index
# that's why we can call ar -rcs again and add there bonus obj files