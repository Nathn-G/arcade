/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** Player.cpp
*/

#include "Snake.hpp"
#include <fstream>
#include <sstream>

Games::Snake::Snake()
{
    this->score = 0;
    this->alive = true;
    this->timeSpeed = 30;
    this->speed = 0;
    this->changeDir = false;
}

int Games::Snake::getScore() const
{
    return this->score;
}

void Games::Snake::setScore(int score)
{
    this->score = score;
}

int Games::Snake::getSize() const
{
    return this->size;
}

void Games::Snake::setSize(int s)
{
    this->size = s;
}

void Games::Snake::addCell(std::string name, int x, int y)
{
    CellSnake *cell = new CellSnake(x, y);

    this->listCell[name] = cell;
}

bool Games::Snake::CheckTilesCollision(int x, int y, int x2, int y2) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = x;
    rightA = x + 32;
    topA = y;
    bottomA = y + 32;

    leftB = x2;
    rightB = x2 + 32;
    topB = y2;
    bottomB = y2 + 32;

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

bool Games::Snake::CheckCollision(int x, int y, std::string type, std::unordered_map<std::string, Arcade::Sprites_t> sprites)
{
    bool first = true;

    if (type.compare("snakeNotFirstEnd") == 0) {
        first = false;
        type = "snake";
    }
    for (auto sprite : sprites) {
        if (sprite.first.find(type) != std::string::npos) {
            if (!first && (sprite.first.compare("snake-0") == 0 ||
            sprite.first.compare("snake-" + std::to_string(this->size - 1)) == 0)) {
                continue;
            }
            if (CheckTilesCollision(x, y, sprite.second.x, sprite.second.y)) {
                return true;
            }
        }
    }
    return false;
}

bool Games::Snake::CollisionInDir(Dir dir, Arcade::Sprites_t *sprite, std::string type, std::unordered_map<std::string, Arcade::Sprites_t> sprites)
{
    if (dir == LEFT) {
        return CheckCollision(sprite->x - 1, sprite->y, type, sprites);
    }
    if (dir == RIGHT) {
        return CheckCollision(sprite->x + 1, sprite->y, type, sprites);
    }
    if (dir == UP) {
        return CheckCollision(sprite->x, sprite->y - 1, type, sprites);
    }
    if (dir == DOWN) {
        return CheckCollision(sprite->x, sprite->y + 1, type, sprites);
    }
    return false;
}

bool Games::Snake::update(std::unordered_map<std::string, Arcade::Sprites_t>& sprites, std::vector<std::pair<int, int>> emptyPos, std::unordered_map<std::string, Arcade::Text_t>& texts)
{
    std::string name = "snake-";
    std::pair<int, int> pos = getPositionSnake();

    if (this->alive == false) {
        this->checkHighScore();
        return false;
    }
    if (this->speed == this->timeSpeed) {
        changeDir = false;
        for (int i = 0; i < this->size; i++) {
            std::string nameCell = name + std::to_string(i);
            std::string before = nameCell;
            if (i != 0) {
                before = name + std::to_string(i - 1);
            }
            this->listCell[nameCell]->updateDir(sprites[nameCell], i, this->listCell[before]);
        }
        this->speed = 0;
        if (this->alive == true && CollisionInDir(this->listCell["snake-0"]->getDirection(), &sprites["snake-0"], "wall", sprites) || 
        this->alive == true && CollisionInDir(this->listCell["snake-0"]->getDirection(), &sprites["snake-0"], "snakeNotFirstEnd", sprites)) {
            this->alive = false;
        } else if (this->alive == true) {
            for (int i = 0; i < this->size; i++) {
                std::string nameCell = name  + std::to_string(i);
                this->listCell[nameCell]->updatePosition();
                auto pos = this->listCell[nameCell]->getPosition();
                sprites[nameCell].x = pos.first;
                sprites[nameCell].y = pos.second;
            }
        }
        pos = getPositionSnake();
        if (this->alive && CheckCollision(pos.first, pos.second, "apple", sprites)) {
            this->score += 10;
            updateScore(texts);
            srand(time(NULL));
            pos = emptyPos[std::rand() % emptyPos.size()];
            while (CheckCollision(pos.first, pos.second, "snake", sprites) != false) {
                srand(time(NULL));
                pos = emptyPos[std::rand() % emptyPos.size()];
            }
            sprites["apple"].x = pos.first;
            sprites["apple"].y = pos.second;
            addCellAtEnd(sprites);
        }
    } else {
        this->speed += 1;
    }
    return true;
}

void Games::Snake::updateScore(std::unordered_map<std::string, Arcade::Text_t> &texts)
{
    std::string str = "Score: " + std::to_string(this->score);

    texts["score"].text = str;
}

void Games::Snake::changeDirection(Games::Dir dir)
{
    std::string name = "snake-";
    std::pair<int, int> pos = getPositionSnake();

    if (changeDir == false) {
        for (int i = 0; i < this->size; i++) {
            std::string nameCell = name  + std::to_string(i);
            if (this->listCell[nameCell]->getDirection() == Dir::UNKNOWN && i > 0 && i < 4) {
                pos = this->listCell[nameCell]->getPosition();
                this->listCell[nameCell]->changeDirection(Dir::UP, pos.first, pos.second);
            } else {
                this->listCell[nameCell]->changeDirection(dir, pos.first, pos.second);
            }
        }
        changeDir = true;
    }
}

std::pair<int, int> Games::Snake::getPositionSnake()
{
    return this->listCell["snake-0"]->getPosition();
}

Games::Dir Games::Snake::getDirection()
{
    return this->listCell["snake-0"]->getDirection();
}

