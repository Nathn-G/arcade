##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

CC	= g++

SRC	= 	SFMLModule.cpp

OBJ	= $(SRC:.cpp=.o)

CPPFLAGS 	= -fPIC -shared -fno-gnu-unique
CPPFLAGS	+= -W -Wall -Wextra

SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

NAME = ../../../lib/arcade_sfml.so

all: $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CPPFLAGS) $(SFMLFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
