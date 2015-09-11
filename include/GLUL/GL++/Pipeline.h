#pragma once

#include <GLUL/Config.h>
#include <GLUL/Exception.h>
#include <GLUL/Interfaces/Camera.h>
#include <GLUL/GL++/MatrixStack.h>

#include <GL/glew.h>
#include <glm/matrix.hpp>


namespace GL {

    class GLUL_API Pipeline {
        public:
            enum class ViewSource {
                Camera,
                Matrix
            };

        public:
            Pipeline();
            ~Pipeline();

            void setViewSource(ViewSource source);
            void setCamera(const GLUL::Interface::Camera* camera);

            void setModel() const;
            void setModel(const glm::mat4& modelMatrix) const;

            void setView();
            void setView(const GLUL::Interface::Camera* camera);
            void setView(const glm::mat4& viewMatrix);

            void setProjection();
            void setProjection(float fov, float aspect, float near, float far);
            void setProjection(const glm::mat4& projectionMatrix);

            const glm::mat4 getMV() const;
            const glm::mat4 getMVP() const;
            const glm::mat4& getModel() const;
            const glm::mat4& getView() const throw(GLUL::Exception::FatalError);
            const glm::mat4& getProjection() const;
            const GLUL::Interface::Camera* getCamera() const;

        private:
            glm::mat4 _model;
            glm::mat4 _view;
            glm::mat4 _projection;

            ViewSource _viewSource;
            const GLUL::Interface::Camera* _camera;
    };

}
