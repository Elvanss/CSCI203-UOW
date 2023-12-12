#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>  // Include the queue library for BFS
#include <limits.h>
#include <cmath>

using namespace std;

class Vertex {
private:
    int label;
    double X, Y;  // Coordinates

public:
    Vertex() {}
    Vertex(const Vertex &vertex) {
        label = vertex.label;
        X = vertex.X;
        Y = vertex.Y;
    }
    Vertex(int label, double X, double Y) {
        this->label = label;
        this->X = X;
        this->Y = Y;
    }
    void display() { cout << "Label: " << label << "  X: " << X << "  Y: " << Y << " "; }
    int getLabel() { return label; }
    double getX() { return X; }
    double getY() { return Y; }
};

class Edge {
private:
    double weight = -1, cost = -1;
    Vertex start, end;

public:
    Edge() {}
    Edge(const Edge &edge) {
        weight = edge.weight;
        cost = edge.cost;
        start = edge.start;
        end = edge.end;
    }
    Edge(Vertex start, Vertex end, double weight) {
        this->start = start;
        this->end = end;
        this->weight = weight;
    }
    void display() {
        cout << "Start: ";
        start.display();
        cout << "End: ";
        end.display();
        cout << "Weight: " << weight << " ";
    }
    void calcCost(Vertex goalVertex) {
        cost = weight + sqrt(pow(end.getX() - goalVertex.getX(), 2) + pow(end.getY() - goalVertex.getY(), 2));  // Calculate heuristic cost
    }
    double getWeight() { return weight; }
    double getCost() { return cost; }
    Vertex getStart() { return start; }
    Vertex getEnd() { return end; }
    double calcDist() { return sqrt(pow(end.getX() - start.getX(), 2) + pow(end.getY() - start.getY(), 2)); }
};

class PriorityQueue {
public:
    PriorityQueue() {}
    bool isEmpty() { return noInQueue <= 0; }
    void enqueue(Edge e) {
        if (noInQueue == 0) {
            queue[noInQueue] = e;
            noInQueue++;
            return;
        }
        queue[noInQueue] = e;
        noInQueue++;
        heapify();
    }
    void dequeue() {
        if (isEmpty()) {
            return;
        }
        swap(queue[0], queue[noInQueue - 1]);
        noInQueue--;
        heapify();
    }
    Edge first() { return queue[0]; }
    void display() {
        for (int i = 0; i < noInQueue; i++) {
            cout << "start: " << queue[i].getStart().getLabel() << " end:" << queue[i].getEnd().getLabel() << " cost:" << queue[i].getCost() << endl;
        }
    }

private:
    Edge queue[100];
    int noInQueue = 0;

    void swap(Edge &e1, Edge &e2) {
        Edge temp = e1;
        e1 = e2;
        e2 = temp;
    }

    void heapify() {
        for (int i = (noInQueue - 1) / 2; i >= 0; i--) {
            siftDown(i, noInQueue - 1);
        }
    }

    void siftDown(int i, int end);
};

class Graph {
private:
    Edge adjMatrix[20][20];

public:
    Graph() {}

    void addEdge(Edge e) {
        adjMatrix[e.getStart().getLabel() - 1][e.getEnd().getLabel() - 1] = e;
        adjMatrix[e.getEnd().getLabel() - 1][e.getStart().getLabel() - 1] = e;
    }

    void display() {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                if (adjMatrix[i][j].getWeight() != -1) {
                    adjMatrix[i][j].display();
                    cout << ", \t";
                } else {
                    cout << " 0 ";
                }
            }
            cout << endl;
        }
        cout << "END" << endl;
    }

    void aStar(int startVertex, Vertex endVertex, bool second);
    void printResults(int Path[], double weights[], int startVertex, Vertex endVertex, bool second);
    void printShortestPath(int path[], int index);
    void removeEdge(int start, int end) {
        Edge empty;
        adjMatrix[start][end] = empty;
    }

    void longestPathBFS(int startVertex);
    void printLongestPath(int parent[], int index);
};

int main() {
    string filename, line, word;
    int nVertices, nEdges, start, end;  // Number of Vertices and Edges
    Graph graph;
    Vertex vList[20];
    Edge eList[100];

    cout << "Enter Filename: " << endl;  // Open file
    cin >> filename;
    ifstream myfile(filename);
    if (myfile.is_open()) {
        getline(myfile, line);
        stringstream ss(line);
        getline(ss, word, '\t');

        nVertices = stoi(word);  // Set vertices
        getline(ss, word, '\t');
        nEdges = stoi(word);  // Set edges

        getline(ss, word);  // Clear buffer

        for (int i = 0; i < nVertices; i++) {
            getline(myfile, line);
            stringstream ss2(line);
            getline(ss2, word, '\t');
            int label = stoi(word);  // Set label
            getline(ss2, word, '\t');
            double X = stod(word);  // Set X coordinate
            getline(ss2, word, '\t');
            double Y = stod(word);  // Set Y coordinate
            Vertex vertex(label, X, Y);  // Create vertex object
            vList[i] = vertex;
        }

        for (int i = 0; i < nEdges; i++) {
            getline(myfile, line);
            stringstream ss2(line);
            getline(ss2, word, '\t');
            int start = stoi(word);  // Set start vertex
            getline(ss2, word, '\t');
            int end = stoi(word);  // Set end vertex
            getline(ss2, word, '\t');
            double weight = stod(word);  // Set Y coordinate
            Edge edge(vList[start - 1], vList[end - 1], weight);  // Create edge object
            eList[i] = edge;
            graph.addEdge(edge);  // Add edge to graph
        }

        getline(myfile, line);
        stringstream ss2(line);
        getline(ss2, word, '\t');

        start = stoi(word);  // Set start vertex
        getline(ss2, word, '\t');
        end = stoi(word);  // Set end vertex

        myfile.close();

        cout << "=============================================" << endl;
        cout << "The number of vertexes in the graph: " << nVertices << endl;
        cout << "The number of edges in the graph: " << nEdges << endl;
        cout << "The start vertexes: " << start << endl;
        cout << "The end vertexes: " << end << endl;
        cout << "=============================================" << endl;

        Edge euclideanEdge(vList[start - 1], vList[end - 1], 0);
        double dist = euclideanEdge.calcDist();
        cout << "The Euclidean distance between the start and the goal vertexes: " << dist << endl;

        cout << endl;
        cout << "Shortest path: ";
        graph.aStar(start - 1, vList[end - 1], false);
        cout << "Longest path: ";
        graph.longestPathBFS(start - 1);
    } else
        cout << "Unable to open file";

    return 0;
}

