//
//  ShiftingBuffer.cpp
//  lab2
//
//  Created by Nishad Krishnan on 2015-03-15.
//  Copyright (c) 2015 Nish. All rights reserved.
//

#include "ShiftingBuffer.h"
#include <iostream>

ShiftingBuffer::ShiftingBuffer(int size) {
    bufferSize = size;
}

int ShiftingBuffer::Push(int num) {
    
    if (buffer.size() < bufferSize) {
        buffer.push_back(num);
        return 1;
    }
    return 0;
    
}

int ShiftingBuffer::ShiftAndFill(int rN) {
    
    int lastNum = 0;
    int result = rN - buffer.front();
    
    if (result < 0)
        result += (bufferSize + 1);
    
    int spacesToShift = (result % (bufferSize + 1));
    
    for (int i = 0; i < spacesToShift; i++) {
        lastNum = buffer.front();
        buffer.pop_front();
    }
    Fill(lastNum);
    return spacesToShift;
}

int ShiftingBuffer::FindRN(int ackSeqNum) {
    
    for (int i = 1; i <= bufferSize; i++) {
        if (((buffer.front() + i) % (bufferSize + 1)) == ackSeqNum)
            return ((buffer.front() + i) % (bufferSize + 1));
    }

    return INT_MIN;
}

int ShiftingBuffer::GetValue(int index) {
    
    if (index >= bufferSize)
        return INT_MIN;
    int i = 0;
    for (std::list<int>::iterator it = buffer.begin(); it != buffer.end(); ++it) {
        if (i == index)
            return *it;
        i++;
    }
    return INT_MIN;
    
}

void ShiftingBuffer::Fill(int lastNum) {
    if (bufferSize == buffer.size())
        return;
    if (!buffer.empty())
        while(Push((buffer.back() + 1)%(bufferSize + 1)));
    else {
        Push((lastNum + 1)%(bufferSize + 1));
        while(Push((buffer.back() + 1)%(bufferSize + 1)));
    }
    
    
    
}

void ShiftingBuffer::PrintBuffer() {
    for (std::list<int>::iterator it = buffer.begin(); it != buffer.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

