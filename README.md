#Computer Networks Lab 2: ARQ Protocol Simulation

##Description
For this lab, two different ARQ Link Layer protocols were investigated, Alternating Bit Protocol (ABP) and Go Back N (GBN). This project was meant to be a simulation for each protocol which outputs the time it takes for 5000 packets to be transferred from a sender to receiver.  The simulations depend on the following parameters:
* Three different Bit Error Rates (0, 0.0001, 0.00001)
* Two different "Wire" propagation delay values (5 ms, 250 ms)
* 5 different Timeout values as a factor of the propagation delay (2.5, 5, 7.5, 10, 12.5)

##Code Structure
There are two important files, ABN.cpp and GBN.cpp along with their cooresponding header definitions. These files both inherit from the base class RetransmissionProtocol which contains the channel which both protocols use. 

##Running Scripts
Each script is in the Scripts folder.  In order to run them your working directory must be in that folder. 

Each script will:
* compile the code 
* output a .csv file in the Data folder.

In each script I remove any existing csv files with the same name, therefore if there isn't already an existing csv file with the same name. A message saying "no file or directory to remove exists", might pop up on the screen, howevever, the script will still create a csv and output the correct data. Therefore, that message means nothing.

