#ifndef UTILS_INTERFACES_MODEL_H_INCLUDED
#define UTILS_INTERFACES_MODEL_H_INCLUDED

#include <Utils/AABB.h>
#include <Utils/GL+/Pipeline.h>

#include <string>

namespace Util {

    namespace Interface {

        class Model {
            public:
                Model();
                virtual ~Model();

                virtual void load(const std::string& path) = 0;
                virtual void reload();
                virtual void clear() = 0;

                virtual void render(const GL::Pipeline& pipeline) const = 0;
                virtual void renderAABB(const GL::Pipeline& pipeline, bool detailed = false) const;
                virtual void update();

                virtual void printStats(bool detailed = false) const;

                virtual void computeFlatNormals(bool overwrite = false);
                virtual void computeSmoothNormals(bool overwrite = false);

                const bool hasVertices() const;
                const bool hasTexCoords() const;
                const bool hasNormals() const;
                const AABB& getAABB() const;
                const std::string& getPath() const;

            private:
                AABB& getAABB();

            private:
                bool _hasVertices;
                bool _hasTexCoords;
                bool _hasNormals;
                AABB _aabb;
                std::string _path;
        };

    }

}

#endif