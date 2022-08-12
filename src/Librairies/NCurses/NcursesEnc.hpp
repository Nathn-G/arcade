/*
** EPITECH PROJECT, 2022
** ncurses enc
** File description:
** ncurses enc
*/

#ifndef __NCURSESENC_HPP__
#define __NCURSESENC_HPP__

    #include <iostream>
    #include <ncurses.h>

class NcursesEnc {
    public:
        NcursesEnc();
        ~NcursesEnc();
        int my_mvprintw(int i, int j, std::string str);

    protected:
    private:
};

#endif /* !__NCURSESENC_HPP__ */
