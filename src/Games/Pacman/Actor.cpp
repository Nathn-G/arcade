/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** Actor.cpp
*/

#include "Actor.hpp"

Games::Actor::Actor(const std::string& name, int lives, int x, int y)
{
    this->name = name;
    this->currentDir = UNKNOWN;
    this->lastDir = UNKNOWN;
    this->lives = lives;
    this->defaultPosX = x;
    this->defaultPosY = y;
    this->speed = 1;
}

std::string Games::Actor::getName() const
{
    return this->name;
}

int Games::Actor::getLives() const
{
    return this->lives;
}

void Games::Actor::removeLives(int value)
{
    if (this->lives > 0) {
        this->lives -= value;
    }
}

bool Games::Actor::CheckTilesCollision(int x, int y, Arcade::Sprites_t wall) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = x;
    rightA = x + 32;
    topA = y;
    bottomA = y + 32;

    leftB = wall.x;
    rightB = wall.x + 32;
    topB = wall.y;
    bottomB = wall.y + 32;

    if (bottomA <= topB)
        return false;
    if (topA >= bottomB)
        return false;
    if (rightA <= leftB)
        return false;
    if (leftA >= rightB)
        return false;
    return true;
}

bool Games::Actor::CheckCollision(int x, int y, std::string type, std::unordered_map<std::string, Arcade::Sprites_t> sprites)
{
    for (auto sprite : sprites) {
        if (sprite.first.find(type) != std::string::npos) {
            if (CheckTilesCollision(x, y, sprite.second)) {
                return true;
            }
        }
    }
    return false;
}

bool Games::Actor::CollisionInDir(Dir dir, Arcade::Sprites_t *sprite, std::string type, std::unordered_map<std::string, Arcade::Sprites_t> sprites)
{
    if (dir == LEFT) {
        return CheckCollision(sprite->x - this->speed, sprite->y, type, sprites);
    }
    if (dir == RIGHT) {
        return CheckCollision(sprite->x + this->speed, sprite->y, type, sprites);
    }
    if (dir == UP) {
        return CheckCollision(sprite->x, sprite->y - this->speed, type, sprites);
    }
    if (dir == DOWN) {
        return CheckCollision(sprite->x, sprite->y + this->speed, type, sprites);
    }
    return false;
}

void Games::Actor::MoveInDir(Dir dir, Arcade::Sprites_t *sprite)
{
    if (dir == LEFT) {
        sprite->x -= this->speed;
    }
    if (dir == RIGHT) {
        sprite->x += this->speed;
    }
    if (dir == UP) {
        sprite->y -= this->speed;
    }
    if (dir == DOWN) {
        sprite->y += this->speed;
    }
}

void Games::Actor::ChangeSpriteDirection(Arcade::Sprites_t* sprite, Dir dir)
{
    if (dir == RIGHT) {
        sprite->rect.y = 0;
    }
    if (dir == LEFT) {
        sprite->rect.y = sprite->rect.w;
    }
    if (dir == UP) {
        sprite->rect.y = sprite->rect.w * 2;
    }
    if (dir == DOWN) {
        sprite->rect.y = sprite->rect.w * 3;
    }
}

void Games::Actor::AnimateSprite(Arcade::Sprites_t* sprite)
{
    if (static_cast<float>(clock() - this->lastUpdate) / CLOCKS_PER_SEC > 0.1) {
        this->lastUpdate = clock();
        if (sprite->rect.x >= sprite->rect.maxW) {
            sprite->rect.x = 0;
        } else {
            sprite->rect.x += sprite->rect.w;
        }
    }
}

void Games::Actor::ResetPosition(Arcade::Sprites_t* sprite)
{
    sprite->x = this->defaultPosX;
    sprite->y = this->defaultPosY;
}
