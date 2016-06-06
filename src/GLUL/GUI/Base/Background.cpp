#include <GLUL/G2D/TexturedBatch.h>
#include <GLUL/GUI/Base/Background.h>
#include <GLUL/GUI/Base/Component.h>


namespace GLUL {

    namespace GUI {

        namespace Base {

            Background::Background(const Component& owner) : _owner(owner), border(owner) { }

            void Background::_invalidate() {
                _owner.setInvalid();
            }

        }

    }

}
