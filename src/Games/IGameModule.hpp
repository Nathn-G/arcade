/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** IGameModule.hpp
*/

#ifndef _I_GAME_MODULE_H_
    #define _I_GAME_MODULE_H_

    #include <vector>
    #include "../includes/Event.hpp"
    #include <iostream>
    #include <memory>
    #include <unordered_map>
    #include "../includes/Drawable.hpp"

namespace Games {
    class IGameModule {
        public:
            virtual ~IGameModule() = default;
            virtual std::unordered_map<std::string, Arcade::Rect_t> getShapes() = 0;
            virtual std::unordered_map<std::string, Arcade::Sprites_t> getSprites() = 0;
            virtual std::unordered_map<std::string, Arcade::Text_t> getTexts() = 0;
            virtual std::pair<int, int> getSizeWindow() = 0;
            virtual std::pair<int, int> getSizePixel() = 0;
            virtual void update(void) = 0;
            virtual void handleEvents(std::vector<Arcade::KeyEvent_t> event) = 0;
    };
}


#endif // _I_GAME_MODULE_H_*/
