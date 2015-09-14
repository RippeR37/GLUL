#include <GLUL/GUI/Font.h>
#include <GLUL/Logger.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <algorithm>
#include <cctype>


namespace GLUL {

    namespace GUI {

        static FT_Library _FT_library;


        Font::Font() throw(GLUL::Exception::FatalError) {
            Font::initializeFT();

            _height = 0;
            _face = new FT_Face();
        }

        Font::Font(const std::string& path) throw(GLUL::Exception::FatalError) : Font() {
            _height = 0;

            load(path);
        }

        Font::~Font() {
            FT_Done_Face((*static_cast<FT_Face*>(_face)));

            delete static_cast<FT_Face*>(_face);
        }

        void Font::load(const std::string& path) {
            setPath(path);

            if(FT_New_Face(_FT_library, getPath().c_str(), 0, static_cast<FT_Face*>(_face)))
                GLUL::Log::Stream("_Library").logError("[FreeType] Unable to load face from file '" + path + "'");
        }

        void Font::load(const std::string& path, unsigned int fontHeight) {
            setPath(path);

            if(FT_New_Face(_FT_library, getPath().c_str(), 0, static_cast<FT_Face*>(_face))) {
                GLUL::Log::Stream("_Library").logError("[FreeType] Unable to load face from file '" + path + "'");

            } else {
                generate(fontHeight);
            }
        }

        void Font::generate(unsigned int fontHeight) {
            FT_Set_Pixel_Sizes((*static_cast<FT_Face*>(_face)), 0, fontHeight);

            // TODO: implement this swith in GL::Context class
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            bool maxWidthReached = false;
            int totalWidth = 0;
            int totalHeight = 1;
            int maxWidth = 2048;
            unsigned int maxHeight = 0;
            unsigned int pixelGlyphInterval = 2;


            // Calculate texture size
            for(int glyph = 0; glyph < 128; ++glyph) {
                if(FT_Load_Char((*static_cast<FT_Face*>(_face)), glyph, FT_LOAD_RENDER)) {
                    GLUL::Log::Stream("_Library").logWarning(
                        "[FreeType] Unable to load glyph of '" + std::to_string(static_cast<char>(glyph)) +
                        "' (" + std::to_string(static_cast<int>(glyph)) + ")"
                    );

                } else {
                    if(std::isgraph(glyph)) {
                        totalWidth += (*static_cast<FT_Face*>(_face))->glyph->bitmap.width + pixelGlyphInterval;
                        maxHeight = std::max<long int>(maxHeight, (*static_cast<FT_Face*>(_face))->glyph->bitmap.rows);

                        if(totalWidth > maxWidth) {
                            maxWidthReached = true;
                            totalWidth = (*static_cast<FT_Face*>(_face))->glyph->bitmap.width;
                            totalHeight += 1;
                        }
                    }
                }
            }

            maxHeight += pixelGlyphInterval;


            // Qucik-function to get next power of 2 value
            auto nextPowOf2 = [](int x) -> int {
                int i = 1;
                while(i < x) (i = i << 1);
                return i;
            };

            // Create texture
            if(maxWidthReached)
                totalWidth = maxWidth;
            else
                totalWidth = std::min(maxWidth, nextPowOf2(totalWidth));

            totalHeight = nextPowOf2(totalHeight * maxHeight); // totalHeight previously stores rows count

            _texture.setTarget(GL::Texture::Target::Tex2D);
            _texture.bind();
            _texture.setParameters(std::list<std::pair<GLenum, GLint>>({
                std::pair<GLenum, GLint>(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE),
                std::pair<GLenum, GLint>(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE),
                std::pair<GLenum, GLint>(GL_TEXTURE_MIN_FILTER, GL_LINEAR),
                std::pair<GLenum, GLint>(GL_TEXTURE_MAG_FILTER, GL_LINEAR),
            }));

            // TODO: Fix this to use GL::Texture's functionality
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, totalWidth, totalHeight, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);



            // Fill texture with glyphs
            int offsetX = 0;
            int offsetY = 0;
            int currentWidth = 0;
            int currentHeight = 0;

