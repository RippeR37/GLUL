#include <Utils/Logger.h>
#include <Utils/GL+/Program.h>
#include <Utils/GL+/VertexArray.h>
#include <Utils/GL+/VertexBuffer.h>
#include <Utils/GL+/GUI/Font.h>
#include <Utils/GL+/GUI/Text.h>
#include <Utils/GL+/GUI/Window.h>

#include <vector>

/**
 * Initialize functions
 */

void initFont(GL::GUI::Font& font, const std::string& fontName, int size) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    font.load("assets/fonts/" + fontName + ".ttf", size);
}

void initText(GL::GUI::Text& text, const GL::GUI::Font& font, GL::GUI::Window& window) {
    text.setFont(&font);
    window.add(&text);
}

void initVertices(std::vector<glm::vec4>& vertices, const GL::GUI::Font& font) {
    // Display whole texture
    float xS = 0.0f;
    float xE = 1.0f;
    float yS = 1.0f;
    float yE = 0.0f;

    /*
    // Display only one character
    char character = '@';
    float xS = font.getMetric(character).texPosStart.x;
    float yS = font.getMetric(character).texPosStart.y;
    float xE = font.getMetric(character).texPosEnd.x;
    float yE = font.getMetric(character).texPosEnd.y;
    */

    vertices.push_back(glm::vec4(-0.9f, -0.3f, xS, yS));
    vertices.push_back(glm::vec4( 0.9f, -0.3f, xE, yS));
    vertices.push_back(glm::vec4(-0.9f,  0.3f, xS, yE));

    vertices.push_back(glm::vec4(-0.9f,  0.3f, xS, yE));
    vertices.push_back(glm::vec4( 0.9f, -0.3f, xE, yS));
    vertices.push_back(glm::vec4( 0.9f,  0.3f, xE, yE));
}

void initProgram(GL::Program& program) {
    program.load(
        GL::Shader("assets/shaders/font.vp", GL::Shader::Type::VertexShader),
        GL::Shader("assets/shaders/font.fp", GL::Shader::Type::FragmentShader)
    );
}

void initVBO(GL::VertexBuffer& vbo, std::vector<glm::vec4>& vertices) {
    GL::VertexBuffer::Data vertexData;

    // VertexData
    vertexData.data = vertices.data();
    vertexData.size = sizeof(glm::vec4) * vertices.size();
    vertexData.pointers.push_back(GL::VertexAttrib(0, 4, GL_FLOAT, 0, 0));

    // VBO settings
    vbo.bind();
        vbo.setData(vertexData);
    vbo.unbind();
}

void initVAO(GL::VertexArray& vao, const GL::VertexBuffer& vbo, const std::vector<glm::vec4>& vertices) {
    vao.setDrawCount(vertices.size());
    vao.setDrawTarget(GL::VertexArray::DrawTarget::Triangles);

    vao.bind();
        vao.attachVBO(&vbo);
        vao.setAttribPointers();
    vao.unbind();
}

/**
 * Main loop
 */
void run() {
    //Util::Window window(800, 600, "Title");
    GL::GUI::Window window(800, 600, "Title");

    GL::Program program;
    GL::VertexArray vao;
    GL::VertexBuffer vbo;
    std::vector<glm::vec4> vertices;

    GL::GUI::Font fontAtlas;
    GL::GUI::Font fontText;
    GL::GUI::Text textHeader;
    GL::GUI::Text textFooter;

    window.create();
    window.getContext().setClearColor(glm::vec4(0.1f, 0.1, 0.1, 1.0f));

    initFont(fontAtlas, "arial", 128);
    initFont(fontText, "verdanai", 32);

    initText(textHeader, fontText, window);
    initText(textFooter, fontText, window);

    textHeader.setText("Texture with font's glyphs:");
    textHeader.setPosition(glm::vec2(200.0f, 420.0f));

    textFooter.setText("void foo() { this->bar(); }");
    textFooter.setPosition(glm::vec2(200.0f, 120.0f));

    initVertices(vertices, fontAtlas);
    initProgram(program);
    initVBO(vbo, vertices);
    initVAO(vao, vbo, vertices);

    while(window.isCreated() && window.shouldClose() == false) {
        window.getContext().clearBuffers(GL::Context::BufferMask::Color);

        fontAtlas.getTexture().bind();

        program.use();
        program["texSampler"].setSampler(0);

            vao.bind();
            vao.drawArrays();
            vao.unbind();

        program.unbind();
        fontAtlas.getTexture().unbind();

        window.render();
        
        window.update();
    }
}

/**
 * Start of application
 */
int main() {
    try {
        run();

    } catch(const Util::Exception::FatalError& exception) {
        Util::Log::Stream("Example", "logExample.log") << "Cought fatal error exception: " + std::string(exception.what());
        return 1;

    } catch(const std::exception& exception) {
        Util::Log::Stream("Example", "logExample.log") << "Cought std::exception: " + std::string(exception.what());
        return 1;

    } catch(...) {
        Util::Log::Stream("Example", "logExample.log") << "Cought unknown exception!";
        return 1;
    }

    return 0;
}
