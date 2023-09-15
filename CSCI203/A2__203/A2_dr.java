import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

//The inner class representing for the Customers
class Customer{
    private double arrivalTime;
    private double serviceTime;
    private int priority;

    public Customer(){
        arrivalTime = 0;
        serviceTime = 0;
        priority = 0;
    }

    public Customer(double arrivalTime, double serviceTime, int priority){
        this.arrivalTime = arrivalTime;
        this.serviceTime = serviceTime;
        this.priority = priority;
    }

    public double getArrivalTime(){
        return arrivalTime;
    }

    public double getServiceTime(){
        return serviceTime;
    }

    public int getPriority(){
        return priority;
    }

    public void printCustomer() {
        System.out.println("Arrival: " + this.arrivalTime + " Service: " + this.serviceTime + " Priority: " + this.priority);
    }
}

//The inner class representing for the Tellers
class Teller {
    private boolean isBusy;
    private double idleTime =0;
    private int customerServed;

    public Teller(){
        this.isBusy = false;
        this.idleTime = 0.0;
        this.customerServed = 0;
    }

    public boolean isBusy(){
        return isBusy;
    }

    public double getEndTime(){
        return idleTime;
    }

    public int getCustomersServed(){
        return customerServed;
    }

    public void increaseIdleTime(double increaseIdleTime) {
        this.idleTime += increaseIdleTime;
    }
}

//priority queue by storing the customer while all tellers are busy in rules (Priority/Arrival time)
class CustomerQueue {
    private Customer[] customerQueue = new Customer[100]; 
    int tail =0;
    int head =0;
    int length=0;



    //check if the queue is empty:
    public boolean isEmpty() {
        return tail == head;
    }

    //if the queue is full
    public boolean isFull() {
        return tail >= customerQueue.length;
    }

    public void enqueue(Customer customer) {
        if (isFull()) {
            System.out.println("The customer queue is over limit! Please stop doing this!");
        }
        int insertIndex = tail + head - 1;
        while (insertIndex > head &&
                (customerQueue[insertIndex].getPriority() < customer.getPriority() ||
                        (customerQueue[insertIndex].getPriority() == customer.getPriority() &&
                                customerQueue[insertIndex].getArrivalTime() > customer.getArrivalTime())))
        {
            customerQueue[insertIndex + 1] = customerQueue[(insertIndex)];
            insertIndex--;
        }
        customerQueue[insertIndex] = customer;
        tail++;
    }
}
    


class ProcessQueue {
    private final int CAPACITY = 100;
    private int tellers;
    //represent for a line where customers arrive and interact with servers/tellers
    private Customer[] processQueue = new Customer[CAPACITY];
    //This bank is able to have 100 tellers 
    private Teller[] teller = new Teller[100]; 
    private int customerServed = 0;//represent for the tail of the queue

    public ProcessQueue(int tellers) {
        this.tellers = tellers;
        for (int i = 0; i < tellers; i++) {
            teller[i] = new Teller();
        }
    }

    public int getTellers() {
        return this.tellers;
    }    

    // Check if the queue is empty
    public boolean isEmpty() {
        return customerServed <= 0;
    }

    // Check if the queue is full
    public boolean isFull() {
        return tellers - customerServed > 0;
    }

    public void siftDown(int parent, int heapSize) {
        int leftChild = 2*parent +1;
        while (leftChild < heapSize) {
            int chosenChild = leftChild;
            if ((leftChild + 1) < heapSize && processQueue[leftChild + 1].getServiceTime() < processQueue[leftChild].getServiceTime()) {
                chosenChild = leftChild + 1;
            }
    
            if (processQueue[parent].getServiceTime() > processQueue[chosenChild].getServiceTime()) {
                eventSwap(parent, chosenChild);
                tellerSwap(parent, chosenChild);
                parent = chosenChild;
                leftChild = 2*parent + 1;
            } else {
                break;
            }
        }
    }

    public void eventSwap(int customer1, int customer2) {
        Customer temp = processQueue[customer1];
        processQueue[customer1] = processQueue[customer2];
        processQueue[customer2] = temp;
    }

    public void tellerSwap(int teller1, int teller2) {
        Teller temp = teller[teller1];
        teller[teller1] = teller[teller2];
        teller[teller2] = temp;
    } 

    public void makeHeap() {    
        for (int i = (customerServed -1)/2; i>=0; i--) {
            siftDown(i, customerServed -1);
        }
    }

    // Add a customer to the queue
    public void enqueue(Customer customer) {
        // if (isFull()) {
        //     System.out.println("Please wait to be server. Thank you!");
        // }
        processQueue[customerServed] = customer; 
        customerServed = customerServed +1;
        makeHeap();
    }

    public Customer dequeue() {
        if (isEmpty()) { 
            return null;
        }
        Customer customer = processQueue[0]; 
        processQueue[0] = processQueue[customerServed - 1];
        siftDown(0, customerServed);
        //Return the sorted customer again after dequeue the smallest element
        return customer;
    }
}

//This is the main class to run through all the functions from Customer and Teller processing
public class A2_dr {
    public static void main(String[] args) {
        double currentTime = 0;
        int customerNum = 0;
        double totalServiceTime = 0;
        double totalWaitingTime = 0;
        CustomerQueue cusQueue = new CustomerQueue();
        Scanner input = new Scanner(System.in);

        System.out.print("Enter the number of tellers: ");
        int tellerNum = input.nextInt();
        ProcessQueue tellerWork = new ProcessQueue(tellerNum);

        System.out.print("Enter file name: ");
        input.nextLine(); // Consume the newline
        String fileName = input.nextLine(); // Use nextLine to read the entire line

        try {
        Scanner readFile = new Scanner(new FileReader(fileName));
            while (readFile.hasNext()) {
                if (readFile.hasNextDouble()) {
                    double arrivalTime = readFile.nextDouble();
                    double serviceTime = readFile.nextDouble();

                    if (!readFile.hasNextInt()) {
                        break;
                    }
                    int priority = readFile.nextInt();

                    Customer customer = new Customer(arrivalTime, serviceTime, priority);
                    // customer.printCustomer();

                    totalServiceTime += customer.getServiceTime();
                    customerNum++;
                }
            } 
            if (readFile.hasNextLine()) {
                readFile.nextLine();
            }
            
        } catch (IOException e) {
            System.out.println("The file name " + fileName + " could not be opened!");
            System.out.println("Error: " + e.getMessage());
        } finally {
            input.close();
        }
    }

    public static void displayResults(int custCount, double currentTime, double averageWaitingTime, double averageServiceTime, double estAvgQueueLength, ProcessQueue tellerWork){
        System.out.println("Number of people served: " + custCount);
        System.out.println("Time last service request is completed: " + currentTime);
        System.out.println("Average total service time per customer: " + averageWaitingTime); //(this excludes the time spent in a queue)
        System.out.println("Average total time in service per customer: " + averageServiceTime); //(this excludes the time spent in a queue)
        System.out.println("Average length of the queue: " + estAvgQueueLength); //(this can be estimated as the ratio between total queuing time and the time last service request is completed)
        // System.out.println("Maximum length: " + maxLength); // i.e. number of customers, of the queue.
        System.out.println("Total idle time for each server: ");
    }
        // sq.displayIdleServers();

    public static double calcAvg(double sum , int i) {
        return sum/i;
    }
}
