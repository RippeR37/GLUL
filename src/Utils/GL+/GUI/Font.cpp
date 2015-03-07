#include <Utils/GL+/GUI/Font.h>
#include <Utils/Logger.h>

#include <algorithm>

namespace GL {

    namespace GUI {

        FT_Library Font::_library;


        Font::Font() {
            Font::initializeFT();
        }

        Font::Font(const std::string& path) {
            Font::initializeFT();

            load(path);
        }

        Font::~Font() {
            FT_Done_Face(_face);
        }

        void Font::load(const std::string& path) {
            setPath(path);

            if(FT_New_Face(Font::_library, getPath().c_str(), 0, &_face))
                Util::Log::Stream("_Library").logError("[FreeType] Unable to load face from file '" + path + "'");
        }

        void Font::load(const std::string& path, unsigned int fontHeight) {
            setPath(path);

            if(FT_New_Face(Font::_library, getPath().c_str(), 0, &_face)) {
                Util::Log::Stream("_Library").logError("[FreeType] Unable to load face from file '" + path + "'");

            } else {
                generate(fontHeight);
            }
        }

        void Font::generate(unsigned int fontHeight) {
            FT_Set_Pixel_Sizes(_face, 0, fontHeight);

            // TODO: implement this swith in GL::Context class
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            bool maxWidthReached = false;
            int totalWidth = 0;
            int totalHeight = 1;
            int maxWidth = 2048;
            unsigned int maxHeight = 0;


            // Calculate texture size
            for(char glyph = 0; glyph < 128; ++glyph) {
                if(FT_Load_Char(_face, glyph, FT_LOAD_RENDER)) {
                    Util::Log::Stream("_Library").logWarning(
                        "[FreeType] Unable to load glyph of '" + std::to_string(glyph) +  
                        "' (" + std::to_string(static_cast<int>(glyph)) + ")"
                    );

                } else {
                    totalWidth += _face->glyph->bitmap.width;
                    maxHeight = std::max(maxHeight, _face->glyph->bitmap.rows);

                    if(totalWidth > maxWidth) {
                        maxWidthReached = true;
                        totalWidth = _face->glyph->bitmap.width;
                        totalHeight += 1;
                    }
                }
            }


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

            _texture.setTarget(Texture::Target::Tex2D);
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

            for(char glyph = 0; glyph < 128; ++glyph) {
                if(FT_Load_Char(_face, glyph, FT_LOAD_RENDER)) {
                    Util::Log::Stream("_Library").logWarning(
                        "[FreeType] Unable to load glyph of '" + std::to_string(glyph) +
                        "' (" + std::to_string(static_cast<int>(glyph)) + ")"
                    );

                } else {
                    currentWidth  = _face->glyph->bitmap.width;
                    currentHeight = _face->glyph->bitmap.rows;

                    // Check if current chunk will fit current row, if not move it to next row
                    if(offsetX + currentWidth >= totalWidth) {
                        offsetX = 0;
                        offsetY += maxHeight;
                    }

                    // Save position of glyph's bitmap in texture
                    _glyphs[glyph].size     = glm::vec2(_face->glyph->bitmap.width, _face->glyph->bitmap.rows);
                    _glyphs[glyph].glyphPos = glm::vec2(_face->glyph->bitmap_left,  _face->glyph->bitmap_top);

                    _glyphs[glyph].advance  = glm::vec2(                                // check if problems !!!!!!!!!!!!!!!!!
                        static_cast<float>(_face->glyph->advance.x) / 64.0f, 
                        static_cast<float>(_face->glyph->advance.y) / 64.0f
                    );

                    _glyphs[glyph].texPos   = glm::vec2(
                        static_cast<float>(offsetX) / static_cast<float>(totalWidth),
                        static_cast<float>(offsetY) / static_cast<float>(totalHeight)
                    );

                    // Write glyph on texture
                    // TODO: Fix this to use GL::Texture's functionality
                    glTexSubImage2D(GL_TEXTURE_2D, 0, offsetX, offsetY, currentWidth, currentHeight, GL_RED, GL_UNSIGNED_BYTE, _face->glyph->bitmap.buffer);

                    // Move to next glyph
                    offsetX += currentWidth;
                }
            }

            _texture.unbind();
        }

        const std::string& Font::getPath() const {
            return _path;
        }

        void Font::setPath(const std::string& path) {
            _path = path;
        }


        void Font::initializeFT() {
            static bool initialized = false;

            if(!initialized) {
                if(FT_Init_FreeType(&Font::_library)) {
                    Util::Log::Stream("_Library").logError("[FreeType] Unable to initialize FreeType2 library");
                    throw Util::Exception::FatalError("Unable to initialize FreeType2 library");
                }

                initialized = true;
            }
        }

    }

}