/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** Player.hpp
*/

#ifndef _PLAYER_H_
    #define _PLAYER_H_

    #include "Actor.hpp"

namespace Games {
    class Player: public Actor {
        public:
            Player(const std::string& name, int lives, int x, int y);
            bool getBonusPhase() const;
            int getScore() const;
            void setScore(int score);
            bool checkCollisionsWithType(std::unordered_map<std::string, Arcade::Sprites_t>& sprites, std::string type);
            void restart(Arcade::Sprites_t *sprite, bool win);
            void update(std::unordered_map<std::string, Arcade::Sprites_t>& sprites, std::unordered_map<std::string, Arcade::Text_t>& texts);

        private:
            bool checkGhostCollisions(std::unordered_map<std::string, Arcade::Sprites_t>& sprites);
            int score;
            bool bonusPhase;
            clock_t bonusTimer;
    };
}

#endif // _PLAYER_H_*/