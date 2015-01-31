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

    bool String::startsWith(const std::string& string, const std::string& prefix) {
        bool result = true;

        if(string.size() < prefix.size())
            result = false;

        else
            for(int i = 0; i < prefix.size(); ++i)
                if(string[i] != prefix[i]) {
                    result = false;
                    break;
                }

        return result;
    }

    bool String::endsWith(const std::string& string, const std::string& sufix) {
        bool result = true;

        if(string.size() < sufix.size())
            result = false;

        else
            for(int i = string.size() - sufix.size(); i < string.size(); ++i)
                if(string[i] != sufix[i]) {
                    result = false;
                    break;
                }

        return result;
    }

}