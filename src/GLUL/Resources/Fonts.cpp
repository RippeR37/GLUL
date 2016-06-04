#include <GLUL/Logger.h>
#include <GLUL/String.h>
#include <GLUL/Resources/Fonts.h>


namespace GLUL {

    namespace Resources {

        Fonts::~Fonts() {
            _reportUnreleasedResources();
        }

        const G2D::Font& Fonts::Get(const std::string& font, unsigned int height, bool isLibraryResource) {
            auto resourcePath = _GetResourcePath(font, isLibraryResource);

            auto& resourceMap = _GetInstance()._resources;
            auto  resourceKey = std::make_pair(resourcePath, height);
            auto  findResult  = resourceMap.find(resourceKey);

            if(findResult == resourceMap.end()) {
                auto emplaceResult = resourceMap.emplace(std::make_pair(
                    resourceKey,
                    std::unique_ptr<G2D::Font> { new G2D::Font(resourcePath, height) }
                ));
                return *emplaceResult.first->second;
            } else {
                return *findResult->second;
            }
        }

        const G2D::Font& Fonts::GetDefault() {
            return GetDefault(DefaultHeight());
        }

        const G2D::Font& Fonts::GetDefault(unsigned int height) {
            return Get(_GetDefaultName(), height, true);
        }

        void Fonts::Release(const std::string& font, unsigned int height, bool isLibraryResource) {
            auto resourcePath = _GetResourcePath(font, isLibraryResource);

            auto& resourceMap = _GetInstance()._resources;
            auto  resourceKey = std::make_pair(resourcePath, height);

            resourceMap.erase(resourceKey);
        }

        void Fonts::ReleaseDefault(unsigned int height) {
            Release(_GetDefaultName(), height, true);
        }

        void Fonts::ReleaseDefaults() {
            auto& resourceMap = _GetInstance()._resources;
            auto defaultsPath = _GetResourcePath(_GetDefaultName(), true);

            auto iter = resourceMap.begin();
            while(iter != resourceMap.end()) {
                if(iter->first.first == defaultsPath)
                    iter = resourceMap.erase(iter);
                else
                    ++iter;
            }
        }

        void Fonts::ReleaseAll() {
            _GetInstance()._resources.clear();
        }

        unsigned int Fonts::DefaultHeight(unsigned int newHeight) {
            static unsigned int defaultHeight = 16u;

            if(newHeight) {
                ReleaseDefault(defaultHeight);
                defaultHeight = newHeight;
            }

            return defaultHeight;
        }

        void Fonts::_reportUnreleasedResources() {
            auto libResPrefix = _GetResourcePath("", true);

            for(auto& resource : _resources)
                if(!String::startsWith(resource.first.first, libResPrefix))
                    Log::LibraryStream().logError(
                        "[Resource] [Font] Unreleased font: { "
                            + resource.first.first + ", "
                            + std::to_string(resource.first.second)
                        + " }"
                    );
        }

        Fonts& Fonts::_GetInstance() {
            static Fonts instance;

            return instance;
        }

        const std::string& Fonts::_GetDefaultName() {
            static std::string defaultName = "SourceSansPro.otf";

            return defaultName;
        }

        std::string Fonts::_GetResourcePath(const std::string& font, bool isLibraryResource) {
            if(isLibraryResource)
                return "resources/fonts/GLUL/" + font;
            else
                return "resources/fonts/" + font;
        }

    }

}
