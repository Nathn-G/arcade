/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** ChasingGhost.hpp
*/

#ifndef _CHASING_GHOST_H_
    #define _CHASING_GHOST_H_

    #include "Ghost.hpp"
    #include "Coord.hpp"
    #include <algorithm>
    #include <climits>

namespace Games {
    class ChasingGhost: public Ghost {
        public:
            ChasingGhost(const std::string& name, int lives, int x, int y);
            void update(std::unordered_map<std::string, Arcade::Sprites_t>& sprites, std::unordered_map<std::string, Arcade::Text_t>& texts);

        private:
            bool ChaseInDirection(std::vector<Dir> possibleDirs, Dir dir);
            bool FindClosestDirection(std::vector<Dir> possibleDirs, std::unordered_map<std::string, Arcade::Sprites_t>& sprites);
    };
}

#endif // _CHASING_GHOST_H_*/