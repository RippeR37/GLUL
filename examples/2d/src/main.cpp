#include <GLUL/Logger.h>
#include <GLUL/GUI/Window.h>
#include <GLUL/G2D/Batch.h>
#include <GLUL/G2D/Circle.h>
#include <GLUL/G2D/Font.h>
#include <GLUL/G2D/Line.h>
#include <GLUL/G2D/LineLoop.h>
#include <GLUL/G2D/Point.h>
#include <GLUL/G2D/Ring.h>
#include <GLUL/G2D/Text.h>
#include <GLUL/G2D/TexturedBatch.h>
#include <GLUL/G2D/TexturedRectangle.h>
#include <GLUL/G2D/TexturedTriangle.h>
#include <GLUL/G2D/TexturedQuad.h>
#include <GLUL/G2D/Triangle.h>
#include <GLUL/G2D/TriangleStrip.h>
#include <GLUL/G2D/Quad.h>


void test_point() {
    static GLUL::G2D::Point p1 { {  40.0f, 500.0f },  5 };
    static GLUL::G2D::Point p2 { {  70.0f, 550.0f }, 10 };
    static GLUL::G2D::Point p3 { { 100.0f, 500.0f }, 15 };
    static GLUL::G2D::Batch batch { p1, p2, p3 };

    batch.render();
}

void test_lines() {
    static GLUL::G2D::Line l1 { { 150.0f, 500.0f }, { 150.0f, 560.0f } };
    static GLUL::G2D::Line l2 { { 170.0f, 480.0f }, { 250.0f, 480.0f }, 2u };
    static GLUL::G2D::Line l3 { { 170.0f, 580.0f }, { 250.0f, 580.0f }, 3u };
    static GLUL::G2D::Line l4 { { 270.0f, 560.0f }, { 270.0f, 500.0f }, 4u };
    static GLUL::G2D::Line l5 { { 170.0f, 560.0f }, { 250.0f, 500.0f }, 5u };
    static GLUL::G2D::Batch batch { l1, l2, l3, l4, l5 };

    batch.render();
}

void test_triangles() {
    static GLUL::G2D::Point p1 { { 350.0f, 490.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } };
    static GLUL::G2D::Point p2 { { 450.0f, 490.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } };
    static GLUL::G2D::Point p3 { { 400.0f, 565.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } };
    static GLUL::G2D::Triangle t { p1, p2, p3 };
    static GLUL::G2D::Batch batch { t };

    batch.render();
}

void test_line_loops() {
    static GLUL::G2D::Point p1 { { 500.0f, 490.0f } };
    static GLUL::G2D::Point p2 { { 550.0f, 565.0f } };
    static GLUL::G2D::Point p3 { { 600.0f, 490.0f } };
    static GLUL::G2D::LineLoop ll { { p1, p2, p3 } };
    static GLUL::G2D::Batch batch { ll };

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
    static GLUL::G2D::Batch batch { ts };

    batch.render();
}

void test_no_batch() {
    static GLUL::G2D::Triangle triangle {
        {  40.0f, 400.0f },
        { 100.0f, 400.0f },
        {  70.0f, 460.0f }
    };
    static GLUL::G2D::Quad quad {
        { 145.0f, 400.0f },
        { 225.0f, 400.0f },
        { 250.0f, 460.0f },
        { 170.0f, 460.0f }
    };

    triangle.setColor({ 0.3f, 0.8f, 0.5f, 1.0f });
    triangle.render();

    quad.setColor({ 0.5f, 0.3f, 0.8f, 1.0f });
    quad.render();
}

void test_circles() {
    static GLUL::G2D::Circle c1 { { { 430.0f, 440.0f }, { 0.7f, 0.2f, 0.7f } }, 40.0f };
    static GLUL::G2D::Circle c2 { { { 325.0f, 440.0f }, { 0.2f, 0.5f, 0.9f } }, 30.0f };
    static GLUL::G2D::Circle c3 { { { 550.0f, 400.0f }, { 1.0f, 0.7f, 0.0f } }, 70.0f };
    static GLUL::G2D::Batch batch { c1, c2, c3 };

    batch.render();
}

void test_rings() {
    static GLUL::G2D::Ring r1 { { { 430.0f, 350.0f }, { 0.7f, 0.2f, 0.7f } }, 30.0f, 40.0f };
    static GLUL::G2D::Ring r2 { { { 325.0f, 350.0f }, { 0.2f, 0.5f, 0.9f } }, 15.0f, 30.0f };

    static GLUL::G2D::Ring r3   { { { 700.0f, 400.0f }, { 1.0f, 0.7f, 0.0f } }, 35.0f, 70.0f };
    static GLUL::G2D::Circle c3 { { { 700.0f, 400.0f }, { 0.2f, 0.2f, 0.2f } }, 35.0f };

    // syncronize point count to avoid artifacts
    c3.pointCount = r3.pointCount;

    static GLUL::G2D::Batch batch { r1, r2, r3, c3 };

    batch.render();
}

