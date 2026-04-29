#include <cassert>

#include "core/math_utils.hpp"

int main()
{
    assert(core::add(2, 2) == 4);
    assert(core::add(-2, 2) == 0);
    assert(core::add(0, 0) == 0);
    assert(core::add(-2, -3) == -5);

    return 0;
}
