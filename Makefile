SRC := \
	src/forks.c		\
	src/main.c		\
	src/monitor.c	\
	src/philo.c		\
	src/time.c		\

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