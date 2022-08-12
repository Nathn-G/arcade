##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

CC	= g++

SRC	=	Actor.cpp	\
		Player.cpp	\
		Ghost.cpp	\
		RandomGhost.cpp	\
		ChasingGhost.cpp	\
		Coord.cpp	\
		PacmanModule.cpp	\
		../GameModule.cpp	\
		../../Utils/File.cpp

OBJ	= $(SRC:.cpp=.o)

CPPFLAGS 	= -fPIC -shared -fno-gnu-unique
CPPFLAGS	+= -W -Wall -Wextra -Wl,--no-undefined

NAME = ../../../lib/arcade_pacman.so

all: $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CPPFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
