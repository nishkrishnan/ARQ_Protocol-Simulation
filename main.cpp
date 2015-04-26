//
//  main.cpp
//  lab2
//
//  Created by Nishad Krishnan on 2015-03-07.
//  Copyright (c) 2015 Nish. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include "ABP.h"
#include "ShiftingBuffer.h"
#include "GBN.h"

using namespace std;

int main(int argc, const char * argv[]) {
	double ber = stod(string(argv[1]));
    double dTFactor = stod(string(argv[2]));
    double roundtripDelay = stod(string(argv[3]));
    
    /*double ber = 0.0;
    double dTFactor = 2.5;
    double roundtripDelay = 10;*/
    bool nak;
    	std::istringstream(argv[4]) >> std::boolalpha >> nak;
    string protocolType = string(argv[5]);
    
    if (protocolType.compare("GBN") == 0)
        RunGBNSimulation(ber, dTFactor, roundtripDelay);
    else
        RunSimulation(ber, dTFactor, roundtripDelay, nak);

    
    /*ShiftingBuffer buffer(4);
    
    buffer.Push(4);
    buffer.Push(0);
    buffer.Push(1);
    buffer.Push(2);
    buffer.PrintBuffer();
    buffer.Shift(buffer.FindRN(0));
    buffer.Fill();
    buffer.PrintBuffer();*/
    
    //std::cout << buffer.GetValue(3) << std::endl;
    /*int i = buffer.FindRN(0);
    std::cout << i << std::endl;
    buffer.Shift(i);
    
    buffer.PrintBuffer();*/
    
}
