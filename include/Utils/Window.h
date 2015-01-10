#ifndef UTIL_WINDOW_H_INCLUDED
#define UTIL_WINDOW_H_INCLUDED

#include "Exception.h"
#include "GL+/Context.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <string>
#include <functional>

namespace Util {
    
    class Window {
        public:
            Window();
            virtual ~Window();
            
            bool create() throw(Util::Exception::FatalError);
            virtual void update();
            void destroy();
            
            void setSize(unsigned int width, unsigned int height);
            void setSize(const glm::uvec2& size);
            void setTitle(const std::string& title);
            void appendTitle(const std::string& text);

            void setDisplayingFPS(bool flag);
            void setCountingFPS(bool flag);
            void setFPSRefreshRate(double refreshRate);
            void setFPSCountCallback(std::function<void(int)> function);
            
            const bool isDisplayingFPS() const;
            const bool isCountingFPS() const;
            const double getFPSRefreshRate() const;
            const int getFPS() const;
            const unsigned int getWidth() const;
            const unsigned int getHeight() const;
            const glm::uvec2& getSize() const;
            const std::string& getTitle() const;

            const bool isCreated() const;
            const double getFrameTime() const;
            GLFWwindow* getHandle();
            GL::Context& getContext();

        protected:
            void setFPSCount(int fpsCount);
            void setHints();
            void setContext();

            static void initializeGLFW() throw(Util::Exception::FatalError);
            static void initializeGLEW() throw(Util::Exception::FatalError);
            
            int _fpsCount;
            bool _isDisplayingFPS;
            bool _isCountingFPS;
            double _fpsRefreshRate;
            double _frameTime;
            GLFWwindow* _handle;
            std::string _title;
            glm::uvec2 _windowSize;
            GL::Context _context;
            std::function<void(int)> _fpsCountCallback;
    };

}

#endif