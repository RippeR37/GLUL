#include <GLUL/Logger.h>
#include <GLUL/Window.h>
#include <GLUL/GL++/Context.h>


namespace GL {

    Context Context::DefaultContext;
    Context* Context::Current = &Context::DefaultContext;

    Context::Context() {
        setActive(false);
        _window = nullptr;
        _clearDepth = 0.0f;
        _clearColor = glm::vec4(0.0f);
        _clearStencil = 0;
        _isScissorTestEnabled = false;

        _pixelPackAlignment = 4;
        _pixelUnpackAlignment = 4;

        _viewportSize = glm::ivec2(0, 0);
        _viewportPosition = glm::ivec2(0, 0);
    }

    Context::~Context() {
        if(this == Context::Current)
            Context::Current = &Context::DefaultContext;
    }



    void Context::makeActive(GLUL::Window* window) {
        setActive(true);
        bindWindow(window);

        Context::Current = this;
    }

    void Context::bindWindow(GLUL::Window* window) {
        _window = window;

        if(window)
            _viewportSize = window->getSize();
    }

    void Context::logErrors(bool flag) {
        static bool streamOpened = false;

        if(GLEW_ARB_debug_output) {
            if(flag) {
                glEnable(GL_DEBUG_OUTPUT);
                glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
                glDebugMessageCallbackARB(&Context::logError, nullptr);

                if(streamOpened == false) {
                    GLUL::Log::Stream("_OpenGL", "logOpenGL.log") << "Logging OpenGL errors has started";
                    streamOpened = true;
                } else {
                    GLUL::Log::Stream("_OpenGL") << "Logging OpenGL errors is resumed";
                }

            } else {
                glDisable(GL_DEBUG_OUTPUT);
                glDisable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
                glDebugMessageCallbackARB(nullptr, nullptr);
                GLUL::Log::Stream("_OpenGL") << "Logging OpenGL errors has ended";
            }
        } else if(flag) {
            GLUL::Log::LibraryStream() << "Unable to register logging OpenGL errors due to lack of support for ARB_debug_output extension";
        }
    }

    void Context::logError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
        std::string logType;
        std::string logPriority;

        (void) id;
        (void) source;
        (void) length;
        (void) userParam;

        switch(severity) {
            case GL_DEBUG_SEVERITY_HIGH_ARB:    logPriority = "[High]   "; break;
            case GL_DEBUG_SEVERITY_MEDIUM_ARB:  logPriority = "[Medium] "; break;
            case GL_DEBUG_SEVERITY_LOW_ARB:     logPriority = "[Low]    "; break;
            default:                            logPriority = "[Other]  "; break;
        };

        switch(type) {
            case GL_DEBUG_TYPE_ERROR_ARB:               logType = "[Error]       ";  break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB: logType = "[Deprecated]  ";  break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:  logType = "[Undefined]   ";  break;
            case GL_DEBUG_TYPE_PORTABILITY_ARB:         logType = "[Portability] ";  break;
            case GL_DEBUG_TYPE_PERFORMANCE_ARB:         logType = "[Performance] ";  break;
            case GL_DEBUG_TYPE_OTHER_ARB:               logType = "[Other]       ";  break;
            default:                                    logType = "[Unknown]     ";  break;
        }

        GLUL::Log::Stream("_OpenGL") << logPriority + logType + message;
    }


    void Context::clearBuffers(Context::BufferMask type) {
        if(isActive())
            glClear(static_cast<GLbitfield>(type));
    }


    void Context::enableScissorTest() {
        if(isActive()) {
            glEnable(GL_SCISSOR_TEST);
            _isScissorTestEnabled = true;
        }
    }

    void Context::disableScissorTest() {
        if(isActive()) {
            glDisable(GL_SCISSOR_TEST);
            _isScissorTestEnabled = false;
        }
    }


    void Context::setClearColor(const glm::vec4& data) {
        _clearColor = data;

        if(isActive())
            glClearColor(data.r, data.g, data.b, data.a);
    }

    void Context::setClearDepth(const GLclampf value) {
        _clearDepth = value;

        if(isActive())
            glClearDepth(value);
    }

    void Context::setClearStencil(const GLint value) {
        _clearStencil = value;

        if(isActive())
            glClearStencil(value);
    }

    void Context::setViewport(GLint x, GLint y, GLint width, GLint height) {
        setViewport(glm::ivec2(x, y), glm::ivec2(width, height));
    }

    void Context::setViewport(const glm::ivec2& position, const glm::ivec2& size) {
        if(isActive()) {
            _viewportSize = size;
            _viewportPosition = position;

            glViewport(position.x, position.y, size.x, size.y);
        }
    }


    void Context::setScissorBox(GLint x, GLint y, GLsizei width, GLsizei height) {
        setScissorBox({
            { static_cast<float>(x),     static_cast<float>(y)      },
            { static_cast<float>(width), static_cast<float>(height) }
        });
    }

    void Context::setScissorBox(const GLUL::G2D::Rectangle& scissorBox) {
        if(isActive()) {
            if(isScissorTestEnabled() == false)
                enableScissorTest();

            glScissor(
                static_cast<GLint>(scissorBox.getPosition().x),
                static_cast<GLint>(scissorBox.getPosition().y),
                static_cast<GLsizei>(scissorBox.getSize().x),
                static_cast<GLsizei>(scissorBox.getSize().y)
            );

            _scissorBox = scissorBox;
        }
    }

    void Context::setPixelPackAlignment(GLint value) {
        if(isActive()) {
            if(_pixelPackAlignment != value &&
                (value == 1 || value == 2 || value == 4 || value == 8))
            {
                glPixelStorei(GL_PACK_ALIGNMENT, value);
                _pixelPackAlignment = value;
            }
        }
    }

    void Context::setPixelUnpackAlignment(GLint value) {
        if(isActive()) {
            if(_pixelUnpackAlignment != value &&
                (value == 1 || value == 2 || value == 4 || value == 8))
            {
                glPixelStorei(GL_UNPACK_ALIGNMENT, value);
                _pixelUnpackAlignment = value;
            }
        }
    }

    bool Context::isScissorTestEnabled() const {
        return _isScissorTestEnabled;
    }


    const glm::vec4& Context::getClearColor() const {
        return _clearColor;
    }

    GLclampf Context::getClearDepth() const {
        return _clearDepth;
    }

    GLint Context::getClearStencil() const {
        return _clearStencil;
    }

    const glm::ivec2& Context::getViewportSize() const {
        return _viewportSize;
    }

    const glm::ivec2& Context::getViewportPosition() const {
        return _viewportPosition;
    }

    const GLUL::G2D::Rectangle& Context::getScissorBox() const {
        return _scissorBox;
    }

    GLint Context::getPixelPackAlignment() const {
        return _pixelPackAlignment;
    }

    GLint Context::getPixelUnpackAlignment() const {
        return _pixelUnpackAlignment;
    }


    GLUL::Window* Context::getWindow() {
        return _window;
    }



    void Context::setActive(bool flag) {
        _isActive = flag;
    }

    bool Context::isActive() const {
        return _isActive;
    }

}
