package Coding_Class;
// import java.io.*;
// import java.util.*;
// import java.util.Map.Entry;

// public class A3 {
//     private static final double INF = Double.MAX_VALUE;
//     private Map<Integer, Point> vertices = new HashMap<>();
//     private List<Edge> edges = new ArrayList<>();
//     private double[][] adjacencyMatrix;
//     private int nVertices, nEdges, startVertex, goalVertex;

//     public static void main(String[] args) throws IOException {
//         BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
//         System.out.print("Enter the file name: ");
//         String filename = reader.readLine();

//         A3 processor = new A3();
//         processor.readFile(filename);

//         System.out.println("Number of Vertices: " + processor.nVertices);
//         System.out.println("Number of Edges: " + processor.nEdges);
//         System.out.println("Start and Goal: " + processor.startVertex + ", " + processor.goalVertex);

//         Point start = processor.vertices.get(processor.startVertex);
//         Point goal = processor.vertices.get(processor.goalVertex);
//         double euclideanDistance = Math.sqrt(Math.pow(start.x - goal.x, 2) + Math.pow(start.y - goal.y, 2));
//         System.out.println("Euclidean distance between start and goal: " + euclideanDistance);

//         // Shortest path
//         Pair<List<Integer>, Double> shortestPath = processor.dijkstra();
//         System.out.println("Shortest Path: " + shortestPath.getKey());
//         System.out.println("Length of Shortest Path: " + shortestPath.getValue());

//         // Longest path
//         Pair<List<Integer>, Double> longestPath = processor.findLongestPath(processor.startVertex, processor.goalVertex, new HashSet<>(), 0.0);
//         System.out.println("Longest Path: " + longestPath.getKey());
//         System.out.println("Length of Longest Path: " + longestPath.getValue());
//     }

//     // Using Dijkstra's algorithm for shortest path
//     private Pair<List<Integer>, Double> dijkstra() {
//         double[] dist = new double[nVertices];
//         int[] prev = new int[nVertices];
//         boolean[] visited = new boolean[nVertices];

//         Arrays.fill(dist, INF);
//         dist[startVertex - 1] = 0;

//         for (int i = 0; i < nVertices; i++) {
//             int u = getMinimumVertex(dist, visited);
//             visited[u] = true;

//             for (int v = 0; v < nVertices; v++) {
//                 if (!visited[v] && adjacencyMatrix[u][v] != INF && dist[u] + adjacencyMatrix[u][v] < dist[v]) {
//                     dist[v] = dist[u] + adjacencyMatrix[u][v];
//                     prev[v] = u;
//                 }
//             }
//         }

//         List<Integer> path = new ArrayList<>();
//         for (int at = goalVertex - 1; at != -1; at = prev[at]) {
//             path.add(at + 1);
//         }
//         Collections.reverse(path);

//         return new Pair<>(path, dist[goalVertex - 1]);
//     }

//     private int getMinimumVertex(double[] distance, boolean[] visited) {
//         int minIndex = -1;
//         for (int i = 0; i < nVertices; i++) {
//             if (!visited[i] && (minIndex == -1 || distance[i] < distance[minIndex])) {
//                 minIndex = i;
//             }
//         }
//         return minIndex;
//     }

//     // Brute force approach for longest path
//     private Pair<List<Integer>, Double> findLongestPath(int current, int destination, Set<Integer> visited, double currentWeight) {
//         visited.add(current);

//         if (current == destination) {
//             return new Pair<>(Collections.singletonList(current), currentWeight);
//         }

//         double maxWeight = -INF;
//         List<Integer> maxPath = new ArrayList<>();

//         for (int next = 0; next < nVertices; next++) {
//             if (adjacencyMatrix[current - 1][next] != INF && !visited.contains(next + 1)) {
//                 Pair<List<Integer>, Double> result = findLongestPath(next + 1, destination, new HashSet<>(visited), currentWeight + adjacencyMatrix[current - 1][next]);
//                 if (result.getValue() > maxWeight) {
//                     maxWeight = result.getValue();
//                     maxPath = result.getKey();
//                 }
//             }
//         }

//         List<Integer> currentPath = new ArrayList<>();
//         currentPath.add(current);
//         currentPath.addAll(maxPath);
//         return new Pair<>(currentPath, maxWeight);
//     }

//     private void readFile(String filename) {
//         try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
//             String[] firstLine = br.readLine().split("\t");
//             nVertices = Integer.parseInt(firstLine[0]);
//             nEdges = Integer.parseInt(firstLine[1]);
//             adjacencyMatrix = new double[nVertices][nVertices];

//             for (int i = 0; i < nVertices; i++) {
//                 for (int j = 0; j < nVertices; j++) {
//                     adjacencyMatrix[i][j] = i == j ? 0 : INF;
//                 }
//             }

