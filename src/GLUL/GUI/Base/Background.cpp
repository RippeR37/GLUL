#include <GLUL/G2D/TexturedBatch.h>
#include <GLUL/GUI/Base/Background.h>
#include <GLUL/GUI/Base/Component.h>


namespace GLUL {

    namespace GUI {

        namespace Base {

            Background::Background(const Component& owner) : border(owner), _owner(owner) { }

            void Background::_invalidate() {
                _owner.setInvalid();
            }

            glm::vec2 Background::_getOwnersRealScreenPosition() const {
                return _owner._getRealScreenPosition();
            }

        }

    }

}
