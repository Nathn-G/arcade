/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** Coord.hpp
*/

#ifndef _COORD_H_
    #define _COORD_H_

    #include <vector>
    #include <memory>

namespace Games {
    class Coord {
        public:
            Coord();
            Coord(int x, int y, int g, int h);
            int isCoordInList(std::vector<std::shared_ptr<Games::Coord>> coords);
            int calculateDistance(int x, int y, std::shared_ptr<Games::Coord> goal);
            void init(int x, int y, int g, int h);
            int x;
            int y;
            int g;
            int h;
            int f;
    };
}

#endif // _COORD_H_*/