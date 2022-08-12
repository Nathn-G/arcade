/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** DLLoader
*/

#ifndef __DLLOADER_HPP__
    #define __DLLOADER_HPP__

    #include <string>
    #include <memory>
    #include <iostream>
    #include "DLEnc.hpp"
    #include <dlfcn.h>
    #include <vector>

template<typename T>
class DLLoader {
    public:
        DLLoader() {}
        ~DLLoader()
        {
            closeInstance();
        }

        std::shared_ptr<T> getInstance(std::string lib)
        {
            std::shared_ptr<T> (*func)(void);

            if (_handler != NULL) {
                closeInstance();
            }
            _handler = _dl.dlopen_enc(lib, RTLD_LAZY);
            if (_handler == NULL) {
                throw Error(_dl.dlerror_enc());
                return NULL;
            }
            func = reinterpret_cast<std::shared_ptr<T> (*)()> (_dl.dlsym_enc(_handler, "create"));
            if (func == NULL) {
                _dl.dlclose_enc(_handler);
                throw Error(_dl.dlerror_enc());
                return NULL;
            }
            return func();
        }

        std::shared_ptr<T> getInstanceList(std::string lib)
        {
            std::shared_ptr<T> (*func)(void);

            void *h = _dl.dlopen_enc(lib, RTLD_LAZY);
            if (h == NULL) {
                throw Error(_dl.dlerror_enc());
                return NULL;
            }
            func = reinterpret_cast<std::shared_ptr<T> (*)()> (_dl.dlsym_enc(h, "create"));
            if (func == NULL) {
                _dl.dlclose_enc(h);
                throw Error(_dl.dlerror_enc());
                return NULL;
            }
            this->_listHandler.push_back(h);
            return func();
        }

        void closeInstance()
        {
            if (_handler != NULL)
                _dl.dlclose_enc(_handler);
            _handler = NULL;
        }

        void *getHandler()
        {
            return _handler;
        }

    private:
        void *_handler = NULL;
        std::vector<void *> _listHandler;
        DLEnc _dl;
};

#endif /* !__DLLOADER_HPP__ */
