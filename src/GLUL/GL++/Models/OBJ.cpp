#include <GLUL/GL++/Models/OBJ.h>
#include <GLUL/File.h>
#include <GLUL/String.h>
#include <GLUL/Logger.h>

#include <iostream>
#include <fstream>


namespace GL {

    namespace Model {

        OBJ::OBJ() {
            _program.load(
                GL::Shader("assets/shaders/GLUL/GL++/Models/MeshOBJ.vp", GL::Shader::Type::VertexShader),
                GL::Shader("assets/shaders/GLUL/GL++/Models/MeshOBJ.fp", GL::Shader::Type::FragmentShader)
            );
        }

        OBJ::OBJ(const std::string& path) : OBJ() {
            load(path);
        }

        OBJ::~OBJ() {

        }

        bool OBJ::load(const std::string& path, NormalType forcedNormalType) {
            return parseFile(path, _aabb, getMeshes(), getMaterials(), getTextures(), forcedNormalType);
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
                const auto& material = getMaterials().find(mesh.materialName);

                pipeline.setModel(getMatrix());

                if(material != getMaterials().end())
                    mesh.render(pipeline, program, material->second);
                else
                    mesh.render(pipeline, program, Material::Default);
            }
        }

        void OBJ::renderAABB(const GL::Pipeline& pipeline, bool detailed) const {
            if(detailed)
                for(auto& mesh : getMeshes())
                    mesh.getAABB().render(pipeline);
            else
                _aabb.render(pipeline);
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
            GLUL::AABB& aabb, 
            std::vector<Mesh>& meshes,
            std::unordered_map<std::string, Material>& materials, 
            std::unordered_map<std::string, GL::Texture>& textures, 
            NormalType forcedNormalType) 

