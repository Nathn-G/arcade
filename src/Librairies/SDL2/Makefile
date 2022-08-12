##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

CC	= g++

SRC	=	SDL2Module.cpp

OBJ	= $(SRC:.cpp=.o)

CPPFLAGS 	= -fPIC -shared -lSDL2 -lSDL2_ttf -lSDL2_image -fno-gnu-unique
CPPFLAGS	+= -W -Wall -Wextra

NAME = ../../../lib/arcade_sdl2.so

all: $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CPPFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
