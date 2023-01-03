NAME = chip8
SRCS = main.cpp Chip8.cpp
DIR = src
OBJS = $(addprefix $(DIR)/,$(SRCS:%.cpp=%.o))
CC = c++
RM = rm -f
FLAGS = -Wall -Wextra -Werror -Wpedantic -std=c++98 -I. -g

R = \033[38;5;1m
G = \033[38;5;2m
B = \033[38;5;4m
D = \033[38;5;255m

.cpp.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(B)Building $(NAME) program.$(D)"
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "$(G)$(NAME) program created.$(D)"

clean:
	@echo "$(R)Remove all object files.$(D)"
	$(RM) $(OBJS)

fclean: clean
	@echo "$(R)Remove $(NAME) program if present.$(D)"
	$(RM) $(NAME)

re: fclean all

run:
	valgrind --leak-check=full ./chip8 -b fishie.ch8
	
.PHONY:  all clean fclean re run
