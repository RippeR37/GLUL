#include <Utils/GL+/Program.h>
#include <Utils/File.h>

#include <iostream>

namespace GL {

    Program::Program() {
        create();
    }

    Program::Program(Program&& program) {
        create();

        std::swap(_linked,      program._linked);
        std::swap(_programID,   program._programID);
        _uniforms.swap(program._uniforms);
    }

    Program::Program(const std::string& vsPath, const std::string& fsPath) {
        create();

        Shader vertexShader(vsPath, Shader::Type::VertexShader);
        Shader fragmentShader(fsPath, Shader::Type::FragmentShader);
        load(vertexShader, fragmentShader);
    }

    Program::Program(const Shader& vertexShader, const Shader& fragmentShader) {
        create();

        load(vertexShader, fragmentShader);
    }

    Program::~Program() {
        destroy();
    }
    
    Program& Program::operator=(Program&& program) {
        std::swap(_linked,      program._linked);
        std::swap(_programID,   program._programID);
        _uniforms.swap(program._uniforms);

        return *this;
    }

    Uniform& Program::operator[](const std::string& uniformName) {
        return _uniforms[uniformName];
    }
    
    void Program::load(const Shader& vertexShader, const Shader& fragmentShader) {
        if(_linked == false) {
            _linked = link(vertexShader, fragmentShader);
            mapUniforms(vertexShader);
            mapUniforms(fragmentShader);
        }
    }

    void Program::use() const {
        if(_linked)
            glUseProgram(_programID);
    }

    void Program::unbind() const {
        glUseProgram(0);
    }
    
    bool Program::isLinked() const {
        return _linked;
    }

    GLuint Program::getID() const {
        return _programID;
    }

    GLuint Program::getUniformLocation(const std::string& uniformName) {
        return _uniforms[uniformName].getLocation();
    }

    const Uniform& Program::getUniform(const std::string& uniformName) {
        return _uniforms[uniformName];
    }

    void Program::create() {
        _programID = glCreateProgram();
        _linked = false;
    }

    void Program::destroy() {
        glDeleteProgram(_programID);
    }

    bool Program::link(const Shader& vertexShader, const Shader& fragmentShader) {
        std::vector<char> programErrorMsg;
        GLint result;
        GLint infoLen;

        // Create and link program
        glAttachShader(_programID, vertexShader.getID());
        glAttachShader(_programID, fragmentShader.getID());
        glLinkProgram(_programID);

        // Check for errors
        glGetProgramiv(_programID, GL_LINK_STATUS, &result);
        glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &infoLen);
        programErrorMsg.resize(infoLen);
        glGetProgramInfoLog(_programID, infoLen, NULL, &programErrorMsg[0]);

        if(result != GL_TRUE) {
            std::string errorMsg = std::string("Program linking failed:") + std::string(&programErrorMsg[0]);
            throw Util::Exception::FatalError(errorMsg.c_str());
        }
        
        return true;
    }

    void Program::mapUniforms(const Shader& shader) {
        std::stringstream stream;
        std::string uniformName;
        std::string uniformType;

        stream.str(shader._code);
        while(stream.good()) {
            stream >> uniformName;
            if(uniformName == "uniform") {
                stream >> uniformType;
                stream >> uniformName;

                // Semicolon
                if(uniformName[uniformName.size()-1] == ';')
                    uniformName.erase(uniformName.size() - 1);

                // Arrays
                uniformName = uniformName.substr(0, uniformName.find_last_of("["));

                _uniforms[uniformName] = Uniform(glGetUniformLocation(_programID, uniformName.c_str()));
            }
        }
    }

}
