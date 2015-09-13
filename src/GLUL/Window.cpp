#include <GLUL/Logger.h>
#include <GLUL/Window.h>
#include <GLUL/Windows.h>
#include <GLUL/Input/Mouse.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace GLUL {

    bool Window::_hintsSet = false;

    Window::Window() : Window(640, 480, "Title") {
        Windows::Get(static_cast<GLUL::Window*>(nullptr));
    }
    
    Window::Window(unsigned int width, unsigned int height, const std::string& title) {
        Windows::Get(static_cast<GLUL::Window*>(nullptr));

        _handle = nullptr;
        _hintsSet = false;
        _isScreenshotFlagSet = false;
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

    bool Window::create() throw(GLUL::Exception::FatalError) {
        if(isCreated())
            destroy();

        initializeGLFW();

        if(_hintsSet == false)
            setDefaultHints();

        _handle = glfwCreateWindow(getWidth(), getHeight(), _title.c_str(), nullptr, nullptr);

        Windows::registerWindow(this);

        setFocusCallback();

        setContext();

        initializeGLEW();

        _lastFrame = glfwGetTime();
        _fpsClock.reset();

        if(isCreated())
            GLUL::Log::LibraryStream().log(
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

        if(_isScreenshotFlagSet) {
            getScreenshotNow(_screenshotOrigin, _screenshotSize).save(_screenshotPath);
            _isScreenshotFlagSet = false;
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

        eventAggregator.notifyAll();
    }

    void Window::destroy() {
        if(isCreated()) {
            skipEvents();

            glfwDestroyWindow(_handle);
            _handle = nullptr;

            GLUL::Log::LibraryStream().log("Window '" + getTitle() + "' has been destroyed");
            Windows::unregisterWindow(this);
        }
    }

    void Window::takeScreenshot() {
        std::string fileLocation;
        std::string fileName;

        fileLocation = "";
        fileName = "screenshot.bmp";

        takeScreenshot(fileLocation + fileName);
    }

    void Window::takeScreenshot(const std::string& path) {
        takeScreenshot(path, glm::ivec2(0, 0), getSize());
    }

    void Window::takeScreenshot(const std::string& path, const glm::ivec2& origin, const glm::ivec2& size) {
        _isScreenshotFlagSet = true;
        _screenshotPath = path;
        _screenshotOrigin = origin;
        _screenshotSize = size;
    }

    void Window::registerEvents() {
        registerEvents({
            GLUL::Input::Event::Type::Character,
            GLUL::Input::Event::Type::Key,
            GLUL::Input::Event::Type::MouseButton,
            GLUL::Input::Event::Type::MouseMovement,
            GLUL::Input::Event::Type::MouseScroll
        });
    }

    void Window::registerEvents(Input::Event::Type type) {
        getContext().makeActive(this);

        switch(type) {
            case Input::Event::Type::Character:
                glfwSetCharCallback(
                    getHandle(), 
                    [](GLFWwindow* window, unsigned int codepoint) {
                        GLUL::Window* inputWindow = GLUL::Windows::Get(window);

                        if(inputWindow) {
                            inputWindow->eventAggregator.registerEvent(
                                new GLUL::Input::CharacterEvent(codepoint)
                            );
                        }
                    }
                );
                break;

            case Input::Event::Type::Key:
                glfwSetKeyCallback(
                    getHandle(), 
                    [](GLFWwindow* window, int key, int scancode, int action, int mods) {
                        (void) scancode;
                        (void) mods;

                        GLUL::Input::Key inputKey = static_cast<GLUL::Input::Key>(key);
                        GLUL::Input::Action inputAction = GLUL::Input::Action::Release;
                        GLUL::Window* inputWindow = GLUL::Windows::Get(window);

                        if(action == GLFW_PRESS)        inputAction = GLUL::Input::Action::Press;
                        else if(action == GLFW_REPEAT)  inputAction = GLUL::Input::Action::Repeat;
                        else if(action == GLFW_RELEASE) inputAction = GLUL::Input::Action::Release;

                        if(inputWindow) {
                            inputWindow->eventAggregator.registerEvent(
                                new GLUL::Input::KeyEvent(inputKey, inputAction)
                            );
                        }
                    }
                );
                break;

            case Input::Event::Type::MouseButton:
                glfwSetMouseButtonCallback(
                    getHandle(), 
                    [](GLFWwindow* window, int button, int action, int mods) {
                        (void) mods;

                        GLUL::Input::MouseButton inputButton = GLUL::Input::MouseButton::Left;
                        GLUL::Input::Action inputAction = GLUL::Input::Action::Release;
                        GLUL::Window* inputWindow = GLUL::Windows::Get(window);

                        switch(button) {
                            case GLFW_MOUSE_BUTTON_LEFT:   inputButton = GLUL::Input::MouseButton::Left; break;
                            case GLFW_MOUSE_BUTTON_RIGHT:  inputButton = GLUL::Input::MouseButton::Right; break;
                            case GLFW_MOUSE_BUTTON_MIDDLE: inputButton = GLUL::Input::MouseButton::Middle; break;
                        }

                        if(action == GLFW_PRESS)        inputAction = GLUL::Input::Action::Press;
                        else if(action == GLFW_REPEAT)  inputAction = GLUL::Input::Action::Repeat;
                        else if(action == GLFW_RELEASE) inputAction = GLUL::Input::Action::Release;

                        if(inputWindow) {
                            inputWindow->eventAggregator.registerEvent(
                                new GLUL::Input::MouseButtonEvent(
                                    inputButton, 
                                    inputAction, 
                                    GLUL::Input::Mouse::getPosition(GLUL::Windows::Get(window))
                                )
                            );
                        }
                    }
                );
                break;

            case Input::Event::Type::MouseMovement:
                glfwSetCursorPosCallback(
                    getHandle(), 
                    [](GLFWwindow* window, double x, double y) {
                        GLUL::Window* inputWindow = GLUL::Windows::Get(window);

                        if(inputWindow) {
                            inputWindow->eventAggregator.registerEvent(
                                new GLUL::Input::MouseMovementEvent(
                                    static_cast<float>(x),
                                    static_cast<float>(y)
                                )
                            );
                        }
                    }
                );
                break;

            case Input::Event::Type::MouseScroll:
                glfwSetScrollCallback(
                    getHandle(), 
                    [](GLFWwindow* window, double x, double y) {
                        (void) x;

                        GLUL::Window* inputWindow;
                        GLUL::Input::ScrollDirection inputScrollDirection;
                        
                        inputWindow = GLUL::Windows::Get(window);
                        inputScrollDirection = (y > 0 ? GLUL::Input::ScrollDirection::Up : GLUL::Input::ScrollDirection::Down);

                        if(inputWindow) {
                            inputWindow->eventAggregator.registerEvent(
                                new GLUL::Input::MouseScrollEvent(inputScrollDirection)
                            );
                        }
                    }
                );
                break;
        }
    }

    void Window::registerEvents(std::initializer_list<Input::Event::Type> types) {
        for(auto type : types) {
            registerEvents(type);
        }
    }
    
    void Window::skipEvents() {
        skipEvents({
            GLUL::Input::Event::Type::Character,
            GLUL::Input::Event::Type::Key,
            GLUL::Input::Event::Type::MouseButton,
            GLUL::Input::Event::Type::MouseMovement,
            GLUL::Input::Event::Type::MouseScroll
        });
    }

    void Window::skipEvents(Input::Event::Type type) {
        switch(type) {
            case GLUL::Input::Event::Type::Character: glfwSetCharCallback(getHandle(), nullptr); break;
            case GLUL::Input::Event::Type::Key: glfwSetKeyCallback(getHandle(), nullptr); break;
            case GLUL::Input::Event::Type::MouseButton: glfwSetMouseButtonCallback(getHandle(), nullptr); break;
            case GLUL::Input::Event::Type::MouseMovement: glfwSetCursorPosCallback(getHandle(), nullptr); break;
            case GLUL::Input::Event::Type::MouseScroll: glfwSetScrollCallback(getHandle(), nullptr); break;
        }
    }

    void Window::skipEvents(std::initializer_list<Input::Event::Type> types) {
        for(auto type : types) {
            skipEvents(type);
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

    bool Window::isDisplayingFPS() const {
        return _isDisplayingFPS;
    }

    bool Window::isCountingFPS() const {
        return _isCountingFPS;
    }

    double Window::getFPSRefreshRate() const {
        return _fpsRefreshRate;
    }
    
    int Window::getFPS() const {
        return _fpsCount;
    }

    unsigned int Window::getWidth() const {
        return _windowSize.x;
    }

    unsigned int Window::getHeight() const {
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

    bool Window::isCreated() const {
        return (_handle != nullptr);
    }

    bool Window::shouldClose() const {
        return glfwWindowShouldClose(_handle) == GL_TRUE;
    }

    double Window::getFrameTime() const {
        return _frameTime;
    }

    GLFWwindow* Window::getHandle() {
        return _handle;
    }

    GL::Context& Window::getContext() {
        return _context;
    }
            
    Image Window::getScreenshotNow() {
        return getScreenshotNow(glm::ivec2(0, 0), getSize());
    }

    Image Window::getScreenshotNow(const glm::ivec2& origin, const glm::ivec2& size) {
        Image screenshot;

        unsigned int bits;
        unsigned int rowStride;
        unsigned char* dataPtr;

        bits = 24;
        rowStride = size.x * (bits / 8);
        rowStride = rowStride + (3 - ((rowStride - 1) % 4));
        dataPtr = new unsigned char[rowStride * size.y];

        glReadPixels(origin.x, origin.y, size.x, size.y, GL_RGB, GL_UNSIGNED_BYTE, dataPtr);
        screenshot.load(size.x, size.y, 24, dataPtr);

        delete[] dataPtr;

        return screenshot;
    }

    void Window::initializeGLFW() throw(GLUL::Exception::FatalError) {
        static bool initialized = false;

        if(initialized == false) {
            // Setting error callback
            static auto errorCallbackFunc = [](int error, const char* description) {
                GLUL::Log::LibraryStream().logError(std::string("[GLFW] Error ") + std::to_string(error) + std::string(": ") + description);
            };

            glfwSetErrorCallback(errorCallbackFunc);

            // Initializing library
            if(glfwInit() == false) {
                GLUL::Log::LibraryStream().logError("Failed to initialize GLFW library");
                throw GLUL::Exception::FatalError(std::string("Failed to initialize GLFW library."));
            }

            initialized = true;
        }
    }

    void Window::initializeGLEW() throw(GLUL::Exception::FatalError) {
        static bool initialized = false;

        if(initialized == false) {
            glewExperimental = GL_TRUE;

            if(glewInit() != GLEW_OK) {
                GLUL::Log::LibraryStream().logError("Failed to initialize GLEW library");
                throw GLUL::Exception::FatalError(std::string("Failed to initialize GLEW library."));
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
        glfwMakeContextCurrent(getHandle());
        getContext().makeActive(this);
    }

    void Window::setFocusCallback() {
        glfwSetWindowFocusCallback(getHandle(), setFocus);
        setFocus(getHandle(), GL_TRUE);
    }

    void Window::setFocus(GLFWwindow* window, int focused) {
        if(focused == GL_TRUE)
            Windows::setActiveWindow(window);
        else if(focused == GL_FALSE)
            Windows::setActiveWindow(static_cast<GLFWwindow*>(nullptr));
    }

}