            for(int glyph = 0; glyph < 128; ++glyph) {
                if(FT_Load_Char((*static_cast<FT_Face*>(_face)), glyph, FT_LOAD_RENDER)) {
                    GLUL::Log::Stream("_Library").logWarning(
                        "[FreeType] Unable to load glyph of '" + std::to_string(static_cast<char>(glyph)) +
                        "' (" + std::to_string(static_cast<int>(glyph)) + ")"
                    );

                } else {
                    if(std::isgraph(glyph)) {
                        // When glyph is drawable (not whitespace or control character)
                        currentWidth  = (*static_cast<FT_Face*>(_face))->glyph->bitmap.width;
                        currentHeight = (*static_cast<FT_Face*>(_face))->glyph->bitmap.rows;

                        // Check if current chunk will fit current row, if not move it to next row
                        if(offsetX + currentWidth >= totalWidth) {
                            offsetX = 0;
                            offsetY += maxHeight;
                        }

                        // Save position of glyph's bitmap in texture
                        _glyphs[glyph].size     = glm::vec2((*static_cast<FT_Face*>(_face))->glyph->bitmap.width, (*static_cast<FT_Face*>(_face))->glyph->bitmap.rows);
                        _glyphs[glyph].glyphPos = glm::vec2((*static_cast<FT_Face*>(_face))->glyph->bitmap_left,  (*static_cast<FT_Face*>(_face))->glyph->bitmap_top);

                        _glyphs[glyph].advance  = glm::vec2(
                            static_cast<float>((*static_cast<FT_Face*>(_face))->glyph->advance.x) / 64.0f, 
                            static_cast<float>((*static_cast<FT_Face*>(_face))->glyph->advance.y) / 64.0f
                        );

                        _glyphs[glyph].texPosStart = glm::vec2(
                            static_cast<float>(offsetX) / static_cast<float>(totalWidth),
                            static_cast<float>(offsetY + currentHeight) / static_cast<float>(totalHeight)
                        );

                        _glyphs[glyph].texPosEnd = glm::vec2(
                            static_cast<float>(offsetX + currentWidth)  / static_cast<float>(totalWidth),
                            static_cast<float>(offsetY) / static_cast<float>(totalHeight)
                        );


                        // Write glyph on texture
                        // TODO: Fix this to use GL::Texture's functionality
                        glTexSubImage2D(GL_TEXTURE_2D, 0, offsetX, offsetY, currentWidth, currentHeight, GL_RED, GL_UNSIGNED_BYTE, (*static_cast<FT_Face*>(_face))->glyph->bitmap.buffer);

                        // Move to next glyph
                        offsetX += currentWidth + pixelGlyphInterval;

                    } else {
                        // When glyph isn't drawable (is whitespace or control character)
                        _glyphs[glyph].size     = glm::vec2(0.0f);
                        _glyphs[glyph].glyphPos = glm::vec2((*static_cast<FT_Face*>(_face))->glyph->bitmap_left,  (*static_cast<FT_Face*>(_face))->glyph->bitmap_top);
                        _glyphs[glyph].advance  = glm::vec2(
                            static_cast<float>((*static_cast<FT_Face*>(_face))->glyph->advance.x) / 64.0f, 
                            static_cast<float>((*static_cast<FT_Face*>(_face))->glyph->advance.y) / 64.0f
                        );
                        _glyphs[glyph].texPosStart = glm::vec2(0.0f);
                        _glyphs[glyph].texPosEnd   = glm::vec2(0.0f);
                    }
                }
            }

            // Correct size for 'space' character
            _glyphs[static_cast<unsigned char>(' ')].size = _glyphs[static_cast<unsigned char>('a')].size;
            
            _height = fontHeight;
            _texture.unbind();
        }

        float Font::getLineHeight() const {
            return static_cast<float>((*static_cast<FT_Face*>(_face))->size->metrics.height) / 64.0f;
        }

        float Font::getAscender() const {
            //_face->size->metrics.ascender
            //_face->ascender

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

        void Font::setPath(const std::string& path) {
            _path = path;
        }


        void Font::initializeFT() throw(GLUL::Exception::FatalError) {
            static bool initialized = false;

            if(!initialized) {
                if(FT_Init_FreeType(&_FT_library)) {
                    GLUL::Log::Stream("_Library").logError("[FreeType] Unable to initialize FreeType2 library");
                    throw GLUL::Exception::FatalError("Unable to initialize FreeType2 library");
                }

                initialized = true;
            }
        }

    }

}
