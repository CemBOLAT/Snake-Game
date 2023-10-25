CXX		  := g++
CXX_FLAGS := -Wall -Wextra -Wno-unused-parameter -std=c++11
SRC :=  ./classes/Game.cpp \
		./classes/Map.cpp \
		./classes/Snake.cpp \
		./classes/Texture.cpp \
		./classes/main.cpp \
		./classes/GameOver.cpp \
		./classes/MainMenu.cpp \
		./classes/LeaderBoard.cpp

INCLUDE	:= include
LIB		:= lib

INCLUDES := -I$(INCLUDE) -I/opt/homebrew/Cellar/sfml/2.6.0/include

LIBRARIES	:= -lsfml-graphics -lsfml-window -lsfml-system -L/opt/homebrew/Cellar/sfml/2.6.0/lib

NAME	:= main

all: $(NAME)

$(NAME): $(SRC)
	$(CXX) $(CXX_FLAGS) $(INCLUDES) $^ -o $@ $(LIBRARIES)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
