/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** PacmanModule.hpp
*/

#include "PacmanModule.hpp"
#include <fstream>
#include <sstream>

Games::PacmanModule::PacmanModule()
{
    File file;

    this->map = file.readFile("assets/pacman/pacman_map.txt");
    this->score = 0;
    createMap();
    this->_texts["score"] = {"Score: 0", 700, 200, 255, 255, 255, 255, 30, "assets/arial.ttf", 2};
    this->height = 672;
    this->width = 864;
}

Games::PacmanModule::~PacmanModule()
{

}

void Games::PacmanModule::restartGame()
{
    destroyGame();
    this->score = 0;
    createMap();
}

void Games::PacmanModule::destroyGame()
{
    if (this->player != nullptr) {
        this->score = this->player->getScore();
        delete this->player;
    }
    for (size_t i = 0; i < this->ghosts.size(); i++) {
        if (this->ghosts[i] != nullptr) {
            delete this->ghosts[i];
        }
    }
    this->ghosts.clear();
}

void Games::PacmanModule::addGhosts(int x, int y, int& indexGhost)
{
    Arcade::Color_t black = createColor(0, 0, 0, 255);
    Arcade::SpriteRect_t rect = createRect(32, 32, 32, 192);
    std::string name = "ghost" + std::to_string(indexGhost++);

    if (indexGhost == 1) {
        Arcade::Color_t red = createColor(255, 0, 0, 255);
        this->ghosts.push_back(new RandomGhost(name, 1, y * 32, x * 32));
        this->_sprites[name] = {y * 32, x * 32, "assets/pacman/ghost" +  std::to_string(indexGhost), rect, black, red, 2};
    }
    if (indexGhost == 2) {
        Arcade::Color_t pink = createColor(255, 150, 200, 255);
        this->ghosts.push_back(new ChasingGhost(name, 1, y * 32, x * 32));
        this->_sprites[name] = {y * 32, x * 32, "assets/pacman/ghost" +  std::to_string(indexGhost), rect, black, pink, 2};
    }
    if (indexGhost == 3) {
        Arcade::Color_t yellow = createColor(255, 255, 0, 255);
        this->ghosts.push_back(new RandomGhost(name, 1, y * 32, x * 32));
        this->_sprites[name] = {y * 32, x * 32, "assets/pacman/ghost" +  std::to_string(indexGhost), rect, black, yellow, 2};
    }
}

void Games::PacmanModule::createMap()
{
    Arcade::SpriteRect_t tileRect = createRect(32, 32, 32, 32);
    Arcade::Color_t blue = createColor(0, 0, 255, 255);
    Arcade::Color_t green = createColor(0, 255, 0, 255);
    Arcade::Color_t black = createColor(0, 0, 0, 255);
    Arcade::Color_t yellow = createColor(255, 255, 0, 255);
    Arcade::Color_t white = createColor(255, 255, 255, 255);
    int indexGhost = 0;

    this->lastUpdate = clock();
    for (size_t x = 0; x < this->map.size(); x++) {
        for (size_t y = 0; y < this->map[x].size(); y++) {
            if (this->map[x][y] == 'x') {
                std::string name = "wall" + std::to_string(y) + " " + std::to_string(x);
                this->_sprites[name] = {y * 32, x * 32, "assets/pacman/wall", tileRect, blue, blue, 0};
            }
            if (this->map[x][y] == ' ') {
                std::string name = "ground" + std::to_string(y) + " " + std::to_string(x);
                this->_sprites[name] = {y * 32, x * 32, "assets/pacman/ground", tileRect, white, black, 0};
                name = "coin" + std::to_string(y) + " " + std::to_string(x);
                this->_sprites[name] = {y * 32, x * 32, "assets/pacman/coin", tileRect, yellow, black, 1};
            }
            if (this->map[x][y] == 'o') {
                std::string name = "ground" + std::to_string(y) + " " + std::to_string(x);
                this->_sprites[name] = {y * 32, x * 32, "assets/pacman/ground", tileRect, white, black, 0};
                name = "bonus" + std::to_string(y) + " " + std::to_string(x);
                this->_sprites[name] = {y * 32, x * 32, "assets/pacman/bonus", tileRect, green, green, 1};
            }
            if (this->map[x][y] == '-') {
                this->_sprites["home"] = {y * 32, x * 32, "assets/pacman/ground", tileRect, white, black, 0};
            }
            if (this->map[x][y] == 'C') {
                Arcade::SpriteRect_t rect = createRect(32, 32, 96, 128);
                this->_sprites["player"] = {y * 32, x * 32, "assets/pacman/pacman", rect, black, yellow, 2};
                this->player = new Player("player", 1, y * 32, x * 32);
                this->player->setScore(this->score);
            }
            if (this->map[x][y] == 'U') {
                this->addGhosts(x, y, indexGhost);
            }
        }
    }
}

