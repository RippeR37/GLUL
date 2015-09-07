#include <gtest/gtest.h>

#include <Utils/Line.h>
#include <Utils/Point.h>

#include <cmath>


TEST(Utils_Line, Constructors) {
    Util::Line line1;
    Util::Line line2(Util::Point(1.0f, 1.0f), Util::Point(2.0f, 2.0f));
    Util::Line line3(glm::vec2(2.0f, 2.0f), glm::vec2(1.0f, 1.0f));
    Util::Line line4(line3);
    Util::Line line5;
    Util::Line line6;

    line5 = line4;
    line6.setLine(line5);

    glm::vec2 vec_0(0.0f, 0.0f);
    glm::vec2 vec_1(1.0f, 1.0f);
    glm::vec2 vec_2(2.0f, 2.0f);

    ASSERT_EQ(vec_0, line1.getPoint1().getPosition());
    ASSERT_EQ(vec_1, line1.getPoint2().getPosition());
    
    ASSERT_EQ(vec_1, line2.getPoint1().getPosition());
    ASSERT_EQ(vec_2, line2.getPoint2().getPosition());
    
    ASSERT_EQ(vec_1, line3.getPoint1().getPosition());
    ASSERT_EQ(vec_2, line3.getPoint2().getPosition());

    ASSERT_EQ(vec_1, line4.getPoint1().getPosition());
    ASSERT_EQ(vec_2, line4.getPoint2().getPosition());

    ASSERT_EQ(vec_1, line5.getPoint1().getPosition());
    ASSERT_EQ(vec_2, line5.getPoint2().getPosition());

    ASSERT_EQ(vec_1, line6.getPoint1().getPosition());
    ASSERT_EQ(vec_2, line6.getPoint2().getPosition());
}

TEST(Utils_Line, Distance) {
    Util::Point point1(0.0f, 0.0f);
    Util::Point point2(1.0f, 0.0f);
    Util::Point point3(0.0f, 1.0f);
    Util::Point point4(2.0f, 5.0f);
    Util::Point point5(3.0f, 1.0f);

    Util::Line line1(point1, point2);
    Util::Line line2(point2, point3);
    Util::Line line3(point2, point4);
    Util::Line line4(point1, point5);

    ASSERT_FLOAT_EQ(5.09902f, static_cast<float>(line1.distance(point4)));
    ASSERT_FLOAT_EQ(2.236068f, static_cast<float>(line2.distance(point5)));
    ASSERT_FLOAT_EQ(1.7650452f, static_cast<float>(line3.distance(point5.getPosition())));
    ASSERT_FLOAT_EQ(0.0f, static_cast<float>(line4.distance(point1)));
}

TEST(Utils_Line, Normals) {
    Util::Point point1(0.0f, 0.0f);
    Util::Point point2(1.0f, 0.0f);
    Util::Point point3(0.0f, 1.0f);
    Util::Point point4(2.0f, 5.0f);

    Util::Line line1(point1, point2);
    Util::Line line2(point2, point3);

    glm::vec2 normal1 = line1.getNormal();
    glm::vec2 normal2 = Util::Line::getNormal(line2);
    glm::vec2 normal3 = Util::Line::getNormal(point2.getPosition(), point4.getPosition());

    ASSERT_FLOAT_EQ(0.0f, normal1.x);
    ASSERT_FLOAT_EQ(1.0f, normal1.y);
    ASSERT_FLOAT_EQ(std::sqrt(2.0f) * 0.5f, normal2.x);
    ASSERT_FLOAT_EQ(std::sqrt(2.0f) * 0.5f, normal2.y);
    ASSERT_FLOAT_EQ(-0.98058069f, normal3.x);
    ASSERT_FLOAT_EQ(0.19611613f, normal3.y);
}

TEST(Utils_Line, Reflected_Vectors) {
    Util::Point point1(0.0f, 0.0f);
    Util::Point point2(1.0f, 0.0f);
    Util::Point point3(0.0f, 1.0f);
    Util::Point point4(2.0f, 5.0f);

    Util::Line line1(point1, point2);
    Util::Line line2(point2, point3);
    Util::Line line3(point2, point4);

    glm::vec2 inputVec1(2.0f, 3.0f);
    glm::vec2 inputVec2(1.0f, 3.5f);

    glm::vec2 reflected1 = line1.getReflectedVector(inputVec1);
    glm::vec2 reflected2 = line2.getReflectedVector(inputVec2);
    glm::vec2 reflected3 = line3.getReflectedVector(inputVec2);

    ASSERT_FLOAT_EQ( 0.5547002f, reflected1.x);
    ASSERT_FLOAT_EQ(-0.83205032f, reflected1.y);
    ASSERT_FLOAT_EQ(-0.96152389f, reflected2.x);
    ASSERT_FLOAT_EQ(-0.27472115f, reflected2.y);
    ASSERT_FLOAT_EQ( 0.11622813f, reflected3.x);
    ASSERT_FLOAT_EQ( 0.99322248f, reflected3.y);
}
