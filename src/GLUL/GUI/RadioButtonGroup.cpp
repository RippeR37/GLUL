#include <GLUL/GUI/RadioButton.h>
#include <GLUL/GUI/RadioButtonGroup.h>

#include <algorithm>


namespace GLUL {

    namespace GUI {

        RadioButtonGroup::RadioButtonGroup(Container& parent) 
            : RadioButtonGroup(&parent) { }

        RadioButtonGroup::RadioButtonGroup(Container* const parent) 
            : _parent(parent), _setButton(nullptr) { }

        RadioButtonGroup::~RadioButtonGroup() {
            for(RadioButton* radioButtonPtr : _buttons)
                delete radioButtonPtr;
        }


        RadioButton& RadioButtonGroup::create() {
            bool state = _buttons.empty();
            RadioButton* radioButtonPtr = new RadioButton(*this, _parent, state);

            _buttons.push_back(radioButtonPtr);

            if(state)
                _setButton = radioButtonPtr;

            return *radioButtonPtr;
        }

        void RadioButtonGroup::remove(RadioButton& radioButton) {
            RadioButton* radioButtonPtr = &radioButton;

            if(!_buttons.empty() && std::find(_buttons.begin(), _buttons.end(), radioButtonPtr) != _buttons.end()) {
                // Deal with buttons that are currently set
                if(_setButton == radioButtonPtr) {
                    bool fixed = false;

                    // Try to set another
                    for(RadioButton* otherRadioButton : _buttons) {
                        if(otherRadioButton != _setButton) {
                            set(*otherRadioButton);
                            fixed = true;
                            break;
                        }
                    }

                    if(!fixed)
                        _setButton = nullptr; // can't be fixed, it's the only button
                }

                // Remove button from vector and delete it's memory
                _buttons.erase(std::remove(_buttons.begin(), _buttons.end(), radioButtonPtr), _buttons.end());
                delete &radioButton;
            }
        }

        void RadioButtonGroup::set(RadioButton& radioButton) {
            if(!_buttons.empty() && std::find(_buttons.begin(), _buttons.end(), &radioButton) != _buttons.end()) {
                RadioButton& oldRef = *_setButton;
                RadioButton& newRef = radioButton;

                oldRef.setState(false);
                newRef.setState(true);

                _setButton = &newRef;

                onValueChange.call(radioButton, GLUL::GUI::Event::ValueChange<RadioButton&>(oldRef, newRef));
            }
        }

    }

}