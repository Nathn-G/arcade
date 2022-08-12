/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** NibblerModule.hpp
*/

#include "NibblerModule.hpp"

Games::NibblerModule::NibblerModule()
{
    File file;

    this->map = file.readFile("assets/nibbler/nibbler_map1.txt");
    this->score = 0;
    createMap();
    this->_texts["score"] = {"Score: 0", 0, 0, 255, 255, 255, 255, 30, "assets/arial.ttf", 2};
    this->height = 672;
    this->width = 864;
    srand(time(NULL));
    this->lastUpdate = clock();
    this->timeUpdate = 0.01;
}

Games::NibblerModule::~NibblerModule()
{

}

void Games::NibblerModule::createMap()
{
    Arcade::SpriteRect_t tileRect = createRect(32, 32, 32, 32);
    Arcade::Color_t blue = createColor(0, 0, 255, 255);
    Arcade::Color_t black = createColor(0, 0, 0, 255);
    Arcade::Color_t yellow = createColor(255, 255, 0, 255);
    Arcade::Color_t white = createColor(255, 255, 255, 255);
    std::pair<int, int> pos;
    this->snake = new Snake();
    this->snake->setScore(this->score);
    this->snake->setSize(4);

    for (int x = 0; x < this->map.size(); x++) {
        for (int y = 0; y < this->map[x].size(); y++) {
            if (this->map[x][y] == 'x') {
                std::string name = "wall" + std::to_string(y) + " " + std::to_string(x);
                this->_sprites[name] = {y * 32, x * 32, "assets/nibbler/wall", tileRect, blue, blue, 0};
            }
            if (this->map[x][y] == ' ') {
                std::string name = "ground" + std::to_string(y) + " " + std::to_string(x);
                this->_sprites[name] = {y * 32, x * 32, "assets/nibbler/ground", tileRect, white, black, 0};
                this->emptyPos.push_back(std::pair<int, int>(y * 32, x * 32));
            }
            if (this->map[x][y] == 'C') {
                Arcade::SpriteRect_t rect = createRect(32, 32, 32, 32);
                this->_sprites["snake-0"] = {(int)y * 32, (int)x * 32, "assets/nibbler/head-sprites", rect, black, yellow, 1};
                this->snake->addCell("snake-0", (int)y * 32, (int)x * 32);
            }
            if (this->map[x][y] == '1') {
                Arcade::SpriteRect_t rect = createRect(32, 32, 32, 32);
                this->_sprites["snake-1"] = {(int)y * 32, (int)x * 32, "assets/nibbler/body-sprite", rect, black, yellow, 1};
                this->snake->addCell("snake-1", (int)y * 32, (int)x * 32);
            }
            if (this->map[x][y] == '2') {
                Arcade::SpriteRect_t rect = createRect(32, 32, 32, 32);
                this->_sprites["snake-2"] = {(int)y * 32, (int)x * 32, "assets/nibbler/body-sprite", rect, black, yellow, 1};
                this->snake->addCell("snake-2", (int)y * 32, (int)x * 32);
            }
            if (this->map[x][y] == '3') {
                Arcade::SpriteRect_t rect = createRect(32, 32, 32, 32);
                this->_sprites["snake-3"] = {(int)y * 32, (int)x * 32, "assets/nibbler/body-sprite", rect, black, yellow, 1};
                this->snake->addCell("snake-3", (int)y * 32, (int)x * 32);
            }
        }
    }
    pos = this->emptyPos[std::rand() % this->emptyPos.size()];
    this->_sprites["apple"] = {pos.first, pos.second, "assets/nibbler/apple", tileRect, black, yellow, 1};
}

std::pair<int, int> Games::NibblerModule::getSizeWindow()
{
    return std::pair<int, int>(864, 672);
}

std::pair<int, int> Games::NibblerModule::getSizePixel()
{
    return std::pair<int, int>(32, 32);
}

void Games::NibblerModule::handleEvents(std::vector<Arcade::KeyEvent_t> event)
{
    Games::Dir direction = this->snake->getDirection();

    for (size_t i = 0; i < event.size(); i++) {
        if (i == 0 && ((event[i].key == Arcade::KeyState::Left && direction == Games::Dir::RIGHT) ||
        (event[i].key == Arcade::KeyState::Right && direction == Games::Dir::LEFT) ||
        (event[i].key == Arcade::KeyState::Up && direction == Games::Dir::DOWN) ||
        (event[i].key == Arcade::KeyState::Down && direction == Games::Dir::UP))) {
            break;
        }
        if (event[i].key == Arcade::KeyState::Left && direction != Games::Dir::RIGHT) {
            this->snake->changeDirection(Games::Dir::LEFT);
        }
        if (event[i].key == Arcade::KeyState::Right && direction != Games::Dir::LEFT) {
            this->snake->changeDirection(Games::Dir::RIGHT);
        }
        if (event[i].key == Arcade::KeyState::Up && direction != Games::Dir::DOWN) {
            this->snake->changeDirection(Games::Dir::UP);
        }
        if (event[i].key == Arcade::KeyState::Down && direction != Games::Dir::UP) {
            this->snake->changeDirection(Games::Dir::DOWN);
        }
        if (event[i].key == Arcade::KeyState::Space) {
            this->timeBoost = this->timeUpdate / 2;
            this->clockBoost = clock();
        }
        if (event[i].key == Arcade::KeyState::R) {
            this->restartGame();
        }
    }
    if (this->timeBoost != 0 && static_cast<float>(clock() - this->clockBoost) / CLOCKS_PER_SEC > 1) {
        this->timeBoost = 0;
    }
}

std::unordered_map<std::string, Arcade::Rect_t> Games::NibblerModule::getShapes()
{
    return (this->_shapes);
}

std::unordered_map<std::string, Arcade::Sprites_t> Games::NibblerModule::getSprites()
{
    return (this->_sprites);
}

std::unordered_map<std::string, Arcade::Text_t> Games::NibblerModule::getTexts()
{
    return (this->_texts);
}

void Games::NibblerModule::update(void)
{
    if (static_cast<float>(clock() - this->lastUpdate) / CLOCKS_PER_SEC < (this->timeUpdate - this->timeBoost))
        return;
    this->lastUpdate = clock();
    bool isdead = !this->snake->update(this->_sprites, this->emptyPos, this->_texts);
    if (isdead) {
        restartGame();
    }
}

void Games::NibblerModule::destroyGame()
{
    this->_shapes.clear();
    this->_sprites.clear();
}

void Games::NibblerModule::restartGame()
{
    destroyGame();
    createMap();
    this->snake->updateScore(this->_texts);
}

extern "C" {
    std::shared_ptr<Games::IGameModule> create(void)
    {
        return std::make_shared<Games::NibblerModule>();
    }
}