#pragma once

#include <type_traits>
#include <utility>


namespace GLUL {

    namespace GUI {

        namespace Base {

            template<class ComponentType, typename... CtorArgs>
            ComponentType& Container::add(CtorArgs... ctorArgs)
            {
                static_assert(
                    std::is_base_of<Component, ComponentType>::value,
                    "Can't add component that doesn't derive from GLUL::GUI::Component!"
                );
                static_assert(
                    std::is_abstract<ComponentType>::value == false,
                    "Cant add component of abstract type!"
                );

                std::unique_ptr<ComponentType> component { new ComponentType(*this, std::forward<CtorArgs>(ctorArgs)...) };
                ComponentType& componentRef = *component;

                _components.push_back(std::move(component));

                setInvalid();

                return componentRef;
            }

        }

    }

}
