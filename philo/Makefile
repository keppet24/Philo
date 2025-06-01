NAME=philo
CC=cc
CFLAGS=-Wall -Werror -Wextra

SRC=    src/main.c \
		src/clean_and_destroy.c \
		src/eat.c \
		src/monitor.c \
		src/one_philo.c \
		src/parsing.c \
		src/philo_died.c \
		src/philo_init.c \
		src/printf_mutex.c \
		src/routine.c \
		src/simulation_is_not_ended.c \
		src/sleep.c \
		src/take_drop_fork.c \
		src/timetamp.c \
		src/wait_all_philo.c \
		src/is_digit.c

OBJ_DIR=obj
OBJS=$(SRC:%.c=$(OBJ_DIR)/%.o)

# Create necessary directories for .o files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

all: $(NAME)

default: all

.PHONY: all re clean fclean