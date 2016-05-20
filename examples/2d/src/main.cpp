#include <GLUL/Logger.h>
#include <GLUL/GUI/Window.h>
#include <GLUL/G2D/Circle.h>
#include <GLUL/G2D/Disk.h>
#include <GLUL/G2D/Line.h>
#include <GLUL/G2D/LineLoop.h>
#include <GLUL/G2D/Point.h>
#include <GLUL/G2D/Triangle.h>
#include <GLUL/G2D/TriangleStrip.h>
#include <GLUL/G2D/Quad.h>
#include <GLUL/G2D/Ring.h>


void test_point() {
    static GLUL::G2D::Point p1 { {  40.0f, 500.0f },  5 };
    static GLUL::G2D::Point p2 { {  70.0f, 550.0f }, 10 };
    static GLUL::G2D::Point p3 { { 100.0f, 500.0f },  5 };
    static GLUL::G2D::GeometryBatch batch { p1, p2, p3 };

    batch.render();
}

void test_lines() {
    static GLUL::G2D::Line l1 { { 150.0f, 500.0f }, { 150.0f, 560.0f } };
    static GLUL::G2D::Line l2 { { 170.0f, 480.0f }, { 250.0f, 480.0f }, 2u };
    static GLUL::G2D::Line l3 { { 170.0f, 580.0f }, { 250.0f, 580.0f }, 3u };
    static GLUL::G2D::Line l4 { { 270.0f, 560.0f }, { 270.0f, 500.0f }, 4u };
    static GLUL::G2D::Line l5 { { 170.0f, 560.0f }, { 250.0f, 500.0f }, 5u };
    static GLUL::G2D::GeometryBatch batch { l1, l2, l3, l4, l5 };

    batch.render();
}

void test_triangles() {
    static GLUL::G2D::Point p1 { { 350.0f, 490.0f } }; p1.setColor({ 1.0f, 0.0f, 0.0f, 1.0f });
    static GLUL::G2D::Point p2 { { 400.0f, 565.0f } }; p2.setColor({ 0.0f, 1.0f, 0.0f, 1.0f });
    static GLUL::G2D::Point p3 { { 450.0f, 490.0f } }; p3.setColor({ 0.0f, 0.0f, 1.0f, 1.0f });
    static GLUL::G2D::Triangle t { p1, p2, p3 };
    static GLUL::G2D::GeometryBatch batch { t };

    batch.render();
}

void test_line_loops() {
    static GLUL::G2D::Point p1 { { 500.0f, 490.0f } };
    static GLUL::G2D::Point p2 { { 550.0f, 565.0f } };
    static GLUL::G2D::Point p3 { { 600.0f, 490.0f } };
    static GLUL::G2D::LineLoop ll { { p1, p2, p3 } };
    static GLUL::G2D::GeometryBatch batch { ll };

    batch.render();
}

void test_triangle_strips() {
    static GLUL::G2D::Point p1 { { 650.0f, 555.0f } };
    static GLUL::G2D::Point p2 { { 650.0f, 505.0f } };
    static GLUL::G2D::Point p3 { { 680.0f, 565.0f } };
    static GLUL::G2D::Point p4 { { 680.0f, 515.0f } };
    static GLUL::G2D::Point p5 { { 710.0f, 545.0f } };
    static GLUL::G2D::Point p6 { { 710.0f, 495.0f } };
    static GLUL::G2D::Point p7 { { 740.0f, 555.0f } };
    static GLUL::G2D::Point p8 { { 740.0f, 505.0f } };
    static GLUL::G2D::TriangleStrip ts { { p1, p2, p3, p4, p5, p6, p7, p8 } };
    static GLUL::G2D::GeometryBatch batch { ts };

    batch.render();
}

void test_no_batch() {
    static GLUL::G2D::Triangle triangle {
        glm::vec2 {  40.0f, 400.0f },
        glm::vec2 {  70.0f, 460.0f },
        glm::vec2 { 100.0f, 400.0f }
    };

    static GLUL::G2D::Quad quad {
        glm::vec2 { 170.0f, 460.0f },
        glm::vec2 { 250.0f, 460.0f },
        glm::vec2 { 225.0f, 400.0f },
        glm::vec2 { 145.0f, 400.0f }
    };

    triangle.setColor({ 0.3f, 0.8f, 0.5f, 1.0f });
    triangle.render();

    quad.setColor({ 0.5f, 0.3f, 0.8f, 1.0f });
    quad.render();
}

void test_circles() {
    static GLUL::G2D::Circle c1 { glm::vec2 { 430.0f, 440.0f }, 40.0f }; c1.setColor({ 0.7f, 0.2f, 0.7f, 1.0f });
    static GLUL::G2D::Circle c2 { glm::vec2 { 325.0f, 440.0f }, 30.0f }; c2.setColor({ 0.2f, 0.5f, 0.9f, 1.0f });
    static GLUL::G2D::Circle c3 { glm::vec2 { 550.0f, 400.0f }, 70.0f }; c3.setColor({ 1.0f, 0.7f, 0.0f, 1.0f });
    static GLUL::G2D::GeometryBatch batch { c1, c2, c3 };

    batch.render();
}

void test_rings_disks() {
    static GLUL::G2D::Ring r1 { glm::vec2 { 430.0f, 350.0f }, 30.0f, 40.0f }; r1.setColor({ 0.7f, 0.2f, 0.7f, 1.0f });
    static GLUL::G2D::Ring r2 { glm::vec2 { 325.0f, 350.0f }, 15.0f, 30.0f }; r2.setColor({ 0.2f, 0.5f, 0.9f, 1.0f });
    static GLUL::G2D::Disk d1 { glm::vec2 { 700.0f, 400.0f }, 35.0f, 70.0f };

    d1.setInnerColor({ 0.2f, 0.2f, 0.2f, 1.0f });
    d1.setOuterColor({ 1.0f, 0.7f, 0.0f, 1.0f });

    static GLUL::G2D::GeometryBatch batch { r1, r2, d1 };

    batch.render();
}

void run() {
    GLUL::GUI::Window window { 800, 600, "2D example" };

    window.create();
    window.getContext().setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

    while(window.isCreated() && !window.shouldClose()) {
        window.getContext().clearBuffers(GL::Context::BufferMask::Color);

        test_point();
        test_lines();
        test_triangles();
        test_line_loops();
        test_triangle_strips();
        test_no_batch();
        test_circles();
        test_rings_disks();

        window.render();
        window.update();
    }
}

int main() {
    try {
        run();

    } catch(const GLUL::Exception::FatalError& exception) {
        GLUL::Log::Stream("Example", "logExample.log") << "Cought fatal error exception: " + std::string(exception.what());
        return 1;

    } catch(const std::exception& exception) {
        GLUL::Log::Stream("Example", "logExample.log") << "Cought std::exception: " + std::string(exception.what());
        return 1;

    } catch(...) {
        GLUL::Log::Stream("Example", "logExample.log") << "Cought unknown exception!";
        return 1;
    }

    return 0;
}
