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
                    "Invalid ComponentType: must derive from GLUL::GUI::Base::Component!"
                );
                static_assert(
                    std::is_abstract<ComponentType>::value == false,
                    "Invalid ComponentType: can't be abstract type!"
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
