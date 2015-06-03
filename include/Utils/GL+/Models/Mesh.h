#ifndef UTILS_GL_MODELS_MESH_H_INCLUDED
#define UTILS_GL_MODELS_MESH_H_INCLUDED

#include <Utils/Interfaces/Model.h>
#include <Utils/GL+/Pipeline.h>
#include <Utils/GL+/Texture.h>
#include <Utils/GL+/VertexArray.h>
#include <Utils/GL+/VertexBuffer.h>

#include <string>

namespace GL {

    namespace Model {

        class Material;

        class Mesh {
            public:
                Mesh(std::unordered_map<std::string, GL::Texture>* textures = nullptr);
                Mesh(const std::string& materialName, std::unordered_map<std::string, GL::Texture>* textures = nullptr);
                Mesh(const Mesh& mesh) = delete;
                Mesh(Mesh&& mesh);

                void build();
                void computeNormals(
                    Util::Interface::Model::NormalType type = Util::Interface::Model::NormalType::Default,
                    bool overwrite = false);

                void render(const GL::Pipeline& pipeline, const GL::Program& program, const Material& material) const;
                void renderAABB(const GL::Pipeline& pipeline) const;

                void addData(const glm::vec3& vertex);
                void addData(const glm::vec3& vertex, const glm::vec2& texCoord);
                void addData(const glm::vec3& vertex, const glm::vec2& texCoord, const glm::vec3& normal);
                void addData(const glm::vec3& vertex, const glm::vec3& normal);

                bool hasNormals() const;
                const Util::AABB& getAABB() const;

            public:
                std::string materialName;
                std::vector<glm::vec3> vertices;
                std::vector<glm::vec3> normals;
                std::vector<glm::vec2> texCoords;

            private:
                Util::AABB _aabb;
                GL::VertexArray _vao;
                GL::VertexBuffer _vboV;
                GL::VertexBuffer _vboT;
                GL::VertexBuffer _vboN;

                std::unordered_map<std::string, GL::Texture>* _textures;
        };

    }

}

#endif