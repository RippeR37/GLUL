#include <Utils/Logger.h>
#include <Utils/Image.h>
#include <Utils/Window.h>
#include <Utils/GL+/VertexArray.h>
#include <Utils/GL+/Program.h>
#include <Utils/GL+/Texture.h>

#include <vector>
#include <iostream>

/**
 * Global variable
 */
GL::Texture texture;


/**
 * Initialize functions
 */
void initVertices(std::vector<glm::vec4>& vertices) {
    vertices.push_back(glm::vec4(-0.5f, -0.5f, 0.0f, 0.0f));
    vertices.push_back(glm::vec4( 0.5f, -0.5f, 1.0f, 0.0f));
    vertices.push_back(glm::vec4(-0.5f,  0.5f, 0.0f, 1.0f));
    
    vertices.push_back(glm::vec4(-0.5f,  0.5f, 0.0f, 1.0f));
    vertices.push_back(glm::vec4( 0.5f, -0.5f, 1.0f, 0.0f));
    vertices.push_back(glm::vec4( 0.5f,  0.5f, 1.0f, 1.0f));
}

void initProgram(GL::Program& program) {
    program.load(
        GL::Shader("assets/shaders/image.vp", GL::Shader::Type::VertexShader),
        GL::Shader("assets/shaders/image.fp", GL::Shader::Type::FragmentShader)
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

void switchTexture(GL::Texture& texture) {
    static unsigned int texID = 0;
    static const unsigned int textureCount = 4;
    
    try {
        switch(texID) {
            case 0: texture.load(Util::Image("assets/images/image0.bmp")); break; // BMP
            case 1: texture.load(Util::Image("assets/images/image1.tga")); break; // TGA
            case 2: texture.load(Util::Image("assets/images/image2.jpg")); break; // JPEG
            case 3: texture.load(Util::Image("assets/images/image3.png")); break; // PNG with alpha channel
        }

    } catch(const Util::Exception::InitializationFailed& exception) {
        std::cerr << "Caught initialization exception: " << exception.what() << std::endl;
    }

    texID = (texID + 1) % textureCount;
}

void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS) {
        if(key == GLFW_KEY_SPACE) {
            switchTexture(texture);
        }
    }
}

/**
 * Main loop
 */
void run() {
    Util::Window window(800, 600, "Press [space] to change image");
    GL::Program program;
    GL::VertexArray vao;
    GL::VertexBuffer vbo;
    std::vector<glm::vec4> vertices;

    window.create();
    window.getContext().setClearColor(glm::vec4(0.1f, 0.1, 0.1, 1.0f));

    initVertices(vertices);
    initProgram(program);
    initVBO(vbo, vertices);
    initVAO(vao, vbo, vertices);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    switchTexture(texture);
    
    glfwSetKeyCallback(window, keyboardHandler);
    while(window.isCreated() && window.shouldClose() == false) {
        window.getContext().clearBuffers(GL::Context::BufferMask::Color);

        glActiveTexture(GL_TEXTURE0);

        texture.bind();
            program.use();
            program["textureSampler"].setSampler(0);
                vao.bind();
                vao.drawArrays();
                vao.unbind();
            program.unbind();
        texture.unbind();
        
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
