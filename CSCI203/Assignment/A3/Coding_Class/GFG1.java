package Coding_Class;

public class GFG1 {
    private int[] dist;
    private boolean[] settled;
    private int V;
    Node[][] adj; // Adjacency list
    CustomPriorityQueue pq;

    public GFG1(int V) {
        this.V = V;
        dist = new int[V];
        settled = new boolean[V];
        pq = new CustomPriorityQueue(V);
    }

    public void dijkstra(Node[][] adj, int src) {
        this.adj = adj;

        for (int i = 0; i < V; i++) {
            dist[i] = Integer.MAX_VALUE;
        }

        pq.add(new Node(src, 0));
        dist[src] = 0;

        while (pq.size() > 0) {
            int u = pq.poll().node;

            if (settled[u])
                continue;

            settled[u] = true;
            e_Neighbours(u);
        }
    }

    private void e_Neighbours(int u) {
        for (Node v : adj[u]) {
            if (v == null) break; // End of neighbors

            if (!settled[v.node]) {
                int edgeDistance = v.cost;
                int newDistance = dist[u] + edgeDistance;

                if (newDistance < dist[v.node])
                    dist[v.node] = newDistance;

                pq.add(new Node(v.node, dist[v.node]));
            }
        }
    }

    public static void main(String arg[]) {
        int V = 7;
        Node[][] adj = new Node[V][];
    
        adj[0] = new Node[] { new Node(1, 9), new Node(2, 6), new Node(3, 5), new Node(4, 3), null };
        adj[1] = new Node[] { new Node(4, 7), new Node(5, 4), null };
        adj[2] = new Node[] { new Node(1, 2), new Node(3, 4), null };
        adj[3] = new Node[] { new Node(4, 2), null };
        adj[4] = new Node[] { null };  // Node 4 has no outgoing edges based on the given structure.
        adj[5] = new Node[] { new Node(6, 2), null };
        adj[6] = new Node[] { new Node(3, 5), new Node(0, 8), null };

    
        System.out.println("Shortest Path Table:");
        System.out.println("--------------------");
        
        for (int source = 0; source < V; source++) {
            GFG1 dpq = new GFG1(V);
            dpq.dijkstra(adj, source);
    
            System.out.println("| Source | Destination | Distance |");
            System.out.println("|--------|-------------|----------|");
            for (int i = 0; i < dpq.dist.length; i++) {
                System.out.printf("| %6d | %11d | %8d |\n", source, i, dpq.dist[i]);
            }
            System.out.println("--------------------");
        }
    }
    
}

class Node {
    public int node;
    public int cost;

    public Node(int node, int cost) {
        this.node = node;
        this.cost = cost;
    }
}

class CustomPriorityQueue {
    private Node[] array;
    private int size = 0;

    public CustomPriorityQueue(int capacity) {
        array = new Node[capacity];
    }

    public void add(Node node) {
        if (size == array.length) {
            // Handle the case where the array is full
            // For simplicity, we double the array size.
            // You could also just print an error and return or handle this case differently.
            resize();
        }
        array[size++] = node;
        int current = size - 1;
    
        while (current > 0 && array[current].cost < array[(current - 1) / 2].cost) {
            Node temp = array[current];
            array[current] = array[(current - 1) / 2];
            array[(current - 1) / 2] = temp;
            current = (current - 1) / 2;
        }
    }
    
    private void resize() {
        Node[] newArray = new Node[array.length * 2];
        for (int i = 0; i < array.length; i++) {
            newArray[i] = array[i];
        }
        array = newArray;
    }
    

    public Node poll() {
        if (size == 0) {
            throw new IllegalStateException("PriorityQueue is empty. Cannot poll.");
        }
        
        Node popped = array[0];
        array[0] = array[--size];
        heapify(0);
        return popped;
    }

    private void heapify(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < size && array[left].cost < array[smallest].cost) {
            smallest = left;
        }

        if (right < size && array[right].cost < array[smallest].cost) {
            smallest = right;
        }

        if (smallest != i) {
            Node swap = array[i];
            array[i] = array[smallest];
            array[smallest] = swap;
            heapify(smallest);
        }
    }

    public int size() {
        return size;
    }
}
