/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** ChasingGhost.cpp
*/

#include "ChasingGhost.hpp"

Games::ChasingGhost::ChasingGhost(const std::string& name, int lives, int x, int y) : Ghost(name, lives, x, y) {}

bool Games::ChasingGhost::ChaseInDirection(std::vector<Dir> possibleDirs, Dir dir)
{
    if (this->bonusPhase == true) {
        if (dir == RIGHT) {
            dir = LEFT;
        } else if (dir == LEFT) {
            dir = RIGHT;
        } else if (dir == UP) {
            dir = DOWN;
        } else {
            dir = UP;
        }
    }
    if (std::find(possibleDirs.begin(), possibleDirs.end(), dir) != possibleDirs.end()) {
        this->lastDir = dir;
        return true;
    }
    return false;
}

bool Games::ChasingGhost::FindClosestDirection(std::vector<Dir> possibleDirs, std::unordered_map<std::string, Arcade::Sprites_t>& sprites)
{
    if (sprites["player"].x == sprites[this->name].x) {
        if (sprites[this->name].y < sprites["player"].y) {
            return ChaseInDirection(possibleDirs, DOWN);
        }
        if (sprites[this->name].y > sprites["player"].y) {
            return ChaseInDirection(possibleDirs, UP);
        }
    }
    if (sprites["player"].y == sprites[this->name].y) {
        if (sprites[this->name].x < sprites["player"].x) {
            return ChaseInDirection(possibleDirs, RIGHT);
        }
        if (sprites[this->name].x > sprites["player"].x) {
            return ChaseInDirection(possibleDirs, LEFT);
        }
    }
    return false;
}

void Games::ChasingGhost::update(std::unordered_map<std::string, Arcade::Sprites_t>& sprites, std::unordered_map<std::string, Arcade::Text_t>& texts)
{
    std::vector<Dir> possibleDirs = GetPossibleDirs(sprites);

    if ((float)(clock() - this->startMoving) / CLOCKS_PER_SEC >= 10) {
        if (this->bonusPhase == false && this->canAnimateDir == false) {
            this->canAnimateDir = true;
        }
        if (this->exitedHome == false) {
            exitHome(sprites, possibleDirs);
        } else if (possibleDirs.size() != 0) {
            if (!this->FindClosestDirection(possibleDirs, sprites)) {
                this->lastDir = possibleDirs[std::rand() % possibleDirs.size()];
            }
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
