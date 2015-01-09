#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif

#include <Utils/GL+/Pipeline.h>

#include <glm/gtc/matrix_transform.hpp>

namespace GL {

    Pipeline::Pipeline() {
        setProjection();
    }

    Pipeline::~Pipeline() {

    }

    void Pipeline::setProjection() {
        setProjection(90.0f, 4.0f/3.0f, 0.01f, 200.0f);
    }

    void Pipeline::setProjection(float fov, float aspect, float near, float far) {
        _fieldOfView = fov;
        _aspectRation = aspect;
        _nearClip = near;
        _farClip = far;

        _projection = glm::perspective(glm::radians(getFoV()), getAspect(), getNear(), getFar());
    }

    void Pipeline::setProjection(const glm::mat4& projectionMatrix) {
        _projection = projectionMatrix;
    }

    glm::mat4  Pipeline::getMVP() {
        return getProjection() * getModelView();
    }

    MatrixStack& Pipeline::getStack() {
        return _modelView;
    }

    const glm::mat4& Pipeline::getProjection() const {
        return _projection;
    }

    const glm::mat4& Pipeline::getModelView() const {
        return _modelView.getMatrix();
    }

    const glm::mat4  Pipeline::getMVP() const {
        return getProjection() * getModelView();
    }

    const MatrixStack& Pipeline::getStack() const {
        return _modelView;
    }

    float Pipeline::getFoV() const {
        return _fieldOfView;
    }

    float Pipeline::getAspect() const {
        return _aspectRation;
    }

    float Pipeline::getNear() const {
        return _nearClip;
    }

    float Pipeline::getFar() const {
        return _farClip;
    }

}