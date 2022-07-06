#pragma once
#include "Event.h"


namespace Agate
{
    class API MouseClick : public Event {
    public:
        MouseClick() {}

        EventTypes GetEventType() override
        {
            return EventTypes::MouseClick;
        }
        void PrintEventName() override
        {
            PRINTMSG("MouseClick");
        }
        void Recived() override
        {
            PRINTMSG("Recvied Mouse Click");
            Event::EventFinised = true;
        }
        bool Handled() override 
        {
            return Event::EventFinised;
        }
    };
}