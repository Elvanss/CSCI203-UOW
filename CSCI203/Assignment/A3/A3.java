
import java.io.FileReader;
import java.io.IOException;

/*
 * @author Duy Le
 * ID 7438321
 * @version 17.0 (JDK Version)
 * The information utilized in the program was sourced from content covered in Lectures during Weeks 8 & 9 (Graph's Theories), 
* as well as from an external reference: https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-in-java-using-priorityqueue/ 
*/

public class A3 {
    //finding the shortest path & length calculation
    private void dijkstra(int src) {
        dist = new double[verticesNum];
        prev = new int[verticesNum];
        boolean[] settled = new boolean[verticesNum];
        PriorityQueue queue = new PriorityQueue(verticesNum);

        //set up the initial value of each distance
        for (int i = 0; i < verticesNum; i++) {
            dist[i] = Double.MAX_VALUE;
            prev[i] = -1;
        }
        dist[src] = 0;
        queue.enqueue(new Node(src, 0));

        while (queue.size() > 0) {
            int u = queue.dequeue().node;
            if (settled[u]) continue;
            settled[u] = true;

            // Add a check for a null adjacency list
            if (adjacencyList[u] == null) {
                continue;
            }
            
            // check the distance of nodes
            for (Node neighbor : adjacencyList[u]) {
                if (neighbor == null) break;

                int v = neighbor.node;
                double weight = neighbor.cost;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    queue.enqueue(new Node(v, dist[v]));
                }
            }
        }
    }

    // find the longest path using DFS algorithm
    private void findLongestPath(int src, int dest, boolean[] visited, double currentDist) {
        visited[src] = true;
        tempPath[pathIndex++] = src;
    
        if (src == dest) {
            if (currentDist > maxDist) {
                maxDist = currentDist;
                for (int i = 0; i < pathIndex; i++) {
                    longestPath[i] = tempPath[i];
                }
                for (int i = pathIndex; i < verticesNum; i++) {
                    longestPath[i] = 0; 
                }
            }
        } else {
            if (adjacencyList[src] != null) {
                for (Node neighbor : adjacencyList[src]) {
                    if (neighbor == null) break;
                    if (!visited[neighbor.node]) {
                        findLongestPath(neighbor.node, dest, visited, currentDist + neighbor.cost);
                    }
                }
            }
        }
    
        visited[src] = false;
        pathIndex--;
    }
      
    //read the formatted file 
    private void readFile(String filename) throws IOException {
        FileReader fr = new FileReader(filename);
        int i;
        StringBuilder sb = new StringBuilder();
        
        // Read the first line (including number of vertices & number of edges)
        sb.setLength(0); 
        while ((i = fr.read()) != -1 && i != '\n') {
            sb.append((char) i);
        }
        String[] parts = sb.toString().trim().split("\t");
        verticesNum = Integer.parseInt(parts[0]);
        edgeNum = Integer.parseInt(parts[1]);
        
        //initialize the graphs with edges and vertexes
        vertices = new Vertex[verticesNum];
        adjacencyList = new Node[verticesNum][];
    
        // Read the vertices
        for (int line = 0; line < verticesNum; line++) {
            sb.setLength(0);
            while ((i = fr.read()) != -1 && i != '\n') {
                sb.append((char) i);
            }
            parts = sb.toString().trim().split("\t");
            int id = Integer.parseInt(parts[0]);
            double x = Double.parseDouble(parts[1]);
            double y = Double.parseDouble(parts[2]);
            vertices[line] = new Vertex(id, x, y);
        }
        // Read the edges
        for (int line = 0; line < edgeNum; line++) {
            sb.setLength(0);
            while ((i = fr.read()) != -1 && i != '\n') {
                sb.append((char) i);
            }
            parts = sb.toString().trim().split("\t");
            int from = Integer.parseInt(parts[0]) - 1;
            int to = Integer.parseInt(parts[1]) - 1;
            double weight = Double.parseDouble(parts[2]);
    
            if (adjacencyList[from] == null) {
                adjacencyList[from] = new Node[verticesNum];
            }
    
            for (int j = 0; j < verticesNum; j++) {
                if (adjacencyList[from][j] == null) {
                    adjacencyList[from][j] = new Node(to, weight);
                    break;
                }
            }
        }
    
        // Read the start and goal vertices, which in the end of the text file
        sb.setLength(0);
        while ((i = fr.read()) != -1 && i != '\n') {
            sb.append((char) i);
        }

        parts = sb.toString().trim().split("\t");
        startVertex = Integer.parseInt(parts[0]);
        goalVertex = Integer.parseInt(parts[1]);
        
        fr.close();
    }
    
    //Vertex of graph
    static class Vertex {
        int id;
        double x, y;

        Vertex(int id, double x, double y) {
            this.id = id;
            this.x = x;
            this.y = y;
        }

        double euclideanDistance(Vertex position) {
            return Math.sqrt(Math.pow(this.x - position.x, 2) + Math.pow(this.y - position.y, 2));
        }
    }

    //Node of graph
    static class Node {
        int node;
        double cost;

        Node(int node, double cost) {
            this.node = node;
            this.cost = cost;
        }
    }

    class PriorityQueue {
        private Node[] array;
        private int size = 0;

        PriorityQueue(int capacity) {
            array = new Node[capacity];
        }

        void enqueue(Node node) {
            if (size >= array.length) {
                return;
            }
            array[size++] = node;
            siftUp();
        }

        Node dequeue() {
            Node element = array[0];
            array[0] = array[--size];
            siftDown();
            return element;
        }

        private void siftUp() {
            int child = size - 1;
            int parent;
            while (child > 0) {
                parent = (child - 1) / 2;
                if (array[parent].cost <= array[child].cost) {
                    break;
                }
                swap(parent, child);
                child = parent;
            }
        }

        private void siftDown() {
            int parent = 0;
            int leftChild = 2 * parent + 1;
            int rightChild = 2 * parent + 2;
            int smallestChild;

            while (leftChild < size) {
                if (rightChild < size && array[rightChild].cost < array[leftChild].cost) {
                    smallestChild = rightChild;
                } else {
                    smallestChild = leftChild;
                }

                if (array[smallestChild].cost >= array[parent].cost) {
                    break;
                }
                swap(parent, smallestChild);
                parent = smallestChild;
                leftChild = 2 * parent + 1;
                rightChild = 2 * parent + 2;
            }
        }

        private void swap(int i, int j) {
            Node temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }

        int size() {
            return size;
        }
    }

    private void print() {
        //print the initial values
        System.out.println("======================================================================================");
        System.out.println("The number of vertexes in the graph: " + verticesNum);
        System.out.println("The number of edges in the graph: " + edgeNum);
        System.out.println("The start vertexes: " + startVertex);
        System.out.println("The end vertexes: " + goalVertex);
        System.out.println("======================================================================================");
        //print the euclidean distance
        double euclideanDistance = vertices[startVertex - 1].euclideanDistance(vertices[goalVertex - 1]);
        System.out.printf("The Euclidean distance between the start and the goal vertices: %.5f\n", euclideanDistance);
    
        //calling the dijkstra function
        dijkstra(startVertex - 1);   
        int[] path = new int[verticesNum];
        int pathIndex = 0;
        int at = goalVertex - 1;
        while (at != -1) {
            path[pathIndex++] = at;
            at = prev[at];
        }
        
        //print the shortest path
        System.out.print("Shortest path: ");
        for (int i = pathIndex - 1; i >= 0; i--) {
            System.out.print((path[i] + 1));
            if (i > 0) {
                System.out.print(" -> ");
            }
        }
        System.out.println();
    
        System.out.println("The length of the shortest path: " + (int) dist[goalVertex - 1]);
    
        boolean[] visited = new boolean[verticesNum];
        tempPath = new int[verticesNum];
        longestPath = new int[verticesNum];
        pathIndex = 0;
        findLongestPath(startVertex - 1, goalVertex - 1, visited, 0);
    
        System.out.print("Longest path: ");
        for (int i = 0; i < verticesNum && longestPath[i] != 0; i++) {
            System.out.print((longestPath[i] + 1));
            if (longestPath[i + 1] != 0) System.out.print(" -> ");
        }
        System.out.println();
        System.out.println("The length of the longest path: " + maxDist);
        System.out.println("======================================================================================");
    }

    public static void main(String[] args) throws IOException {
        System.out.print("Enter the file name: ");
        byte[] inputBytes = new byte[100];
        int bytesRead = System.in.read(inputBytes);
        String filename = new String(inputBytes, 0, bytesRead).trim();

        A3 processor = new A3();
        processor.readFile(filename);
        processor.print();
    }

/*Declare the variable */
    //number of edges and vertices
    private int verticesNum;
    private int edgeNum;
    //Storing graph
    private Vertex[] vertices;
    private Node[][] adjacencyList;
    //Start and goal
    private int startVertex;
    private int goalVertex;
    //
    private double[] dist;
    private int[] prev;
    private double maxDist = 0;
    private int[] longestPath;
    private int[] tempPath;
    private int pathIndex;
}
