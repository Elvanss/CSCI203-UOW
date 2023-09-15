#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Customer
{
private:
  double arrivalTime, serviceTime;
  int priority; 
public:
  Customer()
  {
    this->arrivalTime = 0;
    this->serviceTime = 0;
    this->priority = 0;
  };
  Customer(double arrival, double service, int priority)
  {
    this->arrivalTime = arrival;
    this->serviceTime = service;
    this->priority = priority;
  };
  double getArrival() { return this->arrivalTime; };
  void setArrival(double arrival) { this->arrivalTime = arrival; }
  double getServiceTime() { return this->serviceTime; };
  int getPriority() { return this->priority; } // Add getter for priority
  void decreaseServiceTime(double serviceTime) { this->serviceTime -= serviceTime; };
  void display();
};

void Customer::display()
{
  cout << "Arrival Time: " << this->arrivalTime << ", Service Time: " << this->serviceTime << endl;
}

//-------------------------------------------------------------------------
class Server
{
private:
  double idleTime = 0;
  int customerCounter = 0;
public:
  Server(){};
};

//-------------------------------------------------------------------------
class ArrivalQueue
{
private:
  Customer customerQueue[500];
  int tail = 0, head = 0, maxLength = 0;

public:
  ArrivalQueue(){};
  int getMax() { return maxLength; };
  void enqueue(Customer customer);
  Customer dequeue();
  bool isEmpty();
  void display();
};

void ArrivalQueue::enqueue(Customer customer)
{
  int insertIndex = tail;

  // Find the correct position to insert the customer based on priority and arrival time
  while (insertIndex > head &&
         (customer.getPriority() > customerQueue[(insertIndex - 1) % 500].getPriority() ||
          (customer.getPriority() == customerQueue[(insertIndex - 1) % 500].getPriority() &&
           customer.getArrival() < customerQueue[(insertIndex - 1) % 500].getArrival())))
  {
    // Shift the current customer to the right
    customerQueue[insertIndex % 500] = customerQueue[(insertIndex - 1) % 500];
    insertIndex--;
  }

  // Insert the new customer at the correct position
  customerQueue[insertIndex % 500] = customer;

  // Increment the tail
  tail++;

  // Update maxLength if necessary
  if (this->tail - this->head > this->maxLength) {
    this->maxLength = this->tail - this->head;
  }
}

Customer ArrivalQueue::dequeue()
{
  Customer customer = this->customerQueue[head % 500];
  this->head++;
  return customer;
}

bool ArrivalQueue::isEmpty()
{
  if (this->tail - this->head <= 0)
  {
    return true;
  }
  return false;
}

void ArrivalQueue::display()
{
  for (int i = head; i < tail; i++)
  {
    this->customerQueue[i % 500].display();
  }
}

//-------------------------------------------------------------------------

class ServiceQueue
{
private:
  int serverNum;
  int serviceCount = 0;
  Customer serviceQueue[100];
  Server servers[100];

public:
  ServiceQueue(){};

  ServiceQueue(int serverNum) { this->serverNum = serverNum; };
  double getServiceNum(){return this->serverNum;};
  bool isBusy() { return serviceCount == serverNum;};
  bool isEmpty() { return serviceCount <= 0; };
  void enqueue(Customer c);
  Customer dequeue();
  void siftDown(int i, int end);
  void makeHeap();
  void swap(Customer &c1, Customer &c2);
  void swap(Server &s1, Server &s2);
  void display();
  void displayIdleServers();
};

void ServiceQueue::enqueue(Customer c)
{
  serviceQueue[serviceCount] = c;
  serviceCount++;
  makeHeap();
}

Customer ServiceQueue::dequeue()
{
  Customer c = serviceQueue[0];
  swap(serviceQueue[0], serviceQueue[serviceCount - 1]);
  serviceCount--;
  makeHeap();
  return c;
}

