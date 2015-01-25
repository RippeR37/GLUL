#include <Utils/String.h>

#include <sstream>
#include <istream>

namespace Util {
    
    std::vector<std::string>& String::split(std::vector<std::string> &input,  const std::string& data, char delimiter,  bool skipEmpty) {
        std::stringstream stream(data);
        std::string token;

        while(std::getline(stream, token, delimiter)) {
            if(!token.empty() || !skipEmpty)
                input.push_back(token);
        }

        return input;
    }

    std::vector<std::string> String::split(const std::string& data, char delimiter, bool skipEmpty) {
        std::vector<std::string> tokens;
        String::split(tokens, data, delimiter, skipEmpty);
        return tokens;
    }

}