#include <Utils/String.h>

#include <algorithm>
#include <functional>
#include <istream>
#include <sstream>
#include <cctype>

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

    std::string& String::trim(std::string &string) {
        rtrim(ltrim(string));
        return string;
    }

    std::string& String::ltrim(std::string &string) {
        string.erase(
            string.begin(),
            std::find_if(
                string.begin(),
                string.end(),
                std::not1(std::ptr_fun<int, int>(std::isspace))
            )
        );
        return string;
    }

    std::string& String::rtrim(std::string &string) {
        string.erase(
            std::find_if(
                string.rbegin(),
                string.rend(),
                std::not1(std::ptr_fun<int, int>(std::isspace))
            ).base(), 
            string.end()
        );
        return string;
    }

    bool String::startsWith(const std::string& string, const std::string& prefix) {
        bool result = true;

        if(string.size() < prefix.size())
            result = false;

        else
            for(unsigned int i = 0; i < prefix.size(); ++i)
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
            for(unsigned int i = string.size() - sufix.size(); i < string.size(); ++i)
                if(string[i] != sufix[i]) {
                    result = false;
                    break;
                }

        return result;
    }

}