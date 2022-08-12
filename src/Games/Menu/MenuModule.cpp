/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** MenuModule.hpp
*/

#include "MenuModule.hpp"
#include <fstream>
#include <sstream>

Games::MenuModule::MenuModule()
{
    std::ifstream myfile;
    Arcade::Color_t black = createColor(0, 0, 0, 255);
    Arcade::Color_t white = createColor(255, 255, 255, 255);
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
    this->_sprites["arcade"] = {240, 20, "assets/menu/arcade", (Arcade::SpriteRect_t) {0, 0, 363, 115, 0, 0}, white, black, 2};
    this->_texts["choose"] = {"Choose Your Name", 280, 190, 255, 255, 255, 255, 32, "assets/arial.ttf", 0};
    this->_sprites["up"] = {150, 270, "assets/menu/up", (Arcade::SpriteRect_t) {0, 0, 78, 46, 0, 0}, white, black, 2};
    this->_sprites["up1"] = {270, 270, "assets/menu/up", (Arcade::SpriteRect_t) {0, 0, 78, 46, 0, 0}, white, black, 2};
    this->_sprites["up2"] = {390, 270, "assets/menu/up", (Arcade::SpriteRect_t) {0, 0, 78, 46, 0, 0}, white, black, 2};
    this->_sprites["up3"] = {510, 270, "assets/menu/up", (Arcade::SpriteRect_t) {0, 0, 78, 46, 0, 0}, white, black, 2};
    this->_sprites["up4"] = {630, 270, "assets/menu/up", (Arcade::SpriteRect_t) {0, 0, 78, 46, 0, 0}, white, black, 2};
    this->_sprites["down"] = {150, 470, "assets/menu/down", (Arcade::SpriteRect_t) {0, 0, 78, 46, 0, 0}, white, black, 2};
    this->_sprites["down1"] = {270, 470, "assets/menu/down", (Arcade::SpriteRect_t) {0, 0, 78, 46, 0, 0}, white, black, 2};
    this->_sprites["down2"] = {390, 470, "assets/menu/down", (Arcade::SpriteRect_t) {0, 0, 78, 46, 0, 0}, white, black, 2};
    this->_sprites["down3"] = {510, 470, "assets/menu/down", (Arcade::SpriteRect_t) {0, 0, 78, 46, 0, 0}, white, black, 2};
    this->_sprites["down4"] = {630, 470, "assets/menu/down", (Arcade::SpriteRect_t) {0, 0, 78, 46, 0, 0}, white, black, 2};
    this->_shapes["valid"] = {282, 560, 300, 60, white, 0};
    this->_shapes["valid"] = {282, 560, 300, 60, white, 0};
    this->_texts["valid"] = {"Continue", 360, 570, 0, 0, 0, 255, 32, "assets/arial.ttf", 0};
    this->_shapes["letter1"] = {150, 340, 80, 100, 0, 255, 255, 255, 0};
    this->_shapes["letter2"] = {270, 340, 80, 100, white, 0};
    this->_shapes["letter3"] = {390, 340, 80, 100, white, 0};
    this->_shapes["letter4"] = {510, 340, 80, 100, white, 0};
    this->_shapes["letter5"] = {630, 340, 80, 100, white, 0};
    this->_texts["letter1"] = {"A", 175, 355, black, 50, "assets/arial.ttf", 0};
    this->_texts["letter2"] = {"A", 295, 355, black, 50, "assets/arial.ttf", 0};
    this->_texts["letter3"] = {"A", 415, 355, black, 50, "assets/arial.ttf", 0};
    this->_texts["letter4"] = {"A", 535, 355, black, 50, "assets/arial.ttf", 0};
    this->_texts["letter5"] = {"A", 655, 355, black, 50, "assets/arial.ttf", 0};
    this->_listMenu.push_back("letter1");
    this->_listMenu.push_back("letter2");
    this->_listMenu.push_back("letter3");
    this->_listMenu.push_back("letter4");
    this->_listMenu.push_back("letter5");
    this->_listMenu.push_back("valid");
    this->_idxMenu = 0;
    this->_idxGame = 0;
    this->_idxPage = 0;
}

Games::MenuModule::~MenuModule()
{

}

