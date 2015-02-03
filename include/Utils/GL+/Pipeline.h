#ifndef UTILS_GL_PIPELINE_H_INCLUDED
#define UTILS_GL_PIPELINE_H_INCLUDED

#include <Utils/Exception.h>
#include <Utils/Interfaces/Camera.h>
#include <Utils/GL+/MatrixStack.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/matrix.hpp>

namespace GL {

    class Pipeline {
        public:
            enum class ViewSource {
                Camera,
                Matrix
            };

        public:
            Pipeline();
            ~Pipeline();

            void setViewSource(ViewSource source);
            void setCamera(const Util::Interface::Camera* camera);

            void setModel() const;
            void setModel(const glm::mat4& modelMatrix) const;

            void setView();
            void setView(const Util::Interface::Camera* camera);
            void setView(const glm::mat4& viewMatrix);

            void setProjection();
            void setProjection(float fov, float aspect, float near, float far);
            void setProjection(const glm::mat4& projectionMatrix);

            const glm::mat4 getMV() const;
            const glm::mat4 getMVP() const;
            const glm::mat4& getModel() const;
            const glm::mat4& getView() const throw(Util::Exception::FatalError);
            const glm::mat4& getProjection() const;
            const Util::Interface::Camera* getCamera() const;

        private:
            glm::mat4 _model;
            glm::mat4 _view;
            glm::mat4 _projection;

            ViewSource _viewSource;
            const Util::Interface::Camera* _camera;
    };

}

#endif