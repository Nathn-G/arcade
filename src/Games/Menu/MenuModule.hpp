/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** MenuModule.hpp
*/

#ifndef _I_MENU_MODULE_H_
    #define _I_MENU_MODULE_H_

    #include "../GameModule.hpp"

namespace Games {
    class MenuModule : public GameModule {
        public:
            MenuModule();
            ~MenuModule();
            void handleEvents(std::vector<Arcade::KeyEvent_t> event);
            std::unordered_map<std::string, Arcade::Rect_t> getShapes();
            std::unordered_map<std::string, Arcade::Sprites_t> getSprites();
            std::unordered_map<std::string, Arcade::Text_t> getTexts();
            std::pair<int, int> getSizeWindow();
            std::pair<int, int> getSizePixel();
            void update(void);

        private:
            std::vector<std::string> _listLib = { "lib/arcade_ncurses.so", 
            "lib/arcade_sdl2.so", "lib/arcade_ndk++.so", "lib/arcade_aalib.so",
            "lib/arcade_libcaca.so", "lib/arcade_allegro5.so", "lib/arcade_xlib.so",
            "lib/arcade_gtk+.so", "lib/arcade_sfml.so", "lib/arcade_irrlicht.so",
            "lib/arcade_opengl.so", "lib/arcade_vulkan.so", "lib/arcade_qt5.so"};
            std::vector<std::string> _listGame = { "lib/arcade_nibbler.so",
            "lib/arcade_pacman.so", "lib/arcade_qix.so", "lib/arcade_centipede.so",
            "lib/arcade_solarfox.so"};
            std::vector<std::string> _listMenu;
            int _idxMenu;
            int _idxGame;
            int _idxPage;
            void changeCaseMenu();
            void changeSelectedGame();
            void changePageGame();
            void changePageHow();
            void saveName();
    };
}

#endif // _I_MENU_MODULE_H_*/