std::pair<int, int> Games::MenuModule::getSizeWindow()
{
    return std::pair<int, int>(864, 672);
}

std::pair<int, int> Games::MenuModule::getSizePixel()
{
    return std::pair<int, int>(-1, -1);
}

void Games::MenuModule::changeCaseMenu()
{
    if (this->_idxMenu < 0)
        this->_idxMenu = this->_listMenu.size() - 1;
    if ((long unsigned int)this->_idxMenu > this->_listMenu.size() - 1)
        this->_idxMenu = 0;
    for (long unsigned int i = 0; i < this->_listMenu.size(); i++) {
        this->_shapes[this->_listMenu[i]].bg.r = 255;
        if (i == (long unsigned int)this->_idxMenu)
            this->_shapes[this->_listMenu[i]].bg.r = 0;
    }
}

void Games::MenuModule::changeSelectedGame()
{
    std::stringstream stream;
    std::string content;

    if (this->_idxGame < 0)
        this->_idxGame = this->_listGame.size() - 1;
    if ((long unsigned int)this->_idxGame > this->_listGame.size() - 1)
        this->_idxGame = 0;
    std::fstream s("score/high-" + _listGame[this->_idxGame].substr(11, (_listGame[this->_idxGame].length() - 3 - 11)) + ".txt");
    stream << s.rdbuf();
    content = stream.str();
    s.close();
    this->_texts["highsc"] = {content.substr(content.find('\n') + 1, content.length() - content.find('\n') - 1), 510, 250, 0, 0, 0, 255, 18, "assets/arial.ttf", 0};
    this->_texts["highna"] = {content.substr(0, content.find('\n')), 510, 315, 0, 0, 0, 255, 18, "assets/arial.ttf", 0};
    this->_sprites["game"].path = std::string("assets/menu/") + _listGame[this->_idxGame].substr(11, (_listGame[this->_idxGame].length() - 14)) + std::string("_logo");
}

