#pragma once

#include <GLUL/Config.h>
#include <GLUL/Interfaces/Model.h>
#include <GLUL/GL++/Pipeline.h>
#include <GLUL/GL++/Texture.h>
#include <GLUL/GL++/VertexArray.h>
#include <GLUL/GL++/VertexBuffer.h>

#include <string>


namespace GL {

    namespace Model {

        class Material;

        class GLUL_API Mesh {
            public:
                Mesh(std::unordered_map<std::string, GL::Texture>* textures = nullptr);
                Mesh(const std::string& materialName, std::unordered_map<std::string, GL::Texture>* textures = nullptr);
                Mesh(const Mesh& mesh) = delete;
                Mesh(Mesh&& mesh);

                void build();
                void computeNormals(
                    GLUL::Interface::Model::NormalType type = GLUL::Interface::Model::NormalType::Default,
                    bool overwrite = false);

                void render(const GL::Pipeline& pipeline, const GL::Program& program, const Material& material) const;
                void renderAABB(const GL::Pipeline& pipeline) const;

                void addData(const glm::vec3& vertex);
                void addData(const glm::vec3& vertex, const glm::vec2& texCoord);
                void addData(const glm::vec3& vertex, const glm::vec2& texCoord, const glm::vec3& normal);
                void addData(const glm::vec3& vertex, const glm::vec3& normal);

                bool hasNormals() const;
                const GLUL::AABB& getAABB() const;

            public:
                std::string materialName;
                std::vector<glm::vec3> vertices;
                std::vector<glm::vec3> normals;
                std::vector<glm::vec2> texCoords;

            private:
                GLUL::AABB _aabb;
                GL::VertexArray _vao;
                GL::VertexBuffer _vboV;
                GL::VertexBuffer _vboT;
                GL::VertexBuffer _vboN;

                std::unordered_map<std::string, GL::Texture>* _textures;
        };

    }

}
