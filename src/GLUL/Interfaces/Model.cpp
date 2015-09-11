#include <GLUL/Interfaces/Model.h>

namespace GLUL {

    namespace Interface {

        Model::Model() : _hasVertices(false), _hasTexCoords(false), _hasNormals(false), _path("") {

        }

        Model::~Model() {

        }

        bool Model::reload() {
            if(clear())
                if(load(getPath(), GLUL::Interface::Model::NormalType::Default))
                    return true;
            
            return false;
        }

        void Model::render(const GL::Pipeline& pipeline) const {
            render(pipeline, _program);
        }

        void Model::renderAABB(const GL::Pipeline& pipeline, bool detailed) const {
            (void) detailed;

            _aabb.render(pipeline);
        }

        void Model::update(double deltaTime) {
            (void) deltaTime;
        }

        void Model::printStats(bool detailed) const {
            (void) detailed;
        }

        void Model::setMatrix() {
            setMatrix(glm::mat4(1.0f));
        }

        void Model::setMatrix(const glm::mat4& matrix) {
            _matrix = matrix;
        }

        bool Model::hasVertices() const {
            return _hasVertices;
        }

        bool Model::hasTexCoords() const {
            return _hasTexCoords;
        }

        bool Model::hasNormals() const {
            return _hasNormals;
        }

        const AABB& Model::getAABB() const {
            return _aabb;
        }

        const std::string& Model::getPath() const {
            return _path;
        }

        const glm::mat4& Model::getMatrix() const {
            return _matrix;
        }

        glm::mat4& Model::getMatrix() {
            return _matrix;
        }
    
    }

}