##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

all: pacman nibbler	menu

menu:
	make -C ./Menu/

pacman:
	make -C ./Pacman/

nibbler:
	make -C ./Nibbler/

clean:
	make clean -C ./Menu/
	make clean -C ./Pacman/
	make clean -C ./Nibbler/

fclean: clean
	make fclean -C ./Menu/
	make fclean -C ./Pacman/
	make fclean -C ./Nibbler/

re: fclean all
