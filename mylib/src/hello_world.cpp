#include "mylib/hello_world.h"

#include <print>

namespace mylib {

auto hello_world() -> void {
    std::println("Hello, world!");
}

} // namespace mylib
