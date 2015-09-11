#pragma once

#include <GLUL/Config.h>
#include <GLUL/GL++/Texture.h>

#include <GL/glew.h>
#include <glm/matrix.hpp>

#include <stack>


namespace GL {

    class GLUL_API Framebuffer {
        public:
            enum class Status {
                Complete = GL_FRAMEBUFFER_COMPLETE,
                Undefined = GL_FRAMEBUFFER_UNDEFINED,
                IncompleteAttachment = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
                IncompleteMissingAttachment = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
                IncompleteDrawBuffer = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,
                IncompleteReadBuffer = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
                Unsupported = GL_FRAMEBUFFER_UNSUPPORTED,
                IncompleteMultisample = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
                IncompleteLayerTargets = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS,
            };

            enum class AttachmentType {
                Color = GL_COLOR_ATTACHMENT0, 
                Depth = GL_DEPTH_ATTACHMENT, 
                Stencil = GL_STENCIL_ATTACHMENT,
                DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT,
            };

        public:
            Framebuffer();
            Framebuffer(Framebuffer&& framebuffer);
            Framebuffer(const Framebuffer&) = delete;
            ~Framebuffer();

            Framebuffer& operator=(const Framebuffer&) = delete;
            Framebuffer& operator=(Framebuffer&& framebuffer);

            void create();
            void destroy();

            void bind() const;
            void unbind() const;
            static void bindDefault();

            void attachTexture(const Texture& texture, AttachmentType attachment, GLint colorAttachmentNum = 0, GLint mipmapLevel = 0);
            // void attachRenderbuffer(...)

            bool isComplete() const;
            GLuint getID() const;
            Status getStatus() const;


        private:
            bool isCreated() const;

            bool _isComplete;
            bool _isCompleteValid;
            bool _isCreated;
            GLuint _framebufferID;
    };

}
