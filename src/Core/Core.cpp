/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** core of arcade
*/

#include "Core.hpp"
#include <fstream>

Arcade::Core::Core()
{
    std::ifstream myfile;

    int libs = _listLib.size();
    int games = _listGame.size();

    for (int i = 0; i < libs; i++) {
        myfile.open(_listLib[i]);
        if (!myfile.is_open()) {
            this->_listLib.erase(_listLib.begin() + i);
            i -= 1;
            libs -= 1;
        } else
            myfile.close();
    }
    for (int i = 0; i < games; i++) {
        myfile.open(_listGame[i]);
        if (!myfile.is_open()) {
            this->_listGame.erase(_listGame.begin() + i);
            i -= 1;
            games -= 1;
        } else
            myfile.close();
    }
    this->lastUpdate = clock();
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    this->_idxMenu = 0;
    this->_idxMenuGame = 0;
    this->_idxMenuPage = 0;
}

Arcade::Core::~Core()
{
}

void Arcade::Core::initLib(std::string libName)
{
    bool findLib = false;

    for (size_t i = 0; i < _listLib.size(); i++) {
        if (libName.length() >= _listLib[i].length() && 
        libName.compare(libName.length() - _listLib[i].length(), _listLib[i].length(), _listLib[i]) == 0) {
            findLib = true;
            this->_idxLib = i;
            break;
        }
    }
    try {
        if (findLib == false)
            throw Error("Librairy not found.");
        this->_lib = this->_loaderL->getInstance(libName);
        for (size_t i = 0; i < _listLib.size(); i++) {
            this->_libs.push_back(this->_loaderL->getInstanceList(_listLib[i]));
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
}

void Arcade::Core::initGame(std::string gameName)
{
    try {
        this->_idxGame = 0;
        this->_game = this->_loaderG->getInstance(gameName);
        for (size_t i = 0; i < _listGame.size(); i++) {
            this->_games.push_back(this->_loaderG->getInstanceList(_listGame[i]));
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
}

void Arcade::Core::initloader(std::shared_ptr<DLLoader<Libs::IDisplayModule>> lib, std::shared_ptr<DLLoader<Games::IGameModule>> game)
{
    _loaderL = lib;
    _loaderG = game;
}

void Arcade::Core::runLoop()
{
    std::pair<int, int> size = _game->getSizeWindow();
    _libs[_idxLib]->init("Arcade", size.first, size.second);
    _libs[_idxLib]->setSizePixel(_game->getSizePixel());
    while (_libs[_idxLib]->isOpen()) {
        handleEvents();
        update();
        if (static_cast<float>(clock() - this->lastUpdate) / CLOCKS_PER_SEC > 0.01) {
            draw();
        }
    }
}

void Arcade::Core::update()
{
    this->_game->update();
}

void Arcade::Core::draw()
{
    std::unordered_map<std::string, Rect_t> shapes = this->_game->getShapes();
    std::unordered_map<std::string, Sprites_t> sprites = this->_game->getSprites();
    std::unordered_map<std::string, Text_t> texts = this->_game->getTexts();

    this->_libs[_idxLib]->my_clear();
    this->_libs[_idxLib]->draw(shapes, sprites, texts);
    this->_libs[_idxLib]->display();
    this->lastUpdate = clock();
}

void Arcade::Core::handleEvents()
{
    std::vector<KeyEvent_t> events = _libs[_idxLib]->getEvents();
    for (size_t i = 0; i < events.size(); i++) {
        if (events[i].key == Arcade::KeyState::A)
            return previousLib();
        if (events[i].key == Arcade::KeyState::Z)
            return nextLib();
        if (!(this->_idxGame == 0 && this->_idxMenuPage == 0) && events[i].key == Arcade::KeyState::Q)
            return previousGame();
        if (!(this->_idxGame == 0 && this->_idxMenuPage == 0) && events[i].key == Arcade::KeyState::S)
            return nextGame();
        if (events[i].key == Arcade::KeyState::Escape)
            return exitGame();
        // if (!(this->_idxGame == 0 && this->_idxMenuPage == 0) && events[i].key == Arcade::KeyState::R)
        //     return restartGame();
        if (!(this->_idxGame == 0 && this->_idxMenuPage == 0) && events[i].key == Arcade::KeyState::Return)
            return goMenu();
        if (this->_idxGame == 0) {
            int change = 0;
            if (this->_idxMenuPage == 2) {
                if (events[i].key == Arcade::KeyState::Enter) {
                    this->_idxMenu = 0;
                    this->_idxMenuPage = 1;
                    change = 1;
                }
            }
            if (this->_idxMenuPage == 1) {
                if (this->_idxMenu == 0 && events[i].key == Arcade::KeyState::Enter && change == 0 && this->_listGame.size() != 1) {
                    this->_game = this->_games[_idxMenuGame];
                    this->_idxGame = _idxMenuGame;
                    for (int i = 0; i < this->_libs.size(); i++) {
                        this->_libs[i]->clearAssets();
                    }
                    this->_libs[_idxLib]->setSizeWindows(_game->getSizeWindow());
                    this->_libs[_idxLib]->setSizePixel(_game->getSizePixel());
                    checkchangeGame();
                }
                if (events[i].key == Arcade::KeyState::Down)
                    this->_idxMenu = _idxMenu < 3 ? _idxMenu + 1 : 0;
                if (events[i].key == Arcade::KeyState::Up)
                    this->_idxMenu = _idxMenu > 0 ? _idxMenu - 1 : 3;
                if (this->_idxMenu == 3 && events[i].key == Arcade::KeyState::Enter)
                    return this->_libs[this->_idxLib]->close();
                if (this->_idxMenu == 1) {
                    if (events[i].key == Arcade::KeyState::Right)
                        this->_idxMenuGame = _idxMenuGame < _listGame.size() - 2 ? _idxMenuGame + 1 : 0;
                    if (events[i].key == Arcade::KeyState::Left)
                        this->_idxMenuGame = _idxMenuGame > 0 ? _idxMenuGame - 1 : _listGame.size() - 2;
                }
                if (events[i].key == Arcade::KeyState::Enter && this->_idxMenu == 2) {
                    this->_idxMenu = 0;
                    this->_idxMenuPage = 2;
                }
            }
            if (this->_idxMenuPage == 0) {
                if (events[i].key == Arcade::KeyState::Right)
                    this->_idxMenu = _idxMenu < 5 ? _idxMenu + 1 : 0;
                if (events[i].key == Arcade::KeyState::Left)
                    this->_idxMenu = _idxMenu > 0 ? _idxMenu - 1 : 5;
                if (events[i].key == Arcade::KeyState::Enter && this->_idxMenu == 5) {
                    this->_idxMenu = 0;
                    this->_idxMenuPage = 1;
                }
                if (events[i].key == Arcade::KeyState::Enter && this->_idxMenu == 2) {
                    this->_idxMenu = 0;
                    this->_idxMenuPage = 1;
                }
            }
        }
    }
    _game->handleEvents(events);
}

void Arcade::Core::previousLib()
{
    this->_libs[_idxLib]->close();
    if (this->_idxLib == 0)
        this->_idxLib = this->_listLib.size() - 1;
    else
        this->_idxLib -= 1;
    std::pair<int, int> size = _game->getSizeWindow();
    _libs[_idxLib]->init("Arcade", size.first, size.second);
    _libs[_idxLib]->setSizePixel(_game->getSizePixel());
}

void Arcade::Core::nextLib()
{
    this->_libs[_idxLib]->close();
    if (this->_idxLib == this->_listLib.size() - 1)
        this->_idxLib = 0;
    else
        this->_idxLib += 1;
    std::pair<int, int> size = _game->getSizeWindow();
    _libs[_idxLib]->init("Arcade", size.first, size.second);
    _libs[_idxLib]->setSizePixel(_game->getSizePixel());
}

void Arcade::Core::previousGame()
{
    if (this->_idxGame == 0)
        this->_idxGame = this->_listGame.size() - 2;
    else
        this->_idxGame -= 1;
    this->_game = this->_games[this->_idxGame];
    for (int i = 0; i < this->_libs.size(); i++) {
        this->_libs[i]->clearAssets();
    }
    this->_libs[_idxLib]->setSizeWindows(_game->getSizeWindow());
    this->_libs[_idxLib]->setSizePixel(_game->getSizePixel());
}

void Arcade::Core::nextGame()
{
    if (this->_idxGame >= this->_listGame.size() - 2)
        this->_idxGame = 0;
    else
        this->_idxGame += 1;
    this->_game = this->_games[this->_idxGame];
    for (int i = 0; i < this->_libs.size(); i++) {
        this->_libs[i]->clearAssets();
    }
    this->_libs[_idxLib]->setSizeWindows(_game->getSizeWindow());
    this->_libs[_idxLib]->setSizePixel(_game->getSizePixel());
}

void Arcade::Core::exitGame()
{
    this->_libs[_idxLib]->close();
}

void Arcade::Core::restartGame()
{
}

void Arcade::Core::goMenu()
{
    this->_idxMenu = 0;
    this->_idxMenuGame = 0;
    this->_idxMenuPage = 0;
    this->_idxGame = 0;
    this->_game = this->_loaderG->getInstance("lib/arcade_menu.so");
    for (int i = 0; i < this->_libs.size(); i++) {
        this->_libs[i]->clearAssets();
    }
    this->_libs[_idxLib]->setSizePixel(_game->getSizePixel());
    checkchangeGame();
}

void Arcade::Core::changeGame(std::string lib)
{
    try {
        this->_game = _loaderG->getInstance(lib);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
}

void Arcade::Core::loadGame(std::string game)
{
    try {
        this->_game = _loaderG->getInstance(game);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }
}

void Arcade::Core::checkchangeGame()
{
    if (this->_listLib[this->_idxLib] == "lib/arcade_sdl2.so") {
        this->_libs[_idxLib]->close();
        std::pair<int, int> size = _game->getSizeWindow();
        _libs[_idxLib]->init("Arcade", size.first, size.second);
        _libs[_idxLib]->setSizePixel(_game->getSizePixel());
    }
}