void ServiceQueue::siftDown(int i, int end)
{
  while (i * 2 + 1 < end)
  {
    int child = 2 * i + 1;
    if ((child + 1 < end) && serviceQueue[child].getServiceTime() > serviceQueue[child + 1].getServiceTime())
    {
      child++;
    }
    if (serviceQueue[i].getServiceTime() > serviceQueue[child].getServiceTime())
    {
      swap(serviceQueue[i], serviceQueue[child]);
      swap(servers[i], servers[child]);
      i = child;
    }
    else
    {
      return;
    }
  }
}

void ServiceQueue::makeHeap()
{
  for (int i = (serviceCount - 1) / 2; i >= 0; i--)
  {
    siftDown(i, serviceCount - 1);
  }
}

void ServiceQueue::swap(Customer &c1, Customer &c2)
{
  Customer temp = c1;
  c1 = c2;
  c2 = temp;
}

void ServiceQueue::swap(Server &s1, Server &s2)
{
  Server temp = s1;
  s1 = s2;
  s2 = temp;
}

void ServiceQueue::display()
{
  for (int i = 0; i < serviceCount; i++)
  {
    serviceQueue[i].display();
  }
}

//-------------------------------------------------------------------------
void displayResults(int custCount, double currentTime, double averageWaitingTime, double averageServiceTime, double estAvgQueueLength, int maxLengths, ServiceQueue &sq);
double calcAvg(double sum, int n);

int main()
{
  string filename, line, word;
  double currentTime = 0, totalResponseTime = 0, totalServiceTime = 0;
  int serverNum, custCount = 0;
  ArrivalQueue q;

  cout << "Enter amount of servers: " << endl;
  cin >> serverNum;
  ServiceQueue sq(serverNum);
  cout << "Enter Filename: " << endl;
  cin >> filename;
  ifstream myfile(filename);
  if (myfile.is_open())
  {
    while (getline(myfile, line))
    {
      stringstream ss(line);
      getline(ss, word, ' ');
      if (word != "0" && !word.empty())
            {
                double arrTime = stof(word);
                getline(ss, word, ' ');
                double servTime = stof(word);
                getline(ss, word, ' '); // Add code to read priority
                int priority = stoi(word);
                Customer c(arrTime, servTime, priority);
                totalServiceTime += c.getServiceTime();
                custCount++;

                if (sq.isBusy())
                {
                    q.enqueue(c);
                }
                else
                {
                    sq.enqueue(c);
                }
            }
        }
        myfile.close();

    while (!q.isEmpty())
    { 

    }

    while (!sq.isEmpty())
    {

    }

  //need to be identified
    double averageWaitingTime = 0;
    double averageServiceTime = calcAvg(totalServiceTime, custCount);
    double totalQueueTime = totalResponseTime - totalServiceTime;
    double estAvgQueueLength = totalQueueTime / currentTime;
    int maxLength = q.getMax();
    displayResults(custCount, currentTime, averageWaitingTime, averageServiceTime, estAvgQueueLength, maxLength, sq);
    cout << "Current time: " << currentTime << endl;
  }
  else
    cout << "Unable to open file";
  return 0;
}

void displayResults(int custCount, double currentTime, double averageResponseTime, double averageServiceTime, double estAvgQueueLength, int maxLength, ServiceQueue &sq)
{
  cout << "Number of people served: " << custCount << endl;
  cout << "Time last service request is completed: " << currentTime << endl;
  cout << "Average total waiting time per customer: " << averageResponseTime << endl;   //(this includes the time spent in a queue)
  cout << "Average total time in service per customer: " << averageServiceTime << endl; //(this excludes the time spent in a queue)
  cout << "Average length of the queue: " << estAvgQueueLength << endl;                 //(this can be estimated as the ratio between total queuing time and the time last service request is completed)
  cout << "Maximum length: " << maxLength << endl;                                      // i.e. number of customers, of the queue.
  cout << "Total idle time for each server: " << endl;
  sq.displayIdleServers();
}

// Calculates an average
double calcAvg(double sum, int n)
{
  return sum / n;
}
}

