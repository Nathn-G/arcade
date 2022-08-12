/*
** EPITECH PROJECT, 2022
** ncurses enc
** File description:
** ncurses enc
*/

#include "NcursesEnc.hpp"

NcursesEnc::NcursesEnc()
{
}

NcursesEnc::~NcursesEnc()
{
}

int NcursesEnc::my_mvprintw(int i, int j, std::string str)
{
    return mvprintw(i, j, str.c_str());
}