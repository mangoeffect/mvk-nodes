
/**
 * @file openmp_version.cpp
 * @author mango (2321544362@qq.com)
 * @brief 输出openmp版本
 * @version 0.1
 * @date 2022-04-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <unordered_map>
#include <iostream>
#include <omp.h>

int main(int argc, char *argv[])
{
  std::unordered_map<unsigned,std::string> map{ {200505,"2.5"},{200805,"3.0"},{201107,"3.1"},{201307,"4.0"},{201511,"4.5"},{201811,"5.0"},{202011,"5.1"} };
  std::cout << "We have OpenMP " << map.at(_OPENMP) << ".\n";
  return 0;
}