NAME = philo
CC = cc
SRC = \
	./init/init.c \
	./parsing/parsing.c \
	./src/main.c \
	./src/dinner.c \
	./utils/getters_setters.c \
	./utils/monitoring.c \
	./utils/safe_functions.c \
	./utils/sync_utils.c \
	./utils/utils.c \
	./utils/write.c \

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -g -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

all: $(NAME)

dev :
	make fclean
	git add .; git commit -m "auto/dev"; git push
	make all

PHONY: all clean fclean re dev