#pragma once

#include <GLUL/Config.h>
#include <GLUL/GUI/Base/Background.h>
#include <GLUL/GUI/Base/Component.h>

#include <memory>


namespace GLUL {

    namespace GUI {

        namespace Base {

            class GLUL_API ComponentWithBackground : public Component {
                public:
                    virtual ~ComponentWithBackground() = default;

                    Background& getBackground();

                    template<typename BackgroundType>
                    BackgroundType& getBackground();

                    template<typename BackgroundType, typename... BackgroundCtorArgs>
                    void setBackground(BackgroundCtorArgs&&... args);

                protected:
                    ComponentWithBackground(const Container& parent, Background* background);
                    ComponentWithBackground(const Container& parent, const glm::vec2& size, const glm::vec2& position, Background* background);

                    virtual void _pushToBatch(G2D::TexturedBatch& texBatch) const;

                    std::unique_ptr<Background> _background;

                    friend class Container;

            };

        }

    }

}

#include <GLUL/GUI/Base/ComponentWithBackground.hpp>
