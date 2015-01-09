#ifndef UTILS_GL_PIPELINE_H_INCLUDED
#define UTILS_GL_PIPELINE_H_INCLUDED

#include "MatrixStack.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/matrix.hpp>

namespace GL {

    class Pipeline {
        public:
            Pipeline();
            ~Pipeline();

            void setProjection();
            void setProjection(float fov, float aspect, float near, float far);
            void setProjection(const glm::mat4& projectionMatrix);

            glm::mat4  getMVP();
            MatrixStack& getStack();

            const glm::mat4& getProjection() const;
            const glm::mat4& getModelView() const;
            const glm::mat4  getMVP() const;
            const MatrixStack& getStack() const;

            float getFoV() const;
            float getAspect() const;
            float getNear() const;
            float getFar() const;

        private:
            float _fieldOfView;
            float _aspectRation;
            float _nearClip;
            float _farClip;

            glm::mat4   _projection;
            MatrixStack _modelView;
    };

}

#endif