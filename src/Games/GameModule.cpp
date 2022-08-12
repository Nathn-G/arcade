/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** game module methods
*/

#include "GameModule.hpp"

void Games::GameModule::handleEvents(std::vector<Arcade::KeyEvent_t> event)
{

}

void Games::GameModule::update(void)
{

}

Arcade::SpriteRect_t Games::GameModule::createRect(int width, int height, int maxWidth, int maxHeight)
{
    Arcade::SpriteRect_t rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;
    rect.maxW = maxWidth;
    rect.maxH = maxHeight;
    return rect;
}

Arcade::Color_t Games::GameModule::createColor(int r, int g, int b, int a)
{
    Arcade::Color_t color;

    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    return color;
}

//update text in sdl2