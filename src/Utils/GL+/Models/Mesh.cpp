#include <Utils/GL+/Models/Mesh.h>
#include <Utils/GL+/Models/Material.h>

namespace GL {

    namespace Model {

        Mesh::Mesh() : Mesh("defaultMaterial") {

        }

        Mesh::Mesh(const std::string& materialName) {
            this->materialName = materialName;
        }

        Mesh::Mesh(Mesh&& mesh) :
            materialName(std::move(mesh.materialName)),
            vertices(std::move(mesh.vertices)),
            texCoords(std::move(mesh.texCoords)),
            normals(std::move(mesh.normals)),
            _vao(std::move(mesh._vao)),
            _vboV(std::move(mesh._vboV)),
            _vboT(std::move(mesh._vboT)),
            _vboN(std::move(mesh._vboN)),
            _aabb(std::move(mesh._aabb)) 
        {

        }

        void Mesh::build() {
            _vao.bind();

                _vboV.bind();
                    _vboV.setData(vertices);
                    _vao.enableAttrib(0);
                    _vao.setAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
                _vboV.unbind();

                _vboT.bind();
                    _vboT.setData(texCoords);
                    _vao.enableAttrib(1);
                    _vao.setAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
                _vboT.unbind();

                _vboN.bind();
                    _vboN.setData(normals);
                    _vao.enableAttrib(2);
                    _vao.setAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
                _vboN.unbind();

            _vao.unbind();

            _vao.setDrawCount(vertices.size());
            _vao.setDrawTarget(GL::VertexArray::DrawTarget::Triangles);
        }

        void Mesh::computeNormals(Util::Interface::Model::NormalType type, bool overwrite) {
            if(hasNormals() == false || overwrite) {
                normals.clear();

                glm::vec3 normal = glm::vec3(0.0);
                glm::vec3 edge1;
                glm::vec3 edge2;

                if(type == Util::Interface::Model::NormalType::Smooth) {
                    for(int i = 0; i < vertices.size(); ++i) {
                        for(int j = 0; j < vertices.size(); ++j) {
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
                    for(int i = 0; i < vertices.size(); i += 3) {
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

            /*
            if(hasTextures.x)
                model.getTextures().at(material->textureDiffuse).bind();
            else if(hasTextures.y)
                model.getTextures().at(material->textureAmbient).bind();
            */

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

            /*
            if(hasTextures.x)
                model.getTextures().at(material->textureDiffuse).unbind();
            else if(hasTextures.y)
                model.getTextures().at(material->textureAmbient).unbind();
            */
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

        const Util::AABB& Mesh::getAABB() const {
            return _aabb;
        }

    }

}