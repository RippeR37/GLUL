#include <GLUL/Logger.h>
#include <GLUL/Resource/Font.h>


namespace GLUL {

    namespace Resource {

        Font::~Font() {
            _reportUnreleasedResources();
        }

        G2D::Font& Font::Get(const std::string& font, unsigned int height, bool isLibraryAsset) {
            auto resourcePath = _GetResourcePath(font, isLibraryAsset);

            auto& map = _GetInstance()._resources[resourcePath];
            auto findResult = map.find(height);

            if(findResult == map.end()) {
                auto emplaceResult = map.emplace(std::make_pair(
                    height,
                    std::unique_ptr<G2D::Font> { new G2D::Font(resourcePath, height) }
                ));
                return *emplaceResult.first->second;
            } else {
                return *findResult->second;
            }
        }

        G2D::Font& Font::GetDefault() {
            return GetDefault(DefaultHeight());
        }

        G2D::Font& Font::GetDefault(unsigned int height) {
            return Get(_GetDefaultName(), height, true);
        }

        void Font::Release(const std::string& font, unsigned int height, bool isLibraryAsset) {
            auto resourcePath = _GetResourcePath(font, isLibraryAsset);

            auto& outerMap = _GetInstance()._resources;
            auto resourceMap = outerMap.find(resourcePath);

            if(resourceMap != outerMap.end()) {
                auto& innerMap = resourceMap->second;
                auto resourceIter = innerMap.find(height);

                if(resourceIter != innerMap.end())
                    innerMap.erase(resourceIter); // remove font resource

                if(innerMap.empty())
                    outerMap.erase(resourcePath); // remove map if left empty
            }
        }

        void Font::ReleaseDefault(unsigned int height) {
            Release(_GetDefaultName(), height, true);
        }

        void Font::ReleaseDefaults() {
            _GetInstance()._resources.erase(_GetDefaultName());
        }

        void Font::ReleaseAll() {
            _GetInstance()._resources.clear();
        }

        unsigned int Font::DefaultHeight(unsigned int newHeight) {
            static unsigned int defaultHeight = 16u;

            if(newHeight) {
                ReleaseDefault(defaultHeight);
                defaultHeight = newHeight;
            }

            return defaultHeight;
        }

        void Font::_reportUnreleasedResources() {
            for(auto& outerPair : _resources)
                for(auto& innerPair : outerPair.second)
                    GLUL::Log::LibraryStream().logError(
                        "[Resource] [Font] Unreleased font: '" + outerPair.first + "', size: " + std::to_string(innerPair.first)
                    );
        }

        Font& Font::_GetInstance() {
            static Font instance;

            return instance;
        }

        const std::string& Font::_GetDefaultName() {
            static std::string defaultName = "SourceSansPro.otf";

            return defaultName;
        }

        std::string Font::_GetResourcePath(const std::string& font, bool isLibraryAsset) {
            if(isLibraryAsset)
                return "assets/fonts/GLUL/" + font;
            else
                return "assets/fonts/" + font;
        }

    }

}
