/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** Player.cpp
*/

#include "Player.hpp"

Games::Player::Player(const std::string& name, int lives, int x, int y) : Actor(name, lives, x, y)
{
    this->score = 0;
}

bool Games::Player::getBonusPhase() const
{
    return this->bonusPhase;
}

int Games::Player::getScore() const
{
    return this->score;
}

void Games::Player::setScore(int score)
{
    this->score = score;
}

void Games::Player::restart(Arcade::Sprites_t *sprite, bool win)
{
    this->lives = 3;
    if (win == false) {
        this->score = 0;
    }
    ResetPosition(sprite);
}

bool Games::Player::checkCollisionsWithType(std::unordered_map<std::string, Arcade::Sprites_t>& sprites, std::string type)
{
    (void) sprites;
    (void) type;
    return false;
}

void Games::Player::update(std::unordered_map<std::string, Arcade::Sprites_t>& sprites, std::unordered_map<std::string, Arcade::Text_t>& texts)
{
    bool canAnimate = true;

    // Player
    if (CollisionInDir(this->currentDir, &sprites[this->name], "wall", sprites) == true) {
        if (CollisionInDir(this->lastDir, &sprites[this->name], "wall", sprites) == true) {
            canAnimate = false;
        }
    } else {
        this->lastDir = this->currentDir;
    }

    // Coin Pickup
    int playerX = sprites[this->name].x;
    int playerY = sprites[this->name].y;
    std::string coinName = "coin" + std::to_string(playerX / 32) + " " + std::to_string(playerY / 32);
    std::string bonusName = "bonus" + std::to_string(playerX / 32) + " " + std::to_string(playerY / 32);

    if (sprites.find(coinName) != sprites.end()) {
        if (CheckTilesCollision(playerX, playerY, sprites[coinName]) == true) {
            this->score += 10;
            texts["score"].text = "Score: " + std::to_string(this->score);
            sprites.erase(coinName);
        }
    }

    if (sprites.find(bonusName) != sprites.end()) {
        if (CheckTilesCollision(playerX, playerY, sprites[bonusName]) == true) {
            this->score += 20;
            texts["score"].text = "Score: " + std::to_string(this->score);
            this->bonusPhase = true;
            this->bonusTimer = clock();
            sprites.erase(bonusName);
        }
    }

    if (this->bonusPhase && static_cast<float>(clock() - this->bonusTimer) / CLOCKS_PER_SEC > 10) {
        this->bonusPhase = false;
    }

    if (canAnimate) {
        MoveInDir(this->lastDir, &sprites[this->name]);
        ChangeSpriteDirection(&sprites[this->name], this->lastDir);
        AnimateSprite(&sprites[this->name]);
    }
}
