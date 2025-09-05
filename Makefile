# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

# Directories
SRC_DIR = src
INCLUDE_DIR = includes

# Files
SRC_FILES = $(SRC_DIR)/main.c \
		$(SRC_DIR)/philo_actions.c \
		$(SRC_DIR)/philo_fork.c \
		$(SRC_DIR)/philo_init.c \
		$(SRC_DIR)/philo_monitor.c \
		$(SRC_DIR)/philo_output.c \
		$(SRC_DIR)/philo_parse.c \
		$(SRC_DIR)/philo_routine.c \
		$(SRC_DIR)/philo_stop.c \
		$(SRC_DIR)/philo_time.c \

OBJ_FILES = $(SRC_FILES:.c=.o)

# Executable
NAME = philo

# Rules
all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -I $(INCLUDE_DIR) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
