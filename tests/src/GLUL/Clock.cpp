#include <gtest/gtest.h>

#include <GLUL/Clock.h>
#include <GLUL/Window.h>

#include <chrono>
#include <thread>


TEST(GLUL_Clock, Now_Notdecreasing) {
    auto time1 = GLUL::Clock::now();
    auto time2 = GLUL::Clock::now();

    ASSERT_TRUE(time1 <= time2);
}

TEST(GLUL_Clock, Get_Elapsed_With_Sleep) {
    GLUL::Clock clock;
    double t1, t2, t3;

    t1 = clock.getElapsedTime();
    t2 = clock.getElapsedTime();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    t3 = clock.getElapsedTime();

    ASSERT_TRUE(t1 <= t2);
    ASSERT_TRUE(t2 <= t3);
    ASSERT_TRUE(t3 - t2 >= 0.1);
}

TEST(GLUL_Clock, Reset) {
    GLUL::Clock clock;
    double t1, t2;

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    t1 = clock.getElapsedTime();
    clock.reset();
    t2 = clock.getElapsedTime();

    ASSERT_TRUE(t2 < t1);
}
