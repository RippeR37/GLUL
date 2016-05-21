#include <GLUL/Logger.h>
#include <GLUL/GL++/Context.h>
#include <GLUL/G2D/Font.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <algorithm>
#include <cctype>


namespace GLUL {

    namespace G2D {

        static FT_Library _FT_library;

        Font::Font() throw(GLUL::Exception::FatalError) : _height(0) {
            Font::_initializeFT();

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
                GLUL::Log::Stream("_Library").logError("[FreeType] Unable to load face from file '" + path + "'");
        }

        void Font::load(const std::string& path, unsigned int height) {
            load(path);
            generate(height);
        }

        void Font::generate(unsigned int height) {
            auto textureRowAndTotalSizes = _computeTextureSizes();
            glm::uvec2 rowSize = textureRowAndTotalSizes.first;
            glm::uvec2 totalSize = textureRowAndTotalSizes.second;
            glm::uvec2 glyphOffset = { 0u, 0u };
            glm::uvec2 glyphSize = { 0u, 0u };
            FT_Face face = (*static_cast<FT_Face*>(_face));
            unsigned int pixelGlyphInterval = 2u;

            // Set pixel unpack alignment
            GL::Context::Current->setPixelUnpackAlignment(1);

            // Set height
            _setHeight(height);

            // Prepare texture
            _texture.bind();
            _prepareTexture(totalSize);

            // Fill texture with glyphs
            for(int glyph = 0; glyph < 128; ++glyph) {
                if(FT_Load_Char(face, glyph, FT_LOAD_RENDER)) {
                    _logBrokenGlyph(glyph);

                } else {
                    if(std::isgraph(glyph)) {
                        glyphSize = _getCurrentFaceGlyphSize();

                        if(glyphOffset.x + glyphSize.x >= totalSize.x)
                            glyphOffset = { 0u, glyphOffset.y + rowSize.y };

                        _computeGlyphMetric(glyph, glyphSize, glyphOffset, totalSize);
                        _texture.setSubData2D(glyphOffset.x, glyphOffset.y, glyphSize.x, glyphSize.y, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

                        glyphOffset.x += glyphSize.x + pixelGlyphInterval;

                    } else {
                        _computeEmptyGlyphMetric(glyph);
                    }
                }
            }

            _correctSpaceMetric();
            _texture.unbind();
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

        const std::string& Font::getPath() const {
            return _path;
        }

        const GL::Texture& Font::getTexture() const {
            return _texture;
        }

        const Font::Metric& Font::getMetric(unsigned char character) const {
            return _glyphs[character];
        }

        void Font::_setHeight(unsigned int height) {
            FT_Face face = (*static_cast<FT_Face*>(_face));

            _height = height;
            FT_Set_Pixel_Sizes(face, 0, height);
        }

        void Font::_setPath(const std::string& path) {
            _path = path;
        }

        void Font::_logBrokenGlyph(unsigned int glyphCode) {
            std::string warningMessage;
            warningMessage = "[FreeType2] Unable to load glyph of '";
            warningMessage += static_cast<char>(glyphCode)+"' (" + std::to_string(glyphCode) + ")";

            GLUL::Log::LibraryStream().logWarning(warningMessage);
        }

        void Font::_prepareTexture(const glm::uvec2& textureSize) {
            _texture.setTarget(GL::Texture::Target::Tex2D);
            _texture.setFormat(GL::Texture::Format::Red);
            _texture.setInternalFromat(GL::Texture::InternalFormat::Red);

            _texture.setParameters(std::list<std::pair<GLenum, GLint>>({
                std::pair<GLenum, GLint>(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE),
                std::pair<GLenum, GLint>(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE),
                std::pair<GLenum, GLint>(GL_TEXTURE_MIN_FILTER, GL_LINEAR),
                std::pair<GLenum, GLint>(GL_TEXTURE_MAG_FILTER, GL_LINEAR),
            }));

            _texture.setData2D(textureSize.x, textureSize.y, GL_UNSIGNED_BYTE, nullptr);
        }

        void Font::_computeEmptyGlyphMetric(unsigned int glyphCode) {
            FT_Face face = (*static_cast<FT_Face*>(_face));

            _glyphs[glyphCode].size = {};
            _glyphs[glyphCode].glyphPos = { face->glyph->bitmap_left, face->glyph->bitmap_top };
            _glyphs[glyphCode].advance = glm::vec2(
                static_cast<float>(face->glyph->advance.x) / 64.0f,
                static_cast<float>(face->glyph->advance.y) / 64.0f
                );
            _glyphs[glyphCode].texPosStart = {};
            _glyphs[glyphCode].texPosEnd = {};
        }

        void Font::_computeGlyphMetric(
            unsigned int glyphCode,
            const glm::uvec2& glyphSize,
            const glm::uvec2& glyphOffset,
            const glm::uvec2& totalSize)
        {
            FT_Face face = (*static_cast<FT_Face*>(_face));

            _glyphs[glyphCode].size = {
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows
            };

            _glyphs[glyphCode].glyphPos = {
                face->glyph->bitmap_left,
                face->glyph->bitmap_top
            };

            _glyphs[glyphCode].advance = {
                static_cast<float>(face->glyph->advance.x) / 64.0f,
                static_cast<float>(face->glyph->advance.y) / 64.0f
            };

            _glyphs[glyphCode].texPosStart = {
                static_cast<float>(glyphOffset.x) / static_cast<float>(totalSize.x),
                static_cast<float>(glyphOffset.y + glyphSize.y) / static_cast<float>(totalSize.y)
            };

            _glyphs[glyphCode].texPosEnd = {
                static_cast<float>(glyphOffset.x + glyphSize.x) / static_cast<float>(totalSize.x),
                static_cast<float>(glyphOffset.x) / static_cast<float>(totalSize.y)
            };
        }

        void Font::_correctSpaceMetric() {
            // TODO: HACK: this might be solved better
            _glyphs[static_cast<unsigned char>(' ')].size = _glyphs[static_cast<unsigned char>('a')].size;
        }

        glm::uvec2 Font::_getCurrentFaceGlyphSize() {
            FT_Face face = (*static_cast<FT_Face*>(_face));

            return {
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows
            };
        }

        std::pair<glm::uvec2, glm::uvec2> Font::_computeTextureSizes() {
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
                if(FT_Load_Char((*static_cast<FT_Face*>(_face)), glyph, FT_LOAD_RENDER)) {
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

            return std::make_pair(rowSize, totalSize);
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
