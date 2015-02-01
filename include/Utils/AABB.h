#ifndef UTILS_AABB_H_INCLUDED
#define UTILS_AABB_H_INCLUDED

#include <Utils/Point.h>
#include <Utils/GL+/Pipeline.h>

#include <glm/vec3.hpp>

#include <vector>

namespace Util {

    class AABB {
        public:
            AABB();
            AABB(const glm::vec3& min, const glm::vec3& max);

            void clear();

            bool intersect(const AABB& box2) const;
            void render(const GL::Pipeline& pipeline) const;
            void updateBy(const glm::vec3& vertex);

            void setMin(const glm::vec3& min);
            void setMax(const glm::vec3& max);
            void setMin(float x, float y, float z);
            void setMax(float x, float y, float z);

            void setMinX(float x);
            void setMinY(float y);
            void setMinZ(float z);
            void setMaxX(float x);
            void setMaxY(float y);
            void setMaxZ(float z);

            const glm::vec3& getMin() const;
            const glm::vec3& getMax() const;
            glm::vec3 getCenter() const;

        public:
            static bool intersect(const AABB& box1, const AABB& box2);
            static void render(const AABB& box, const GL::Pipeline& pipeline);
            static void setLines(const AABB& box, std::vector<glm::vec3>& lines);
            static std::vector<glm::vec3> getLines(const AABB& box);

        private:
            bool _initialized;
            glm::vec3 _min;
            glm::vec3 _max;
    };

}

#endif