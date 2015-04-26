//
//  ABP.cpp
//  lab2
//
//  Created by Nishad Krishnan on 2015-03-08.
//  Copyright (c) 2015 Nish. All rights reserved.
//

#include "ABP.h"
#include <tgmath.h>



void RunSimulation(double bR, double deltaTaoFactor, double roundtripDelay, bool nak) {
    
    //Calculating one way delay from roundtrip delay from ms to s
    double channelDelay = (roundtripDelay/2)/1000;
    
    ABP simulator(54*8,                                         // Header Length in bits
                  1500*8,                                       // Payload length in bits
                  5000000,                                      // Link Rate
                  bR,                                           // Bit Error Rate
                  5000,                                         // Number of packets for simulation
                  channelDelay,                                 // One way channel delay
                  deltaTaoFactor);                              // Delta/Tau
    
    simulator.Simulate(nak);
}


ABP::ABP(int hLength,
         int pLength,
         int tR,
         double bER,
         int numPacketsForSim,
         double channDelay,
         double deltaTaoFact)

:RetransmissionProtocol(hLength, pLength, tR, bER, numPacketsForSim, channDelay, deltaTaoFact) {}


void ABP::Sender(bool nak) {
    
    //Delcare and Initialize local variables
    int sequenceNum = 0;                                        // Sequence number of packet being sent
    int prevSequenceNum = -1;                                   // Sequence number of previous packet sent
    int nextExpectedAck = 1;                                    // Next expected ACK
    double timeoutVal = deltaTaoFactor * channelDelay;          // Timeout value
    double curTime = 0;                                         // Current Time
    int fullPacketLength = frameHeaderLength + packetLength;    // Full Packet length
    EventScheduler scheduler;                                   // Event Scheduler

    while (packetsDelivered < numPacketsToSend) {
        
        // If previous sequence number equals sequenceNum then there was error and need to wait for timeout
        // to occur before purging and adding a new one. (disregard for nak)
        if (prevSequenceNum != sequenceNum || nak) {
            scheduler.PurgeTimeouts();
            scheduler.QueueEvent(CreateEvent(TIMEOUT, curTime + (double)fullPacketLength/(double)transmissionRate + timeoutVal));
            scheduler.QueueEvent(Send(curTime, sequenceNum, fullPacketLength));
        }
        
        // Get First Event, and set current time to event time
        Event* curEvent = scheduler.GetFirstEvent();
        scheduler.DequeueEvent();
        curTime = curEvent->time;
        
        // Timeout
        if (curEvent->type == TIMEOUT) {
            prevSequenceNum = -1;
            continue;
        }
        else {
            
            // If packet has error, this will ensure that simulator waits for timout instead of
            // retransmitting
            prevSequenceNum = sequenceNum;
            
            // Successful Delivery
            if (curEvent->status == NOERROR && curEvent->seqNum == nextExpectedAck) {
                packetsDelivered++;
                ++sequenceNum %= 2;
                ++nextExpectedAck %= 2;
            }
        }
    }
    //Output final throughput
    std::cout << ((double)packetsDelivered*(double)packetLength)/curTime;
}


int ABP::Receiver(double time, int sN, int status) {
    
    //Increment next expected frame if there is no error and SN is correct, else return same frame
    if (status == NOERROR && nextExpectedFrame == sN) {
        return ++nextExpectedFrame %= 2;
    }
    return nextExpectedFrame;
}








