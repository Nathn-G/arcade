##
##EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

CC	=	g++

SRC =	main.cpp	\
		Core.cpp	\
		Error.cpp	\
		DLEnc.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	../../arcade

CPPFLAGS = -fno-gnu-unique
CPPFLAGS	+= -W -Wall -Wextra

all: $(OBJ)
	$(CC) -o $(NAME) $(SRC) -ldl

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
