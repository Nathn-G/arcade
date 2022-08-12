/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** main.cpp
*/

#include "../Librairies/IDisplayModule.hpp"
#include "Core.hpp"

int main(int argc, char **argv)
{
    std::shared_ptr<DLLoader<Libs::IDisplayModule>> loader = std::make_shared<DLLoader<Libs::IDisplayModule>>();
    std::shared_ptr<DLLoader<Games::IGameModule>> loaderG = std::make_shared<DLLoader<Games::IGameModule>>();
    Arcade::Core core;

    if (argc != 2) {
        std::cout << "Usage: ./arcade [dynamic library file]" << std::endl;
        return (84);
    }
    core.initloader(loader, loaderG);
    try {
        core.initLib(std::string(argv[1]));
        core.initGame("lib/arcade_menu.so");
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
    core.runLoop();
    return 0;
}
