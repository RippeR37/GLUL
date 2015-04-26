#ifndef UTILS_GL_GUI_FONT_H_INCLUDED
#define UTILS_GL_GUI_FONT_H_INCLUDED

#include <Utils/Exception.h>
#include <Utils/GL+/Texture.h>

#include <GL/glew.h>
#include <glm/vec2.hpp>


namespace GL {

    namespace GUI {

        class Font {
            private:
                struct Metric {
                    glm::vec2 advance;
                    glm::vec2 size;
                    glm::vec2 texPosStart;
                    glm::vec2 texPosEnd;
                    glm::vec2 glyphPos;
                };


            public:
                Font() throw(Util::Exception::FatalError);
                Font(const std::string& path) throw(Util::Exception::FatalError);
                ~Font();

                void load(const std::string& path);
                void load(const std::string& path, unsigned int fontHeight);

                void generate(unsigned int fontHeight);
                
                const float getLineHeight() const;
                const float getAscender() const;
                const float getDescender() const;

                const unsigned int getHeight() const;
                const std::string& getPath() const;
                const Texture& getTexture() const;
                const Metric& getMetric(char character) const;

            private:
                void setPath(const std::string& path);

                unsigned int _height;
                std::string _path;
                Texture _texture;
                Metric _glyphs[128];
                void* _face;


            private:
                static void initializeFT() throw(Util::Exception::FatalError);
        };

    }

}


#endif