/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** NibblerModule.hpp
*/

#ifndef _I_NIBBLER_MODULE_H_
    #define _I_NIBBLER_MODULE_H_

    #include "../GameModule.hpp"
    #include "Snake.hpp"

namespace Games {
    class NibblerModule : public GameModule {
        public:
            NibblerModule();
            ~NibblerModule();
            void handleEvents(std::vector<Arcade::KeyEvent_t> event);
            std::unordered_map<std::string, Arcade::Rect_t> getShapes();
            std::unordered_map<std::string, Arcade::Sprites_t> getSprites();
            std::unordered_map<std::string, Arcade::Text_t> getTexts();
            std::pair<int, int> getSizeWindow();
            std::pair<int, int> getSizePixel();
            void update(void);
            void createMap(void);
            void destroyGame();
            void restartGame();

        private:
            std::vector<std::string> map;
            std::vector<std::pair<int, int>> emptyPos;
            int score;
            Snake *snake;
            clock_t lastUpdate;
            float timeUpdate;
            float timeBoost;
            clock_t clockBoost;
    };
}


#endif // _I_NIBBLER_MODULE_H_*/
