//
// Created by mango on 3/20/2020.
//

#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

int main() 
{
	plt::plot({ 1,3,2,4 });
	plt::show();
}