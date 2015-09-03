#include <gtest/gtest.h>

#include <Utils/Clock.h>
#include <Utils/Window.h>

#include <chrono>
#include <thread>


TEST(Utils_Clock, Now_Notdecreasing) {
    double time1, time2;

    Util::Window::initializeGLFW();
    time1 = Util::Clock::now();
    time2 = Util::Clock::now();

    ASSERT_TRUE(time1 <= time2);
}

TEST(Utils_Clock, Get_Elapsed_With_Sleep) {
    Util::Clock clock;
    double time1, time2, time3;

    Util::Window::initializeGLFW();
    time1 = clock.getElapsedTime();
    time2 = clock.getElapsedTime();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    time3 = clock.getElapsedTime();

    ASSERT_TRUE(time1 <= time2);
    ASSERT_TRUE(time2 <= time3);
    ASSERT_TRUE(time3 - time2 >= 0.045);
}

TEST(Utils_Clock, Reset) {
    Util::Clock clock;
    double time1, time2;

    Util::Window::initializeGLFW();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    time1 = clock.getElapsedTime();
    clock.reset();
    time2 = clock.getElapsedTime();

    ASSERT_TRUE(time2 < time1);
}
