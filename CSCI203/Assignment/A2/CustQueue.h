//The structure of customer (approximately 100 peoples from the text file)
struct Customer {
    double arrivalTime;
    double serviceTime;
    int priority;
};

//The structure of teller, it could be 1 or multiple one while doing the simulation
struct Teller {
    double endTime = 0;
    double workingTime = 0;
    int customersServed = 0;
};

/*This structure implement a priority queue (insertion sort when queueing), which set the priority in 
descending and arrival time in ascending order then.*/
struct CustomerWaitedQueue {
    Customer* data;
    int head;
    int tail;
    int capacity;

//Set up the total number of customers, who will be in the waited line for serving
    CustomerWaitedQueue(int size) {
        data = new Customer[size];
        head = 0;
        tail = -1;
        capacity = size;
    }
    //clear the data after set
    ~CustomerWaitedQueue() {
        delete[] data;
    }

    //the queue is empty
    bool isEmpty() {
        if (tail < head) {
        return true;
        }
        return false;
    }

    //the queue is full
    bool isFull() {
        if (tail - capacity - 1 == 0) {
            return true;
        }
        return false;
    }

    //This method put the data to the node of queue, and then sort the nodes in queue base on the priority and arrivalTime while queuing
    void enqueue(const Customer& customer) {
        if (isFull()) {
            return;
        }
        int i;
        //Sorting the priority and arrival time
        for (i = tail; i >= head &&
            (customer.priority > data[i].priority ||(customer.priority == data[i].priority 
            && customer.arrivalTime < data[i].arrivalTime)); i--) {
            data[i + 1] = data[i];
        }
        data[i + 1] = customer;
        tail++;
    }

    //Remove the first node from the queue
    void dequeue() {
        if (!isEmpty()) {
            head++;
        }
    }

    //The peek of queue
    Customer& peek() {
        return data[head];
    }

    //The size of queue
    int size() {
        return tail - head + 1;
    }
};

//Definition of all method in main file (A2.cpp)
void printResult(int customerCount, int num,  double currentTime, double totalServiceTime, double totalWaitingTime, int maxQueueLength,Teller tellers[]);
int freeTeller(Teller* tellers, int num);
int calcMax(int val1, int val2);
double calcAverage(double sum, int num);