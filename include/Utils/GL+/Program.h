#ifndef UTILS_GL_PROGRAM_H_INCLUDED
#define UTILS_GL_PROGRAM_H_INCLUDED

#include <Utils/Exception.h>
#include <Utils/GL+/Shader.h>
#include <Utils/GL+/Uniform.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>
#include <string>
#include <vector>
#include <sstream>

namespace GL {

    class Program {
        public:
            Program();
            Program(Program&& program);
            Program(const std::string& vsPath, const std::string& fsPath);
            Program(const Shader& vertexShader, const Shader& fragmentShader);
            ~Program();

            Program& operator=(Program&& program);
            Uniform& operator[](const std::string& uniformName) throw(std::out_of_range);
            const Uniform& operator[](const std::string& uniformName) const throw(std::out_of_range);

            void load(const Shader& vertexShader, const Shader& fragmentShader);
            void use() const;
            void unbind() const;

            bool isLinked() const;
            GLuint getID() const;
            GLuint getUniformLocation(const std::string& uniformName);
            const Uniform& getUniform(const std::string& uniformName);

        private:
            Program& operator=(const Program&);
            Program(const Program&);

            void create();
            void destroy();
            void mapUniforms(const Shader& shader);
            bool link(const Shader& vertexShader, const Shader& fragmentShader) throw(Util::Exception::FatalError);

            bool _linked;
            GLuint _programID;
            std::map<std::string, Uniform> _uniforms;
    };

}

#endif