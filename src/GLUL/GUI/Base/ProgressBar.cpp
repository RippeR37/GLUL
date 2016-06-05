#include <GLUL/GUI/Base/Container.h>
#include <GLUL/GUI/Base/ProgressBar.h>

#include <algorithm>


namespace GLUL {

    namespace GUI {

        namespace Base {

            ProgressBar::ProgressBar(const Container& parent, float progress)
                : ProgressBar(parent, {}, {}, progress) { }

            ProgressBar::ProgressBar(const Container& parent, const glm::vec2& size, const glm::vec2& position, float progress)
                : Component(parent, size, position), _progress(progress) { }

            float ProgressBar::getProgress() const {
                return _progress;
            }

            void ProgressBar::setProgress(float progress) {
                if(getProgress() != progress) {
                    auto oldProgress = getProgress();

                    _progress = progress;
                    setInvalid();

                    onValueChange.call(*this, { oldProgress, getProgress() });
                }
            }

            bool ProgressBar::increaseProgress(float value) {
                setProgress(std::min(getProgress() + value, 1.0f));

                return getProgress() == 1.0f;
            }

            bool ProgressBar::decreaseProgress(float value) {
                setProgress(std::max(getProgress() + value, 0.0f));

                return getProgress() == 0.0f;
            }

        }

    }

}
