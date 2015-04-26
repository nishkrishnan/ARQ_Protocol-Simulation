//
//  ShiftingBuffer.h
//  lab2
//
//  Created by Nishad Krishnan on 2015-03-15.
//  Copyright (c) 2015 Nish. All rights reserved.
//

#ifndef __lab2__ShiftingBuffer__
#define __lab2__ShiftingBuffer__

#include <stdio.h>
#include <list>
#include <limits.h>


class ShiftingBuffer{
public:
    ShiftingBuffer(int size);
    int Push(int num);
    int ShiftAndFill(int rN);
    int FindRN(int ackSeqNum);
    void PrintBuffer();
    int GetValue(int index);
    void Fill(int lastNum);
private:
    std::list<int> buffer;
    int bufferSize;
};

#endif /* defined(__lab2__ShiftingBuffer__) */
