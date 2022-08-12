/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** IDisplayModule.hpp
*/

#ifndef _I_DISPLAY_MODULE_H_
    #define _I_DISPLAY_MODULE_H_

    #include <string>
    #include <memory>
    #include <vector>
    #include "../includes/Event.hpp"
    #include "../includes/Drawable.hpp"
    #include <unordered_map>

namespace Libs {
    class IDisplayModule {
        public:
            virtual void init(std::string name = "Unknown", int w = 800, int h = 600) = 0;
            virtual bool isOpen() const = 0;
            virtual void close() = 0;
            virtual void my_clear() const = 0;
            virtual void setBackgroundColor(int, int, int) = 0;
            virtual void display() const = 0;
            virtual void draw(std::unordered_map<std::string, Arcade::Rect_t> shapes, std::unordered_map<std::string, Arcade::Sprites_t> sprites, std::unordered_map<std::string, Arcade::Text_t> texts) = 0;
            virtual std::vector<Arcade::KeyEvent_t> getEvents() = 0;
            virtual void setSizePixel(std::pair<int, int> size) = 0;
            virtual void clearAssets() = 0;
            virtual void setSizeWindows(std::pair<int, int> size) = 0;
            virtual ~IDisplayModule() = default;
    };
}


#endif // _I_DISPLAY_MODULE_H_*/
