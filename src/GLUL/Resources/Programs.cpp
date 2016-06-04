#include <GLUL/Logger.h>
#include <GLUL/String.h>
#include <GLUL/Resources/Programs.h>


namespace GLUL {

    namespace Resources {

        Programs::~Programs() {
            _reportUnreleasedResources();
        }

        const GL::Program& Programs::Get(const std::string& vShader, const std::string& fShader, bool isLibraryResource) {
            auto vShaderPath = _GetResourcePath(vShader, isLibraryResource);
            auto fShaderPath = _GetResourcePath(fShader, isLibraryResource);

            auto& resourceMap = _GetInstance()._resources;
            auto  resourceKey = std::make_pair(vShaderPath, fShaderPath);
            auto  findResult  = resourceMap.find(resourceKey);

            if(findResult == resourceMap.end()) {
                auto emplaceResult = resourceMap.emplace(std::make_pair(
                    resourceKey,
                    std::unique_ptr<GL::Program> { new GL::Program(vShaderPath, fShaderPath) }
                ));
                return *emplaceResult.first->second;
            } else {
                return *findResult->second;
            }
        }

        void Programs::Release(const std::string& vShader, const std::string& fShader, bool isLibraryResource) {
            auto vShaderPath = _GetResourcePath(vShader, isLibraryResource);
            auto fShaderPath = _GetResourcePath(fShader, isLibraryResource);

            auto& resourceMap = _GetInstance()._resources;
            auto  resourceKey = std::make_pair(vShaderPath, fShaderPath);

            resourceMap.erase(resourceKey);
        }

        void Programs::ReleaseAll() {
            _GetInstance()._resources.clear();
        }

        void Programs::_reportUnreleasedResources() {
            auto libResourcePrefix = _GetResourcePath("", true);

            for(const auto& resource : _resources)
                if(!String::startsWith(resource.first.first, libResourcePrefix) &&
                   !String::startsWith(resource.first.second, libResourcePrefix))
                {
                    Log::LibraryStream().logError(
                        "[Resource] [Program] Unreleased program: { "
                            + resource.first.first + ", "
                            + resource.first.second
                        + " }"
                    );
                }
        }

        Programs& Programs::_GetInstance() {
            static Programs instance;

            return instance;
        }

        std::string Programs::_GetResourcePath(const std::string& path, bool isLibraryResource) {
            if(isLibraryResource)
                return "resources/shaders/GLUL/" + path;
            else
                return "resources/shaders/" + path;
        }

    }

}
