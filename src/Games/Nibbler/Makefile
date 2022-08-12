##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

CC	= g++

SRC	=	NibblerModule.cpp \
		Snake.cpp \
		CellSnake.cpp \
		../GameModule.cpp \
		../../Utils/File.cpp

OBJ	= $(SRC:.cpp=.o)

CPPFLAGS 	= -fPIC -shared -fno-gnu-unique
CPPFLAGS	+= -W -Wall -Wextra

NAME = ../../../lib/arcade_nibbler.so

all: $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CPPFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