//             for (int i = 0; i < nVertices; i++) {
//                 String[] line = br.readLine().split("\t");
//                 int k = Integer.parseInt(line[0]);
//                 double x = Double.parseDouble(line[1]);
//                 double y = Double.parseDouble(line[2]);
//                 vertices.put(k, new Point(x, y));
//             }

//             for (int i = 0; i < nEdges; i++) {
//                 String[] line = br.readLine().split("\t");
//                 int from = Integer.parseInt(line[0]);
//                 int to = Integer.parseInt(line[1]);
//                 double weight = Double.parseDouble(line[2]);
//                 edges.add(new Edge(from, to, weight));
//                 adjacencyMatrix[from - 1][to - 1] = weight; // considering 0-based indexing
//             }

//             String[] lastLine = br.readLine().split("\t");
//             startVertex = Integer.parseInt(lastLine[0]);
//             goalVertex = Integer.parseInt(lastLine[1]);

//         } catch (IOException e) {
//             e.printStackTrace();
//         }
//     }

//     class Point {
//         double x, y;
//         public Point(double x, double y) {
//             this.x = x;
//             this.y = y;
//         }
//     }

//     class Edge {
//         int from, to;
//         double weight;

//         public Edge(int from, int to, double weight) {
//             this.from = from;
//             this.to = to;
//             this.weight = weight;
//         }
//     }

//     class Pair<K, V> {
//         private final K key;
//         private final V value;

//         public Pair(K key, V value) {
//             this.key = key;
//             this.value = value;
//         }

//         public K getKey() {
//             return key;
//         }

//         public V getValue() {
//             return value;
//         }
//     }
// }
import java.io.*;

public class GraphAlgorithms {
    private int nVertices;
    private int nEdges;
    private Vertex[] vertices;
    private Edge[] edges;
    private int startVertex;
    private int goalVertex;

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Enter the file name: ");
        String filename = reader.readLine();

        GraphAlgorithms processor = new GraphAlgorithms();
        processor.readFile(filename);
        processor.process();
    }

    private void process() {
        // Compute shortest path using Dijkstra
        double[] dist = new double[nVertices];
        boolean[] visited = new boolean[nVertices];
        int[] previous = new int[nVertices];
        for (int i = 0; i < nVertices; i++) {
            dist[i] = Double.MAX_VALUE;
            visited[i] = false;
        }
        dist[startVertex - 1] = 0;

        for (int i = 0; i < nVertices; i++) {
            int u = findNextVertex(dist, visited);
            visited[u] = true;
            for (int j = 0; j < nEdges; j++) {
                if (edges[j].from == u + 1 && !visited[edges[j].to - 1] && dist[u] + edges[j].weight < dist[edges[j].to - 1]) {
                    dist[edges[j].to - 1] = dist[u] + edges[j].weight;
                    previous[edges[j].to - 1] = u;
                }
            }
        }

        // Output shortest path
        System.out.println("Shortest path from " + startVertex + " to " + goalVertex + ":");
        int[] path = new int[nVertices];
        int count = 0;
        for (int v = goalVertex - 1; v != startVertex - 1; v = previous[v]) {
            path[count++] = v + 1;
        }
        path[count++] = startVertex;

        for (int i = count - 1; i >= 0; i--) {
            System.out.print(path[i] + " ");
        }
        System.out.println("\nLength: " + dist[goalVertex - 1]);
        // Longest path would be calculated similarly, but this is omitted as it's computationally hard.
    }

    private int findNextVertex(double[] dist, boolean[] visited) {
        int minVertex = -1;
        double minDist = Double.MAX_VALUE;
        for (int i = 0; i < nVertices; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                minVertex = i;
            }
        }
        return minVertex;
    }

    private void readFile(String filename) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader(filename));
        String[] parts = br.readLine().split("\t");
        nVertices = Integer.parseInt(parts[0]);
        nEdges = Integer.parseInt(parts[1]);
        vertices = new Vertex[nVertices];
        edges = new Edge[nEdges];

        for (int i = 0; i < nVertices; i++) {
            parts = br.readLine().split("\t");
            vertices[i] = new Vertex(Integer.parseInt(parts[0]), Double.parseDouble(parts[1]), Double.parseDouble(parts[2]));
        }

        for (int i = 0; i < nEdges; i++) {
            parts = br.readLine().split("\t");
            edges[i] = new Edge(Integer.parseInt(parts[0]), Integer.parseInt(parts[1]), Double.parseDouble(parts[2]));
        }

        parts = br.readLine().split("\t");
        startVertex = Integer.parseInt(parts[0]);
        goalVertex = Integer.parseInt(parts[1]);
        br.close();
    }

    static class Vertex {
        int id;
        double x;
        double y;

        Vertex(int id, double x, double y) {
            this.id = id;
            this.x = x;
            this.y = y;
        }
    }

    static class Edge {
        int from;
        int to;
        double weight;

        Edge(int from, int to, double weight) {
            this.from = from;
            this.to = to;
            this.weight = weight;
        }
    }
}