void test_textured_triangles() {
    static GL::Texture texture("assets/textures/tex.bmp");

    static GLUL::G2D::TexturedPoint tp1 { {  20.0f, 250.0f }, { 0.0f, 0.0f } };
    static GLUL::G2D::TexturedPoint tp2 { { 120.0f, 250.0f }, { 1.0f, 0.0f } };
    static GLUL::G2D::TexturedPoint tp3 { { 120.0f, 350.0f }, { 1.0f, 1.0f } };

    static GLUL::G2D::TexturedPoint tp4 { {  20.0f, 260.0f }, { 0.0f, 0.0f } };
    static GLUL::G2D::TexturedPoint tp5 { { 120.0f, 360.0f }, { 1.0f, 1.0f } };
    static GLUL::G2D::TexturedPoint tp6 { {  20.0f, 360.0f }, { 0.0f, 1.0f } };

    static GLUL::G2D::TexturedTriangle t1 { tp1, tp2, tp3 };
    static GLUL::G2D::TexturedTriangle t2 { tp4, tp5, tp6 };
    static GLUL::G2D::TexturedBatch batch { { t1, t2 }, texture };

    batch.render();
}

void test_textured_batching() {
    static GL::Texture texture1("assets/textures/tex.bmp");
    static GL::Texture texture2("assets/textures/tex.bmp");

    static GLUL::G2D::TexturedPoint tp_t1 { { 320.0f, 250.0f }, { 0.0f, 0.0f } };
    static GLUL::G2D::TexturedPoint tp_t2 { { 420.0f, 250.0f }, { 1.0f, 0.0f } };
    static GLUL::G2D::TexturedPoint tp_t3 { { 370.0f, 350.0f }, { 0.5f, 1.0f } };

    static GLUL::G2D::TexturedPoint tp_q1 { { 160.0f, 255.0f }, { 0.0f, 0.0f } };
    static GLUL::G2D::TexturedPoint tp_q2 { { 260.0f, 255.0f }, { 1.0f, 0.0f } };
    static GLUL::G2D::TexturedPoint tp_q3 { { 260.0f, 355.0f }, { 1.0f, 1.0f } };
    static GLUL::G2D::TexturedPoint tp_q4 { { 160.0f, 355.0f }, { 0.0f, 1.0f } };

    static GLUL::G2D::TexturedTriangle triangle { tp_t1, tp_t2, tp_t3 };
    static GLUL::G2D::TexturedQuad quad { tp_q1, tp_q2, tp_q3, tp_q4 };
    static GLUL::G2D::TexturedRectangle rectangle { { 500.0f, 250.0f }, { 250.0f, 60.0f } };

    static GLUL::G2D::TexturedBatch batch { { quad, texture2 }, { triangle, texture1 }, { rectangle, texture1 } };

    batch.render();
}

void test_font_text() {
    static GLUL::G2D::Font font { "assets/fonts/arial.ttf", 24 };

    static std::string lorem_ipsum { "Lorem ipsum" };
    static std::string text1 { "To left\n"  + lorem_ipsum };
    static std::string text2 { "To right\n" + lorem_ipsum };
    static std::string text3 { "Centered\n" + lorem_ipsum };

    static GLUL::G2D::Text t1 { text1, {  50.0f, 200.0f }, { 1.0f, 0.2f, 0.2f } };
    static GLUL::G2D::Text t2 { text2, { 750.0f, 200.0f }, { 0.2f, 1.0f, 0.2f }, GLUL::G2D::Text::Alignment::Right };
    static GLUL::G2D::Text t3 { text3, { 400.0f, 200.0f }, { 0.2f, 0.2f, 1.0f }, GLUL::G2D::Text::Alignment::Center };

    static GLUL::G2D::TexturedBatch batch { { t1, t2, t3 }, font };

    batch.render();
}

void run() {
    GLUL::GUI::Window window { 800, 600, "2D example" };

    window.create();
    window.getContext().setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);

    while(window.isCreated() && !window.shouldClose()) {
        window.getContext().clearBuffers(GL::Context::BufferMask::Color);

        test_point();
        test_lines();
        test_triangles();
        test_line_loops();
        test_triangle_strips();
        test_no_batch();
        test_circles();
        test_rings();
        test_textured_triangles();
        test_textured_batching();
        test_font_text();

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
