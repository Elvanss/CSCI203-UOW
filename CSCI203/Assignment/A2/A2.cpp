#include <iostream>
#include <fstream>
//import data accessible from "CustQueue.h"
#include "CustQueue.h"

using namespace std;

int main() {
    //Get the user input (File name and the number of tellers)
    int numTellers;
    string fileName;
    cout << "Enter the number of tellers: ";
    cin >> numTellers;
    cout << "Enter file name: ";
    cin >> fileName;

    //insert ifstream 
    ifstream inputFile(fileName);
    //Handling Exception while reading file
    if (!inputFile) {
        cerr << "Error: Unable to open file " << fileName << endl;
        return 1;
    }
    //the queue for customers should not be move over than 100 people (100:TextFile)
    const int customerNumber = 100;
    //create the waiting queue
    Customer* customerLine = new Customer[customerNumber];
    int customerCount = 0;
    double currentTime = 0;
    const double LARGE_TIME_VALUE = 1.0e9;
    double totalServiceTime = 0;
    double totalWaitingTime = 0;
    int maxQueueLength = 0;
    int currentCust = 0;

    //Read file from a2-sample.txt with 3 given attributes (arrivalTime, serviceTime, and Priority)
    while (customerCount < customerNumber && 
    //Get each attributes
       inputFile >> customerLine[customerCount].arrivalTime && 
       inputFile >> customerLine[customerCount].serviceTime && 
       inputFile >> customerLine[customerCount].priority) {
       customerCount++;
    }
    inputFile.close();

    //Create a tellers array pointing from Teller Structure
    Teller* tellers = new Teller[numTellers];
    //Create a waiting queue to store customers who wait in needed (Max: 120)
    CustomerWaitedQueue customerQueue(customerNumber);

    // In the process that the current of customers is smaller than the total expected customer, or customerQueue is not empty
    while (currentCust < customerCount || !customerQueue.isEmpty()) {
        //if the time of current customer arrive is smaller then the current time 
        while (currentCust < customerCount && customerLine[currentCust].arrivalTime <= currentTime) {
            //get the tellers to finíh the service
            //
            int tellerWork = freeTeller(tellers, numTellers);
            if (currentTime >= tellers[tellerWork].endTime) {
                tellers[tellerWork].workingTime += customerLine[currentCust].serviceTime;
                tellers[tellerWork].endTime = currentTime + customerLine[currentCust].serviceTime;
                totalServiceTime += customerLine[currentCust].serviceTime;
                tellers[tellerWork].customersServed++;
                currentCust++;
            } else {
                customerQueue.enqueue(customerLine[currentCust]);
                currentCust++;
            }
        }

    //Check if customer in waiting queue but the bank in the end of service.
    while (!customerQueue.isEmpty()) {
        int tellerWork = freeTeller(tellers, numTellers);
        if (currentTime >= tellers[tellerWork].endTime) {
            tellers[tellerWork].workingTime += customerQueue.peek().serviceTime;
            totalServiceTime += customerQueue.peek().serviceTime;
            totalWaitingTime += currentTime - customerQueue.peek().arrivalTime;
            tellers[tellerWork].endTime = currentTime + customerQueue.peek().serviceTime;
            tellers[tellerWork].customersServed++;
            customerQueue.dequeue();
        } else {
            break;
        }
    }
    // Update the max queue length
    maxQueueLength = calcMax(maxQueueLength, customerQueue.size());

    // Calculate the next event time (either customer arrival or teller finishing service)
    //Set the time nextEventTime in availability
    double nextEventTime = LARGE_TIME_VALUE;
    //The Time of next event can be identified by getting the time that current customers arrive
    if (currentCust < customerCount) {
        nextEventTime = customerLine[currentCust].arrivalTime;
    }
    for (int i = 0; i < numTellers; i++) {
        if (tellers[i].endTime > currentTime && tellers[i].endTime < nextEventTime) {
            nextEventTime = tellers[i].endTime;
        }
    }
    currentTime = nextEventTime;
}

//Calculate time step to identify the time in last service (->Forward Direction)
    double lastServiceTime = 0;
    for (int i = 0; i < numTellers; i++) {
        lastServiceTime = max(lastServiceTime, tellers[i].endTime);
    }
    currentTime = max(currentTime, lastServiceTime);
    printResult(customerCount,numTellers, currentTime, totalServiceTime, totalWaitingTime, maxQueueLength, tellers);
    
//clearing caches (including the inital customer queue and the list of tellers)
    delete[] customerLine; 
    delete[] tellers;
    return 0;
}

/*Print the report, including all information about the number of customer, 
total max of waiting average(service/waiting/length of queue), and idle rate of each tellers */
void printResult(int customerCount, int num,  double currentTime, double totalServiceTime, double totalWaitingTime, int maxQueueLength,Teller tellers[]) {
    cout << "[----------------------------------------------------]"<<endl;
    cout << "Total customers being served in this simulation: " << customerCount << endl;
        for (int i = 0; i < num; i++) {
            cout << "Number of customers served by teller " << (i + 1) << ": " << tellers[i].customersServed << endl;
    }
    cout << "-----------------------------------------------------"<<endl;
    cout << "Total time of the simulation: " << currentTime << endl;
    cout << "Average service time per customer (this excludes the time spent in the queue): " <<  calcAverage(totalServiceTime, customerCount)<< endl;
    cout << "Average waiting time per customer (this excludes the time spent in the service): " <<  calcAverage(totalWaitingTime, customerCount)<< endl;
    cout << "The maximum length of the queue: " << maxQueueLength << endl;
    cout << "Average length of queue: " << totalWaitingTime / currentTime << endl;

    // Idles rate of tellers:
    for (int i = 0; i < num; i++) {
        double idleRate = (currentTime - tellers[i].workingTime) / currentTime;
        cout << "Idle rate of teller " << (i + 1) << ": " << idleRate << endl;
    }
}

//Find the free tellers 
int freeTeller (Teller* tellers, int num) {
    int workReady = 0;
    double earliestAvailableTime = tellers[0].endTime; 
    for (int i = 1; i < num; i++) {
        if (tellers[i].endTime < earliestAvailableTime) {
            earliestAvailableTime = tellers[i].endTime;
            workReady = i;
        }
    }
    return workReady;
}
//Get max number of 2 elements in calculation
 int calcMax(int val1, int val2) {
    if (val1>val2) {
        return val1;
    } 
    return val2;
   
}
//Get average number
double calcAverage(double sum, int num) {
    return sum/num;
}