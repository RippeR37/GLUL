#include <GLUL/Logger.h>
#include <GLUL/String.h>
#include <GLUL/Resources/Textures.h>


namespace GLUL {

    namespace Resources {

        Textures::~Textures() {
            _reportUnreleasedResources();
        }

        const GL::Texture& Textures::Get(const std::string& texture, bool isLibraryResource) {
            return Get(texture,
                GL::Texture::Target::Tex2D,
                GL::Texture::Format::DefaultFormat,
                GL::Texture::InternalFormat::DefaultFormat,
                isLibraryResource
            );
        }

        const GL::Texture& Textures::Get(
            const std::string& texture,
            GL::Texture::Target target,
            GL::Texture::Format format,
            GL::Texture::InternalFormat internalFormat,
            bool isLibraryResource)
        {
            auto texPath = _GetResourcePath(texture, isLibraryResource);

            auto& resourceMap = _GetInstance()._resources;
            auto  resourceKey = std::make_tuple(texPath, target, format, internalFormat);
            auto  findResult = resourceMap.find(resourceKey);

            try {
                if(findResult == resourceMap.end()) {
                    auto emplaceResult = resourceMap.emplace(std::make_pair(
                        resourceKey,
                        std::unique_ptr<GL::Texture> { new GL::Texture(texPath, target, format, internalFormat)}
                    ));
                    return *emplaceResult.first->second;
                } else {
                    return *findResult->second;
                }

            } catch(const GLUL::Exception&) {
                // Could not load request texture, return error texture instead
                return GetErrorTexture();
            }
        }

        const GL::Texture& Textures::GetDefault() {
            return Get(_GetDefaultName(), true);
        }

        const GL::Texture& Textures::GetErrorTexture() {
            return Get(_GetErrorName(), true);
        }

        void Textures::Release(const std::string& texture, bool isLibraryResource) {
            Release(
                texture,
                GL::Texture::Target::Tex2D,
                GL::Texture::Format::DefaultFormat,
                GL::Texture::InternalFormat::DefaultFormat,
                isLibraryResource
            );
        }

        void Textures::Release(const std::string& texture,
            GL::Texture::Target target,
            GL::Texture::Format format,
            GL::Texture::InternalFormat internalFormat,
            bool isLibraryResource)
        {
            auto texPath = _GetResourcePath(texture, isLibraryResource);

            auto& resourceMap = _GetInstance()._resources;
            auto  resourceKey = std::make_tuple(texPath, target, format, internalFormat);

            resourceMap.erase(resourceKey);
        }

        void Textures::ReleaseDefault() {
            Release(_GetDefaultName(), true);
        }

        void Textures::ReleaseErrorTexture() {
            Release(_GetErrorName(), true);
        }

        void Textures::ReleaseAll() {
            _GetInstance()._resources.clear();
        }

        void Textures::_reportUnreleasedResources() {
            auto libResourcePrefix = _GetResourcePath("", true);

            for(const auto& resource : _resources)
                if(!String::startsWith(std::get<0>(resource.first), libResourcePrefix))
                {
                    Log::LibraryStream().logError(
                        std::string("[Resource] [Texture] Unreleased texture: { ")
                        + "path: " + std::get<0>(resource.first) + ", "
                        + "target: " + std::to_string(static_cast<unsigned int>(std::get<1>(resource.first)))
                        + " }"
                    );
                }
        }

        Textures& Textures::_GetInstance() {
            static Textures instance;

            return instance;
        }

        const std::string& Textures::_GetDefaultName() {
            static std::string defaultName = "_defaultTexture.bmp";

            return defaultName;
        }

        const std::string& Textures::_GetErrorName() {
            static std::string errorName = "_errorTexture.bmp";

            return errorName;
        }

        std::string Textures::_GetResourcePath(const std::string& path, bool isLibraryResource) {
            if(isLibraryResource)
                return "resources/textures/GLUL/" + path;
            else
                return "resources/textures/" + path;
        }

    }

}
