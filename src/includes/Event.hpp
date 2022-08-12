/*
** EPITECH PROJECT, 2021
** B-OOP-400-MPL-4-1-arcade-mathis.lorenzo
** File description:
** Event header
*/

#ifndef __EVENT_HPP__
    #define __EVENT_HPP__

namespace Arcade {
    enum KeyState {
        Unknown = -1,
        MouseClick,
        Left,
        Right,
        Up,
        Down,
        Enter,
        Escape,
        Return,
        Space,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
    };

    typedef struct KeyEvent_s {
        float x;
        float y;
        KeyState key;
    } KeyEvent_t;
}

#endif // __EVENT_HPP__ */