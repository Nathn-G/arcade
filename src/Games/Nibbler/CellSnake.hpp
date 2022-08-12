/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** class CellSnake
*/

#ifndef __CELL_SNAKE_HPP__
    #define __CELL_SNAKE_HPP__

    #include <vector>
    #include "../GameModule.hpp"

typedef struct cellShift_s {
    int x;
    int y;
    Games::Dir dir;
} cellShift_t;

class CellSnake {
    public:
        CellSnake(int x, int y);
        ~CellSnake();
        std::pair<int, int> getPosition();
        void updatePosition();
        void changeDirection(Games::Dir dir, int x, int y);
        Games::Dir getDirection();
        void updateDir(Arcade::Sprites_t &sprite, int index, CellSnake *before);
        void ChangeSpriteDirection(Arcade::Sprites_t &sprite, Games::Dir dir, int index, CellSnake *before);
        std::vector<cellShift_t> getHistoryShift();
        int getIndexShift();
        void loadHistoryShift(std::vector<cellShift_t> history, int currentShift, int x, int y, Games::Dir currentDir);
        void setSpriteDirection(Arcade::Sprites_t &sprite, Games::Dir dir, Games::Dir direction);

    private:
        int _x;
        int _y;
        Games::Dir _dir;
        Games::Dir _oldDir;
        std::vector<cellShift_t> _historyShift;
        int _currentShift;
        int _newCell;
        Games::Dir _nextDir;
};

#endif /* !__CELL_SNAKE_HPP__ */
