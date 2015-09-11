#pragma once

#include <GLUL/Config.h>
#include <GLUL/Clock.h>
#include <GLUL/Image.h>
#include <GLUL/Exception.h>
#include <GLUL/Windows.h>
#include <GLUL/GL++/Context.h>
#include <GLUL/Input/EventAggregator.h>

#include <glm/vec2.hpp>

#include <list>
#include <string>
#include <vector>
#include <functional>


struct GLFWwindow;

namespace GLUL {
    
    class GLUL_API Window {
        public:
            Window();
            Window(unsigned int width, unsigned int height, const std::string& title);
            Window(const glm::uvec2& size, const std::string& title);
            virtual ~Window();

            operator GLFWwindow*();
            
            bool create() throw(GLUL::Exception::FatalError);
            virtual void update();
            void destroy();

            void takeScreenshot();
            void takeScreenshot(const std::string& path);
            void takeScreenshot(const std::string& path, const glm::ivec2& origin, const glm::ivec2& size);

            void registerEvents();
            void registerEvents(Input::Event::Type type);
            void registerEvents(std::initializer_list<Input::Event::Type> types);
            
            void skipEvents();
            void skipEvents(Input::Event::Type type);
            void skipEvents(std::initializer_list<Input::Event::Type> types);

            void setSize(unsigned int width, unsigned int height);
            void setSize(const glm::uvec2& size);
            void setPosition(int posX, int posY);
            void setPosition(const glm::ivec2& position);
            void setTitle(const std::string& title);
            void appendTitle(const std::string& text);

            void setDisplayingFPS(bool flag);
            void setCountingFPS(bool flag);
            void setFPSRefreshRate(double refreshRate);

            void setFPSCountCallback(const std::function<void(int)>& function);
            void setDestroyCallback(const std::function<void()>& function);
            
            bool isDisplayingFPS() const;
            bool isCountingFPS() const;
            double getFPSRefreshRate() const;
            int getFPS() const;
            unsigned int getWidth() const;
            unsigned int getHeight() const;
            const glm::uvec2& getSize() const;
            const glm::ivec2& getPosition() const;
            const std::string& getTitle() const;

            bool isCreated() const;
            bool shouldClose() const;
            double getFrameTime() const;
            GLFWwindow* getHandle();
            GL::Context& getContext();
            
            Image getScreenshotNow();
            Image getScreenshotNow(const glm::ivec2& origin, const glm::ivec2& size);

            static void setHint(int option, int value);
            static void setHints(const std::list<std::pair<int, int>>& hints);
            static void setHints(const std::vector<std::pair<int, int>>& hints);
            static void setDefaultHints();

            static void initializeGLFW() throw(GLUL::Exception::FatalError);
            static void initializeGLEW() throw(GLUL::Exception::FatalError);
            
            Input::EventAggregator eventAggregator;

        protected:
            void setFPSCount(int fpsCount);
            void setContext();
            void setFocusCallback();

            int _fpsCount;
            unsigned int _framesCount;
            bool _isScreenshotFlagSet;
            bool _isDisplayingFPS;
            bool _isCountingFPS;
            double _lastFrame;
            double _thisFrame;
            double _fpsTime;
            double _fpsRefreshRate;
            double _frameTime;
            GLFWwindow* _handle;
            std::string _title;
            std::string _screenshotPath;
            glm::uvec2 _windowSize;
            glm::ivec2 _windowPosition;
            glm::ivec2 _screenshotOrigin;
            glm::ivec2 _screenshotSize;
            GL::Context _context;
            std::function<void(int)> _fpsCountCallback;
            std::function<void()> _destroyCallback;
            Clock _fpsClock;

            static bool _hintsSet;

        private:
            static void setFocus(GLFWwindow* window, int focused);
    };

}
