/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** class DLEnc
*/

#ifndef __DLENC_HPP__
    #define __DLENC_HPP__

    #include <string>

class DLEnc {
    public:
        DLEnc();
        ~DLEnc();
        void *dlopen_enc(std::string name, int mode);
        void *dlsym_enc(void *handler, std::string name);
        int dlclose_enc(void *handler);
        std::string dlerror_enc();

};
#endif /* !__DLENC_HPP__ */
