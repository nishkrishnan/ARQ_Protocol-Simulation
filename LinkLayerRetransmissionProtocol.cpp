//
//  LinkLayerRetransmissionProtocol.cpp
//  lab2
//
//  Created by Nishad Krishnan on 2015-03-13.
//  Copyright (c) 2015 Nish. All rights reserved.
//

#include "LinkLayerRetransmissionProtocol.h"

RetransmissionProtocol::RetransmissionProtocol(int hLength, int pLength, int tR, double bER, int numPacketsForSim, double channDelay, double deltaTaoFact) {
    
    frameHeaderLength = hLength;                        // Header length
    packetLength = pLength;                             // Payload length
    transmissionRate = tR;                              // Link Rate
    packetsDelivered = 0;                               // Packets delivered Successfully
    nextExpectedFrame = 0;                              // Initialize next expected frame
    bitErrorRate = bER;                                 // Bit Error Rate
    numPacketsToSend = numPacketsForSim;                // Number of packets for simulation
    channelDelay = channDelay;                          // Channel Delay
    deltaTaoFactor = deltaTaoFact;                      // Delta/Tau
    packetsLost = 0;                                    // Number of packets lost
    
    srand((uint)time(NULL));                            // Seed RNG to current time
    
}

void RetransmissionProtocol::Simulate(bool nak) {
    Sender(nak);
    
}

int RetransmissionProtocol::Channel(int length, double& propagationDelay) {
    int zeroCount = 0;
    
    //Add channel delay to overall delay
    propagationDelay += channelDelay;
    
    // Iterate through bits and count zeroes to get number of errors
    for (int i = 0; i < length; i++) {
        double randomValue = (rand()/((double)RAND_MAX + 1));
        if (randomValue < bitErrorRate)
            zeroCount++;    
    }
    
    if (zeroCount > 0 && zeroCount <= 4)
        return ERROR;
    else if (zeroCount == 0)
        return NOERROR;
    
    packetsLost++;
    return LOSS;
    
    
}

Event* RetransmissionProtocol::Send(double senderTime, int sN, int length) {
    
    if (sN >= 0) {
        
        // Sending frame to channel has delay
        double propagationDelay = senderTime + (double)length/(double)transmissionRate;
        int rSeqNum = INT_MIN;
        int status = 0;
        
        //Forward Channel
        status = Channel(length, propagationDelay);
        
        // If loss receiver doesnt get called
        if (status != LOSS)
            rSeqNum = Receiver(propagationDelay, sN, status);
        
        
        if (rSeqNum >= 0) {
            
            // Reverse Channel
            status = Channel(frameHeaderLength, propagationDelay);
            
            //Sending ack to channel has delay
            propagationDelay += (double)frameHeaderLength/(double)transmissionRate;
            
            // If loss no event gets created
            if (status != LOSS)
                return CreateEvent(ACK, propagationDelay, status, rSeqNum);
        }
    }
    return NULL;
}

