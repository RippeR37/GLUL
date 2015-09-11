#include <GLUL/Logger.h>
#include <GLUL/Image.h>
#include <GLUL/Window.h>
#include <GLUL/GL++/VertexArray.h>
#include <GLUL/GL++/Program.h>
#include <GLUL/GL++/Texture.h>

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
    static glm::uvec4 firstPixel;
    
    try {
        GLUL::Image image;

        switch(texID) {
            case 0: image.load("assets/images/image0.bmp"); break; // BMP
            case 1: image.load("assets/images/image1.tga"); break; // TGA
            case 2: image.load("assets/images/image2.jpg"); break; // JPEG
            case 3: image.load("assets/images/image3.png"); break; // PNG with alpha channel
        }

        texture.load(image);

        image.save("lastImage.tga");

    } catch(const GLUL::Exception::InitializationFailed& exception) {
        std::cerr << "Caught initialization exception: " << exception.what() << std::endl;
    }

    texID = (texID + 1) % textureCount;
}

/**
 * Main loop
 */
void run() {
    GLUL::Window window(800, 600, "Press [space] to change image or [enter] to take screenshot");
    GL::Program program;
    GL::VertexArray vao;
    GL::VertexBuffer vbo;
    std::vector<glm::vec4> vertices;

    window.create();
    window.getContext().setClearColor(glm::vec4(0.1f, 0.1, 0.1, 1.0f));
    
    // Input handling
    window.registerEvents(GLUL::Input::Event::Type::Key);
    window.eventAggregator.registerTrigger(
        GLUL::Input::Event::Type::Key,
        [&](GLUL::Input::Event& inputEvent) {
            GLUL::Input::KeyEvent& keyEvent = *inputEvent.asKeyEvent();

            if(keyEvent.getAction() == GLUL::Input::Action::Press) { // if key is pressed, not released or repeated signal
                switch(keyEvent.getKey()) {
                    case GLUL::Input::Key::Space:
                        switchTexture(texture);
                        break;
                
                    case GLUL::Input::Key::Enter:
                        window.takeScreenshot();    // takeScreenshot() sets flag to take screenshot just before swapping buffers (frame 
                                                    // is complete), but if you want partialy rendered frame, use getScreenshotNow(...) method
                        break;

                    case GLUL::Input::Key::Escacpe:
                        window.destroy();
                        break;

                    default:
                        break;
                }
            }
        }
    );

    initVertices(vertices);
    initProgram(program);
    initVBO(vbo, vertices);
    initVAO(vao, vbo, vertices);
    switchTexture(texture);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    while(window.isCreated() && window.shouldClose() == false) {
        window.getContext().clearBuffers(GL::Context::BufferMask::Color);

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
