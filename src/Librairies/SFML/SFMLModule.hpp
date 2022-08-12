/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** SFML_MODULE.hpp
*/

#ifndef _SFML_MODULE_H_
    #define _SFML_MODULE_H_

    #include "../IDisplayModule.hpp"
    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>
    #include <SFML/System.hpp>
    #include <iostream>

namespace Libs {
    std::map<int, Arcade::KeyState> mapEvent = {
        {sf::Keyboard::Left, Arcade::KeyState::Left},
        {sf::Keyboard::Right, Arcade::KeyState::Right},
        {sf::Keyboard::Up, Arcade::KeyState::Up},
        {sf::Keyboard::Down, Arcade::KeyState::Down},
        {sf::Keyboard::Enter, Arcade::KeyState::Enter},
        {sf::Keyboard::Escape, Arcade::KeyState::Escape},
        {sf::Keyboard::BackSpace, Arcade::KeyState::Return},
        {sf::Keyboard::Space, Arcade::KeyState::Space},
        {sf::Keyboard::A, Arcade::KeyState::A},
        {sf::Keyboard::B, Arcade::KeyState::B},
        {sf::Keyboard::C, Arcade::KeyState::C},
        {sf::Keyboard::D, Arcade::KeyState::D},
        {sf::Keyboard::E, Arcade::KeyState::E},
        {sf::Keyboard::F, Arcade::KeyState::F},
        {sf::Keyboard::G, Arcade::KeyState::G},
        {sf::Keyboard::H, Arcade::KeyState::H},
        {sf::Keyboard::I, Arcade::KeyState::I},
        {sf::Keyboard::J, Arcade::KeyState::J},
        {sf::Keyboard::K, Arcade::KeyState::K},
        {sf::Keyboard::L, Arcade::KeyState::L},
        {sf::Keyboard::M, Arcade::KeyState::M},
        {sf::Keyboard::N, Arcade::KeyState::N},
        {sf::Keyboard::O, Arcade::KeyState::O},
        {sf::Keyboard::P, Arcade::KeyState::P},
        {sf::Keyboard::Q, Arcade::KeyState::Q},
        {sf::Keyboard::R, Arcade::KeyState::R},
        {sf::Keyboard::S, Arcade::KeyState::S},
        {sf::Keyboard::T, Arcade::KeyState::T},
        {sf::Keyboard::U, Arcade::KeyState::U},
        {sf::Keyboard::V, Arcade::KeyState::V},
        {sf::Keyboard::W, Arcade::KeyState::W},
        {sf::Keyboard::X, Arcade::KeyState::X},
        {sf::Keyboard::Y, Arcade::KeyState::Y},
        {sf::Keyboard::Z, Arcade::KeyState::Z},
    };

    class SFMLModule : public IDisplayModule {
        public:
            SFMLModule();
            ~SFMLModule();
            void init(std::string name, int w, int h);
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
            void drawShape(std::unordered_map<std::string, Arcade::Rect_t> shapes, size_t layer);
            void drawSprite(std::unordered_map<std::string, Arcade::Sprites_t> sprites, size_t layer);
            void drawText(std::unordered_map<std::string, Arcade::Text_t> texts, size_t layer);
            bool isKeyGameLib(int keyCode);
            sf::RenderWindow *_window;
            sf::Event _event;
            sf::Color color = sf::Color::Black;
            std::unordered_map<std::string, sf::RectangleShape> _shapes;
            std::unordered_map<std::string, sf::Sprite> _sprites;
            std::unordered_map<std::string, sf::Texture> _textures;
            std::unordered_map<std::string, sf::Text> _texts;
            std::unordered_map<std::string, sf::Font> _fonts;
            std::map<int, bool> keyPressed;
            std::pair<int, int> _sizePixel;
    };
}

#endif // _SFML_MODULE_H_*/
