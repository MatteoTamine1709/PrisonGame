##
## EPITECH PROJECT, 2019
## PrisonGame
## File description:
## Makefile
##

SRC =   *.cpp

CFLAGS = 

LIB = -lsfml-graphics -lsfml-system -lm -lsfml-window -lsfml-audio

OBJ =   $(SRC:.cpp=.o)

NAME    =   PrisonGame

all:    $(NAME)

$(NAME):
	g++ -o $(NAME) $(SRC) $(LIB)

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf $(OBJ)
	rm -rf vg*

re: fclean all

debug: CFLAGS += -g

debug: fclean all

.PHONY: all clean fclean re debug
