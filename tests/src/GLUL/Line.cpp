#include <gtest/gtest.h>

#include <GLUL/Line.h>
#include <GLUL/Point.h>

#include <cmath>


TEST(GLUL_Line, Constructors) {
    GLUL::Line line1;
    GLUL::Line line2(GLUL::Point(1.0f, 1.0f), GLUL::Point(2.0f, 2.0f));
    GLUL::Line line3(glm::vec2(2.0f, 2.0f), glm::vec2(1.0f, 1.0f));
    GLUL::Line line4(line3);
    GLUL::Line line5;
    GLUL::Line line6;

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

TEST(GLUL_Line, Distance) {
    GLUL::Point point1(0.0f, 0.0f);
    GLUL::Point point2(1.0f, 0.0f);
    GLUL::Point point3(0.0f, 1.0f);
    GLUL::Point point4(2.0f, 5.0f);
    GLUL::Point point5(3.0f, 1.0f);

    GLUL::Line line1(point1, point2);
    GLUL::Line line2(point2, point3);
    GLUL::Line line3(point2, point4);
    GLUL::Line line4(point1, point5);

    ASSERT_FLOAT_EQ(5.09902f, static_cast<float>(line1.distance(point4)));
    ASSERT_FLOAT_EQ(2.236068f, static_cast<float>(line2.distance(point5)));
    ASSERT_FLOAT_EQ(1.7650452f, static_cast<float>(line3.distance(point5.getPosition())));
    ASSERT_FLOAT_EQ(0.0f, static_cast<float>(line4.distance(point1)));
}

TEST(GLUL_Line, Normals) {
    GLUL::Point point1(0.0f, 0.0f);
    GLUL::Point point2(1.0f, 0.0f);
    GLUL::Point point3(0.0f, 1.0f);
    GLUL::Point point4(2.0f, 5.0f);

    GLUL::Line line1(point1, point2);
    GLUL::Line line2(point2, point3);

    glm::vec2 normal1 = line1.getNormal();
    glm::vec2 normal2 = GLUL::Line::getNormal(line2);
    glm::vec2 normal3 = GLUL::Line::getNormal(point2.getPosition(), point4.getPosition());

    ASSERT_FLOAT_EQ(0.0f, normal1.x);
    ASSERT_FLOAT_EQ(1.0f, normal1.y);
    ASSERT_FLOAT_EQ(std::sqrt(2.0f) * 0.5f, normal2.x);
    ASSERT_FLOAT_EQ(std::sqrt(2.0f) * 0.5f, normal2.y);
    ASSERT_FLOAT_EQ(-0.98058069f, normal3.x);
    ASSERT_FLOAT_EQ(0.19611613f, normal3.y);
}

TEST(GLUL_Line, Reflected_Vectors) {
    GLUL::Point point1(0.0f, 0.0f);
    GLUL::Point point2(1.0f, 0.0f);
    GLUL::Point point3(0.0f, 1.0f);
    GLUL::Point point4(2.0f, 5.0f);

    GLUL::Line line1(point1, point2);
    GLUL::Line line2(point2, point3);
    GLUL::Line line3(point2, point4);

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

TEST(GLUL_Line, Set_Line_Equal_Points) {
    glm::vec2 pos(3.14f);
    GLUL::Line line;

    line.setLine(pos, pos);

    ASSERT_EQ(line.getPosition1(), pos);
    ASSERT_EQ(line.getPosition2(), pos);
}
