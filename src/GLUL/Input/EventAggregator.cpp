#include <GLUL/Input/EventAggregator.h>
#include <GLUL/Input/EventHandler.h>


namespace GLUL {

    namespace Input {

        EventAggregator::EventAggregator() {
            _nextTriggerID = 0;
        }

        EventAggregator::~EventAggregator() {
            clear();
        }

        void EventAggregator::registerEvent(Event* inputEvent) {
            if(inputEvent) {
                _events.emplace_back(inputEvent);
            }
        }

        void EventAggregator::registerHandler(Event::Type type, EventHandler* inputHandler) {
            if(inputHandler) {
                _handlers[type].insert(inputHandler);
                inputHandler->_inputEventAggregators[type].insert(this);
            }
        }
        
        void EventAggregator::registerHandler(std::initializer_list<Event::Type> types, EventHandler* inputHandler) {
            for(auto type : types) {
                registerHandler(type, inputHandler);
            }
        }

        unsigned int EventAggregator::registerTrigger(Event::Type type, const std::function<void(Event&)>& inputTrigger) {
            return registerTrigger(std::initializer_list<Event::Type>{type}, inputTrigger);
        }

        unsigned int EventAggregator::registerTrigger(std::initializer_list<Event::Type> types, const std::function<void(Event&)>& inputTrigger) {
            unsigned int triggerID = _getNextTriggerID();
            
            for(auto type : types) {
                _triggers[type][triggerID] = inputTrigger;
            }

            return triggerID;
        }

        void EventAggregator::unregisterHandler(Event::Type type, EventHandler* inputHandler, bool removeFromHandler) {
            auto handler = _handlers[type].find(inputHandler);

            if(handler != _handlers[type].end()) {
                if(removeFromHandler)
                    (*handler)->_removeAggregator(type, this);

                _handlers[type].erase(handler);
            }
        }
        
        void EventAggregator::unregisterHandler(std::initializer_list<Event::Type> types, EventHandler* inputHandler, bool removeFromHandler) {
            for(auto type : types) {
                unregisterHandler(type, inputHandler, removeFromHandler);
            }
        }

        void EventAggregator::unregisterTrigger(Event::Type type, unsigned int triggerID) {
            _triggers[type].erase(triggerID);
        }
        
        void EventAggregator::unregisterTrigger(std::initializer_list<Event::Type> types, unsigned int triggerID) {
            for(auto type : types) {
                unregisterTrigger(type, triggerID);
            }
        }
        
        void EventAggregator::notifyAll() {
            for(auto& inputEventPtr : _events) {
                for(auto& typeHandler : _handlers[inputEventPtr.get()->getType()]) {
                    typeHandler->handleInputEvent(inputEventPtr.operator*());
                }

                for(auto& typeTrigger : _triggers[inputEventPtr.get()->getType()]) {
                    typeTrigger.second(inputEventPtr.operator*());
                }
            }

            _events.clear();
        }

        void EventAggregator::clear() {
            clearEvents();
            clearTriggers();
            clearSubscribers();
        }

        void EventAggregator::clearEvents() {
            _events.clear();
        }

        void EventAggregator::clearTriggers() {
            _triggers.clear();
        }

        void EventAggregator::clearSubscribers() {
            for(auto& pairTypeSet : _handlers) {
                for(EventHandler* handler : pairTypeSet.second) {
                    unregisterHandler(pairTypeSet.first, handler);
                }
            }
        }

        const std::vector<std::unique_ptr<Event>>& EventAggregator::getEvents() {
            return _events;
        }

        unsigned int EventAggregator::_getNextTriggerID() {
            return _nextTriggerID++;
        }

    }

}
