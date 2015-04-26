//
//  DiscreteEventScheduler.h
//  ece358lab1
//
//  Created by Nishad Krishnan on 2015-01-19.
//  Copyright (c) 2015 nish. All rights reserved.
//

#ifndef __ece358lab1__DiscreteEventScheduler__
#define __ece358lab1__DiscreteEventScheduler__

#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>

#define NOERROR 0
#define ERROR 1
#define LOSS 2
#define TIMEOUT 3
#define ACK 4


class Event {
public:
    Event(int, double, int, int);
    int type, status, seqNum;
    double time;
    
    
};

struct CompareTime {
    bool operator() (Event* e1, Event* e2) {
        return e1->time > e2->time;
    }
};



class EventScheduler {
public:
    EventScheduler ();
    void QueueEvent(Event* e);
    Event* GetFirstEvent();
    void PurgeTimeouts();
    void DequeueEvent();
    void PrintQueue();
    bool isQueueEmpty();
    double CalculateLambda(double rho);
    

    
private:

    int simulationTime;
    double observerAlpha, arrivalLambda, avgPacketLength, transmissionRate;
    void GenPacketArrivalTimes();
    void GenObserverTimes();

    
    
    
    std::priority_queue<Event*, std::vector<Event*>, CompareTime> eventQueue;
    
};

Event* CreateEvent(int type, double time, int status = 0, int sN = 0);
void GenerateTestEventsPurgeTimeouts();


#endif /* defined(__ece358lab1__DiscreteEventScheduler__) */
