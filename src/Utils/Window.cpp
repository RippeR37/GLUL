#include <Utils/Window.h>
#include <Utils/Clock.h>

namespace Util {

    Window::Window() {
        _handle = nullptr;

        // Default options
        _windowSize = glm::uvec2(640, 480);
        _title = std::string("Title");

        setCountingFPS(false);
    }

    Window::~Window() {
        destroy();
    }

    bool Window::create() {
        if(isCreated())
            destroy();

        Window::initializeGLFW();

        setHints();

        _handle = glfwCreateWindow(getWidth(), getHeight(), _title.c_str(), nullptr, nullptr);

        setContext();

        Window::initializeGLEW();

        return isCreated();
    }

    void Window::update() {
        static double lastFrame = glfwGetTime();
        static double thisFrame;
        static Clock fpsClock;
        static double fpsTime;
        static unsigned int framesCount = 0;

        thisFrame  = glfwGetTime();
        _frameTime = thisFrame - lastFrame;
        lastFrame  = thisFrame;
        
        glfwSwapBuffers(_handle);
        glfwPollEvents();

        if(isCountingFPS()) {
            framesCount += 1;
            fpsTime = fpsClock.getElapsedTime();

            if(fpsTime > getFPSRefreshRate()) {
                framesCount = static_cast<unsigned int>(framesCount * (1.0 / fpsTime));
                appendTitle(std::string(" | FPS: ") + std::to_string(framesCount));

                framesCount = 0;
                fpsClock.reset();
            }
        }
    }

    void Window::destroy() {
        if(isCreated()) {
            glfwDestroyWindow(_handle);
            _handle = nullptr;
        }
    }

    void Window::setCountingFPS(bool flag) {
        _isCountingFPS = flag;

        setFPSCount(-1);
    }
    
    void Window::setFPSRefreshRate(double refreshRate) {
        _fpsRefreshRate = refreshRate;
    }

    void Window::setSize(unsigned int width, unsigned int height) {
        setSize(glm::uvec2(width, height));
    }

    void Window::setSize(const glm::uvec2& size) {
        _windowSize = size;

        if(isCreated())
            glfwSetWindowSize(_handle, getWidth(), getHeight());
    }

    void Window::setTitle(const std::string& title) {
        _title = title;

        if(isCreated())
            glfwSetWindowTitle(_handle, _title.c_str());
    }
    
    void Window::appendTitle(const std::string& text) {
        std::string appendedTitle = getTitle() + text;

        if(isCreated())
            glfwSetWindowTitle(_handle, appendedTitle.c_str());
    }

    const bool Window::isCountingFPS() const {
        return _isCountingFPS;
    }

    const double Window::getFPSRefreshRate() const {
        return _fpsRefreshRate;
    }
    
    const int Window::getFPS() const {
        return _fpsCount;
    }

    const unsigned int Window::getWidth() const {
        return _windowSize.x;
    }

    const unsigned int Window::getHeight() const {
        return _windowSize.y;
    }

    const glm::uvec2& Window::getSize() const {
        return _windowSize;
    }
    const std::string& Window::getTitle() const {
        return _title;
    }

    const bool Window::isCreated() const {
        return (_handle != nullptr);
    }

    const double Window::getFrameTime() const {
        return _frameTime;
    }

    GLFWwindow* Window::getHandle() {
        return _handle;
    }

    GL::Context& Window::getContext() {
        return _context;
    }

    void Window::setFPSCount(int fpsCount) {
        _fpsCount = fpsCount;
    }

    void Window::setHints() {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    }

    void Window::setContext() {
        glfwMakeContextCurrent(_handle);
        getContext().makeActive(this);
    }

    void Window::initializeGLFW() {
        static bool initialized = false;

        if(initialized == false) {
            initialized = true;

            if(glfwInit() == false)
                throw Util::Exception::FatalError(std::string("Failed to initialize GLFW library."));
        }
    }

    void Window::initializeGLEW() {
        static bool initialized = false;

        if(initialized == false) {
            initialized = true;
            glewExperimental = GL_TRUE;

            if(glewInit() != GLEW_OK)
                throw Util::Exception::FatalError(std::string("Failed to initialize GLEW library."));
        }
    }

}