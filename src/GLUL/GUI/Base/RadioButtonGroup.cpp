#include <GLUL/GUI/Base/Container.h>
#include <GLUL/GUI/Base/RadioButton.h>
#include <GLUL/GUI/Base/RadioButtonGroup.h>

#include <algorithm>


namespace GLUL {

    namespace GUI {

        namespace Base {

            RadioButtonGroup::RadioButtonGroup(const Container& parent)
                : Component(parent, parent.getSize(), {}), _setButton(nullptr) { }

            void RadioButtonGroup::remove(RadioButton& radioButton) {
                RadioButton* radioButtonPtr = &radioButton;

                if(_isInGroup(radioButton)) {
                    // If radioButton is currently set, set another one before removing this one
                    if(_setButton == radioButtonPtr)
                        _setDifferentThanCurrent();

                    // Remove button from vector
                    _buttons.erase(
                        std::remove_if(_buttons.begin(), _buttons.end(),
                            [radioButtonPtr](const std::unique_ptr<RadioButton>& radioButtonIter) {
                                return radioButtonIter.get() == radioButtonPtr;
                            }
                        ),
                        _buttons.end()
                    );
                }
            }

            void RadioButtonGroup::set(RadioButton& radioButton) {
                if(_isInGroup(radioButton)) {
                    RadioButton& oldRef = *_setButton;
                    RadioButton& newRef = radioButton;

                    oldRef._setState(false);
                    newRef._setState(true);

                    _setButton = &newRef;

                    onValueChange.call(radioButton, { oldRef, newRef });
                }
            }


            bool RadioButtonGroup::_isInGroup(RadioButton& radioButton) {
                RadioButton* radioButtonPtr = &radioButton;

                auto find_result = std::find_if(_buttons.begin(), _buttons.end(),
                    [radioButtonPtr](const std::unique_ptr<RadioButton>& radioButtonIter) {
                        return radioButtonIter.get() == radioButtonPtr;
                    }
                );

                return find_result != _buttons.end();
            }

            bool RadioButtonGroup::_setDifferentThanCurrent() {
                bool setExisting = false;

                // Try to set another
                for(auto& radioButtonIter : _buttons) {
                    if(radioButtonIter.get() != _setButton) {
                        set(*radioButtonIter);
                        setExisting = true;
                        break;
                    }
                }

                if(!setExisting)
                    _setButton = nullptr; // there aren't any other RadioButtons left

                return setExisting;
            }

            RadioButton& RadioButtonGroup::_add(bool set, RadioButton* radioButton) {
                bool isFirst = _buttons.empty();

                std::unique_ptr<RadioButton> radioButtonPtr { radioButton };
                RadioButton& radioButtonRef = *radioButtonPtr;

                _buttons.push_back(std::move(radioButtonPtr));

                if(isFirst) {
                    _setButton = &radioButtonRef;
                    radioButton->_setState(true);

                } else if(set) {
                    radioButtonRef.set();
                }

                return radioButtonRef;
            }

        }

    }

}
