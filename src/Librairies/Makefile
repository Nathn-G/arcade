##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

all: ncurses sdl2 sfml

ncurses:
	make -C ./NCurses/

sdl2:
	make -C ./SDL2/

sfml:
	make -C ./SFML/

clean:
	make clean -C ./NCurses/
	make clean -C ./SDL2/
	make clean -C ./SFML/

fclean: clean
	make fclean -C ./NCurses/
	make fclean -C ./SDL2/
	make fclean -C ./SFML/

re: fclean all
