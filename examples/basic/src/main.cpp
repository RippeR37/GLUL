#include <GLUL/Logger.h>
#include <GLUL/Window.h>
#include <GLUL/GL++/VertexArray.h>
#include <GLUL/GL++/Program.h>

#include <vector>

/**
 * Initialize functions
 */
void initVertices(std::vector<glm::vec4>& vertices) {
    vertices.push_back(glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f));
    vertices.push_back(glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f));
    vertices.push_back(glm::vec4( 0.0f,  0.5f, 0.0f, 1.0f));
}

void initProgram(GL::Program& program) {
    program.load(
        GL::Shader("assets/shaders/basic.vp", GL::Shader::Type::VertexShader),
        GL::Shader("assets/shaders/basic.fp", GL::Shader::Type::FragmentShader)
    );
}

void initVBO(GL::VertexBuffer& vbo, std::vector<glm::vec4>& vertices) {
    GL::VertexBuffer::Data vertexData;

    // VertexData
    vertexData.data = vertices.data(); //pointer to data
    vertexData.size = sizeof(glm::vec4) * vertices.size(); // size of data
    vertexData.pointers.push_back(GL::VertexAttrib(0, 4, GL_FLOAT, 0, nullptr)); // vertex attributes description

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
    GLUL::Window window(800, 600, "Title");
    GL::Program program;
    GL::VertexArray vao;
    GL::VertexBuffer vbo;
    std::vector<glm::vec4> vertices;

    window.create(); // You have to create OpenGL context before using most of GL::* functionality
    window.getContext().setClearColor(glm::vec4(0.1f, 0.1, 0.1, 1.0f));

    initVertices(vertices);         // initialize vertices for VBO
    initProgram(program);           // load program (vertex shader & fragment shader)
    initVBO(vbo, vertices);         // set-up VBO
    initVAO(vao, vbo, vertices);    // set-up VAO & attach VBO to it

    while(window.isCreated() && window.shouldClose() == false) {
        window.getContext().clearBuffers(GL::Context::BufferMask::Color);

        program.use();
            vao.bind();
            vao.drawArrays();
            vao.unbind();
        program.unbind();
        
        window.update();
    }
}

/**
 * Start of application
 */
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
