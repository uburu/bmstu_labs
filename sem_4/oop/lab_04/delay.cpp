#include "delay.h"

#include <thread>
#include <chrono>

void delay(size_t ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
