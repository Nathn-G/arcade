##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

CC	= g++

SRC	=	NCursesModule.cpp	\
		../../Utils/File.cpp \
		NcursesEnc.cpp

OBJ	= $(SRC:.cpp=.o)

CPPFLAGS 	= -fPIC -shared -fno-gnu-unique
CPPFLAGS	+= -W -Wall -Wextra

NCURSEFLAGS = -lncurses

NAME = ../../../lib/arcade_ncurses.so

all: $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CPPFLAGS) $(NCURSEFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
