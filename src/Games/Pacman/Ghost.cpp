/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** Ghost.cpp
*/

#include "Ghost.hpp"

Games::Ghost::Ghost(const std::string& name, int lives, int x, int y) : Actor(name, lives, x, y)
{
    this->name = name;
    this->lastDir = UP;
    this->exitedHome = false;
    this->startMoving = clock();
    this->hitPlayer = clock();
    this->canAnimateDir = true;
    this->bonusPhase = false;
}

std::vector<Games::Dir> Games::Ghost::GetPossibleDirs(std::unordered_map<std::string, Arcade::Sprites_t>& sprites)
{
    std::vector<Dir> possibleDirs;

    if (CollisionInDir(RIGHT, &sprites[this->name], "wall", sprites) == false && (this->lastDir != LEFT || !this->exitedHome)) {
        possibleDirs.push_back(RIGHT);
    }
    if (CollisionInDir(LEFT, &sprites[this->name], "wall", sprites) == false && (this->lastDir != RIGHT || !this->exitedHome)) {
        possibleDirs.push_back(LEFT);
    }
    if (CollisionInDir(UP, &sprites[this->name], "wall", sprites) == false && (this->lastDir != DOWN || !this->exitedHome)) {
        possibleDirs.push_back(UP);
    }
    if (CollisionInDir(DOWN, &sprites[this->name], "wall", sprites) == false && (this->lastDir != UP || !this->exitedHome)) {
        if (CollisionInDir(DOWN, &sprites[this->name], "home", sprites) == false) {
            possibleDirs.push_back(DOWN);
        }
    }
    return possibleDirs;
}

void Games::Ghost::exitHome(std::unordered_map<std::string, Arcade::Sprites_t>& sprites, std::vector<Dir> possibleDirs)
{
    if (CheckCollision(sprites[this->name].x, sprites[this->name].y, "home", sprites) == true) {
        this->exitedHome = true;
    }
    if (std::find(possibleDirs.begin(), possibleDirs.end(), UP) != possibleDirs.end()) {
        this->lastDir = UP;
    } else if (std::find(possibleDirs.begin(), possibleDirs.end(), this->lastDir) == possibleDirs.end()) {
    this->lastDir = possibleDirs[std::rand() % possibleDirs.size()];
    }
    MoveInDir(this->lastDir, &sprites[this->name]);
}

void Games::Ghost::restart(Arcade::Sprites_t *sprite, bool win)
{
    (void) win;
    this->lives = 1;
    this->startMoving = clock();
    ResetPosition(sprite);
    this->canAnimateDir = false;
    sprite->rect.y = 160;
}

bool Games::Ghost::checkCollisionsWithType(std::unordered_map<std::string, Arcade::Sprites_t>& sprites, std::string type)
{
    if (static_cast<float>(clock() - this->hitPlayer) / CLOCKS_PER_SEC >= 2) {
        if (CollisionInDir(this->lastDir, &sprites[this->name], type, sprites)) {
            this->hitPlayer = clock();
            return true;
        }
    }
    return false;
}

void Games::Ghost::ToggleGhostAppearance(Arcade::Sprites_t *sprite, bool bonusPhase)
{
    this->bonusPhase = bonusPhase;
    if (sprite->rect.y == 160) {
        return;
    }
    if (bonusPhase == true) {
        sprite->rect.y = 128;
    }
}

void Games::Ghost::update(std::unordered_map<std::string, Arcade::Sprites_t>& sprites, std::unordered_map<std::string, Arcade::Text_t>& texts)
{
    std::vector<Dir> possibleDirs = GetPossibleDirs(sprites);

    (void) texts;
    if (static_cast<float>(clock() - this->startMoving) / CLOCKS_PER_SEC >= 10) {
        if (this->bonusPhase == false && this->canAnimateDir == false) {
            this->canAnimateDir = true;
        }
        if (this->exitedHome == false) {
            exitHome(sprites, possibleDirs);
        } else if (possibleDirs.size() != 0) {
            this->lastDir = possibleDirs[std::rand() % possibleDirs.size()];
            MoveInDir(this->lastDir, &sprites[this->name]);
        } else {
            Dir randDir = (Dir)(std::rand() % 4);
            if (CollisionInDir(randDir, &sprites[this->name], "wall", sprites) == false) {
                this->lastDir = randDir;
            }
        }
    }

    if (sprites[this->name].x == 0) {
        sprites[this->name].y = 288;
    }

    if (this->bonusPhase == false && this->canAnimateDir == true) {
        ChangeSpriteDirection(&sprites[this->name], this->lastDir);
    }
    AnimateSprite(&sprites[this->name]);
}
