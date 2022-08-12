/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** methods of class Error
*/

#include "Error.hpp"

Error::Error(std::string message)
{
    _message = message;
}

const char *Error::what() const noexcept
{
    return _message.c_str();
}

