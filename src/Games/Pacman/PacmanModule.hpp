/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** PacmanModule.hpp
*/

#ifndef _I_PACMAN_MODULE_H_
    #define _I_PACMAN_MODULE_H_

    #include "Player.hpp"
    #include "RandomGhost.hpp"
    #include "ChasingGhost.hpp"
    #include <cmath>

namespace Games {
    class PacmanModule : public GameModule {
        public:
            PacmanModule();
            ~PacmanModule();
            void handleEvents(std::vector<Arcade::KeyEvent_t> event);
            std::unordered_map<std::string, Arcade::Rect_t> getShapes();
            std::unordered_map<std::string, Arcade::Sprites_t> getSprites();
            std::unordered_map<std::string, Arcade::Text_t> getTexts();
            std::pair<int, int> getSizeWindow();
            std::pair<int, int> getSizePixel();
            void update(void);
            void restartGame(void);
            void destroyGame(void);
            void createMap();

        private:
            void addGhosts(int x, int y, int &indexGhost);
            std::vector<std::string> map;
            Player *player;
            std::vector<Ghost *> ghosts;
            int score;
            clock_t lastUpdate;
            void checkHighScore();
    };
}

#endif // _I_PACMAN_MODULE_H_*/
