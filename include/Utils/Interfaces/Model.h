#ifndef UTILS_INTERFACES_MODEL_H_INCLUDED
#define UTILS_INTERFACES_MODEL_H_INCLUDED

#include <Utils/AABB.h>
#include <Utils/GL+/Pipeline.h>
#include <Utils/GL+/Program.h>

#include <string>

namespace Util {

    namespace Interface {

        class Model {
            public:
                enum class NormalType {
                    Flat,
                    Smooth,
                    Default,
                };

            public:
                Model();
                virtual ~Model();

                virtual bool load(const std::string& path, Util::Interface::Model::NormalType forcedNormalType) = 0;
                virtual bool reload();
                virtual bool clear() = 0;

                virtual void render(const GL::Pipeline& pipeline) const;
                virtual void render(const GL::Pipeline& pipeline, const GL::Program& program) const = 0;
                virtual void renderAABB(const GL::Pipeline& pipeline, bool detailed) const;
                virtual void update(double deltaTime);

                virtual void printStats(bool detailed) const;

                virtual void computeNormals(Util::Interface::Model::NormalType type, bool overwrite) = 0;

                virtual void setMatrix();
                virtual void setMatrix(const glm::mat4& matrix);

                const bool hasVertices() const;
                const bool hasTexCoords() const;
                const bool hasNormals() const;
                const AABB& getAABB() const;
                const std::string& getPath() const;
                const glm::mat4& getMatrix() const;

            protected:
                AABB& getAABB();
                glm::mat4& getMatrix();

                bool _hasVertices;
                bool _hasTexCoords;
                bool _hasNormals;
                AABB _aabb;
                std::string _path;
                glm::mat4 _matrix;
                GL::Program _program;
        };

    }

}

#endif