#pragma once

#include <GLUL/Config.h>
#include <GLUL/GL++/Texture.h>

#include <glm/vec2.hpp>

#include <string>
#include <utility>


namespace GLUL {

    namespace G2D {

        class GLUL_API Font {
            public:
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
                Font(const std::string& path, unsigned int height) throw(GLUL::Exception::FatalError);
                ~Font();

                void load(const std::string& path);
                void load(const std::string& path, unsigned int height);
                void generate(unsigned int height);

                const std::string& getPath() const;
                const GL::Texture& getTexture() const;

                // Font metrics
                float getLineHeight() const;
                float getAscender() const;
                float getDescender() const;
                unsigned int getHeight() const;
                const Metric& getMetricOf(unsigned char character) const;

                // Text metrics
                void getBoundsOf(const std::string& text) const;
                void getBoundsOf(const std::string& text, unsigned int height);
                void getBaselineBoundsOf(const std::string& text);
                void getBaselineBoundsOf(const std::string& text, unsigned int height);

            private:
                void _setHeight(unsigned int height);
                void _setPath(const std::string& path);

                void _logBrokenGlyph(unsigned int glyphCode);
                void _prepareTexture(const glm::uvec2& textureSize);
                void _computeEmptyGlyphMetric(unsigned int glyphCode);
                void _computeGlyphMetric(unsigned int glyphCode,
                    const glm::uvec2& glyphSize, const glm::uvec2& glyphOffset, const glm::uvec2& textureSize);
                void _correctSpaceMetric();

                glm::uvec2 _getCurrentFaceGlyphSize();
                std::pair<glm::uvec2, glm::uvec2> _computeTextureSizes();

                bool _textureSet;
                unsigned int _height;
                std::string _path;
                GL::Texture _texture;
                Metric _glyphs[128];
                void* _face;

                static void _initializeFT() throw(GLUL::Exception::FatalError);

                friend class TexturedGeometryBatch;
        };

    }

}
