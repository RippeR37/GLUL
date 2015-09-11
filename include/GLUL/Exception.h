#pragma once

#include <GLUL/Config.h>

#include <string>
#include <exception>


namespace GLUL {

    class GLUL_API Exception : public std::exception {

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

#include <GLUL/Exceptions/FatalError.h>
#include <GLUL/Exceptions/InitializationFailed.h>
#include <GLUL/Exceptions/InvalidArgument.h>
