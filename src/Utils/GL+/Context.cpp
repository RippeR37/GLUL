#include <Utils/GL+/Context.h>
#include <Utils/Logger.h>

#include <iostream>

namespace GL {


    Context Context::DefaultContext;
    Context& Context::Current = Context::DefaultContext;



    Context::Context() {
        setActive(false);
        _window = nullptr;
    }



    void Context::makeActive(Util::Window* window) {
        setActive(true);
        bindWindow(window);
    }
    
    void Context::bindWindow(Util::Window* window) {
        _window = window;
    }

    void Context::logErrors(bool flag) {
        if(GLEW_ARB_debug_output) {
            if(flag) {
                glDebugMessageCallbackARB(&Context::logError, nullptr);
                Util::Log::Stream("_OpenGL") << "Logging OpenGL errors has started";
            } else {
                glDebugMessageCallbackARB(nullptr, nullptr);
                Util::Log::Stream("_OpenGL") << "Logging OpenGL errors has ended";
            }
        } else if(flag) {
            Util::Log::Stream("_OpenGL") << "Unable to register logging OpenGL errors due to lack of support for ARB_debug_output extension";
        }
    }

    void Context::logError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
        std::string logType;
        std::string logPriority;

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

        Util::Log::Stream("_OpenGL") << logPriority + logType + message;
    }


    void Context::clearBuffers(Context::BufferMask type) {
        if(isActive())
            glClear(static_cast<GLbitfield>(type));
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



    const glm::vec4& Context::getClearColor() const {
        return _clearColor;
    }

    GLclampf Context::getClearDepth() const {
        return _clearDepth;
    }

    GLint Context::getClearStencil() const {
        return _clearStencil;
    }



    void Context::setActive(bool flag) {
        _isActive = flag;
    }

    bool Context::isActive() const {
        return _isActive;
    }

}