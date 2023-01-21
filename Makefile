CC = cc
NAME = libftprintf.a
SRC = ft_printf.c\
get_size.c\
is_type_flag.c\
libft_ft_printf.c\
pars_utils.c\
parsing.c\
print_c_str.c\
print_diuxp.c\
print_zero_space.c\
states_proceed_1.c\
states_proceed_2.c\
utils.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: re

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

.PHONY: all clean fclean re bonus

# all - compile starter (execute other rules)

# CFLAGS is used automatically

# ar -rcs adds files in archve and replace them
# if they have already been there
# (if the library already exists)
# c creates the library if there is no one
# s creates a sorted index
# that's why we can call ar -rcs again and add there bonus obj files
