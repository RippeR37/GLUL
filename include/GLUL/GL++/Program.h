#pragma once

#include <GLUL/Config.h>
#include <GLUL/Exception.h>
#include <GLUL/GL++/Shader.h>
#include <GLUL/GL++/Uniform.h>

#include <GL/glew.h>

#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>


namespace GL {

    class GLUL_API Program {
        public:
            Program();
            Program(Program&& program);
            Program(const std::string& vsPath, const std::string& fsPath);
            Program(const Shader& vertexShader, const Shader& fragmentShader);
            Program(const Program&) = delete;
            ~Program();

            Program& operator=(const Program&) = delete;
            Program& operator=(Program&& program);

            Uniform& operator[](const std::string& uniformName);
            const Uniform& operator[](const std::string& uniformName) const;

            void create();
            void destroy();

            void load(const Shader& vertexShader, const Shader& fragmentShader);
            void use() const;
            void unbind() const;

            bool isLinked() const;
            GLuint getID() const;

            GLuint getUniformLocation(const std::string& uniformName) const throw(std::out_of_range);
            const Uniform& getUniform(const std::string& uniformName) const throw(std::out_of_range);

        private:
            void mapUniforms(const Shader& shader);
            bool link(const Shader& vertexShader, const Shader& fragmentShader) throw(GLUL::Exception::FatalError);

            bool isCreated() const;

            bool _isLinked;
            bool _isCreated;
            GLuint _programID;
            std::unordered_map<std::string, Uniform> _uniforms;
    };

}
