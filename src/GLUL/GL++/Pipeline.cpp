#include <GLUL/GL++/Pipeline.h>

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>


namespace GL {

    Pipeline::Pipeline() {
        setModel();
        setView();
        setProjection();

        setViewSource(ViewSource::Matrix);
    }

    Pipeline::~Pipeline() {

    }

    void Pipeline::setViewSource(ViewSource source) {
        _viewSource = source;
    }

    void Pipeline::setCamera(const GLUL::Interface::Camera* camera) {
        _camera = camera;
    }

    void Pipeline::setModel() const {
        setModel(glm::mat4(1.0f));
    }

    void Pipeline::setModel(const glm::mat4& modelMatrix) const {
        Pipeline* thisConstless = const_cast<Pipeline*>(this);

        thisConstless->_model = modelMatrix;
    }

    void Pipeline::setView() {
        setView(glm::mat4(1.0f));
    }

    void Pipeline::setView(const GLUL::Interface::Camera* camera) {
        setCamera(camera);
        setViewSource(ViewSource::Camera);
    }

    void Pipeline::setView(const glm::mat4& viewMatrix) {
        _view = viewMatrix;
        setViewSource(ViewSource::Matrix);
    }

    void Pipeline::setProjection() {
        setProjection(60.0f, 4.0f/3.0f, 0.01f, 1000.0f);
    }

    void Pipeline::setProjection(float fov, float aspect, float near, float far) {
        _projection = glm::perspective(glm::radians(fov), aspect, near, far);
    }

    void Pipeline::setProjection(const glm::mat4& projectionMatrix) {
        _projection = projectionMatrix;
    }

    const glm::mat4 Pipeline::getMV() const {
        return getView() * getModel();
    }

    const glm::mat4 Pipeline::getMVP() const {
        return getProjection() * getView() * getModel();
    }

    const glm::mat4& Pipeline::getModel() const {
        return _model;
    }

    const glm::mat4& Pipeline::getView() const throw(GLUL::Exception::FatalError) {
        if(_viewSource == ViewSource::Camera)
            if(_camera != nullptr)
                return _camera->getMatrix();
            else
                throw GLUL::Exception::FatalError("Request for view matrix without camera");
        else
            return _view;
    }

    const glm::mat4& Pipeline::getProjection() const {
        return _projection;
    }

    const GLUL::Interface::Camera* Pipeline::getCamera() const {
        return _camera;
    }

}
