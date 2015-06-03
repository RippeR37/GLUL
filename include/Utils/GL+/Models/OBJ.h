#ifndef UTILS_GL_MODELS_OBJ_H_INCLUDED
#define UTILS_GL_MODELS_OBJ_H_INCLUDED

#include <Utils/Interfaces/Model.h>
#include <Utils/GL+/Texture.h>
#include <Utils/GL+/Models/Mesh.h>
#include <Utils/GL+/Models/Material.h>

#include <string>
#include <unordered_map>

namespace GL {

    namespace Model {

        class OBJ : public Util::Interface::Model {
            public:
                OBJ();
                OBJ(const std::string& path);
                ~OBJ();

                bool load(const std::string& path, NormalType forcedNormalType = NormalType::Default);
                bool clear();

                void render(const GL::Pipeline& pipeline, const GL::Program& program) const;
                void renderAABB(const GL::Pipeline& pipeline, bool detailed) const;
                void printStats(bool withDetails = false) const;

                void computeNormals(NormalType type = NormalType::Default, bool overwrite = false);

                const std::vector<Mesh>& getMeshes() const;
                const std::unordered_map<std::string, Material>& getMaterials() const;
                const std::unordered_map<std::string, GL::Texture>& getTextures() const;

                static bool parseFile(
                    const std::string& path,
                    Util::AABB& aabb,
                    std::vector<Mesh>& meshes,
                    std::unordered_map<std::string, Material>& materials,
                    std::unordered_map<std::string, GL::Texture>& textures,
                    NormalType forcedNormalType = NormalType::Default
                );

                static bool loadMaterials(
                    const std::string& path,
                    std::unordered_map<std::string, Material>& materials,
                    std::unordered_map<std::string, GL::Texture>& textures
                );

            private:
                std::vector<Mesh>& getMeshes();
                std::unordered_map<std::string, Material>& getMaterials();
                std::unordered_map<std::string, GL::Texture>& getTextures();

                std::vector<Mesh> _meshes;
                std::unordered_map<std::string, Material> _materials;
                std::unordered_map<std::string, GL::Texture> _textures;

            public:
                using Util::Interface::Model::render; // make render(const GL::Pipeline&) visible
        };

    }

}

#endif