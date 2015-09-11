#pragma once

#include <GLUL/Config.h>


namespace GLUL {

    namespace Interface {

        namespace MVC {

            /***
             * Template class of view where type T is view's assigned model
             */
            template<typename T>
            class GLUL_API View {
                public:
                    virtual ~View() { }

                    virtual void init(const T& object) = 0;
                    virtual void render(const T& object) = 0;
            };


            /***
             * Template specialization of view for views without models
             */
            template<>
            class GLUL_API View<void> {
                public:
                    virtual ~View() { }

                    virtual void init() = 0;
                    virtual void render() = 0;
            };

        }

    }

}
