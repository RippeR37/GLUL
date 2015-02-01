#include <Utils/GL+/Context.h>

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