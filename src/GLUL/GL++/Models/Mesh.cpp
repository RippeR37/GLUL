#include <GLUL/GL++/Models/Mesh.h>
#include <GLUL/GL++/Models/Material.h>


namespace GL {

    namespace Model {

        Mesh::Mesh(std::unordered_map<std::string, GL::Texture>* textures) : Mesh("defaultMaterial", textures) {

        }

        Mesh::Mesh(const std::string& materialName, std::unordered_map<std::string, GL::Texture>* textures) {
            this->materialName = materialName;
            this->_textures = textures;
        }

        Mesh::Mesh(Mesh&& mesh) :
            materialName(std::move(mesh.materialName)),
            vertices(std::move(mesh.vertices)),
            normals(std::move(mesh.normals)),
            texCoords(std::move(mesh.texCoords)),
            _aabb(std::move(mesh._aabb)),
            _vao(std::move(mesh._vao)),
            _vboV(std::move(mesh._vboV)),
            _vboT(std::move(mesh._vboT)),
            _vboN(std::move(mesh._vboN)),
            _textures(std::move(mesh._textures))
        {

        }

        void Mesh::build() {
            _vao.bind();

                if(vertices.empty() == false) {
                    _vboV.bind();
                        _vboV.setData(vertices);
                        _vao.enableAttrib(0);
                        _vao.setAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
                    _vboV.unbind();
                }

                if(texCoords.empty() == false) {
                    _vboT.bind();
                        _vboT.setData(texCoords);
                        _vao.enableAttrib(1);
                        _vao.setAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
                    _vboT.unbind();
                }

                if(normals.empty() == false) {
                    _vboN.bind();
                        _vboN.setData(normals);
                        _vao.enableAttrib(2);
                        _vao.setAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
                    _vboN.unbind();
                }

            _vao.unbind();

            _vao.setDrawCount(vertices.size());
            _vao.setDrawTarget(GL::VertexArray::DrawTarget::Triangles);
        }

        void Mesh::computeNormals(GLUL::Interface::Model::NormalType type, bool overwrite) {
            if(hasNormals() == false || overwrite) {
                normals.clear();

                glm::vec3 normal = glm::vec3(0.0);
                glm::vec3 edge1;
                glm::vec3 edge2;

                if(type == GLUL::Interface::Model::NormalType::Smooth) {
                    for(unsigned int i = 0; i < vertices.size(); ++i) {
                        for(unsigned int j = 0; j < vertices.size(); ++j) {
                            if(i != j) {
                                if(vertices[i] == vertices[j]) {
                                    int k = j - (j % 3);

                                    edge1 = vertices[k + 1] - vertices[k];
                                    edge2 = vertices[k + 2] - vertices[k];
                                    normal += glm::normalize(glm::cross(edge1, edge2));
                                }
                            }
                        }

                        normal = glm::normalize(normal);
                        normals.push_back(normal);
                    }

                } else {
                    for(unsigned int i = 0; i < vertices.size(); i += 3) {
                        edge1 = vertices[i + 1] - vertices[i];
                        edge2 = vertices[i + 2] - vertices[i];
                        normal = glm::normalize(glm::cross(edge1, edge2));

                        normals.push_back(normal);
                        normals.push_back(normal);
                        normals.push_back(normal);
                    }
                }
            }
        }

        void Mesh::render(const GL::Pipeline& pipeline, const GL::Program& program, const Material& material) const {
            glm::ivec4 hasTextures = glm::ivec4(0);

            // Transparent objects not supported
            if(material.alphaFactor < 1.0f - 0.01f)
                return;

            // Texture query
            hasTextures.x = (material.textureDiffuse != "") ? true : false;
            hasTextures.y = (material.textureAmbient != "") ? true : false;
            //hasTextures.z = (material.textureSpecular != "") ? true : false; // not supported yet
            //hasTextures.w = (material.textureBumpmap  != "") ? true : false; // not supported yet

            if(_textures) {
                glActiveTexture(GL_TEXTURE0);

                if(hasTextures.x)
                    _textures->at(material.textureDiffuse).bind();
                else if(hasTextures.y)
                    _textures->at(material.textureAmbient).bind();
            }

            program.use();

                program["matrixMVP"] = pipeline.getMVP();
                program["uColorD"] = glm::vec4(material.colorDiffuse, 1.0f);
                program["uColorA"] = glm::vec4(material.colorAmbient, material.alphaFactor);
                program["uColorS"] = glm::vec4(material.colorSpecular, material.exponentSpecular);
                program["hasTextures"] = hasTextures;
                program["texSampler"] = 0;

                _vao.bind();
                _vao.drawArrays();
                _vao.unbind();

            program.unbind();

            if(_textures) {
                if(hasTextures.x)
                    _textures->at(material.textureDiffuse).unbind();
                else if(hasTextures.y)
                    _textures->at(material.textureAmbient).unbind();
            }
        }

        void Mesh::renderAABB(const GL::Pipeline& pipeline) const {
            getAABB().render(pipeline);
        }

        void Mesh::addData(const glm::vec3& vertex) {
            vertices.push_back(vertex);

            _aabb.updateBy(vertex);
        }

        void Mesh::addData(const glm::vec3& vertex, const glm::vec2& texCoord) {
            vertices.push_back(vertex);
            texCoords.push_back(texCoord);

            _aabb.updateBy(vertex);
        }

        void Mesh::addData(const glm::vec3& vertex, const glm::vec2& texCoord, const glm::vec3& normal) {
            vertices.push_back(vertex);
            texCoords.push_back(texCoord);
            normals.push_back(normal);

            _aabb.updateBy(vertex);
        }

        void Mesh::addData(const glm::vec3& vertex, const glm::vec3& normal) {
            vertices.push_back(vertex);
            normals.push_back(normal);

            _aabb.updateBy(vertex);
        }

        bool Mesh::hasNormals() const {
            return (vertices.size() == normals.size());
        }

        const GLUL::AABB& Mesh::getAABB() const {
            return _aabb;
        }

    }

}
