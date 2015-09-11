#pragma once

#include <GLUL/Config.h>

#include <glm/glm.hpp>


namespace GLUL {

    namespace Interface {

        class GLUL_API Camera {
            public:
                Camera();
                virtual ~Camera();

                virtual void update(double deltaTime) = 0;
                virtual void updateMouse(double x, double y) = 0;
                virtual void updateKeyboard(int key, int scancode, int action, int mods) = 0;
                virtual void updateMouseWheel(double x, double y) = 0;
                virtual void updateMouseButton(int button, int action, int mods) = 0;

                virtual const glm::vec2  getPos2D() const = 0;
                virtual const glm::vec3& getPos3D() const = 0;

                virtual const glm::mat4& getMatrix() const;
                virtual const glm::mat4& getProjection() const;
                virtual const glm::vec3& getUp() const;
                virtual const glm::vec3& getRight() const;
                virtual const glm::vec3& getDirection() const;


            protected:
                glm::vec3 _up;
                glm::vec3 _right;
                glm::vec3 _direction;
                glm::vec3 _position;

                glm::mat4 _matrix;
                glm::mat4 _projectionMatrix;
        };

    }

}
