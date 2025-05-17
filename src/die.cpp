#include "die.h"
#include <ctime>
#include <cstdlib>

int Die::roll()
{
    return rand() % 6 + 1;
}

void Die::set()
{
    std::srand(std::time(0));
}