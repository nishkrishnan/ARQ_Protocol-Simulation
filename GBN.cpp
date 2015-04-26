//
//  GBN.cpp
//  lab2
//
//  Created by Nishad Krishnan on 2015-03-13.
//  Copyright (c) 2015 Nish. All rights reserved.
//

#include "GBN.h"

GBN::GBN(int hLength,                                      // Header length
         int pLength,                                      // Payload length
         int tR,                                           // Link Rate
         double bER,                                       // Bit Error Rate
         int numPacketsForSim,                             // Number of Packets for Simulation
         double channDelay,                                // Channel Delay for one way
         double deltaTaoFactor,                            // Delta/Tau
         int buffSize)                                     // buffer size

:RetransmissionProtocol(hLength, pLength, tR, bER, numPacketsForSim, channDelay, deltaTaoFactor) {
    bufferSize = buffSize;
}

void RunGBNSimulation(double bR, double deltaTaoFactor, double roundtripDelay) {
    
    // one way delay from roundtrip delay from ms to s
    double channelDelay = (roundtripDelay/2)/1000;
    
    GBN simulator(
                  54*8,                                     // Header Length in bits
                  1500*8,                                   // Payload length in bits
                  5000000,                                  // Link Rate in bits/sec
                  bR,                                       // Bit error Rate
                  5000,                                     // Number of packets for simulation
                  channelDelay,                             // One way channel delay
                  deltaTaoFactor,                           // Delta/Tau
                  4);                                       // buffer size
    
    simulator.Simulate(
                       false);                              // nak is set to false
}



//Sends Packets
void GBN::Sender(bool nak) {
    
    //initializing local variables
    int fullPacketLength = packetLength + frameHeaderLength; // total packet length in bits
    double curTime = 0;                                      // current time at sender
    double timeoutVal = deltaTaoFactor * channelDelay;       // calculate timeout value (delta/Tau * Tau)
    int sequenceNum = 0;                                     // the buffer index
    int packetsDelivered = 0;                                // packets successfully delivered
    bool addTimeout = true;                                  // boolean for when to add timeouts
    double times[bufferSize + 1];                            // storing times for each packet in buffer
    
    //Declaring Event Scheduler and Shifting Buffer Objects
    EventScheduler scheduler;
    ShiftingBuffer buffer(bufferSize);
    
    //Initialize time values
    for (int i = 0; i < (bufferSize + 1); i++) {
        times[i] = 0;
    }
    
    //Fill buffer with initial values to send
    buffer.Fill(bufferSize);
    
    while (packetsDelivered < numPacketsToSend) {
        
        //Queue Acks only if sequenceNum is valid.
        if (sequenceNum < bufferSize) {
            scheduler.QueueEvent(Send(curTime, buffer.GetValue(sequenceNum), fullPacketLength));
            curTime += (double)fullPacketLength/(double)transmissionRate;
            times[buffer.GetValue(sequenceNum)] = curTime;
        }
        
        //Purging Timeouts and Adding a new one
        if (addTimeout) {
            scheduler.PurgeTimeouts();
            scheduler.QueueEvent(CreateEvent(TIMEOUT, times[buffer.GetValue(0)] + timeoutVal));
            addTimeout = false;
        }

        //Sends all packets before the time of the next queued event
        if (curTime < scheduler.GetFirstEvent()->time && sequenceNum < (bufferSize - 1)) {
            sequenceNum++;
            addTimeout = false;
            continue;
        }
        else {
            //Gets first event and sets curent time
            Event* curEvent = scheduler.GetFirstEvent();
            if (curEvent->time > curTime)
                curTime = curEvent->time;
            scheduler.DequeueEvent();
            
            //Timeout
            if (curEvent->type == TIMEOUT) {
                sequenceNum = 0;
                addTimeout = true;
            }
            else {
                
                //Check if rN is valid
                int rN = buffer.FindRN(curEvent->seqNum);
                
                //No error and valid rN
                if (curEvent->status == NOERROR &&  rN>= 0) {
                    
                    int shiftAmount = buffer.ShiftAndFill(rN);
                    ++sequenceNum -= shiftAmount;
                    
                    //sequenceNum should never go below 0 since it is technically the buffer index
                    if (sequenceNum < 0)
                        sequenceNum = 0;
                    
                    //Sets timeout to true in order to add timeout for oldest packet in buffer
                    addTimeout = true;
                    
                    packetsDelivered += shiftAmount;
                }
                
                //Error or invalid rN
                else if (curEvent->status == ERROR || rN < 0){
                    sequenceNum++; //Keep transmitting from buffer
                }
            }
        }
    }
    //Final output of throughput
    std::cout << (packetsDelivered*packetLength)/curTime;
}

//Receives Packets
int GBN::Receiver(double time, int sN, int status) {
    
    //If noerror and sN is valid increment next expected frame, else return current one
    if (status == NOERROR && nextExpectedFrame == sN) {
        return ++nextExpectedFrame %= (bufferSize + 1);
    }

    return nextExpectedFrame;
}