        {
            int lineNumber = 0;
            bool meshInitialized;
            bool smoothNormals;

            std::string relativePath;
            std::string currentLine;
            std::string currentMeshName;
            std::ifstream objFile;
            std::vector<std::string> tokens;

            std::vector<glm::vec3> dataVertices;
            std::vector<glm::vec2> dataTexCoords;
            std::vector<glm::vec3> dataNormals;

            relativePath = GLUL::File::getPath(path);
            meshInitialized = false;
            smoothNormals = (forcedNormalType == NormalType::Smooth);
            
            objFile.open(path);

            if(objFile.is_open() == false) {
                GLUL::Log::LibraryStream() << "Unable to open OBJ model file '" + path + "'";
                return false;

            } else {
                while(std::getline(objFile, currentLine)) {
                    ++lineNumber;

                    tokens = GLUL::String::split(currentLine, ' ');

                    if(tokens.empty() == false) {

                        if(tokens[0] == "#") {
                            // comment, just ignore it

                        } else if(tokens[0] == "mtllib") {
                            if(tokens.size() > 1) {
                                loadMaterials(relativePath + tokens[1], materials, textures);
                            } else {
                                GLUL::Log::LibraryStream() << 
                                    "[" + std::to_string(lineNumber) + "] Unable to read parameter '" + tokens[0] + "' in file '" + path + "'";
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
                                meshes.emplace_back(currentMeshName, &textures);

                            } else {
                                GLUL::Log::LibraryStream() <<
                                    "[" + std::to_string(lineNumber) + "] Unable to read parameter '" + tokens[0] + "' in file '" + path + "'";
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
                                GLUL::Log::LibraryStream() <<
                                    "[" + std::to_string(lineNumber) + "] Unable to read parameter '" + tokens[0] + "' in file '" + path + "'";
                            }

                        } else if(tokens[0] == "vt" && (tokens.size() == 3 || tokens.size() == 4)) {
                            try {
                                float vt1 = std::stof(tokens[1]);
                                float vt2 = std::stof(tokens[2]);

                                dataTexCoords.emplace_back(vt1, vt2);

                            } catch(...) {
                                GLUL::Log::LibraryStream() <<
                                    "[" + std::to_string(lineNumber) + "] Unable to read parameter '" + tokens[0] + "' in file '" + path + "'";
                            }

                        } else if(tokens[0] == "vn" && tokens.size() == 4) {
                            try {
                                float vn1 = std::stof(tokens[1]);
                                float vn2 = std::stof(tokens[2]);
                                float vn3 = std::stof(tokens[3]);

                                dataNormals.emplace_back(glm::normalize(glm::vec3(vn1, vn2, vn3)));

                            } catch(...) {
                                GLUL::Log::LibraryStream() <<
                                    "[" + std::to_string(lineNumber) + "] Unable to read parameter '" + tokens[0] + "' in file '" + path + "'";
                            }

                        } else if(tokens[0] == "f" && tokens.size() > 3) {
                            if(meshInitialized == false) {
                                meshes.emplace_back(&textures);
                                meshInitialized = true;
                            }

                            std::vector<std::vector<std::string>> faceTokens(tokens.size() - 1);
                            bool validFace = true;

                            for(unsigned int i = 1; i < tokens.size(); ++i)
                                faceTokens[i-1] = GLUL::String::split(tokens[i], '/', false);

                            for(unsigned int i = 0; i < faceTokens.size() - 1; ++i)
                                if(faceTokens[i].size() != faceTokens[i+1].size())
                                    validFace = false;

                            if(validFace) {
                                if(faceTokens[0].size() == 1) {
                                    std::vector<int> idV;

                                    try {
                                        for(unsigned int i = 0; i < faceTokens.size(); ++i) {
                                            idV.push_back(std::stoi(faceTokens[i][0]));

                                            if(idV.back() < 0)
                                                idV.back() = dataVertices.size() + idV.back() + 1;
                                        }

                                        for(unsigned int i = 1; i < faceTokens.size() - 1; ++i) {
                                            meshes.back().addData(dataVertices[idV[0] - 1]);
                                            meshes.back().addData(dataVertices[idV[i] - 1]);
                                            meshes.back().addData(dataVertices[idV[i+1] - 1]);
                                        }

                                    } catch(...) {
                                        GLUL::Log::LibraryStream() <<
                                            "[" + std::to_string(lineNumber) + "] Unable to read parameter '" + tokens[0] + "' in file '" + path + "'";
                                    }

                                } else if(faceTokens[0].size() == 2) {
                                    std::vector<int> idV;
                                    std::vector<int> idT;

                                    try {
                                        for(unsigned int i = 0; i < faceTokens.size(); ++i) {
                                            idV.push_back(std::stoi(faceTokens[i][0]));
                                            idT.push_back(std::stoi(faceTokens[i][1]));

                                            if(idV.back() < 0)
                                                idV.back() = dataVertices.size() + idV.back() + 1;

                                            if(idT.back() < 0)
                                                idT.back() = dataTexCoords.size() + idT.back() + 1;
                                        }

                                        for(unsigned int i = 1; i < faceTokens.size() - 1; ++i) {
                                            meshes.back().addData(dataVertices[idV[0] - 1],   dataTexCoords[idT[0] - 1]);
                                            meshes.back().addData(dataVertices[idV[i] - 1],   dataTexCoords[idT[i] - 1]);
                                            meshes.back().addData(dataVertices[idV[i+1] - 1], dataTexCoords[idT[i+1] - 1]);
                                        }

                                    } catch(...) {
                                        GLUL::Log::LibraryStream() <<
                                            "[" + std::to_string(lineNumber) + "] Unable to read parameter '" + tokens[0] + "' in file '" + path + "'";
                                    }

                                } else if(faceTokens[0].size() == 3) {
                                    bool texIncluded = true;

                                    for(unsigned int i = 0; i < faceTokens.size(); ++i)
                                        if(faceTokens[i][1] == "")
                                            texIncluded = false;

                                    if(texIncluded) {
                                        std::vector<int> idV;
                                        std::vector<int> idT;
                                        std::vector<int> idN;

                                        try {
                                            for(unsigned int i = 0; i < faceTokens.size(); ++i) {
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

                                            for(unsigned int i = 1; i < faceTokens.size() - 1; ++i) {
                                                meshes.back().addData(dataVertices[idV[0] - 1],   dataTexCoords[idT[0] - 1],   dataNormals[idN[0] - 1]);
                                                meshes.back().addData(dataVertices[idV[i] - 1],   dataTexCoords[idT[i] - 1],   dataNormals[idN[i] - 1]);
                                                meshes.back().addData(dataVertices[idV[i+1] - 1], dataTexCoords[idT[i+1] - 1], dataNormals[idN[i+1] - 1]);
                                            }

                                        } catch(...) {
                                            GLUL::Log::LibraryStream() <<
                                                "[" + std::to_string(lineNumber) + "] Unable to read parameter '" + tokens[0] + "' in file '" + path + "'";
                                        }


                                    } else {
                                        std::vector<int> idV;
                                        std::vector<int> idN;

                                        try {
                                            for(unsigned int i = 0; i < faceTokens.size(); ++i) {
                                                idV.push_back(std::stoi(faceTokens[i][0]));
                                                idN.push_back(std::stoi(faceTokens[i][2]));

                                                if(idV.back() < 0)
                                                    idV.back() = dataVertices.size() + idV.back() + 1;

                                                if(idN.back() < 0)
                                                    idN.back() = dataNormals.size() + idN.back() + 1;
                                            }

                                            for(unsigned int i = 1; i < faceTokens.size() - 1; ++i) {
                                                meshes.back().addData(dataVertices[idV[0] - 1], dataNormals[idN[0] - 1]);
                                                meshes.back().addData(dataVertices[idV[i] - 1], dataNormals[idN[i] - 1]);
                                                meshes.back().addData(dataVertices[idV[i+1] - 1], dataNormals[idN[i+1] - 1]);
                                            }

                                        } catch(...) {
                                            GLUL::Log::LibraryStream() <<
                                                "[" + std::to_string(lineNumber) + "] Unable to read parameter '" + tokens[0] + "' in file '" + path + "'";
                                        }
                                    }

                                } else {
                                    GLUL::Log::LibraryStream() <<
                                        "[" + std::to_string(lineNumber) + "] Unable to read parameter '" + tokens[0] + "' in file '" + path + "'";
                                }

                            } else {
                                GLUL::Log::LibraryStream() <<
                                    "[" + std::to_string(lineNumber) + "] Unable to read parameter '" + tokens[0] + "' in file '" + path + "'";
                            }

                        } else {
                            GLUL::Log::LibraryStream() <<
                                "[" + std::to_string(lineNumber) + "] Unsupported parameter '" + tokens[0] + "' in file '" + path + "'";
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
            std::string currentDirectory = GLUL::File::getPath(path);
            std::vector<std::string> tokens;

            mtlFile.open(path);

            if(mtlFile.is_open() == false) {
                GLUL::Log::LibraryStream() << "Unable to open OBJ material file '" + path + "'";
                return false;

            } else {
                while(std::getline(mtlFile, currentLine)) {
                    tokens = GLUL::String::split(currentLine, ' ');

                    if(tokens.empty() == false) {

                        if(tokens[0] == "newmtl") {
                            currentMaterial = tokens[1];
                            materials.emplace(
                                tokens[1],
                                Material(tokens[1])
                            );

                        } else if(currentMaterial.size() > 0) {

                            if(GLUL::String::startsWith(tokens[0], "map_")) {
                                if(GLUL::File::exists(currentDirectory + tokens[1])) {
                                    try {
                                        textures.emplace(
                                            tokens[1],
                                            currentDirectory + tokens[1]
                                        );
                                    } catch(...) {
                                        GLUL::Log::LibraryStream().log( 
                                            "Unable to load material's texture '" + 
                                            currentDirectory + tokens[1] + 
                                            "' from material file '" + path + "'"
                                        );
                                    }
                                } else {
                                    GLUL::Log::LibraryStream() << "Unable to open OBJ material's texture '" + currentDirectory + tokens[1] + "'";
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
