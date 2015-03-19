#include <Utils/Window.h>
#include <Utils/Logger.h>

namespace Util {

    bool Window::_hintsSet = false;

    Window::Window() : Window(640, 480, "Title") {

    }
    
    Window::Window(unsigned int width, unsigned int height, const std::string& title) {
        _handle = nullptr;
        _hintsSet = false;
        _framesCount = 0;

        setSize(glm::uvec2(width, height));
        setTitle(title);

        setCountingFPS(false);
        setDisplayingFPS(false);
        setDestroyCallback([this]() {
            destroy();
        });
    }

    Window::Window(const glm::uvec2& size, const std::string& title) : Window(size.x, size.y, title) {

    }

    Window::~Window() {
        destroy();
    }

    Window::operator GLFWwindow*() {
        return getHandle();
    }

    bool Window::create() throw(Util::Exception::FatalError) {
        if(isCreated())
            destroy();

        initializeGLFW();

        if(_hintsSet == false)
            setDefaultHints();

        _handle = glfwCreateWindow(getWidth(), getHeight(), _title.c_str(), nullptr, nullptr);

        setContext();

        initializeGLEW();

        _lastFrame = glfwGetTime();
        _fpsClock.reset();

        if(isCreated())
            Util::Log::Stream("_Library").log(
                "Window '" + getTitle() + "' has been created with size: " +
                std::to_string(getSize().x) + "x" + std::to_string(getSize().y)
            );

        return isCreated();
    }

    void Window::update() {
        if(glfwWindowShouldClose(getHandle())) {
            if(_destroyCallback)
                _destroyCallback();

            return;
        }

        _thisFrame  = glfwGetTime();
        _frameTime = _thisFrame - _lastFrame;
        _lastFrame  = _thisFrame;
        
        glfwSwapBuffers(_handle);
        glfwPollEvents();

        if(isCountingFPS()) {
            _framesCount += 1;
            _fpsTime = _fpsClock.getElapsedTime();

            if(_fpsTime > getFPSRefreshRate()) {
                setFPSCount(static_cast<unsigned int>(_framesCount * (1.0 / _fpsTime)));

                if(isDisplayingFPS())
                    appendTitle(std::string(" | FPS: ") + std::to_string(getFPS()));

                if(_fpsCountCallback)
                    _fpsCountCallback(getFPS());

                _framesCount = 0;
                _fpsClock.reset();
            }
        }
    }

    void Window::destroy() {
        if(isCreated()) {
            glfwDestroyWindow(_handle);
            _handle = nullptr;

            Util::Log::Stream("_Library").log("Window '" + getTitle() + "' has been destroyed");
        }
    }

    void Window::setSize(unsigned int width, unsigned int height) {
        setSize(glm::uvec2(width, height));
    }

    void Window::setSize(const glm::uvec2& size) {
        _windowSize = size;

        if(isCreated())
            glfwSetWindowSize(_handle, getWidth(), getHeight());
    }

    void Window::setPosition(int posX, int posY) {
        setPosition(glm::ivec2(posX, posY));
    }

    void Window::setPosition(const glm::ivec2& position) {
        _windowPosition = position;

        if(isCreated())
            glfwSetWindowPos(getHandle(), getPosition().x, getPosition().y);
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

    void Window::setDisplayingFPS(bool flag) {
        _isDisplayingFPS = flag;

        if(isDisplayingFPS())
            setCountingFPS(true);
    }

    void Window::setCountingFPS(bool flag) {
        _isCountingFPS = flag;

        setFPSCount(-1);
    }
    
    void Window::setFPSRefreshRate(double refreshRate) {
        _fpsRefreshRate = refreshRate;
    }
    
    void Window::setFPSCountCallback(const std::function<void(int)>& function) {
        _fpsCountCallback = function;
    }

    void Window::setDestroyCallback(const std::function<void()>& function) {
        _destroyCallback = function;
    }

    const bool Window::isDisplayingFPS() const {
        return _isDisplayingFPS;
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

    const glm::ivec2& Window::getPosition() const {
        return _windowPosition;
    }

    const std::string& Window::getTitle() const {
        return _title;
    }

    const bool Window::isCreated() const {
        return (_handle != nullptr);
    }

    const bool Window::shouldClose() const {
        return glfwWindowShouldClose(_handle) == GL_TRUE;
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

    void Window::initializeGLFW() throw(Util::Exception::FatalError) {
        static bool initialized = false;

        if(initialized == false) {
            // Setting error callback
            static auto errorCallbackFunc = [](int error, const char* description) {
                Util::Log::Stream("_Library").logError(std::string("[GLFW] ") + description);
            };

            glfwSetErrorCallback(errorCallbackFunc);

            // Initializing library
            if(glfwInit() == false) {
                Util::Log::Stream("_Library").logError("Failed to initialize GLFW library");
                throw Util::Exception::FatalError(std::string("Failed to initialize GLFW library."));
            }

            initialized = true;
        }
    }

    void Window::initializeGLEW() throw(Util::Exception::FatalError) {
        static bool initialized = false;

        if(initialized == false) {
            glewExperimental = GL_TRUE;

            if(glewInit() != GLEW_OK) {
                Util::Log::Stream("_Library").logError("Failed to initialize GLEW library");
                throw Util::Exception::FatalError(std::string("Failed to initialize GLEW library."));
            }

            initialized = true;
        }
    }


    void Window::setHint(int option, int value) {
        glfwWindowHint(option, value);

        _hintsSet = true;
    }

    void Window::setHints(const std::list<std::pair<int, int>>& hints) {
        for(auto& hint : hints)
            glfwWindowHint(hint.first, hint.second);

        _hintsSet = true;
    }

    void Window::setHints(const std::vector<std::pair<int, int>>& hints) {
        for(auto& hint : hints)
            glfwWindowHint(hint.first, hint.second);

        _hintsSet = true;
    }

    void Window::setDefaultHints() {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        _hintsSet = true;
    }

    void Window::setFPSCount(int fpsCount) {
        _fpsCount = fpsCount;
    }

    void Window::setContext() {
        glfwMakeContextCurrent(_handle);
        getContext().makeActive(this);
    }

}