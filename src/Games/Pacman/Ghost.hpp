/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** Ghost.hpp
*/

#ifndef _GHOST_H_
    #define _GHOST_H_

    #include "Actor.hpp"
    #include <algorithm>

namespace Games {
    class Ghost: public Actor {
        public:
            Ghost(const std::string& name, int lives, int x, int y);
            bool checkCollisionsWithType(std::unordered_map<std::string, Arcade::Sprites_t>& sprites, std::string type);
            void restart(Arcade::Sprites_t *sprite, bool win);
            void update(std::unordered_map<std::string, Arcade::Sprites_t>& sprites, std::unordered_map<std::string, Arcade::Text_t>& texts);
            void ToggleGhostAppearance(Arcade::Sprites_t *sprite, bool bonusPhase);

        protected:
            void exitHome(std::unordered_map<std::string, Arcade::Sprites_t>& sprites, std::vector<Dir> possibleDirs);
            std::vector<Dir> GetPossibleDirs(std::unordered_map<std::string, Arcade::Sprites_t>& sprites);
            bool checkCollisions(std::unordered_map<std::string, Arcade::Sprites_t>& sprites);
            std::string name;
            bool exitedHome;
            clock_t startMoving;
            clock_t hitPlayer;
            bool bonusPhase;
            bool canAnimateDir;
    };
}

#endif // _GHOST_H_*/