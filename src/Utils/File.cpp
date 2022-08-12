/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** File.cpp
*/

#include "File.hpp"

std::vector<std::string> File::readFile(std::string filename)
{
    std::vector<std::string> content;
    std::string line;
    std::ifstream file(filename);

    if (file.is_open()) {
        while (std::getline(file, line)) {
            content.push_back(line);
        }
    }
    return content;
}
