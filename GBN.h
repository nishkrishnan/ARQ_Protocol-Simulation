//
//  GBN.h
//  lab2
//
//  Created by Nishad Krishnan on 2015-03-13.
//  Copyright (c) 2015 Nish. All rights reserved.
//

#ifndef __lab2__GBN__
#define __lab2__GBN__

#include <stdio.h>
#include "LinkLayerRetransmissionProtocol.h"
#include "ShiftingBuffer.h"


class GBN: public RetransmissionProtocol {
    
    public:
        GBN(int hLength, int pLength, int tR, double bER, int numPacketsForSim, double channDelay, double deltaTaoFactor, int buffSize);
        void Sender(bool nak);
        int Receiver(double time, int sN, int status);
        
    private:
        int bufferSize;
};

void RunGBNSimulation(double bR, double deltaTaoFactor, double roundtripDelay);

#endif /* defined(__lab2__GBN__) */