void Games::MenuModule::changePageGame()
{
    Arcade::Color_t black = createColor(0, 0, 0, 255);
    Arcade::Color_t white = createColor(255, 255, 255, 255);
    std::fstream f("score/current_name.txt");
    std::string name = "";
    std::fstream s("score/high-" + _listGame[0].substr(11, (_listGame[0].length() - 3 - 11)) + ".txt");
    std::stringstream stream;
    std::stringstream stream2;
    std::string content;

    stream << s.rdbuf();
    content = stream.str();
    s.close();
    stream2 << f.rdbuf();
    name = stream2.str();
    f.close();
    this->_listMenu.clear();
    this->_shapes.clear();
    this->_sprites.clear();
    this->_texts.clear();
    this->_sprites["arcade"] = {240, 20, "assets/menu/arcade", (Arcade::SpriteRect_t) {0, 0, 363, 115, 0, 0}, white, black, 2};
    this->_shapes["libs"] = {0, 620, 864, 100, (Arcade::Color_t){255, 255, 255, 255}, 0};
    this->_texts["libs"] = {"Libs:", 20, 640, (Arcade::Color_t){0, 0, 0, 255}, 16, "assets/arial.ttf", 0};
    this->_shapes["play"] = {282, 150, 300, 60, (Arcade::Color_t){0, 255, 255, 255}, 0};
    this->_texts["play"] = {"Play", 412, 160, (Arcade::Color_t){0, 0, 0, 255}, 20, "assets/arial.ttf", 0};
    this->_shapes["game"] = {232, 225, 400, 150, (Arcade::Color_t){255, 255, 255, 255}, 0};
    this->_shapes["how_to_play"] = {282, 420, 300, 60, (Arcade::Color_t){255, 255, 255, 255}, 0};
    this->_texts["how_to_play"] = {"How to play", 377, 435, (Arcade::Color_t){0, 0, 0, 255}, 20, "assets/arial.ttf", 0};
    this->_shapes["quit"] = {282, 500, 300, 60, (Arcade::Color_t){255, 255, 255, 255}, 0};
    this->_texts["quit"] = {"Quit", 412, 515, (Arcade::Color_t){0, 0, 0, 255}, 20, "assets/arial.ttf", 0};
    this->_texts["player"] = {"Player:", 20, 10, (Arcade::Color_t){255, 255, 255, 255}, 18, "assets/arial.ttf", 0};
    this->_texts["name"] = {name, 20, 40, (Arcade::Color_t){255, 255, 255, 255}, 20, "assets/arial.ttf", 0};
    if (this->_listGame.size() != 0) {
        this->_texts["highs"] = {"High-Score:", 510, 230, (Arcade::Color_t){0, 0, 0, 255}, 15, "assets/arial.ttf", 0};
        this->_texts["highsc"] = {content.substr(content.find('\n') + 1, content.length() - content.find('\n') - 1), 510, 250, (Arcade::Color_t){0, 0, 0, 255}, 18, "assets/arial.ttf", 0};
        this->_texts["highn"] = {"By:", 510, 295, (Arcade::Color_t){0, 0, 0, 255}, 15, "assets/arial.ttf", 0};
        this->_texts["highna"] = {content.substr(0, content.find('\n')), 510, 315, (Arcade::Color_t){0, 0, 0, 255}, 18, "assets/arial.ttf", 0};
    }
    this->_sprites["game"] = {245, 235, "assets/menu/no_game", (Arcade::SpriteRect_t) {0, 0, 300, 125, 0, 0}, white, black, 2};
    if (this->_listGame.size() != 0) {
        this->_texts["left"] = {"<", 192, 270, (Arcade::Color_t){255, 255, 255, 255}, 50, "assets/arial.ttf", 0};
        this->_texts["right"] = {">", 642, 270, (Arcade::Color_t){255, 255, 255, 255}, 50, "assets/arial.ttf", 0};
        this->_sprites["game"] = {245, 235, std::string("assets/menu/") + _listGame[0].substr(11, (_listGame[0].length() - 3 - 11)) + std::string("_logo"), (Arcade::SpriteRect_t) {0, 0, 256, 125, 0, 0}, white, black, 2};
    }
    for (long unsigned int i = 0; i < _listLib.size(); i++) {
        this->_texts[_listLib[i]] = {_listLib[i].substr(11, (_listLib[i].length() - 3 - 11)), 0, 640, (Arcade::Color_t){0, 0, 0, 255}, 16, "assets/arial.ttf", 0};
        this->_texts[_listLib[i]].x = 60 + 80 * i;
    }
    this->_listMenu.push_back("play");
    this->_listMenu.push_back("game");
    this->_listMenu.push_back("how_to_play");
    this->_listMenu.push_back("quit");
    this->_idxMenu = 0;
    this->_idxGame = 0;
}

