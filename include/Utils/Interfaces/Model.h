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
                Model();
                virtual ~Model();

                virtual bool load(const std::string& path) = 0;
                virtual bool reload();
                virtual bool clear() = 0;

                virtual void render(const GL::Pipeline& pipeline) const;
                virtual void render(const GL::Pipeline& pipeline, const GL::Program& program) const = 0;
                virtual void renderAABB(const GL::Pipeline& pipeline, bool detailed = false) const;
                virtual void update(double deltaTime = 0.0);

                virtual void printStats(bool detailed = false) const;

                virtual void computeFlatNormals(bool overwrite = false);
                virtual void computeSmoothNormals(bool overwrite = false);

                const bool hasVertices() const;
                const bool hasTexCoords() const;
                const bool hasNormals() const;
                const AABB& getAABB() const;
                const std::string& getPath() const;

            protected:
                AABB& getAABB();

                bool _hasVertices;
                bool _hasTexCoords;
                bool _hasNormals;
                AABB _aabb;
                std::string _path;
                GL::Program _program;
        };

    }

}

#endif