#pragma once

#include <GLUL/Config.h>

#include <cstddef>
#include <functional>

namespace GLUL {

    namespace Helper {

        struct GLUL_API HashEnum {
            public:
                template <typename T>
                std::size_t operator()(T t) const {
                    return std::hash<unsigned int>()(static_cast<unsigned int>(t));
                }
        };

    }

}
