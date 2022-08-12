/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** RandomGhost.cpp
*/

#include "RandomGhost.hpp"

Games::RandomGhost::RandomGhost(const std::string& name, int lives, int x, int y) : Ghost(name, lives, x, y) {}

void Games::RandomGhost::update(std::unordered_map<std::string, Arcade::Sprites_t>& sprites, std::unordered_map<std::string, Arcade::Text_t>& texts)
{
    std::vector<Dir> possibleDirs = GetPossibleDirs(sprites);

    if ((float)(clock() - this->startMoving) / CLOCKS_PER_SEC >= 10) {
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
