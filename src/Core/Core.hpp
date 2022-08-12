/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** core of arcade
*/

#ifndef __CORE_HPP__
    #define __CORE_HPP__

    #include "../Librairies/IDisplayModule.hpp"
    #include "../Games/IGameModule.hpp"
    #include "Error.hpp"
    #include "DLLoader.hpp"
    #include <memory>
    #include <thread>
    #include <chrono>
    #include <cstdlib>
    #include <vector>
    #include <exception>
    #include <iostream>
    #include <map>
    #include <algorithm>
    #include <string_view>
    #include <ctime>

namespace Arcade {
    class Core {
        public:
            Core();
            ~Core();
            void initLib(std::string libName);
            void initGame(std::string gameName);
            void initloader(std::shared_ptr<DLLoader<Libs::IDisplayModule>> lib, std::shared_ptr<DLLoader<Games::IGameModule>> game);
            void runLoop();
            void changeLib(std::string lib);
            void changeGame(std::string lib);
            void loadGame(std::string game);
            void checkchangeGame();
            void handleEvents();
            void previousLib();
            void nextLib();
            void previousGame();
            void nextGame();
            void exitGame();
            void restartGame();
            void goMenu();
            void update();
            void draw();

        private:
            std::vector<std::shared_ptr<Libs::IDisplayModule>> _libs;
            std::shared_ptr<Libs::IDisplayModule> _lib;
            std::vector<std::shared_ptr<Games::IGameModule>> _games;
            std::shared_ptr<Games::IGameModule> _game;
            std::shared_ptr<DLLoader<Games::IGameModule>> _loaderG;
            std::shared_ptr<DLLoader<Libs::IDisplayModule>> _loaderL;
            size_t _idxLib;
            size_t _idxGame;
            size_t _idxMenu;
            size_t _idxMenuGame;
            size_t _idxMenuPage;
            std::vector<std::string> _listLib = { "lib/arcade_ncurses.so", 
            "lib/arcade_sdl2.so", "lib/arcade_ndk++.so", "lib/arcade_aalib.so",
            "lib/arcade_libcaca.so", "lib/arcade_allegro5.so", "lib/arcade_xlib.so",
            "lib/arcade_gtk+.so", "lib/arcade_sfml.so", "lib/arcade_irrlicht.so",
            "lib/arcade_opengl.so", "lib/arcade_vulkan.so", "lib/arcade_qt5.so"};
            std::vector<std::string> _listGame = { "lib/arcade_nibbler.so",
            "lib/arcade_pacman.so", "lib/arcade_qix.so", "lib/arcade_centipede.so",
            "lib/arcade_solarfox.so", "lib/arcade_menu.so"};
            clock_t lastUpdate;
    };
}


#endif /* !__CORE_HPP__ */