void Games::Snake::addCellAtEnd(std::unordered_map<std::string, Arcade::Sprites_t>& sprites)
{
    Arcade::Color_t black = createColor(0, 0, 0, 255);
    Arcade::Color_t yellow = createColor(255, 255, 0, 255);
    Arcade::SpriteRect_t tileRect = createRect(32, 32, 32, 32);
    int indexNext = this->listCell.size();
    std::string name = "snake-" + std::to_string(indexNext);
    std::string lastname = "snake-" + std::to_string(indexNext - 1);
    std::string lastlastname = "snake-" + std::to_string(indexNext - 2);
    Arcade::Sprites_t lastCell = sprites[lastname];
    this->size++;

    this->listCell[lastname]->updateDir(sprites[lastname], indexNext - 1, this->listCell[lastname]);
    if (!CheckCollision(lastCell.x + 32, lastCell.y, "wall", sprites) && !CheckCollision(lastCell.x + 32, lastCell.y, "snake", sprites)) {
        tileRect.x = tileRect.w;
        sprites[name] = {lastCell.x + 32, lastCell.y, "assets/nibbler/body-sprite", tileRect, black, yellow, 1};
        this->addCell(name, lastCell.x + 32, lastCell.y);
        this->listCell[name]->changeDirection(Dir::LEFT, lastCell.x + 32, lastCell.y);
        this->listCell[name]->loadHistoryShift(this->listCell[lastname]->getHistoryShift(), this->listCell[lastname]->getIndexShift(), lastCell.x, lastCell.y, this->listCell[lastname]->getDirection());
        this->listCell[lastname]->setSpriteDirection(sprites[lastname], Games::Dir::LEFT, this->listCell[lastlastname]->getDirection());
    } else if (!CheckCollision(lastCell.x - 32, lastCell.y, "wall", sprites) && !CheckCollision(lastCell.x - 32, lastCell.y, "snake", sprites)) {
        tileRect.x = tileRect.w;
        sprites[name] = {lastCell.x - 32, lastCell.y, "assets/nibbler/body-sprite", tileRect, black, yellow, 1};
        this->addCell(name, lastCell.x - 32, lastCell.y);
        this->listCell[name]->changeDirection(Dir::RIGHT, lastCell.x - 32, lastCell.y);
        this->listCell[name]->loadHistoryShift(this->listCell[lastname]->getHistoryShift(), this->listCell[lastname]->getIndexShift(), lastCell.x, lastCell.y, this->listCell[lastname]->getDirection());
        this->listCell[lastname]->setSpriteDirection(sprites[lastname], Games::Dir::RIGHT, this->listCell[lastlastname]->getDirection());
    } else if (!CheckCollision(lastCell.x, lastCell.y + 32, "wall", sprites) && !CheckCollision(lastCell.x, lastCell.y + 32, "snake", sprites)) {
        sprites[name] = {lastCell.x, lastCell.y + 32, "assets/nibbler/body-sprite", tileRect, black, yellow, 1};
        this->addCell(name, lastCell.x, lastCell.y + 32);
        this->listCell[name]->changeDirection(Dir::UP, lastCell.x, lastCell.y + 32);
        this->listCell[name]->loadHistoryShift(this->listCell[lastname]->getHistoryShift(), this->listCell[lastname]->getIndexShift(), lastCell.x, lastCell.y, this->listCell[lastname]->getDirection());
        this->listCell[lastname]->setSpriteDirection(sprites[lastname], Games::Dir::DOWN, this->listCell[lastlastname]->getDirection());
    } else if (!CheckCollision(lastCell.x, lastCell.y - 32, "wall", sprites) && !CheckCollision(lastCell.x, lastCell.y - 32, "snake", sprites)) {
        sprites[name] = {lastCell.x, lastCell.y - 32, "assets/nibbler/body-sprite", tileRect, black, yellow, 1};
        this->addCell(name, lastCell.x, lastCell.y - 32);
        this->listCell[name]->changeDirection(Dir::DOWN, lastCell.x, lastCell.y - 32);
        this->listCell[name]->loadHistoryShift(this->listCell[lastname]->getHistoryShift(), this->listCell[lastname]->getIndexShift(), lastCell.x, lastCell.y, this->listCell[lastname]->getDirection());
        this->listCell[lastname]->setSpriteDirection(sprites[lastname], Games::Dir::UP, this->listCell[lastlastname]->getDirection());
    } else {
        this->size--;
        this->alive = false;
    }
}

Arcade::SpriteRect_t Games::Snake::createRect(int width, int height, int maxWidth, int maxHeight)
{
    Arcade::SpriteRect_t rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;
    rect.maxW = maxWidth;
    rect.maxH = maxHeight;
    return rect;
}

Arcade::Color_t Games::Snake::createColor(int r, int g, int b, int a)
{
    Arcade::Color_t color;

    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    return color;
}

void Games::Snake::checkHighScore()
{
    std::stringstream stream;
    std::stringstream stream2;
    std::string content;
    std::string name;
    std::fstream s("score/high-nibbler.txt");
    std::fstream f_name("score/current_name.txt");

    if (!s.is_open() || !f_name.is_open())
        return;
    stream << s.rdbuf();
    content = stream.str();
    stream2 << f_name.rdbuf();
    name = stream2.str();
    s.close();
    int c_hs = std::stoi(content.substr(content.find("\n") + 1, content.length() - content.find("\n") - 2));
    if (c_hs < this->score) {
        std::fstream f("score/high-nibbler.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
        f << name + "\n" + std::to_string(this->score);
        f.close();
    }
}
