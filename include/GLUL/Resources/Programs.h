#pragma once

#include <GLUL/Config.h>
#include <GLUL/GL++/Program.h>

#include <map>
#include <memory>
#include <string>
#include <utility>


namespace GLUL {

    namespace Resources {

        class GLUL_API Programs {
            public:
                static const GL::Program& Get(const std::string& vShader, const std::string& fShader, bool isLibraryResource = false);

                static void Release(const std::string& vShader, const std::string& fShader, bool isLibraryResource = false);
                static void ReleaseAll();

            private:
                Programs() = default;
                ~Programs();

                Programs(const Programs&) = delete;
                Programs& operator=(const Programs&) = delete;

                void _reportUnreleasedResources();

                static Programs& _GetInstance();
                static std::string _GetResourcePath(const std::string& path, bool isLibraryResource);

                std::map<std::pair<std::string, std::string>, std::unique_ptr<GL::Program>> _resources;
        };

    }

}
