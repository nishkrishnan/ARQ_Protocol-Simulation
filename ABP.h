//
//  ABP.h
//  lab2
//
//  Created by Nishad Krishnan on 2015-03-08.
//  Copyright (c) 2015 Nish. All rights reserved.
//

#ifndef __lab2__ABP__
#define __lab2__ABP__

#include <stdio.h>
#include "LinkLayerRetransmissionProtocol.h"

class ABP : public RetransmissionProtocol {
public:
    ABP(int hLength, int pLength, int tR, double bER, int numPacketsForSim, double channDelay, double deltaTaoFactor);
    void Sender(bool nak);
    int Receiver(double time, int sN, int status);
};
void RunSimulation(double bR, double deltaTaoFactor, double roundtripDelay, bool nak);

#endif /* defined(__lab2__ABP__) */
