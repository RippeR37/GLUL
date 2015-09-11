#pragma once

#include <GLUL/Exception.h>
#include <GLUL/GL++/Texture.h>

#include <GL/glew.h>
#include <glm/vec2.hpp>


namespace GLUL {

    namespace GUI {

        class GLUL_API Font {
            private:
                struct Metric {
                    glm::vec2 advance;
                    glm::vec2 size;
                    glm::vec2 texPosStart;
                    glm::vec2 texPosEnd;
                    glm::vec2 glyphPos;
                };


            public:
                Font() throw(GLUL::Exception::FatalError);
                Font(const std::string& path) throw(GLUL::Exception::FatalError);
                ~Font();

                void load(const std::string& path);
                void load(const std::string& path, unsigned int fontHeight);

                void generate(unsigned int fontHeight);
                
                float getLineHeight() const;
                float getAscender() const;
                float getDescender() const;
                unsigned int getHeight() const;

                const std::string& getPath() const;
                const GL::Texture& getTexture() const;
                const Metric& getMetric(unsigned char character) const;

            private:
                void setPath(const std::string& path);

                unsigned int _height;
                std::string _path;
                GL::Texture _texture;
                Metric _glyphs[128];
                void* _face;


            private:
                static void initializeFT() throw(GLUL::Exception::FatalError);
        };

    }

}
