class Customer:
    def __init__(self, arrivalTime, serviceTime, priority):
        self.arrivalTime = arrivalTime
        self.serviceTime = serviceTime
        self.priority = priority

class Teller:
    def __init__(self):
        self.idleTimeStamp = 0
        self.customersServed = 0
        self.idleTime = 0

def main():
    numTellers = int(input("Input the number of tellers: "))
    filePath = input("Enter file path: ")
    try:
        with open(filePath, 'r') as file:
            customers = []
            for line in file:
                data = line.split()
                if len(data) == 3:
                    arrivalTime = float(data[0])
                    serviceTime = float(data[1])
                    priority = int(data[2])
                    customer = Customer(arrivalTime, serviceTime, priority)
                    customers.append(customer)

        totalCustomers = len(customers)
        # Create a list of tellers
        tellers = []
        for _ in range(numTellers):
            teller = Teller()
            tellers.append(teller)

        currentTime = 0 # Initialize currentTime
        totalServiceTime = 0 # Initialize totalServiceTime
        totalWaitingTime = 0 # Initialize totalWaitingTime
        maxQueueLength = 0 # Add a variable to keep track of the maximum queue length

        queueList = []

        print("\nProcessing, please wait...")

        while customers or queueList:
            # Create a list of available tellers
            availableTellers = []
            for teller in tellers:
                if teller.idleTimeStamp <= currentTime:
                    availableTellers.append(teller)

            while customers and customers[0].arrivalTime <= currentTime:
                queueList.append(customers.pop(0))

                # Update the maximum queue length if necessary
                maxQueueLength = max(maxQueueLength, len(queueList))

            queueList.sort(key=lambda x: (-x.priority, x.arrivalTime))

            if availableTellers and queueList:
                availableTellers.sort(key=lambda teller: teller.idleTimeStamp)
                availableTeller = availableTellers[0]
                customer = queueList.pop(0)

                currentTime = max(currentTime, customer.arrivalTime)

                # Update the idle time of the teller
                availableTeller.idleTime += currentTime - availableTeller.idleTimeStamp

                waitingTime = currentTime - customer.arrivalTime
                serviceTime = customer.serviceTime

                totalServiceTime += serviceTime
                totalWaitingTime += waitingTime

                availableTeller.idleTimeStamp = currentTime + customer.serviceTime
                availableTeller.customersServed += 1

            elif customers and not queueList and all(teller.idleTimeStamp <= currentTime for teller in tellers):
                currentTime = customers[0].arrivalTime

            else:
                currentTime += 0.0001

        print("Finished!\n")

        for i, teller in enumerate(tellers):
            print(f"Teller {i + 1} served {teller.customersServed} customers")

        simulationTime = max(teller.idleTimeStamp for teller in tellers)
        print(f"Total time of simulation: {simulationTime:.4f}")

        averageServiceTime = totalServiceTime / totalCustomers
        print(f"Average service time per customer (excluding queue time): {averageServiceTime:.4f}")

        averageWaitingTime = totalWaitingTime / totalCustomers
        print(f"Average waiting time per customer (excluding service time): {averageWaitingTime:.4f}")

        print(f"Maximum queue length: {maxQueueLength}")

        averageQueueLength = totalWaitingTime / simulationTime
        print(f"Average queue length: {averageQueueLength:.4f}")

        for i, teller in enumerate(tellers):
            idleRate = teller.idleTime / simulationTime 
            print(f"Idle rate of Teller {i + 1}: {idleRate:.2f}%")

    except FileNotFoundError:
        print("Error: File not found.")

main()