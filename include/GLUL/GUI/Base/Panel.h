#pragma once

#include <GLUL/GUI/Base/Container.h>

#include <glm/vec2.hpp>


namespace GLUL {

    namespace GUI {

        namespace Base {

            class GLUL_API Panel : public Container {
                public:
                    virtual ~Panel() = default;

                    virtual void validate() const;

                    virtual const glm::vec2 getScreenPosition() const;
                    virtual const glm::vec2 getOffset() const;
                    virtual const glm::vec2& getAreaSize() const;

                    virtual void setAreaSize(const glm::vec2& areaSize);

                protected:
                    Panel(const Container& parent);
                    Panel(const Container& parent, const glm::vec2& position, const glm::vec2& size);
                    Panel(const Container& parent, const glm::vec2& position, const glm::vec2& size, const glm::vec2& areaSize);

                    glm::vec2 _areaSize;

                    friend class Container;
            };

        }

    }

}