void PriorityQueue::siftDown(int i, int end) {
    while (i * 2 + 1 < end) {
        int child = 2 * i + 1;
        if ((child + 1 < end) && queue[child].getCost() > queue[child + 1].getCost()) {
            child++;
        }
        if (queue[i].getCost() > queue[child].getCost()) {
            swap(queue[i], queue[child]);
            i = child;
        } else {
            return;
        }
    }
}

void Graph::aStar(int startVertex, Vertex endVertex, bool second) {
    double distance[20];
    double weights[20];
    bool explored[20];
    int path[20];

    for (int i = 0; i < 20; i++) {
        distance[i] = INT_MAX;
        weights[i] = INT_MAX;
        explored[i] = false;
        path[i] = INT_MAX;
    }

    path[startVertex] = -1;
    distance[startVertex] = 0;
    weights[startVertex] = 0;

    PriorityQueue pq;

    for (int i = 0; i < 20; i++) {
        if (adjMatrix[startVertex][i].getWeight() != -1) {
            adjMatrix[startVertex][i].calcCost(endVertex);
            pq.enqueue(adjMatrix[startVertex][i]);
            distance[i] = adjMatrix[startVertex][i].getCost();
            weights[i] = adjMatrix[startVertex][i].getWeight();
            path[i] = startVertex;
        }
    }

    while (!pq.isEmpty()) {
        int index = pq.first().getEnd().getLabel() - 1;
        pq.dequeue();
        if (explored[index] == false) {
            explored[index] = true;
            for (int i = 0; i < 20; i++) {
                if (adjMatrix[index][i].getWeight() != -1) {
                    adjMatrix[index][i].calcCost(endVertex);
                    if (distance[index] + adjMatrix[index][i].getCost() < distance[i]) {
                        distance[i] = distance[index] + adjMatrix[index][i].getCost();
                        weights[i] = weights[index] + adjMatrix[index][i].getWeight();
                        path[i] = index;
                        pq.enqueue(adjMatrix[index][i]);
                    }
                }
            }
        }
    }
    printResults(path, weights, startVertex, endVertex, second);
}

void Graph::printResults(int path[], double weights[], int startVertex, Vertex endVertex, bool second) {
    if (!second)
        cout << "The length of the shortest path: " << weights[endVertex.getLabel() - 1] << endl;
    else
        cout << "The length of the second shortest path: " << weights[endVertex.getLabel() - 1] << endl;

    cout << "The vertices on this path are ";
    printShortestPath(path, endVertex.getLabel() - 1);
    cout << endl;
}

void Graph::printShortestPath(int path[], int index) {
    if (path[index] == -1) {
        cout << index + 1;
        return;
    }

    printShortestPath(path, path[index]);
    cout << " -> " << index + 1;
}

void Graph::longestPathBFS(int startVertex) {
    double weights[20];     // Total weights from start to each vertex
    int parent[20];        
    bool visited[20];

    for (int i = 0; i < 20; i++) {
        weights[i] = 0;
        parent[i] = -1;
        visited[i] = false;
    }

    queue<int> q;

    visited[startVertex] = true;
    q.push(startVertex);

    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();

        for (int i = 0; i < 20; i++) {
            if (adjMatrix[currentVertex][i].getWeight() != -1 && !visited[i]) {
                double newWeight = weights[currentVertex] + adjMatrix[currentVertex][i].getWeight();
                if(newWeight > weights[i]) {
                    weights[i] = newWeight;
                    parent[i] = currentVertex;
                }
                visited[i] = true;
                q.push(i);
            }
        }
    }

    double maxWeight = -1;
    int farthestVertex = -1;

    for (int i = 0; i < 20; i++) {
        if (weights[i] > maxWeight) {
            maxWeight = weights[i];
            farthestVertex = i;
        }
    }

    if (maxWeight == -1) {
        cout << "No path found from the starting vertex " << startVertex + 1 << "." << endl;
    } else {
        cout << "The weight of the longest path: " << maxWeight << endl;
        cout << "The longest path: ";
        printLongestPath(parent, farthestVertex);
        cout << endl;
    }
}


void Graph::printLongestPath(int parent[], int index) {
    if (index == -1) return;
    printLongestPath(parent, parent[index]);
    cout << index + 1;
    if (parent[index] != -1) {
        cout << " -> ";
    }
}