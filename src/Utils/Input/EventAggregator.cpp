#include <Utils/Input/EventAggregator.h>
#include <Utils/Input/EventHandler.h>

namespace Util {

    namespace Input {

        EventAggregator::EventAggregator() {

        }

        EventAggregator::~EventAggregator() {
            clear();
        }

        void EventAggregator::registerEvent(Event* inputEvent) {
            if(inputEvent) {
                _events.emplace_back(inputEvent);
            }
        }

        void EventAggregator::registerSubscriber(Event::Type type, EventHandler* inputHandler) {
            if(inputHandler) {
                _subscribers[type].insert(inputHandler);
                inputHandler->_aggregators[type].insert(this);
            }
        }

        unsigned int EventAggregator::registerTrigger(Event::Type type, const std::function<void(Event&)>& inputTrigger) {
            unsigned int triggerID = _getNextTriggerID();

            _triggers[type][triggerID] = inputTrigger;

            return triggerID;
        }

        void EventAggregator::unregisterSubscriber(Event::Type type, EventHandler* inputHandler) {
            auto iter = _subscribers[type].find(inputHandler);

            if(iter != _subscribers[type].end()) {
                (*iter)->_aggregators[type].erase(this);
                _subscribers[type].erase(iter);
            }
        }

        void EventAggregator::unregisterTrigger(Event::Type type, unsigned int triggerID) {
            _triggers[type].erase(triggerID);
        }
        
        void EventAggregator::notifyAll() {
            for(auto& inputEventPtr : _events) {
                for(auto& typeHandler : _subscribers[inputEventPtr.get()->getType()]) {
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
            for(auto& pairTypeSet : _subscribers) {
                for(EventHandler* handler : pairTypeSet.second) {
                    unregisterSubscriber(pairTypeSet.first, handler);
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