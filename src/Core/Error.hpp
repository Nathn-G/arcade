/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** class error
*/

#ifndef __ERROR_HPP__
    #define __ERROR_HPP__

    #include <string>

class Error : public std::exception {
    public:
        Error(std::string message);
        const char *what() const noexcept override;
    
    private:
        std::string _message;
};
#endif /* !__ERROR_HPP__ */
