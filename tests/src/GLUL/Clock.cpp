#include <gtest/gtest.h>

#include <GLUL/Clock.h>
#include <GLUL/Window.h>

#include <chrono>
#include <thread>


TEST(GLUL_Clock, Now_Notdecreasing) {
    double time1, time2;

    GLUL::Window::initializeGLFW();
    time1 = GLUL::Clock::now();
    time2 = GLUL::Clock::now();

    ASSERT_TRUE(time1 <= time2);
}

TEST(GLUL_Clock, Get_Elapsed_With_Sleep) {
    GLUL::Clock clock;
    double time1, time2, time3;

    GLUL::Window::initializeGLFW();
    time1 = clock.getElapsedTime();
    time2 = clock.getElapsedTime();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    time3 = clock.getElapsedTime();

    ASSERT_TRUE(time1 <= time2);
    ASSERT_TRUE(time2 <= time3);
    ASSERT_TRUE(time3 - time2 >= 0.05);
}

TEST(GLUL_Clock, Reset) {
    GLUL::Clock clock;
    double time1, time2;

    GLUL::Window::initializeGLFW();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    time1 = clock.getElapsedTime();
    clock.reset();
    time2 = clock.getElapsedTime();

    ASSERT_TRUE(time2 < time1);
}
