#ifndef UTILS_INTERFACES_MVC_VIEW_H_INCLUDED
#define UTILS_INTERFACES_MVC_VIEW_H_INCLUDED

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Util {

    namespace Interface {

        namespace MVC {

            /***
             * Template class of view where type T is view's assigned model
             */

            template<typename T>
            class View {
                public:
                    virtual ~View() { }

                    virtual void init(const T& object) = 0;
                    virtual void render(const T& object) = 0;
            };

            /***
             * Template specialization of view for views without models
             */

            template<>
            class View<void> {
                public:
                    virtual ~View() { }

                    virtual void init() = 0;
                    virtual void render() = 0;
            };

        }

    }

}

#endif