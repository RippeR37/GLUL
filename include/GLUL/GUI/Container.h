#pragma once

#include <GLUL/GUI/Component.h>

#include <list>
#include <memory>
#include <set>


namespace GLUL {

    namespace GUI {

        class GLUL_API Container : public Component {
            public:
                virtual ~Container() = default;

                virtual void render() const;
                virtual void update(double deltaTime);
                virtual void validate() const;

                template<class ComponentType, typename... CtorArgs>
                ComponentType& add(CtorArgs...);

                void remove(Component& component);

                bool isUnderMouse(const Component& component) const;
                virtual const glm::vec2 getOffset() const;

                virtual void setInvalid() const;
                virtual void setFocused(bool flag);

            protected:
                Container();
                Container(const Container& parent);
                Container(const Container& parent, const glm::vec2& size, const glm::vec2& position);

                void _invalidateComponents() const;
                void _initializeEventForwarding();
                void _rebuildBatch() const;
                void _setupClipping() const;
                void _revertClipping() const;
                virtual void _pushToBatch(G2D::TexturedBatch& texBatch) const;

                mutable bool _wasScissorTestActive;
                mutable G2D::Rectangle _scissorTestBox;
                mutable G2D::TexturedBatch _batch;
                std::list<std::unique_ptr<Component>> _components;
                std::set<Component*> _componentsUnderMouse;

                friend Component;
        };

    }

}

#include <GLUL/GUI/Container.hpp>
