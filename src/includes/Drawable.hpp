/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Drawable
*/

#ifndef __DRAWABLE_HPP__
    #define __DRAWABLE_HPP__

    #include <string>

namespace Arcade {
    typedef struct Color_s {
        int r, g, b, a;
    } Color_t;

    typedef struct Rect_s {
        int x, y, w, h;
        Color_t bg;
        size_t layer;
    } Rect_t;

    typedef struct SpriteRect_s {
        int x, y, w, h;
        int maxW, maxH;
    } SpriteRect_t;

    typedef struct Sprites_s {
        int x, y;
        std::string path;
        SpriteRect_t rect;
        Color_t text;
        Color_t bg;
        size_t layer;
    } Sprites_t;

    typedef struct Text_s {
        std::string text;
        int x, y;
        Color_t colorText;
        unsigned int size;
        std::string font;
        size_t layer;
    } Text_t;
}


#endif /* !__DRAWABLE_HPP__ */
