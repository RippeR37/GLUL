#ifndef UTILS_HELPERS_HASHENUM_H_INCLUDED
#define UTILS_HELPERS_HASHENUM_H_INCLUDED

#include <Utils/Config.h>

#include <cstddef>
#include <functional>

namespace Util {

    namespace Helper {

        struct UTILS_API HashEnum {
            public:
                template <typename T>
                std::size_t operator()(T t) const {
                    return std::hash<unsigned int>()(static_cast<unsigned int>(t));
                }
        };

    }

}

#endif