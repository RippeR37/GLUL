#include <Utils/GL+/Models/Material.h>
#include <Utils/Logger.h>

namespace GL {

    namespace Model {

        const Material Material::Default = Material("defaultMaterial");

        Material::Material(const std::string& name) {
            this->name = name;

            colorAmbient  = glm::vec3(1.0f);
            colorDiffuse  = glm::vec3(1.0f);
            colorSpecular = glm::vec3(0.0f);

            exponentSpecular = 10.0f;
            alphaFactor = 1.0f;

            illumination = 2;

            textureAmbient = "";
            textureDiffuse = "";
            textureSpecular = "";
        }

        bool Material::processInput(const std::vector<std::string>& tokens) {
            if(tokens.size() > 0) {
                if(tokens[0][0] == '#') {
                    // comment, just ignore it

                } else if(tokens[0] == "Ka" && tokens.size() > 3) {
                    try {
                        glm::vec3 data;

                        data.r = std::stof(tokens[1]);
                        data.g = std::stof(tokens[2]);
                        data.b = std::stof(tokens[3]);

                        colorAmbient = data;

                    } catch(...) {
                        Util::Log::Stream("_Library") << "Unable to read parameter '" + tokens[0] + "' for material '" + name + "'";
                    }

                } else if(tokens[0] == "Kd" && tokens.size() > 3) {
                    try {
                        glm::vec3 data;

                        data.r = std::stof(tokens[1]);
                        data.g = std::stof(tokens[2]);
                        data.b = std::stof(tokens[3]);

                        colorDiffuse = data;

                    } catch(...) {
                        Util::Log::Stream("_Library") << "Unable to read parameter '" + tokens[0] + "' for material '" + name + "'";
                    }

                } else if(tokens[0] == "Ks" && tokens.size() > 3) {
                    try {
                        glm::vec3 data;

                        data.r = std::stof(tokens[1]);
                        data.g = std::stof(tokens[2]);
                        data.b = std::stof(tokens[3]);

                        colorSpecular = data;

                    } catch(...) {
                        Util::Log::Stream("_Library") << "Unable to read parameter '" + tokens[0] + "' for material '" + name + "'";
                    }

                } else if(tokens[0] == "Ns" && tokens.size() > 1) {
                    try {
                        float value;

                        value = std::stof(tokens[1]);
                        exponentSpecular = value;

                    } catch(...) {
                        Util::Log::Stream("_Library") << "Unable to read parameter '" + tokens[0] + "' for material '" + name + "'";
                    }

                } else if((tokens[0] == "d" || tokens[0] == "Tr") && tokens.size() > 1) {
                    try {
                        float value;

                        value = std::stof(tokens[1]);
                        alphaFactor = value;

                    } catch(...) {
                        Util::Log::Stream("_Library") << "Unable to read parameter '" + tokens[0] + "' for material '" + name + "'";
                    }

                } else if(tokens[0] == "illum" && tokens.size() > 1) {
                    try {
                        unsigned int value;

                        value = static_cast<unsigned int>(std::stoul(tokens[1]));
                        illumination = value;

                    } catch(...) {
                        Util::Log::Stream("_Library") << "Unable to read parameter '" + tokens[0] + "' for material '" + name + "'";
                    }

                } else if(tokens[0] == "map_Ka" && tokens.size() > 1) {
                    textureAmbient = tokens[1];

                } else if(tokens[0] == "map_Kd" && tokens.size() > 1) {
                    textureDiffuse = tokens[1];

                } else if(tokens[0] == "map_Ks" && tokens.size() > 1) {
                    textureSpecular = tokens[1];

                } else {
                    Util::Log::Stream("_Library") << "Unsupported parameter '" + tokens[0] + "' found for material '" + name + "'";
                }
            }

            return true;
        }

    }

}