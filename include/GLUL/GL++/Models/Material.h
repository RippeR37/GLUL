#pragma once

#include <GLUL/Config.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <string>
#include <vector>


namespace GL {

    namespace Model {

        // Unsupported:
        //
        // map_Ns - specular gighlight component
        // map_d - alpha texture map
        // map_bump, bump - bump map
        // disp - displacement map
        // decal - stencil decal texture
        //
        // and special options for these

        class GLUL_API Material {
            public:
                static const Material Default;

            public:
                Material(const std::string& name);

                bool processInput(const std::vector<std::string>& tokens);


            public:
                std::string name;               // name
                glm::vec3 colorAmbient;         // Ka
                glm::vec3 colorDiffuse;         // Kd
                glm::vec3 colorSpecular;        // Ks
                float exponentSpecular;         // Ns
                float alphaFactor;              // d, Tr
                unsigned int illumination;      // illum
                std::string textureAmbient;     // map_Ka
                std::string textureDiffuse;     // map_Kd
                std::string textureSpecular;    // map_Ks
        };

    }

}
