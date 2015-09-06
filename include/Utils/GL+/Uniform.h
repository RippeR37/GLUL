#ifndef UTILS_GL_UNIFORM_H_INCLUDED
#define UTILS_GL_UNIFORM_H_INCLUDED

#include <Utils/Config.h>

#include <GL/glew.h>

#include <string>


namespace GL {

    class UTILS_API Uniform {
        public:
            Uniform();
            Uniform(GLuint location);
            ~Uniform();

            GLuint getLocation() const;
            
            void setSampler(GLint value) const;

        public:
            template<typename T> void operator=(const T& value) const;

            template<typename T> void set(T v0) const;
            template<typename T> void set(T v0, T v1) const;
            template<typename T> void set(T v0, T v1, T v2) const;
            template<typename T> void set(T v0, T v1, T v2, T v3) const;
            
            template<typename T> void setVec(const T& value, GLsizei count = 1) const;
            template<typename T> void setMatrix(const T& value, GLsizei count = 1, GLboolean transpose = GL_FALSE) const;

        private:
            GLint _location;
    };

}

#endif
