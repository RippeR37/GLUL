#include <gtest/gtest.h>

#include <Utils/Point.h>

#include <cmath>


TEST(Utils_Point, Constructor_Default) {
    Util::Point point;

    ASSERT_EQ(0.0f, point.getX());
    ASSERT_EQ(0.0f, point.getY());
    ASSERT_EQ(glm::vec2(0.0f, 0.0f), point.getPosition());
}

TEST(Utils_Point, Constructor_Parameterized) {
    float x = 3.13f;
    float y = 0.33f;
    glm::vec2 vec = glm::vec2(x, y);

    Util::Point point1(x, y);
    Util::Point point2(vec);

    ASSERT_EQ(x, point1.getX());
    ASSERT_EQ(y, point1.getY());
    ASSERT_EQ(x, point2.getX());
    ASSERT_EQ(y, point2.getY());
}

TEST(Utils_Point, Constructor_Copy) {
    glm::vec2 vec(12.34f, 56.78f);
    Util::Point point_org(vec);

    Util::Point point_cpy(point_org);
    point_org.setPoint(glm::vec2(0.0f));

    ASSERT_EQ(glm::vec2(0.0f), point_org.getPosition());
    ASSERT_EQ(vec, point_cpy.getPosition());
}

TEST(Utils_Point, Operator_Assignment) {
    glm::vec2 vec(12.34f, 56.78f);
    Util::Point point_org(vec);

    Util::Point point1 = point_org;
    Util::Point point2 = vec;

    ASSERT_EQ(vec, point1.getPosition());
    ASSERT_EQ(vec, point2.getPosition());
}

TEST(Utils_Point, Getters_Same_Value) {
    glm::vec2 vec(123.45f, 67.890f);
    Util::Point point(vec);
    
    ASSERT_EQ(vec, point.getPosition());
    ASSERT_EQ(point.getX(), point.getPosition().x);
    ASSERT_EQ(point.getY(), point.getPosition().y);
    ASSERT_EQ(glm::vec2(point.getX(), point.getY()), point.getPosition());
}

TEST(Utils_Point, Setters) {
    glm::vec2 oldPosition(111.222f, 333.444f);
    glm::vec2 newPosition(321.123f, 654.456f);
    Util::Point point1;
    Util::Point point2(oldPosition);
    Util::Point point3(point2);

    point1.setPoint(point2);
    point2.setPoint(newPosition);
    point3.setPoint(newPosition.x, newPosition.y);

    ASSERT_EQ(oldPosition, point1.getPosition());
    ASSERT_EQ(newPosition, point2.getPosition());
    ASSERT_EQ(newPosition, point3.getPosition());
}

TEST(Utils_Point, Distance_Point) {
    const double DOUBLE_EPSILON = 0.0000001;
    Util::Point point1(1.0f, 1.0f);
    Util::Point point2(2.0f, 1.0f);
    Util::Point point3(1.0f, 3.0f);

    double dist12 = 1.0;
    double dist13 = 2.0;
    double dist23 = std::sqrt(5.0);
    
    ASSERT_EQ(point1.distance(point2), point2.distance(point1));
    ASSERT_EQ(point1.distance(point3), point3.distance(point1));
    ASSERT_EQ(point2.distance(point3), point3.distance(point2));
    ASSERT_LE(std::abs(point1.distance(point2) - dist12), DOUBLE_EPSILON);
    ASSERT_LE(std::abs(point1.distance(point3) - dist13), DOUBLE_EPSILON);
    ASSERT_LE(std::abs(point2.distance(point3) - dist23), DOUBLE_EPSILON);
}

TEST(Utils_Point, Distance_Line) {
    // TODO: add test for computing distance between point and line

    ASSERT_TRUE(true);
}
