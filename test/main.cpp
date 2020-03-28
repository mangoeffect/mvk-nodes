#include "gtest/gtest.h"
#include <opencvinfo.h>
int main(int argc, char *argv[]) {
//  ::testing::InitGoogleTest(&argc, argv);
//  return RUN_ALL_TESTS();
  mv::OpenCVInfo op;
  op.Print();
  return 0;
}
