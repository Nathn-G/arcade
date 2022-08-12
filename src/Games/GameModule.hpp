/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** abstract class of IGameModule
*/

#ifndef __GAME_MODULE_HPP__
    #define __GAME_MODULE_HPP__

    #include "IGameModule.hpp"
    #include "../Utils/File.hpp"
    #include <vector>
    #include <iostream>
    #include <memory>

namespace Games {
    class GameModule : public IGameModule {
        public:
            virtual ~GameModule() = default;
            virtual void handleEvents(std::vector<Arcade::KeyEvent_t> event) = 0;
            virtual std::unordered_map<std::string, Arcade::Rect_t> getShapes() = 0;
            virtual std::unordered_map<std::string, Arcade::Sprites_t> getSprites() = 0;
            virtual std::unordered_map<std::string, Arcade::Text_t> getTexts() = 0;
            virtual std::pair<int, int> getSizeWindow() = 0;
            virtual std::pair<int, int> getSizePixel() = 0;
            virtual void update(void) = 0;

        protected:
            Arcade::SpriteRect_t createRect(int width, int height, int maxWidth, int maxHeight);
            Arcade::Color_t createColor(int r, int g, int b, int a);
            std::vector<Arcade::KeyEvent_t> _events;
            std::unordered_map<std::string, Arcade::Rect_t> _shapes;
            std::unordered_map<std::string, Arcade::Sprites_t> _sprites;
            std::unordered_map<std::string, Arcade::Text_t> _texts;
            int width;
            int height;
    };

    enum Dir {
        RIGHT,
        LEFT,
        UP,
        DOWN,
        UNKNOWN
    };
}

#endif /* !__GAME_MODULE_HPP__ */
