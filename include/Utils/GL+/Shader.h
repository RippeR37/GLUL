#ifndef UTILS_GL_SHADER_H_INCLUDED
#define UTILS_GL_SHADER_H_INCLUDED

#include <Utils/Config.h>
#include <Utils/Exception.h>

#include <GL/glew.h>

#include <map>
#include <string>


namespace GL {

    class UTILS_API Shader {
        public:
            enum class Type : GLenum {
                VertexShader   = GL_VERTEX_SHADER,
                FragmentShader = GL_FRAGMENT_SHADER,
                GeometryShader = GL_GEOMETRY_SHADER,
            };

        public:
            Shader(Type type);
            Shader(const std::string& path, Type type);
            Shader(Shader&& shader);
            Shader(const Shader&) = delete;
            ~Shader();

            Shader& operator=(const Shader&) = delete;
            Shader& operator=(Shader&& shader);

            void create();
            void destroy();

            void load(const std::string& path);

            bool isCompiled() const;
            GLuint getID() const;
            Type getType() const;

        private:
            bool compile() throw(Util::Exception::FatalError);

            bool isCreated() const;
            
            bool _isCreated;
            bool _isCompiled;
            Type _type;
            GLuint _shaderID;
            std::string _path;
            std::string _code;

        public:
            friend class Program;
    };

}

#endif
