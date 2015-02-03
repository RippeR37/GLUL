#include <Utils/Interfaces/Model.h>

namespace Util {

    namespace Interface {

        Model::Model() : _hasVertices(false), _hasTexCoords(false), _hasNormals(false), _path("") {

        }

        Model::~Model() {

        }

        bool Model::reload() {
            if(clear())
                if(load(getPath()))
                    return true;
            
            return false;
        }

        void Model::render(const GL::Pipeline& pipeline) const {
            render(pipeline, _program);
        }

        void Model::renderAABB(const GL::Pipeline& pipeline, bool detailed) const {
            _aabb.render(pipeline);
        }

        void Model::update(double deltaTime) {

        }

        void Model::printStats(bool detailed) const {

        }

        void Model::computeFlatNormals(bool overwrite) {

        }

        void Model::computeSmoothNormals(bool overwrite) {

        }

        const bool Model::hasVertices() const {
            return _hasVertices;
        }

        const bool Model::hasTexCoords() const {
            return _hasTexCoords;
        }

        const bool Model::hasNormals() const {
            return _hasNormals;
        }

        const AABB& Model::getAABB() const {
            return _aabb;
        }

        const std::string& Model::getPath() const {
            return _path;
        }

        AABB& Model::getAABB() {
            return _aabb;
        }
    
    }

}