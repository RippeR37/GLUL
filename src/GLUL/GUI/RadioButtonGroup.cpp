#include <GLUL/GUI/RadioButton.h>
#include <GLUL/GUI/RadioButtonGroup.h>

#include <algorithm>


namespace GLUL {

    namespace GUI {

        RadioButtonGroup::RadioButtonGroup(Container& parent) 
            : RadioButtonGroup(&parent) { }

        RadioButtonGroup::RadioButtonGroup(Container* const parent) 
            : _parent(parent), _setButton(nullptr) { }


        RadioButton& RadioButtonGroup::create() {
            bool isFirst = _buttons.empty();
            std::unique_ptr<RadioButton> radioButtonPtr { new RadioButton(*this, _parent, isFirst) };
            RadioButton& result = *radioButtonPtr;

            _buttons.push_back(std::move(radioButtonPtr));

            if(isFirst)
                _setButton = &result;

            return result;
        }

        void RadioButtonGroup::remove(RadioButton& radioButton) {
            RadioButton* radioButtonPtr = &radioButton;

            if(_isInGroup(radioButton)) {
                // If radioButton is currently set, set another one before removing this one
                if(_setButton == radioButtonPtr)
                    _setDifferentThanCurrent();

                // Remove button from vector
                _buttons.erase(
                    std::remove_if(_buttons.begin(), _buttons.end(),
                        [radioButtonPtr](const std::unique_ptr<RadioButton>& rbPtr) {
                            return rbPtr.get() == radioButtonPtr;
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

                oldRef.setState(false);
                newRef.setState(true);

                _setButton = &newRef;

                onValueChange.call(radioButton, GLUL::GUI::Event::ValueChange<RadioButton&>(oldRef, newRef));
            }
        }


        bool RadioButtonGroup::_isInGroup(RadioButton& radioButton) {
            RadioButton* radioButtonPtr = &radioButton;

            auto find_result = std::find_if(_buttons.begin(), _buttons.end(),
                [radioButtonPtr](std::unique_ptr<RadioButton>& rbPtr) {
                    return rbPtr.get() == radioButtonPtr;
                }
            );

            return find_result != _buttons.end();
        }

        bool RadioButtonGroup::_setDifferentThanCurrent() {
            bool setExisting = false;

            // Try to set another
            for(auto& otherRadioButton : _buttons) {
                if(otherRadioButton.get() != _setButton) {
                    set(*otherRadioButton);
                    setExisting = true;
                    break;
                }
            }

            if(!setExisting)
                _setButton = nullptr; // can't be fixed, it's the only button

            return setExisting;
        }

    }

}
