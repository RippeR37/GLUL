#pragma once

#include <GLUL/GUI/Container.h>

#include <glm/vec2.hpp>


namespace GLUL {

    namespace GUI {

        class GLUL_API Panel : public Container {
            public:
                virtual ~Panel() = default;

                virtual void validate() const;

                const glm::vec2 getScreenPosition() const;
                const glm::vec2 getOffset() const;
                const glm::vec2& getAreaSize() const;

                void setAreaSize(const glm::vec2& areaSize);

            protected:
                Panel(const Container& parent);
                Panel(const Container& parent, const glm::vec2& position, const glm::vec2& size);
                Panel(const Container& parent, const glm::vec2& position, const glm::vec2& size, const glm::vec2& areaSize);

                virtual void _pushToBatch(G2D::TexturedBatch& texBatch) const;

                glm::vec2 _areaSize;

                friend class Container;
        };

    }

}
