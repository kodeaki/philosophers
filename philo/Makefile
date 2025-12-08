SRC := \
	forks_and_eat.c	\
	get.c			\
	main.c			\
	monitor.c		\
	philo.c			\
	time.c			\

NAME 	:= philo
HEADER	:= src/philo.h
CFLAGS 	:= -Wall -Wextra -Werror -pthread
OBJS 	:= $(SRC:%.c=%.o)

%.o: %.c $(HEADER)
	cc -c $< -o $@ $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJS)
	cc $^ -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJS)
