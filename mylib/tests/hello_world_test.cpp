#include "mylib/hello_world.h"

#include <gtest/gtest.h>

TEST(MyLib, HelloWorldTest) {
    mylib::hello_world();
    SUCCEED();
}
