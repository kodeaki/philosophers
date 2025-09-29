

NAME			:=	philo

LIBFT			:=	libft/libft.a

COMPILER		:=	cc
CFLAGS			:=	-Wall -Wextra -Werror

SRC_DIR			:= src/
OBJ_DIR			:= obj/

VPATH			:= $(SRC_DIR)

SRCS			:=	main.c\
					ft_args_valid.c

OBJS			:= $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all:	$(NAME)

$(NAME):	$(OBJS)
	$(COMPILER) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean:
	@rm -f philo

re: fclean all

.SECONDARY: $(OBJS)
.PHONY: all clean fclean re
