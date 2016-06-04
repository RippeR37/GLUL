#pragma once

#include <GLUL/Config.h>
#include <GLUL/G2D/Font.h>

#include <map>
#include <memory>
#include <string>
#include <utility>


namespace GLUL {

    namespace Resources {

        class GLUL_API Fonts {
            public:
                static const G2D::Font& Get(const std::string& font, unsigned int height, bool isLibraryResource = false);
                static const G2D::Font& GetDefault();
                static const G2D::Font& GetDefault(unsigned int height);

                static void Release(const std::string& font, unsigned int height, bool isLibraryResource = false);
                static void ReleaseDefault(unsigned int height);
                static void ReleaseDefaults();
                static void ReleaseAll();

                static unsigned int DefaultHeight(unsigned int newHeight = 0);

            private:
                Fonts() = default;
                ~Fonts();

                Fonts(const Fonts&) = delete;
                Fonts& operator=(const Fonts&) = delete;

                void _reportUnreleasedResources();

                static Fonts& _GetInstance();
                static const std::string& _GetDefaultName();
                static std::string _GetResourcePath(const std::string& font, bool isLibraryResource);

                std::map<std::pair<std::string, unsigned int>, std::unique_ptr<G2D::Font>> _resources;
        };

    }

}
