#include <GLUL/Logger.h>
#include <GLUL/GL++/Context.h>
#include <GLUL/G2D/Font.h>
#include <GLUL/G2D/Text.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <algorithm>
#include <cctype>


namespace GLUL {

    namespace G2D {

        static FT_Library _FT_library;

        Font::Font() throw(GLUL::Exception::FatalError) : _isGenerated(false), _height(0u) {
            _initializeFT();
            _face = new FT_Face();
        }

        Font::Font(const std::string& path) throw(GLUL::Exception::FatalError) : Font() {
            load(path);
        }

        Font::Font(const std::string& path, unsigned int height) throw(GLUL::Exception::FatalError) : Font(path) {
            generate(height);
        }

        Font::~Font() {
            FT_Done_Face((*static_cast<FT_Face*>(_face)));
            delete static_cast<FT_Face*>(_face);
        }

        void Font::load(const std::string& path) {
            _setPath(path);

            if(FT_New_Face(_FT_library, getPath().c_str(), 0, static_cast<FT_Face*>(_face)))
                GLUL::Log::LibraryStream().logError("[FreeType] Unable to load face from file '" + path + "'");
        }

        void Font::load(const std::string& path, unsigned int height) {
            load(path);
            generate(height);
        }

        void Font::generate(unsigned int height) {
            _setHeight(height);
            _glyphs.clear();
            _glyphs.resize(128);

            auto textureRowAndTotalSizes = _computeTextureSizes();
            glm::uvec2 rowSize = textureRowAndTotalSizes.first;
            glm::uvec2 totalSize = textureRowAndTotalSizes.second;
            glm::uvec2 glyphOffset = { 0u, 0u };
            glm::uvec2 glyphSize = { 0u, 0u };
            FT_Face face = (*static_cast<FT_Face*>(_face));
            unsigned int pixelGlyphInterval = 2u;

            // Set pixel unpack alignment
            GL::Context::Current->setPixelUnpackAlignment(1);

            // Prepare texture
            _texture.bind();
            _prepareTexture(totalSize);

            // Fill texture with glyphs
            for(unsigned int glyph = 0u; glyph < 128u; ++glyph) {
                if(FT_Load_Char(face, glyph, FT_LOAD_RENDER)) {
                    _logBrokenGlyph(glyph);

                } else {
                    glyphSize = _getCurrentFaceGlyphSize();

                    if(std::isgraph(glyph)) {
                        if(glyphOffset.x + glyphSize.x >= totalSize.x)
                            glyphOffset = { 0u, glyphOffset.y + rowSize.y };

                        _computeGlyphMetric(glyph, glyphSize, glyphOffset, totalSize);
                        _texture.setSubData2D(glyphOffset.x, glyphOffset.y, glyphSize.x, glyphSize.y, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

                        glyphOffset.x += glyphSize.x + pixelGlyphInterval;

                    } else {
                        _computeGlyphMetric(glyph, glyphSize, {}, totalSize);
                    }
                }
            }

            _texture.unbind();
            _isGenerated = true;
        }

        const std::string& Font::getPath() const {
            return _path;
        }

        const GL::Texture& Font::getTexture() const {
            return _texture;
        }

        float Font::getLineHeight() const {
            return static_cast<float>((*static_cast<FT_Face*>(_face))->size->metrics.height) / 64.0f;
        }

        float Font::getAscender() const {
            return static_cast<float>((*static_cast<FT_Face*>(_face))->size->metrics.ascender) / 64.0f;
        }

        float Font::getDescender() const {
            return static_cast<float>((*static_cast<FT_Face*>(_face))->size->metrics.descender) / 64.0f;
        }

        unsigned int Font::getHeight() const {
            return _height;
        }

        const Font::Metric& Font::getMetricOf(unsigned char character) const {
            return _glyphs[character];
        }

        glm::vec2 Font::getBoundsOf(const std::string& text) const {
            if(!_isGenerated)
                return {};

            glm::vec2 baseline;
            glm::vec2 cursorPos;
            glm::vec2 maxPos, minPos;

            for(char character : text)
            {
                bool isDrawn = (std::isgraph(character) > 0);
                auto& metric = getMetricOf(character);
                auto posStart = cursorPos + metric.glyphPos - glm::vec2 { 0.0f, metric.size.y };
                auto posEnd = posStart + metric.size;

                maxPos = { std::max(maxPos.x, posEnd.x),   std::max(maxPos.y, posEnd.y)   };
                minPos = { std::min(minPos.x, posStart.x), std::min(minPos.y, posStart.y) };

                Text::moveCursor(cursorPos, baseline, character, *this);
            }

            return maxPos - minPos;
        }

        void Font::_setHeight(unsigned int height) {
            FT_Face face = (*static_cast<FT_Face*>(_face));

            _height = height;
            FT_Set_Pixel_Sizes(face, 0, height);
        }

        void Font::_setPath(const std::string& path) {
            _path = path;
        }

        void Font::_logBrokenGlyph(unsigned int glyphCode) const {
            std::string warningMessage;
            warningMessage = "[FreeType2] Unable to load glyph of '";
            warningMessage.push_back(static_cast<char>(glyphCode));
            warningMessage += std::string("' (") + std::to_string(glyphCode) + std::string(")");

            GLUL::Log::LibraryStream().logWarning(warningMessage);
        }

        void Font::_prepareTexture(const glm::uvec2& textureSize) {
            if(!_isGenerated) {
                _texture.setTarget(GL::Texture::Target::Tex2D);
                _texture.setFormat(GL::Texture::Format::Red);
                _texture.setInternalFromat(GL::Texture::InternalFormat::Red);

                _texture.setParameters(std::list<std::pair<GLenum, GLint>> {
                    { GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE },
                    { GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE },
                    { GL_TEXTURE_MIN_FILTER, GL_LINEAR },
                    { GL_TEXTURE_MAG_FILTER, GL_LINEAR },
                    { GL_TEXTURE_SWIZZLE_R, GL_ONE },
                    { GL_TEXTURE_SWIZZLE_G, GL_ONE },
                    { GL_TEXTURE_SWIZZLE_B, GL_ONE },
                    { GL_TEXTURE_SWIZZLE_A, GL_RED },
                });
            }

            _texture.setData2D(textureSize.x, textureSize.y, GL_UNSIGNED_BYTE, nullptr);
        }

        void Font::_computeGlyphMetric(
            unsigned int glyphCode,
            const glm::uvec2& glyphSize,
            const glm::uvec2& glyphOffset,
            const glm::uvec2& totalSize)
        {
            FT_Face face = (*static_cast<FT_Face*>(_face));

            _glyphs[glyphCode].size     = {
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows
            };

            _glyphs[glyphCode].glyphPos = {
                face->glyph->bitmap_left,
                face->glyph->bitmap_top
            };

            _glyphs[glyphCode].advance  = {
                static_cast<float>(face->glyph->advance.x) / 64.0f,
                static_cast<float>(face->glyph->advance.y) / 64.0f
            };

            _glyphs[glyphCode].texPosStart = {
                static_cast<float>(glyphOffset.x)               / static_cast<float>(totalSize.x),
                static_cast<float>(glyphOffset.y + glyphSize.y) / static_cast<float>(totalSize.y)
            };

            _glyphs[glyphCode].texPosEnd = {
                static_cast<float>(glyphOffset.x + glyphSize.x) / static_cast<float>(totalSize.x),
                static_cast<float>(glyphOffset.y)               / static_cast<float>(totalSize.y)
            };
        }

        glm::uvec2 Font::_getCurrentFaceGlyphSize() const {
            FT_Face face = (*static_cast<FT_Face*>(_face));

            return {
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows
            };
        }

        std::pair<glm::uvec2, glm::uvec2> Font::_computeTextureSizes() const {
            FT_Face face = (*static_cast<FT_Face*>(_face));
            glm::uvec2 rowSize;
            glm::uvec2 totalSize = { 0u, 1u };
            unsigned int maxRowWidth = 2048u;
            unsigned int heighestRow = 0u;
            unsigned int pixelGlyphInterval = 2u;

            auto nextPowerOf2 = [](unsigned int x, unsigned int y) {
                while(y < x) y = (y << 1);
                return y;
            };

            for(unsigned int glyph = 0; glyph < 128u; ++glyph) {
                if(FT_Load_Char(face, glyph, FT_LOAD_RENDER)) {
                    _logBrokenGlyph(glyph);
                } else {
                    if(std::isgraph(glyph)) {
                        totalSize.x += (*static_cast<FT_Face*>(_face))->glyph->bitmap.width + pixelGlyphInterval;
                        heighestRow = std::max<long int>(heighestRow, (*static_cast<FT_Face*>(_face))->glyph->bitmap.rows);

                        if(totalSize.x > maxRowWidth) {
                            totalSize.x  = (*static_cast<FT_Face*>(_face))->glyph->bitmap.width;
                            totalSize.y += 1u;
                        }
                    }
                }
            }

            heighestRow += pixelGlyphInterval;
            rowSize = { totalSize.x, heighestRow };
            totalSize = {
                nextPowerOf2(totalSize.x, 1u),
                nextPowerOf2(totalSize.y * heighestRow, 1u) // totalSize.y stored row count
            };

            return { rowSize, totalSize };
        }

        void Font::_initializeFT() throw(GLUL::Exception::FatalError) {
            static bool initialized = false;

            if(!initialized) {
                if(FT_Init_FreeType(&_FT_library)) {
                    GLUL::Log::LibraryStream().logError("[FreeType] Unable to initialize FreeType2 library.");
                    throw GLUL::Exception::FatalError("[FreeType] Unable to initialize FreeType2 library.");
                }

                initialized = true;
            }
        }

    }

}
