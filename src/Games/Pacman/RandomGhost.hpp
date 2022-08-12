/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** RandomGhost.hpp
*/

#ifndef _RANDOM_GHOST_H_
    #define _RANDOM_GHOST_H_

    #include "Ghost.hpp"
    #include <algorithm>

namespace Games {
    class RandomGhost: public Ghost {
        public:
            RandomGhost(const std::string& name, int lives, int x, int y);
            void update(std::unordered_map<std::string, Arcade::Sprites_t>& sprites, std::unordered_map<std::string, Arcade::Text_t>& texts);
    };
}

#endif // _RANDOM_GHOST_H_*/