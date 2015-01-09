#include <Utils/GL+/Shader.h>
#include <Utils/File.h>

#include <vector>

namespace GL {

    Shader::Shader(Type type) {
        create(type);
    }

    Shader::Shader(const std::string& path, Type type) {
        create(type);
        load(path, type);
    }
    
    Shader::Shader(Shader&& shader) {
        create(shader.getType());

        std::swap(_compiled, shader._compiled);
        std::swap(_type, shader._type);
        std::swap(_shaderID, shader._shaderID);

        _path.swap(shader._path);
        _code.swap(shader._code);
    }

    Shader::~Shader() {
        destroy();
    }

    Shader& Shader::operator=(Shader&& shader) {
        std::swap(_compiled, shader._compiled);
        std::swap(_type, shader._type);
        std::swap(_shaderID, shader._shaderID);

        _path.swap(shader._path);
        _code.swap(shader._code);

        return *this;
    }
    
    GLuint Shader::getID() const {
        if(_compiled) {
            return _shaderID;
        } else {
            return 0;
        }
    }

    Shader::Type Shader::getType() const {
        return _type;
    }

    void Shader::create(Type type) {
        _shaderID = glCreateShader(static_cast<GLenum>(type));
        _compiled = false;
    }

    void Shader::destroy() {
        glDeleteShader(_shaderID);
    }

    void Shader::load(const std::string& path, Type type) {
        if(_compiled == false) {
            _path = path;
            _code = Util::File::read(_path, Util::File::ReadMode::Text, true);
            _compiled = compile();
        }
    }

    bool Shader::compile() {
        std::vector<char> shaderErrorMsg;
        GLint result;
        GLint infoLen;
        GLchar const* codePtr;

        // Create and compile shader
        codePtr  = _code.c_str();
        glShaderSource(_shaderID, 1, &codePtr, nullptr);
        glCompileShader(_shaderID);

        // Check for errors
        glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &result);
        glGetShaderiv(_shaderID, GL_INFO_LOG_LENGTH, &infoLen);
        shaderErrorMsg.resize(infoLen);
        glGetShaderInfoLog(_shaderID, infoLen, NULL, &shaderErrorMsg[0]);

        if(result != GL_TRUE) {
            std::string errorMsg = std::string("Shader compilation failed:\nFile: " + _path + "\nMessage:\n" + &shaderErrorMsg[0]);
            throw Util::Exception::FatalError(errorMsg.c_str());
        }

        return true;
    }

}
