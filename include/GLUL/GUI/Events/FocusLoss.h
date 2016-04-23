#pragma once

#include <GLUL/GUI/Events/EventTemplate.hpp>


namespace GLUL {

    namespace GUI {

        namespace Event {

            class GLUL_API FocusLoss : public EventTemplate<FocusLoss> {
                public:
                    FocusLoss& operator=(const FocusLoss&) = delete;
            };

        }

    }

}
