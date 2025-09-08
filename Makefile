






NAME			:=	philo

COMPILER	:=	cc
CFLAGS		:=	-Wall -Wextra -Werror



VPATH			:=	src

SRC				:=	main.c


all:	$(NAME) $()




clean:


fclean:


re: fclean all


.PHONY: all clean fclean re
