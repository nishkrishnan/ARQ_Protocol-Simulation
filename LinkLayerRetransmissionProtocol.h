//
//  LinkLayerRetransmissionProtocol.h
//  lab2
//
//  Created by Nishad Krishnan on 2015-03-13.
//  Copyright (c) 2015 Nish. All rights reserved.
//

#ifndef __lab2__LinkLayerRetransmissionProtocol__
#define __lab2__LinkLayerRetransmissionProtocol__

#include <stdio.h>
#include "EventScheduler.h"
#include <limits.h>
class RetransmissionProtocol {
public:
    RetransmissionProtocol(int hLength, int pLength, int tR, double bER, int numPacketsForSim, double channDelay, double deltaTaoFactor);
    void Simulate(bool nak);
    virtual void Sender(bool nak) = 0;
    Event* Send(double senderTime, int sN, int l);
    virtual int Receiver(double time, int sN, int status) = 0;
    int Channel(int length, double& propagationDelay);
    
    
    
protected:
    int frameHeaderLength, packetLength, transmissionRate, nextExpectedFrame, packetsDelivered, packetsSent,
    numPacketsToSend, packetsLost;
    double bitErrorRate, channelDelay, deltaTaoFactor;
    
    
    
};

#endif /* defined(__lab2__LinkLayerRetransmissionProtocol__) */
