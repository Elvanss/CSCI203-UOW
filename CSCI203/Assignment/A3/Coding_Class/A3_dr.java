package Coding_Class;
public class A3_dr {
    
}

// Initialize the node of graph
class Vertex {
    int node;
    int cost;

    public Vertex (int node, int cost) {
        this.node = node;
        this.cost = cost;
    }
}

// Implement the basic priority queue
class PriorityQueue {
   private Vertex[] vertex;
   private int size = 0;
   
   public PriorityQueue(int capacity) {
        vertex = new Vertex[capacity];
   }

   public void enqueue(Vertex node) {
        vertex[size++] = node;
        int current = size - 1;

        while (current > 0 && vertex[current].cost < vertex[(current - 1) / 2].cost) {
            Vertex temp = vertex[current];
            vertex[current] = vertex[(current - 1) / 2];
            vertex[(current - 1) / 2] = temp;
            current = (current - 1) / 2;
    }
   }

   public Vertex dequeue() {
    if (size == 0) {
        throw new IllegalStateException("The queue is empty");
    }

    Vertex index = vertex[0];
    vertex[0] = vertex[--size];
    heapify(0);
    return index;
}

   private void heapify(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < size && vertex[left].cost < vertex[smallest].cost) {
            smallest = left;
        }

        if (right < size && vertex[right].cost < vertex[smallest].cost) {
            smallest = right;
        }

        if (smallest != i) {
            swap(i, smallest);
            heapify(smallest);
        }
    }

    private void swap(int i, int j) {
        Vertex temp = vertex[i];
        vertex[i] = vertex[j];
        vertex[j] = temp;
    }
}

