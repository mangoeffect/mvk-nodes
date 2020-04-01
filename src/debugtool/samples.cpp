//
// Created by mango on 3/20/2020.
//

#include "plot.h"

#include <iostream>

int main()
{
    std::vector<int> x(500);
    std::vector<int> y(500);
    for (int i = 0; i < 500; ++i)
    {
        x.at(i) = i;
        y.at(i) = 50 + x.at(i);
    }

    mv::Plot(x, y, "y = x + 50");
    return 0;
}