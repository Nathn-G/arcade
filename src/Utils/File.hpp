/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** File.hpp
*/

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class File {
    public:
        std::vector<std::string> readFile(std::string filename);
};