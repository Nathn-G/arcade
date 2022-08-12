/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** NCurses_MODULE.hpp
*/

#ifndef _NCURSES_MODULE_H_
    #define _NCURSES_MODULE_H_

    #include "../IDisplayModule.hpp"
    #include "../../Utils/File.hpp"
    #include <ncurses.h>
    #include <iostream>
    #include <map>
    #include <vector>
    #include <algorithm>
    #include "./NcursesEnc.hpp"

namespace Libs {
    std::map<int, Arcade::KeyState> mapEvent = {
        {KEY_LEFT, Arcade::KeyState::Left},
        {KEY_RIGHT, Arcade::KeyState::Right},
        {KEY_UP, Arcade::KeyState::Up},
        {KEY_DOWN, Arcade::KeyState::Down},
        {10, Arcade::KeyState::Enter},
        {27, Arcade::KeyState::Escape},
        {32, Arcade::KeyState::Space},
        {KEY_BACKSPACE, Arcade::KeyState::Return},
        {97, Arcade::KeyState::A},
        {98, Arcade::KeyState::B},
        {99, Arcade::KeyState::C},
        {100, Arcade::KeyState::D},
        {101, Arcade::KeyState::E},
        {102, Arcade::KeyState::F},
        {103, Arcade::KeyState::G},
        {104, Arcade::KeyState::H},
        {105, Arcade::KeyState::I},
        {106, Arcade::KeyState::J},
        {107, Arcade::KeyState::K},
        {108, Arcade::KeyState::L},
        {109, Arcade::KeyState::M},
        {110, Arcade::KeyState::N},
        {111, Arcade::KeyState::O},
        {112, Arcade::KeyState::P},
        {113, Arcade::KeyState::Q},
        {114, Arcade::KeyState::R},
        {115, Arcade::KeyState::S},
        {116, Arcade::KeyState::T},
        {117, Arcade::KeyState::U},
        {118, Arcade::KeyState::V},
        {119, Arcade::KeyState::W},
        {120, Arcade::KeyState::X},
        {121, Arcade::KeyState::Y},
        {122, Arcade::KeyState::Z},
    };

    class NCursesModule : public IDisplayModule {
        public:
            NCursesModule();
            ~NCursesModule();
            void init(std::string name, int w = 1920, int h = 1080);
            void my_clear() const;
            void display() const;
            void close();
            bool isOpen() const;
            void setBackgroundColor(int r, int g, int b);
            void draw(std::unordered_map<std::string, Arcade::Rect_t> shapes, std::unordered_map<std::string, Arcade::Sprites_t> sprites, std::unordered_map<std::string, Arcade::Text_t> texts);
            std::vector<Arcade::KeyEvent_t> getEvents();
            void setSizePixel(std::pair<int, int> size);
            void clearAssets();
            void setSizeWindows(std::pair<int, int> size);

        private:
            bool _is_open;
            WINDOW *window;
            float width, height;
            void drawShape(std::unordered_map<std::string, Arcade::Rect_t> shapes, size_t layer);
            void drawSprite(std::unordered_map<std::string, Arcade::Sprites_t> sprites, size_t layer);
            void drawText(std::unordered_map<std::string, Arcade::Text_t> texts, size_t layer);
            std::unordered_map<std::string, Arcade::Rect_t> _shapes;
            std::unordered_map<std::string, std::vector<std::string>> _sprites;
            std::vector<std::vector<int>> _colors;
            int getIndexColor(Arcade::Color_t first, Arcade::Color_t second);
            std::pair<int, int> _sizePixel;
            int setPixelPosition(int &y, int &x, int positionY, int positionX);
            void centerPixelPosition(int &y, int &x);
            NcursesEnc enc;
    };
}


#endif // _NCURSES_MODULE_H_*/
