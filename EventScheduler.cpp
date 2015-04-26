//
//  DiscreteEventScheduler.cpp
//  ece358lab1
//
//  Created by Nishad Krishnan on 2015-01-19.
//  Copyright (c) 2015 nish. All rights reserved.
//

#include "EventScheduler.h"
#include <tgmath.h>



//////////////////////////////////////////////////////////////////////////////////////////
////////// Event Scheduler - deals with queue push and pop and generation of events
//////////////////////////////////////////////////////////////////////////////////////////
EventScheduler::EventScheduler() {
    
}

Event::Event(int type, double time, int status, int sN):
    type(type),
    time(time),
    status(status),
    seqNum(sN){
    
}

Event* CreateEvent(int type, double time, int status, int sN) {
    Event* e = new Event(type, time, status, sN);
    return e;
}

void EventScheduler::QueueEvent(Event* e) {
    if (e != NULL)
        eventQueue.push(e);
    
}

void EventScheduler::PurgeTimeouts() {
    std::vector<Event*> tempBuffer;
    
    while (!this->isQueueEmpty()) {
        Event* currentEvent = this->GetFirstEvent();
        
        // push non timeout events to temp vector
        if (currentEvent->type != TIMEOUT)
            tempBuffer.push_back(currentEvent);

        this->DequeueEvent();
    }
    
    // move all events back from temp vector to queue
    for (std::vector<Event*>::iterator it = tempBuffer.begin(); it != tempBuffer.end(); ++it) {
        this->QueueEvent(*it);
    }
    
}

bool EventScheduler::isQueueEmpty() {
    return eventQueue.empty();
}


Event* EventScheduler::GetFirstEvent() {
    return eventQueue.top();
}

void EventScheduler::DequeueEvent() {
    eventQueue.pop();
}

//////////////////////////////////////////////////////////////////////////////////////////
////////// Test Methods
//////////////////////////////////////////////////////////////////////////////////////////

void EventScheduler::PrintQueue() {
    std::vector<Event*> tempBuffer;
    while (!isQueueEmpty()) {
        tempBuffer.push_back(GetFirstEvent());
        std::cout << "Type: " << GetFirstEvent()->type << " Time: " << GetFirstEvent()->time << std::endl;
        DequeueEvent();
    }
    for (std::vector<Event*>::iterator it = tempBuffer.begin(); it != tempBuffer.end(); ++it) {
        
        this->QueueEvent(*it);
    }
    
}

void GenerateTestEventsPurgeTimeouts() {
    EventScheduler scheduler;
    int type;
    for (int i = 0; i < 10; i++) {
        double randomValue = (rand()/((double)RAND_MAX + 1));
        randomValue > 0.5 ? type = TIMEOUT : type = ACK;
        
        scheduler.QueueEvent(CreateEvent(type, randomValue));
        
    }
    scheduler.PrintQueue();
    std::cout << " " << std::endl;
    scheduler.PurgeTimeouts();
    scheduler.PrintQueue();
    
}

