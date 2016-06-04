#pragma once

#include <GLUL/Config.h>
#include <GLUL/GL++/Texture.h>

#include <map>
#include <memory>
#include <string>
#include <tuple>


namespace GLUL {

    namespace Resources {

        class GLUL_API Textures {
            public:
                static const GL::Texture& Get(const std::string& texture, bool isLibraryResource);
                static const GL::Texture& Get(const std::string& texture,
                    GL::Texture::Target target = GL::Texture::Target::Tex2D,
                    GL::Texture::Format format = GL::Texture::Format::DefaultFormat,
                    GL::Texture::InternalFormat internalFormat = GL::Texture::InternalFormat::DefaultFormat,
                    bool isLibraryResource = false);
                static const GL::Texture& GetDefault();
                static const GL::Texture& GetErrorTexture();

                static void Release(const std::string& texture, bool isLibraryResource);
                static void Release(const std::string& texture,
                    GL::Texture::Target target = GL::Texture::Target::Tex2D,
                    GL::Texture::Format format = GL::Texture::Format::DefaultFormat,
                    GL::Texture::InternalFormat internalFormat = GL::Texture::InternalFormat::DefaultFormat,
                    bool isLibraryResource = false);
                static void ReleaseDefault();
                static void ReleaseErrorTexture();
                static void ReleaseAll();

            private:
                using key_type = std::tuple<std::string, GL::Texture::Target, GL::Texture::Format, GL::Texture::InternalFormat>;

                Textures() = default;
                ~Textures();

                Textures(const Textures&) = delete;
                Textures& operator=(const Textures&) = delete;

                void _reportUnreleasedResources();

                static Textures& _GetInstance();
                static const std::string& _GetDefaultName();
                static const std::string& _GetErrorName();
                static std::string _GetResourcePath(const std::string& path, bool isLibraryResource);

                std::map<key_type, std::unique_ptr<GL::Texture>> _resources;
        };

    }

}
