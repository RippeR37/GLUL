#include <Utils/GL+/Models/OBJ.h>
#include <Utils/File.h>
#include <Utils/String.h>

#include <iostream>
#include <fstream>

namespace GL {

    namespace Model {

        OBJ::OBJ() {
            _program.load(
                GL::Shader("assets/shaders/utilMeshOBJ.vp", GL::Shader::Type::VertexShader),
                GL::Shader("assets/shaders/utilMeshOBJ.fp", GL::Shader::Type::FragmentShader)
            );
        }

        OBJ::OBJ(const std::string& path) : OBJ() {
            load(path);
        }

        OBJ::~OBJ() {

        }

        bool OBJ::load(const std::string& path, NormalType forcedNormalType) {
            return parseFile(path, getAABB(), getMeshes(), getMaterials(), getTextures(), forcedNormalType);
        }

        bool OBJ::clear() {
            getMeshes().clear();
            getMaterials().clear();
            getTextures().clear();
            _aabb.clear();

            return true;
        }

        void OBJ::render(const GL::Pipeline& pipeline, const GL::Program& program) const {
            for(auto& mesh : getMeshes()) {
                auto& material = getMaterials().find(mesh.materialName);

                pipeline.setModel(getMatrix());

                if(material != getMaterials().end())
                    mesh.render(pipeline, program, material->second);
                else
                    mesh.render(pipeline, program, Material::Default);
            }
        }

        void OBJ::printStats(bool withDetails) const {
            std::cout << std::endl;
            std::cout << "Loaded meshes:    " << getMeshes().size() << std::endl;
            std::cout << "Loaded materials: " << getMaterials().size() << std::endl;
            std::cout << std::endl;

            if(withDetails) {
                int i = 0;
                std::string materialStatus;

                for(auto& mesh : getMeshes()) {
                    if(getMaterials().count(mesh.materialName) > 0)
                        materialStatus = "Ok";
                    else
                        materialStatus = "Missing!";

                    std::cout << "Mesh #" << i << std::endl;
                    std::cout << "   Material:  " << mesh.materialName << " (" << materialStatus << ")" << std::endl;
                    std::cout << "   Vertices:  " << mesh.vertices.size() << std::endl;
                    std::cout << "   TexCoords: " << mesh.texCoords.size() << std::endl;
                    std::cout << "   Normals:   " << mesh.normals.size() << std::endl;
                    std::cout << std::endl;
                    ++i;
                }
            }
        }

        void OBJ::computeNormals(NormalType type, bool overwrite) {
            for(auto& mesh : getMeshes()) {
                mesh.computeNormals(type, overwrite);
                mesh.build();
            }
        }

        bool OBJ::parseFile (
            const std::string& path,
            Util::AABB& aabb, 
            std::vector<Mesh>& meshes,
            std::unordered_map<std::string, Material>& materials, 
            std::unordered_map<std::string, GL::Texture>& textures, 
            NormalType forcedNormalType) 