std::pair<int, int> Games::PacmanModule::getSizeWindow()
{
    return std::pair<int, int>(this->width, this->height);
}

std::pair<int, int> Games::PacmanModule::getSizePixel()
{
    return std::pair<int, int>(32, 32);
}

void Games::PacmanModule::handleEvents(std::vector<Arcade::KeyEvent_t> event)
{
    for (size_t i = 0; i < event.size(); i++) {
        if (event[i].key == Arcade::KeyState::Left) {
            this->player->currentDir = LEFT;
        }
        if (event[i].key == Arcade::KeyState::Right) {
            this->player->currentDir = RIGHT;
        }
        if (event[i].key == Arcade::KeyState::Up) {
            this->player->currentDir = UP;
        }
        if (event[i].key == Arcade::KeyState::Down) {
            this->player->currentDir = DOWN;
        }
        if (event[i].key == Arcade::KeyState::R) {
            this->restartGame();
        }
    }
}

std::unordered_map<std::string, Arcade::Rect_t> Games::PacmanModule::getShapes()
{
    return (this->_shapes);
}

std::unordered_map<std::string, Arcade::Sprites_t> Games::PacmanModule::getSprites()
{
    return (this->_sprites);
}

std::unordered_map<std::string, Arcade::Text_t> Games::PacmanModule::getTexts()
{
    return (this->_texts);
}

void Games::PacmanModule::update(void)
{
    if (static_cast<float>(clock() - this->lastUpdate) / CLOCKS_PER_SEC < 0.009)
        return;
    this->lastUpdate = clock();
    this->player->update(this->_sprites, this->_texts);

    // Loop back player
    if (this->_sprites["player"].x > this->width) {
        this->_sprites["player"].x = 0;
    } else if (this->_sprites["player"].x < 0) {
        this->_sprites["player"].x = this->width;
    }

    // Update ghost position
    for (size_t i = 0; i < this->ghosts.size(); i++) {
        std::string ghostName = this->ghosts[i]->getName();
        if (this->_sprites[ghostName].x > this->width) {
            this->_sprites[ghostName].x = 0;
        } else if (this->_sprites[ghostName].x < 0) {
            this->_sprites[ghostName].x = this->width;
        }
        this->ghosts[i]->ToggleGhostAppearance(&this->_sprites[ghostName], this->player->getBonusPhase());
        this->ghosts[i]->update(this->_sprites, this->_texts);
        if (this->ghosts[i]->checkCollisionsWithType(this->_sprites, "player")) {
            if (this->player->getBonusPhase()) {
                this->ghosts[i]->restart(&this->_sprites[ghostName], false);
            } else {
                this->player->removeLives(1);
            }
        }
    }

    // Check player life
    if (this->player->getLives() == 0) {
        this->checkHighScore();
        this->player->restart(&this->_sprites["player"], false);
        this->restartGame();
    }

    int nbCoins = 0;
    for (auto sprite: this->_sprites) {
        if (sprite.first.find("coin") != std::string::npos) {
            nbCoins++;
        }
        if (sprite.first.find("bonus") != std::string::npos) {
            nbCoins++;
        }
    }
    if (nbCoins == 0) {
        this->player->restart(&this->_sprites["player"], true);
        this->restartGame();
    }
}

void Games::PacmanModule::checkHighScore()
{
    std::stringstream stream;
    std::stringstream stream2;
    std::string content;
    std::string name;
    std::fstream s("score/high-pacman.txt");
    std::fstream f_name("score/current_name.txt");

    if (!s.is_open() || !f_name.is_open())
        return;
    stream << s.rdbuf();
    content = stream.str();
    stream2 << f_name.rdbuf();
    name = stream2.str();
    s.close();
    int c_hs = std::stoi(content.substr(content.find("\n") + 1, content.length() - content.find("\n") - 2));
    if (c_hs < this->player->getScore()) {
        std::fstream f("score/high-pacman.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
        f << name + "\n" + std::to_string(this->player->getScore());
        f.close();
    }
}

extern "C" {
    std::shared_ptr<Games::IGameModule> create(void)
    {
        return std::make_shared<Games::PacmanModule>();
    }
}
