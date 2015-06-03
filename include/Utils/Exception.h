#ifndef UTILS_EXCEPTION_H_INCLUDED
#define UTILS_EXCEPTION_H_INCLUDED

#include <string>
#include <exception>

namespace Util {

    class Exception : public std::exception {

        public:
            Exception() throw();
            Exception(const std::string& description) throw();
            virtual ~Exception() throw();

            virtual void print() const;

            const char* what() const throw();
            const std::string& getDescription() const throw();

        protected:
            std::string _description;

        public:
            class FatalError;
            class InitializationFailed;
            class InvalidArgument;
    };

}

#include <Utils/Exceptions/FatalError.h>
#include <Utils/Exceptions/InitializationFailed.h>
#include <Utils/Exceptions/InvalidArgument.h>

#endif