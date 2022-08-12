/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** Actor.hpp
*/

#ifndef _ACTOR_H_
    #define _ACTOR_H_

    #include "../GameModule.hpp"

namespace Games {
    class Actor {
        public:
            Actor(const std::string& name, int lives, int x, int y);
            virtual ~Actor() {};
            virtual bool checkCollisionsWithType(std::unordered_map<std::string, Arcade::Sprites_t>& sprites, std::string type) = 0;
            virtual void update(std::unordered_map<std::string, Arcade::Sprites_t>& sprites, std::unordered_map<std::string, Arcade::Text_t>& texts) = 0;
            Dir currentDir;
            Dir lastDir;
            std::string getName() const;
            int getLives() const;
            void removeLives(int value);

        protected:
            virtual void restart(Arcade::Sprites_t *sprite, bool win) = 0;
            void ResetPosition(Arcade::Sprites_t* sprite);
            void AnimateSprite(Arcade::Sprites_t* sprite);
            void ChangeSpriteDirection(Arcade::Sprites_t* sprite, Dir dir);
            bool CollisionInDir(Dir dir, Arcade::Sprites_t *sprite, std::string type, std::unordered_map<std::string, Arcade::Sprites_t> sprites);
            void MoveInDir(Dir dir, Arcade::Sprites_t *sprite);
            bool CheckCollision(int x, int y, std::string type, std::unordered_map<std::string, Arcade::Sprites_t> sprites);
            bool CheckTilesCollision(int x, int y, Arcade::Sprites_t wall);
            clock_t lastUpdate;
            std::string name;
            int lives;
            int defaultPosX;
            int defaultPosY;
            int speed;
    };
}

#endif /*_ACTOR_H_*/