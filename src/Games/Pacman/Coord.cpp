/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** Coord.cpp
*/

#include "Coord.hpp"

Games::Coord::Coord(int x, int y, int g, int h)
{
    this->x = x;
    this->y = y;
    this->g = g;
    this->h = h;
    this->f = g + h;
}

Games::Coord::Coord()
{
    this->x = 0;
    this->y = 0;
    this->g = 0;
    this->h = 0;
    this->f = 0;
}

void Games::Coord::init(int x, int y, int g, int h)
{
    this->x = x;
    this->y = y;
    this->g = g;
    this->h = h;
    this->f = g + h;
}

int Games::Coord::calculateDistance(int x, int y, std::shared_ptr<Games::Coord> goal)
{
    int dist1 = x - goal.get()->x;
    int dist2 = y - goal.get()->y;

    dist1 = dist1 < 0 ? dist1 * -1 : dist1;
    dist2 = dist2 < 0 ? dist2 * -1 : dist2;
    return dist1 + dist2;
}

int Games::Coord::isCoordInList(std::vector<std::shared_ptr<Games::Coord>> coords)
{
    for (size_t i = 0; i < coords.size(); i++) {
        if (this->x == coords[i].get()->x && this->y == coords[i].get()->y) {
            return i;
        }
    }
    return -1;
}
