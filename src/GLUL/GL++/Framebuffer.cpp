#include <GLUL/GL++/Framebuffer.h>


namespace GL {

    Framebuffer::Framebuffer() {
        _isCreated = false;
        _isComplete = false;
        _isCompleteValid = true;
    }

    Framebuffer::Framebuffer(Framebuffer&& framebuffer) {
        _isCreated = false;
        _isComplete = false;
        _isCompleteValid = true;

        std::swap(_isComplete, framebuffer._isComplete);
        std::swap(_isCompleteValid, framebuffer._isCompleteValid);
        std::swap(_isCreated,       framebuffer._isCreated);
        std::swap(_framebufferID,   framebuffer._framebufferID);
    }

    Framebuffer::~Framebuffer() {
        destroy();
    }

    Framebuffer& Framebuffer::operator=(Framebuffer&& framebuffer) {
        std::swap(_isComplete, framebuffer._isComplete);
        std::swap(_isCompleteValid, framebuffer._isCompleteValid);
        std::swap(_isCreated, framebuffer._isCreated);
        std::swap(_framebufferID, framebuffer._framebufferID);

        return *this;
    }

    void Framebuffer::create() {
        destroy();

        glGenFramebuffers(1, &_framebufferID);
        _isCreated = true;
    }

    void Framebuffer::destroy() {
        if(isCreated()) {
            glDeleteFramebuffers(1, &_framebufferID);

            _isCreated = false;
            _isComplete = false;
            _isCompleteValid = true;
        }
    }

    void Framebuffer::bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, getID());
    }

    void Framebuffer::unbind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::bindDefault() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::attachTexture(const Texture& texture, AttachmentType attachment, GLint colorAttachmentNum, GLint mipmapLevel) {
        if(attachment == AttachmentType::Color)
            glFramebufferTexture2D(
                GL_FRAMEBUFFER, 
                static_cast<GLenum>(attachment) + colorAttachmentNum , 
                static_cast<GLenum>(texture.getTarget()), 
                texture.getID(), 
                mipmapLevel
            );
        else
            glFramebufferTexture2D(
                GL_FRAMEBUFFER,
                static_cast<GLenum>(attachment),
                static_cast<GLenum>(texture.getTarget()),
                texture.getID(),
                mipmapLevel
            );
    }

    bool Framebuffer::isComplete() const {
        if(_isCompleteValid) {
            return _isComplete;
        } else {
            Framebuffer* thisPtr = const_cast<Framebuffer*>(this);
            thisPtr->_isCompleteValid = true;

            if(getStatus() == Status::Complete)
                return (thisPtr->_isComplete = true);
            else
                return (thisPtr->_isComplete = false);
        }
    }

    GLuint Framebuffer::getID() const {
        if(!isCreated())
            const_cast<Framebuffer*>(this)->create();

        return _framebufferID;
    }

    Framebuffer::Status Framebuffer::getStatus() const {
        Status result = Status::Undefined;

        switch(glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
            case GL_FRAMEBUFFER_COMPLETE: 
                result = Status::Complete; break;

            case GL_FRAMEBUFFER_UNDEFINED: 
                result = Status::Undefined; break;

            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: 
                result = Status::IncompleteAttachment; break;

            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: 
                result = Status::IncompleteMissingAttachment; break;

            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER: 
                result = Status::IncompleteDrawBuffer; break;

            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER: 
                result = Status::IncompleteReadBuffer; break;

            case GL_FRAMEBUFFER_UNSUPPORTED: 
                result = Status::Unsupported; break;

            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE: 
                result = Status::IncompleteMultisample; break;

            case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS: 
                result = Status::IncompleteLayerTargets; break;
        }

        return result;
    }
    
    bool Framebuffer::isCreated() const {
        return _isCreated;
    }

}