        {
            int lineNumber = 0;
            bool meshInitialized;
            bool smoothNormals;

            std::string linePrefix;
            std::string fileName;
            std::string relativePath;
            std::string currentLine;
            std::string currentMeshName;
            std::ifstream objFile;
            std::vector<std::string> tokens;

            std::vector<glm::vec3> dataVertices;
            std::vector<glm::vec2> dataTexCoords;
            std::vector<glm::vec3> dataNormals;

            fileName = Util::File::getFilenameExtensionless(path);
            relativePath = Util::File::getPath(path) + "/";
            meshInitialized = false;
            smoothNormals = (forcedNormalType == NormalType::Smooth);
            
            objFile.open(path);

            if(objFile.is_open() == false) {
                // TODO : log it
                return false;

            } else {
                while(std::getline(objFile, currentLine)) {
                    ++lineNumber;
                    linePrefix = std::string("Line ") + std::to_string(lineNumber) + ": ";

                    tokens = Util::String::split(currentLine, ' ');

                    if(tokens.size() > 0) {

                        if(tokens[0] == "#") {
                            // comment, just ignore it

                        } else if(tokens[0] == "mtllib") {
                            if(tokens.size() > 1) {
                                loadMaterials(relativePath + tokens[1], materials, textures);
                            } else {
                                // TODO: log it
                            }

                        } else if(tokens[0] == "usemtl") {
                            if(tokens.size() > 1) {
                                if(meshes.size() > 0) {
                                    if(forcedNormalType != NormalType::Default) {
                                        meshes.back().computeNormals(forcedNormalType, false);
                                    } else {
                                        if(smoothNormals)
                                            meshes.back().computeNormals(NormalType::Smooth);
                                        else
                                            meshes.back().computeNormals(NormalType::Flat);
                                    }
                                }

                                meshInitialized = true;
                                currentMeshName = tokens[1];
                                meshes.emplace_back(currentMeshName);

                            } else {
                                // TODO: log it
                            }

                        } else if(tokens[0] == "s" && tokens.size() > 1) {
                            if(tokens[1] == "off" || tokens[1] == "0")
                                smoothNormals = false;
                            else
                                smoothNormals = true;

                        } else if(tokens[0] == "v" && tokens.size() == 4) {
                            try {
                                float v1 = std::stof(tokens[1]);
                                float v2 = std::stof(tokens[2]);
                                float v3 = std::stof(tokens[3]);

                                dataVertices.emplace_back(v1, v2, v3);
                                aabb.updateBy(glm::vec3(v1, v2, v3));

                            } catch(...) {
                                // TODO: log it
                            }

                        } else if(tokens[0] == "vt" && (tokens.size() == 3 || tokens.size() == 4)) {
                            try {
                                float vt1 = std::stof(tokens[1]);
                                float vt2 = std::stof(tokens[2]);

                                dataTexCoords.emplace_back(vt1, vt2);

                            } catch(...) {
                                // TODO: log it
                            }

                        } else if(tokens[0] == "vn" && tokens.size() == 4) {
                            try {
                                float vn1 = std::stof(tokens[1]);
                                float vn2 = std::stof(tokens[2]);
                                float vn3 = std::stof(tokens[3]);

                                dataNormals.emplace_back(glm::normalize(glm::vec3(vn1, vn2, vn3)));

                            } catch(...) {
                                // TODO: log it
                            }

                        } else if(tokens[0] == "f" && tokens.size() > 3) {
                            if(meshInitialized == false) {
                                meshes.emplace_back();
                                meshInitialized = true;
                            }

                            std::vector<std::vector<std::string>> faceTokens(tokens.size() - 1);
                            bool validFace = true;

                            for(int i = 1; i < tokens.size(); ++i)
                                faceTokens[i-1] = Util::String::split(tokens[i], '/', false);

                            for(int i = 0; i < faceTokens.size() - 1; ++i)
                                if(faceTokens[i].size() != faceTokens[i+1].size())
                                    validFace = false;

                            if(validFace) {
                                if(faceTokens[0].size() == 1) {
                                    std::vector<int> idV;

                                    try {
                                        for(int i = 0; i < faceTokens.size(); ++i) {
                                            idV.push_back(std::stoi(faceTokens[i][0]));

                                            if(idV.back() < 0)
                                                idV.back() = dataVertices.size() + idV.back() + 1;
                                        }

                                        for(int i = 1; i < faceTokens.size() - 1; ++i) {
                                            meshes.back().addData(dataVertices[idV[0] - 1]);
                                            meshes.back().addData(dataVertices[idV[i] - 1]);
                                            meshes.back().addData(dataVertices[idV[i+1] - 1]);
                                        }

                                    } catch(...) {
                                        // TODO: log it
                                    }

                                } else if(faceTokens[0].size() == 2) {
                                    std::vector<int> idV;
                                    std::vector<int> idT;

                                    try {
                                        for(int i = 0; i < faceTokens.size(); ++i) {
                                            idV.push_back(std::stoi(faceTokens[i][0]));
                                            idT.push_back(std::stoi(faceTokens[i][1]));

                                            if(idV.back() < 0)
                                                idV.back() = dataVertices.size() + idV.back() + 1;

                                            if(idT.back() < 0)
                                                idT.back() = dataTexCoords.size() + idT.back() + 1;
                                        }

                                        for(int i = 1; i < faceTokens.size() - 1; ++i) {
                                            meshes.back().addData(dataVertices[idV[0] - 1],   dataTexCoords[idT[0] - 1]);
                                            meshes.back().addData(dataVertices[idV[i] - 1],   dataTexCoords[idT[i] - 1]);
                                            meshes.back().addData(dataVertices[idV[i+1] - 1], dataTexCoords[idT[i+1] - 1]);
                                        }

                                    } catch(...) {
                                        // TODO: log it
                                    }

                                } else if(faceTokens[0].size() == 3) {
                                    bool texIncluded = true;

                                    for(int i = 0; i < faceTokens.size(); ++i)
                                        if(faceTokens[i][1] == "")
                                            texIncluded = false;

                                    if(texIncluded) {
                                        std::vector<int> idV;
                                        std::vector<int> idT;
                                        std::vector<int> idN;

                                        try {
                                            for(int i = 0; i < faceTokens.size(); ++i) {
                                                idV.push_back(std::stoi(faceTokens[i][0]));
                                                idT.push_back(std::stoi(faceTokens[i][1]));
                                                idN.push_back(std::stoi(faceTokens[i][2]));

                                                if(idV.back() < 0)
                                                    idV.back() = dataVertices.size() + idV.back() + 1;

                                                if(idT.back() < 0)
                                                    idT.back() = dataTexCoords.size() + idT.back() + 1;

                                                if(idN.back() < 0)
                                                    idN.back() = dataNormals.size() + idN.back() + 1;
                                            }

                                            for(int i = 1; i < faceTokens.size() - 1; ++i) {
                                                meshes.back().addData(dataVertices[idV[0] - 1],   dataTexCoords[idT[0] - 1],   dataNormals[idN[0] - 1]);
                                                meshes.back().addData(dataVertices[idV[i] - 1],   dataTexCoords[idT[i] - 1],   dataNormals[idN[i] - 1]);
                                                meshes.back().addData(dataVertices[idV[i+1] - 1], dataTexCoords[idT[i+1] - 1], dataNormals[idN[i+1] - 1]);
                                            }

                                        } catch(...) {
                                            // TODO: log it
                                        }


                                    } else {
                                        std::vector<int> idV;
                                        std::vector<int> idN;

                                        try {
                                            for(int i = 0; i < faceTokens.size(); ++i) {
                                                idV.push_back(std::stoi(faceTokens[i][0]));
                                                idN.push_back(std::stoi(faceTokens[i][2]));

                                                if(idV.back() < 0)
                                                    idV.back() = dataVertices.size() + idV.back() + 1;

                                                if(idN.back() < 0)
                                                    idN.back() = dataNormals.size() + idN.back() + 1;
                                            }

                                            for(int i = 1; i < faceTokens.size() - 1; ++i) {
                                                meshes.back().addData(dataVertices[idV[0] - 1], dataNormals[idN[0] - 1]);
                                                meshes.back().addData(dataVertices[idV[i] - 1], dataNormals[idN[i] - 1]);
                                                meshes.back().addData(dataVertices[idV[i+1] - 1], dataNormals[idN[i+1] - 1]);
                                            }

                                        } catch(...) {
                                            // TODO: log it
                                        }
                                    }

                                } else {
                                    // TODO: log it
                                }

                            } else {
                                // TODO: log it
                            }

                        } else {
                            // TODO: log it
                        }

                    }
                }

                if(meshInitialized) {
                    if(forcedNormalType != NormalType::Default) {
                        meshes.back().computeNormals(forcedNormalType, false);
                    } else {
                        if(smoothNormals)
                            meshes.back().computeNormals(NormalType::Smooth);
                        else
                            meshes.back().computeNormals(NormalType::Flat);
                    }
                }

                for(auto& mesh : meshes)
                    mesh.build();
            }

            objFile.close();

            return true;
        }