void Games::MenuModule::saveName()
{
    std::fstream f("score/current_name.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
    std::string name = this->_texts["letter1"].text + this->_texts["letter2"].text + this->_texts["letter3"].text +
    this->_texts["letter4"].text + this->_texts["letter5"].text;

    if (!f.is_open())
        std::cout << "error file\n";
    f << name;
    f.close();
}

void Games::MenuModule::changePageHow()
{
    Arcade::Color_t black = createColor(0, 0, 0, 255);
    Arcade::Color_t white = createColor(255, 255, 255, 255);

    this->_listMenu.clear();
    this->_shapes.clear();
    this->_sprites.clear();
    this->_texts.clear();
    this->_shapes["back"] = {282, 530, 300, 60, (Arcade::Color_t){0, 255, 255, 255}, 0};
    this->_texts["back"] = {"Back", 412, 545, black, 20, "assets/arial.ttf", 0};
    this->_texts["libs"] = {"Change graphic lib:", 80, 80, white, 25, "assets/arial.ttf", 0};
    this->_sprites["a"] = {100, 120, "assets/menu/a", (Arcade::SpriteRect_t) {0, 0, 59, 59, 0, 0}, white, black, 2};
    this->_sprites["z"] = {200, 120, "assets/menu/z", (Arcade::SpriteRect_t) {0, 0, 59, 59, 0, 0}, white, black, 2};
    this->_texts["games"] = {"Change game:", 550, 80, white, 25, "assets/arial.ttf", 0};
    this->_sprites["q"] = {550, 120, "assets/menu/q", (Arcade::SpriteRect_t) {0, 0, 59, 59, 0, 0}, white, black, 2};
    this->_sprites["s"] = {650, 120, "assets/menu/s", (Arcade::SpriteRect_t) {0, 0, 59, 59, 0, 0}, white, black, 2};
    this->_texts["menu"] = {"Return to menu:", 80, 290, white, 25, "assets/arial.ttf", 0};
    this->_sprites["b"] = {100, 330, "assets/menu/back", (Arcade::SpriteRect_t) {0, 0, 132, 59, 0, 0}, white, black, 2};
    this->_texts["quit"] = {"Quit the program:", 550, 290, white, 25, "assets/arial.ttf", 0};
    this->_sprites["e"] = {580, 330, "assets/menu/esc", (Arcade::SpriteRect_t) {0, 0, 59, 59, 0, 0}, white, black, 2};
    this->_texts["restart"] = {"Restart the game:", 340, 250, white, 25, "assets/arial.ttf", 0};
    this->_sprites["r"] = {360, 300, "assets/menu/r", (Arcade::SpriteRect_t) {0, 0, 59, 59, 0, 0}, white, black, 2};
}

void Games::MenuModule::handleEvents(std::vector<Arcade::KeyEvent_t> event)
{
    for (size_t i = 0; i < event.size(); i++) {
        if (this->_idxPage == 0) {
            if (event[i].key == Arcade::KeyState::Right) {
                this->_idxMenu += 1;
                this->changeCaseMenu();
            }
            if (event[i].key == Arcade::KeyState::Left) {
                this->_idxMenu -= 1;
                this->changeCaseMenu();
            }
            if (event[i].key == Arcade::KeyState::Up && this->_idxMenu < 5) {
                std::string news = "a";
                news[0] = this->_texts[this->_listMenu[this->_idxMenu]].text[0] + 1;
                news[0] = news[0] > 'Z' ? 'A' : news[0];
                this->_texts[this->_listMenu[this->_idxMenu]].text = news;
            }
            if (event[i].key == Arcade::KeyState::Down && this->_idxMenu < 5) {
                std::string news = "a";
                news[0] = this->_texts[this->_listMenu[this->_idxMenu]].text[0] - 1;
                news[0] = news[0] < 'A' ? 'Z' : news[0];
                this->_texts[this->_listMenu[this->_idxMenu]].text = news;
            }
            if (this->_idxMenu == 5 && event[i].key == Arcade::KeyState::Enter) {
                this->_idxPage = 1;
                this->saveName();
                this->changePageGame();
            }
        }
        if (this->_idxPage == 2 && event[i].key == Arcade::KeyState::Enter) {
            this->_idxPage = 1;
            this->changePageGame();
        }
        if (this->_idxPage != 0) {
            if (event[i].key == Arcade::KeyState::Down) {
                this->_idxMenu += 1;
                this->changeCaseMenu();
            }
            if (event[i].key == Arcade::KeyState::Up) {
                this->_idxMenu -= 1;
                this->changeCaseMenu();
            }
            if (this->_idxMenu == 2 && event[i].key == Arcade::KeyState::Enter) {
                this->_idxPage = 2;
                this->changePageHow();
            }
            if (this->_listGame.size() != 0 &&
            this->_listMenu[this->_idxMenu].compare("game") == 0) {
                if (event[i].key == Arcade::KeyState::Left) {
                    this->_idxGame -= 1;
                    this->changeSelectedGame();
                }
                if (event[i].key == Arcade::KeyState::Right) {
                    this->_idxGame += 1;
                    this->changeSelectedGame();
                }
            }
        }        
    }
}

std::unordered_map<std::string, Arcade::Rect_t> Games::MenuModule::getShapes()
{
    return (this->_shapes);
}

std::unordered_map<std::string, Arcade::Sprites_t> Games::MenuModule::getSprites()
{
    return (this->_sprites);
}

std::unordered_map<std::string, Arcade::Text_t> Games::MenuModule::getTexts()
{
    return (this->_texts);
}

void Games::MenuModule::update(void)
{

}

extern "C" {
    std::shared_ptr<Games::IGameModule> create(void)
    {
        return std::make_shared<Games::MenuModule>();
    }
}
