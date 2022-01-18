CC=clang++
RM=rm -rf
NAME=computor

SRC_DIR=src
INC_DIR=include
SRC=$(wildcard ./$(SRC_DIR)/*.cpp)
SRC+=$(wildcard ./$(SRC_DIR)/classes/*.cpp)
INC=$(wildcard ./$(INC_DIR)/*.hpp)
OBJ:=$(SRC:.cpp=.o)

FSANITIZE=-fsanitize=address
FLAGS=-Wall -Wextra -Werror -g3 -I$(INC_DIR)

%.o:%.cpp
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(OBJ): $(INC)

$(NAME): $(OBJ) $(INC)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

sanitize:
	$(CC) $(FLAGS) $(FSANITIZE) $(OBJ) -o $(NAME)

re: fclean all

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

.PHONY: all sanitize clean fclean re