/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** Snake.hpp
*/

#ifndef _SNAKE_H_
    #define _SNAKE_H_

    #include <unordered_map>
    #include "../GameModule.hpp"
    #include "CellSnake.hpp"

namespace Games {
    class Snake {
        public:
            Snake();
            ~Snake();
            int getScore() const;
            void setScore(int score);
            int getSize() const;
            void setSize(int size);
            bool update(std::unordered_map<std::string, Arcade::Sprites_t>& sprites, std::vector<std::pair<int, int>> emptyPos, std::unordered_map<std::string, Arcade::Text_t>& texts);
            void addCell(std::string name, int x, int y);
            void changeDirection(Games::Dir dir);
            Games::Dir getDirection();
            void updateScore(std::unordered_map<std::string, Arcade::Text_t>& texts);

        private:
            int score;
            int size;
            int speed;
            int timeSpeed;
            std::unordered_map<std::string, CellSnake *> listCell;
            bool CollisionInDir(Dir dir, Arcade::Sprites_t *sprite, std::string type, std::unordered_map<std::string, Arcade::Sprites_t> sprites);
            bool alive;
            std::pair<int, int> getPositionSnake();
            bool CheckTilesCollision(int x, int y, int x2, int y2);
            bool CheckCollision(int x, int y, std::string type, std::unordered_map<std::string, Arcade::Sprites_t> sprites);
            Arcade::SpriteRect_t createRect(int width, int height, int maxWidth, int maxHeight);
            Arcade::Color_t createColor(int r, int g, int b, int a);
            void addCellAtEnd(std::unordered_map<std::string, Arcade::Sprites_t>& sprites);
            bool changeDir;
            void checkHighScore();
    };
}

#endif // _SNAKE_H_*/