all:
	g++ -std=c++11 main.cpp ABP.cpp EventScheduler.cpp LinkLayerRetransmissionProtocol.cpp GBN.cpp ShiftingBuffer.cpp -o RUNSIM
