#ifndef UTILS_STRING_H_INCLUDED
#define UTILS_STRING_H_INCLUDED

#include <string>
#include <vector>

namespace Util {

    class String {
        public:
            typedef std::vector<std::string> stringVector;

        public:
            static stringVector& split(stringVector& input, const std::string& data, char delimiter, bool skipEmpty = true);
            static stringVector  split(const std::string& data, char delimiter, bool skipEmpty = true);

            static bool startsWith(const std::string& string, const std::string& prefix);
            static bool endsWith(const std::string& string, const std::string& sufix);
    };

}

#endif