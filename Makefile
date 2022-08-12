##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

all: core games graphicals

core:
	make -C ./src/Core/

games:
	make -C ./src/Games/

graphicals:
	make -C ./src/Librairies/

clean:
	make clean -C ./src/Core/
	make clean -C ./src/Games/
	make clean -C ./src/Librairies/

fclean: clean
	make fclean -C ./src/Core/
	make fclean -C ./src/Games/
	make fclean -C ./src/Librairies/

re: fclean all
