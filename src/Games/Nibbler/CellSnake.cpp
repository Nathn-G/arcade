/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** methods of class CellSnake
*/

#include "CellSnake.hpp"

CellSnake::CellSnake(int x, int y)
{
    this->_x = x;
    this->_y = y;
    this->_dir = Games::Dir::UNKNOWN;
    this->_oldDir = Games::Dir::UNKNOWN;
    this->_currentShift = -1;
    this->_newCell = 0;
    this->_nextDir = Games::Dir::UNKNOWN;
}

CellSnake::~CellSnake()
{
}

void CellSnake::updateDir(Arcade::Sprites_t &sprite, int index, CellSnake *before)
{
    if (this->_currentShift != -1) {
        if (this->_historyShift[this->_currentShift].x == this->_x &&
        this->_historyShift[this->_currentShift].y == this->_y) {
            this->_oldDir = this->_dir;
            this->_dir = this->_historyShift[this->_currentShift].dir;
            this->_currentShift += 1;
        }
        ChangeSpriteDirection(sprite, _dir, index, before);
    }
}

void CellSnake::ChangeSpriteDirection(Arcade::Sprites_t &sprite, Games::Dir dir, int index, CellSnake *before)
{
    if (index == 0) {
        if (dir == Games::Dir::UP) {
            sprite.rect.x = 0;
        }
        if (dir == Games::Dir::RIGHT) {
            sprite.rect.x = sprite.rect.w;
        }
        if (dir == Games::Dir::DOWN) {
            sprite.rect.x = sprite.rect.w * 2;
        }
        if (dir == Games::Dir::LEFT) {
            sprite.rect.x = sprite.rect.w * 3;
        }
    } else {
        Games::Dir direction = before->getDirection();
        setSpriteDirection(sprite, dir, direction);
    }
}

void CellSnake::setSpriteDirection(Arcade::Sprites_t &sprite, Games::Dir dir, Games::Dir direction)
{
    if ((dir == Games::Dir::UP || dir == Games::Dir::DOWN) && (direction == Games::Dir::DOWN || direction == Games::Dir::UP)) {
        sprite.rect.x = 0;
        sprite.rect.y = 0;
    } else if ((dir == Games::Dir::RIGHT || dir == Games::Dir::LEFT) && (direction == Games::Dir::RIGHT || direction == Games::Dir::LEFT)) {
        sprite.rect.x = sprite.rect.w;
        sprite.rect.y = 0;
    } else if ((dir == Games::Dir::UP && direction == Games::Dir::LEFT) ||
    (dir == Games::Dir::RIGHT && direction == Games::Dir::DOWN)) {
        sprite.rect.x = sprite.rect.w;
        sprite.rect.y = sprite.rect.h;
    } else if ((dir == Games::Dir::UP && direction == Games::Dir::RIGHT) ||
    (dir == Games::Dir::LEFT && direction == Games::Dir::DOWN)) {
        sprite.rect.x = 0;
        sprite.rect.y = sprite.rect.h * 2;
    } else if ((dir == Games::Dir::DOWN && direction == Games::Dir::LEFT) ||
    (dir == Games::Dir::RIGHT && direction == Games::Dir::UP)) {
        sprite.rect.x = sprite.rect.w;
        sprite.rect.y = sprite.rect.h * 2;
    } else if ((dir == Games::Dir::DOWN && direction == Games::Dir::RIGHT) ||
    (dir == Games::Dir::LEFT && direction == Games::Dir::UP)) {
        sprite.rect.x = 0;
        sprite.rect.y = sprite.rect.h;
    }
}

void CellSnake::updatePosition()
{
    if (this->_dir == Games::Dir::DOWN) {
        this->_y += 32;
    } else if (this->_dir == Games::Dir::LEFT) {
        this->_x -= 32;
    } else if (this->_dir == Games::Dir::RIGHT) {
        this->_x += 32;
    } else if (this->_dir == Games::Dir::UP) {
        this->_y -= 32;
    }
}

std::pair<int, int> CellSnake::getPosition()
{
    return std::pair<int, int>(this->_x, this->_y);
}

void CellSnake::changeDirection(Games::Dir dir, int x, int y)
{
    if (this->_dir == Games::Dir::UNKNOWN) {
        this->_dir = dir;
    } else {
        if (this->_currentShift == -1) {
            this->_currentShift += 1;
        }
        
        this->_historyShift.push_back({x, y, dir});
    }
}

Games::Dir CellSnake::getDirection()
{
    return this->_dir;
}

std::vector<cellShift_t> CellSnake::getHistoryShift()
{
    return this->_historyShift;
}

int CellSnake::getIndexShift()
{
    return this->_currentShift;
}

void CellSnake::loadHistoryShift(std::vector<cellShift_t> history, int currentShift, int x, int y, Games::Dir currentDir)
{
    this->_currentShift = 0;
    this->_historyShift.push_back({x, y, currentDir});
    for (long unsigned int i = currentShift; i < history.size(); i++) {
        this->_historyShift.push_back(history[i]);
    }
}
