#pragma once

#include <type_traits>
#include <utility>


namespace GLUL {

    namespace GUI {

        namespace Base {

            template<typename BackgroundType>
            BackgroundType& ComponentWithBackground::getBackground() {
                return static_cast<BackgroundType&>(*_background);
            }

            template<typename BackgroundType, typename... BackgroundCtorArgs>
            void ComponentWithBackground::setBackground(BackgroundCtorArgs&&... ctorArgs) {
                static_assert(
                    std::is_base_of<Background, BackgroundType>::value,
                    "Invalid BackgroundType: must derive from GLUL::GUI::Base::Background!"
                );
                static_assert(
                    std::is_abstract<BackgroundType>::value == false,
                    "Invalid BackgroundType: can't be abstract!"
                );

                BackgroundType* newBackground = new BackgroundType(*this, std::forward<BackgroundCtorArgs>(ctorArgs)...);

                _background.reset(newBackground);

                setInvalid();
            }

        }

    }

}
