/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** DLEnc
*/

#include "DLEnc.hpp"
#include <dlfcn.h>

DLEnc::DLEnc()
{
}

DLEnc::~DLEnc()
{
}

void *DLEnc::dlopen_enc(std::string name, int mode)
{
    return dlopen(name.c_str(), mode);
}

void *DLEnc::dlsym_enc(void *handler, std::string name)
{
    return dlsym(handler, name.c_str());
}

int DLEnc::dlclose_enc(void *handler)
{
    return dlclose(handler);
}

std::string DLEnc::dlerror_enc()
{
    return std::string(dlerror());
}