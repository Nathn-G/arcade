/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** SDL2_MODULE.hpp
*/

#ifndef _SDL2_MODULE_H_
    #define _SDL2_MODULE_H_

    #include "../IDisplayModule.hpp"
    #include <SDL2/SDL.h>
    #include "SDL2/SDL_ttf.h"
    #include "SDL2/SDL_image.h"
    #include <map>
    #include <iostream>

namespace Libs {
    std::map<int, Arcade::KeyState> mapEvent = {
        {SDLK_LEFT, Arcade::KeyState::Left},
        {SDLK_RIGHT, Arcade::KeyState::Right},
        {SDLK_UP, Arcade::KeyState::Up},
        {SDLK_DOWN, Arcade::KeyState::Down},
        {SDLK_RETURN, Arcade::KeyState::Enter},
        {SDL_QUIT, Arcade::KeyState::Escape},
        {SDLK_ESCAPE, Arcade::KeyState::Escape},
        {SDLK_BACKSPACE, Arcade::KeyState::Return},
        {SDLK_SPACE, Arcade::KeyState::Space},
        {SDLK_a, Arcade::KeyState::A},
        {SDLK_b, Arcade::KeyState::B},
        {SDLK_c, Arcade::KeyState::C},
        {SDLK_d, Arcade::KeyState::D},
        {SDLK_e, Arcade::KeyState::E},
        {SDLK_f, Arcade::KeyState::F},
        {SDLK_g, Arcade::KeyState::G},
        {SDLK_h, Arcade::KeyState::H},
        {SDLK_i, Arcade::KeyState::I},
        {SDLK_j, Arcade::KeyState::J},
        {SDLK_k, Arcade::KeyState::K},
        {SDLK_l, Arcade::KeyState::L},
        {SDLK_m, Arcade::KeyState::M},
        {SDLK_n, Arcade::KeyState::N},
        {SDLK_o, Arcade::KeyState::O},
        {SDLK_p, Arcade::KeyState::P},
        {SDLK_q, Arcade::KeyState::Q},
        {SDLK_r, Arcade::KeyState::R},
        {SDLK_s, Arcade::KeyState::S},
        {SDLK_t, Arcade::KeyState::T},
        {SDLK_u, Arcade::KeyState::U},
        {SDLK_v, Arcade::KeyState::V},
        {SDLK_w, Arcade::KeyState::W},
        {SDLK_x, Arcade::KeyState::X},
        {SDLK_y, Arcade::KeyState::Y},
        {SDLK_z, Arcade::KeyState::Z},
    };

    class SDL2Module : public IDisplayModule {
        private:
            SDL_Window *window;
            SDL_Renderer *renderer;
            bool _is_open;
            void drawShape(std::unordered_map<std::string, Arcade::Rect_t> shapes, size_t layer);
            void drawSprite(std::unordered_map<std::string, Arcade::Sprites_t> sprites, size_t layer);
            void drawText(std::unordered_map<std::string, Arcade::Text_t> texts, size_t layer);
            std::unordered_map<std::string, SDL_Rect> _shapes;
            std::unordered_map<std::string, SDL_Texture *> _textures;
            std::unordered_map<std::string, TTF_Font *> _fonts;
            SDL_Texture *createText(Arcade::Text_t text, TTF_Font *font);
            void drawTexture(Arcade::SpriteRect_t rect, SDL_Texture *texture, int x, int y);
            std::map<int, bool> keyPressed;
            bool isKeyGameLib(int keyCode);
            std::pair<int, int> _sizePixel;
            

        public:
            SDL2Module();
            ~SDL2Module();
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
    };
}

#endif // _SDL2_MODULE_H_*/
