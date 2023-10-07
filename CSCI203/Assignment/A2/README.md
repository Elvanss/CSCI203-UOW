## Program design

### Class: Customer
- Arrival Time
- Service Time
- Priority

Constructor()
Constructor with parameter
Methods:
(Getter and setter)
### Class: Teller

Attributes:
- Number of customers served: `_numOfCustomers`
- Total time served: `timeStamp`
- Total idle time: `_timeIdled`
Constructor()
Constructor with parameter
Method

### Queue: ServingQueue

Attributes:
- Time elapsed: `_timeElapsed`
- Maximum length: `_maxLength`

## Outputs

1. Number of customers served

Sum of Teller._numOfCustomersServed

2. Total time of simulation

Only 1 teller required:
teller[0].getTimeServed() + teller[0].getTimeIdled()
SUM(Teller._timeServed + Teller._timeIdled)

3. Average serving time per customer

SUM(Teller._timeServed) / COUNT(Customers)

4. Average waiting time per customer

SUM(Customers._timeWaited) / COUNT(Customers)

5. Maximum length of the queue

ServingQueue._maxLength

6. The average length of the queue

ServingQueue._timeElapsed / (SUM(Teller._timeServed + ServingQueue._timeElapsed))

7. The idle rate of each teller

SUM(Tellers._timeIdled) / (SUM(Teller._timeServed + Teller._timeIdled))