        bool OBJ::loadMaterials(
            const std::string& path,
            std::unordered_map<std::string, Material>& materials,
            std::unordered_map<std::string, GL::Texture>& textures
        ) 
        
        {
            std::ifstream mtlFile;
            std::string currentLine;
            std::string currentMaterial = "";
            std::string currentDirectory = Util::File::getPath(path) + "/";
            std::vector<std::string> tokens;

            mtlFile.open(path);

            if(mtlFile.is_open() == false) {
                // TODO: log it
                return false;

            } else {
                while(std::getline(mtlFile, currentLine)) {
                    tokens = Util::String::split(currentLine, ' ');

                    if(tokens.size() > 0) {

                        if(tokens[0] == "newmtl") {
                            currentMaterial = tokens[1];
                            materials.emplace(
                                tokens[1],
                                Material(tokens[1])
                            );

                        } else if(currentMaterial.size() > 0) {

                            if(Util::String::startsWith(tokens[0], "map_")) {
                                if(Util::File::exists(currentDirectory + tokens[1])) {
                                    textures.emplace(
                                        tokens[1],
                                        currentDirectory + tokens[1]
                                    );
                                } else {
                                    // TODO: log it
                                }
                            }

                            materials.at(currentMaterial).processInput(tokens);
                        }
                    }
                }
            }

            mtlFile.close();
            return true;
        }

        const std::vector<Mesh>& OBJ::getMeshes() const {
            return _meshes;
        }

        const std::unordered_map<std::string, Material>& OBJ::getMaterials() const {
            return _materials;
        }

        const std::unordered_map<std::string, GL::Texture>& OBJ::getTextures() const {
            return _textures;
        }

        std::vector<Mesh>& OBJ::getMeshes() {
            return _meshes;
        }

        std::unordered_map<std::string, Material>& OBJ::getMaterials() {
            return _materials;
        }

        std::unordered_map<std::string, GL::Texture>& OBJ::getTextures() {
            return _textures;
        }

    }

}