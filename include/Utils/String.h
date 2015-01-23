#ifndef UTILS_STRING_H_INCLUDED
#define UTILS_STRING_H_INCLUDED

#include <string>
#include <vector>

namespace Util {

    class String {
        public:
            static std::vector<std::string>& split(
                std::vector<std::string> &input, 
                const std::string& data, 
                char delimiter, 
                bool skipEmpty = true
            );

            static std::vector<std::string> split(
                const std::string& data, 
                char delimiter, 
                bool skipEmpty = true
            );
    };

}

#endif