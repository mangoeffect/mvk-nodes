//
// Created by mango on 2024/2/26.
//

#ifndef MANGO_TEST_HELPER_H
#define MANGO_TEST_HELPER_H

#include <cstring>
#include <fstream>

bool IsFileExists(std::string& name)
{
    std::ifstream f(name.c_str());
    return f.good();
}

bool IsFileExists(const char* name)
{
    std::ifstream f(name);
    return f.good();
}

#endif //MANGO_TEST_HELPER_H
