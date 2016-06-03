#pragma once

#include <GLUL/Config.h>
#include <GLUL/G2D/Font.h>

#include <map>
#include <memory>
#include <string>


namespace GLUL {

    namespace Resource {

        class GLUL_API Font {
            public:
                static G2D::Font& Get(const std::string& font, unsigned int height, bool isLibraryAsset = false);
                static G2D::Font& GetDefault();
                static G2D::Font& GetDefault(unsigned int height);

                static void Release(const std::string& font, unsigned int height, bool isLibraryAsset = false);
                static void ReleaseDefault(unsigned int height);
                static void ReleaseDefaults();
                static void ReleaseAll();

                static unsigned int DefaultHeight(unsigned int newHeight = 0);

            private:
                Font() = default;
                ~Font();

                Font(const Font&) = delete;
                Font& operator=(const Font&) = delete;

                void _reportUnreleasedResources();

                static Font& _GetInstance();
                static const std::string& _GetDefaultName();
                static std::string _GetResourcePath(const std::string& font, bool isLibraryAsset);

                std::map<std::string, std::map<unsigned int, std::unique_ptr<G2D::Font>>> _resources;
        };

    }

}
