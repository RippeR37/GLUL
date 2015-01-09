#include <Utils/Window.h>
#include <Utils/GL+/VertexArray.h>
#include <Utils/GL+/Program.h>

#include <iostream>
#include <vector>

void run() {
    std::vector<glm::vec4> vertices;
    vertices.push_back(glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f));
    vertices.push_back(glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f));
    vertices.push_back(glm::vec4( 0.0f,  0.5f, 0.0f, 1.0f));

    Util::Window window;
    window.setSize(800, 600);
    window.setTitle("Title");
    window.create();

    GL::Program program(
        GL::Shader("assets/shaders/example.vs", GL::Shader::Type::VertexShader),
        GL::Shader("assets/shaders/example.fs", GL::Shader::Type::FragmentShader)
    );

    GL::VertexArray vao;
    GL::VertexBuffer vbo;
    GL::VertexBuffer::Data vertexData;

    // VertexData
    vertexData.data = &vertices[0];
    vertexData.size = sizeof(glm::vec4) * vertices.size();
    vertexData.pointers.push_back(GL::VertexAttrib(0, 4, GL_FLOAT, 0, 0));

    // VBO
    vbo.setTarget(GL::VertexBuffer::Target::Array);
    vbo.setUsage(GL::VertexBuffer::Usage::StaticDraw);
    vbo.bind();
        vbo.setData(vertexData);
    vbo.unbind();

    // VAO
    vao.setDrawCount(vertices.size());
    vao.setDrawTarget(GL::VertexArray::DrawTarget::Triangles);

    vao.bind();
    vao.attachVBO(&vbo);
    vao.setAttribPointers();
    vao.unbind();

    window.getContext().setClearColor(glm::vec4(0.1f, 0.1, 0.1, 1.0f));
    while(window.isCreated()) {
        window.update();
        window.getContext().clearBuffers(GL::Context::BufferMask::Color);

        program.use();
            vao.bind();
            vao.drawArrays();
            vao.unbind();
        program.unbind();

        if(glfwGetKey(window.getHandle(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            window.destroy();
    }
}

int main() {
    try {
        run();
    } catch(const Util::Exception::FatalError& exception) {
        std::cerr << "Cought fatal error exception:\n" << exception.what() << std::endl;
    } catch(const std::exception& exception) {
        std::cerr << "Cought std::exception:\n" << exception.what() << std::endl;
    } catch(...) {
        std::cerr << "Cought unknown exception!" << std::endl;
    }

}
