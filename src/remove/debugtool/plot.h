//
// Created by $mango on 4/1/2020.
//

#ifndef MACHINE_VISION_LIBRARY_PLOT_H
#define MACHINE_VISION_LIBRARY_PLOT_H

#include "opencv2/opencv.hpp"

namespace mvp
{
    // y = f(x), (x,y)
    void Plot(const std::vector<int>& x, const std::vector<int>& y, const std::string& title = "Figure1");
};//namespace mvp
#endif //MACHINE_VISION_LIBRARY_PLOT_H
