#include <iostream>
#include <fstream>
using namespace std;

void makeHeap();
void siftDown(int);


const int HEAP_SIZE = 100;
int heap [HEAP_SIZE];
int size = 0;

int main() {

    char filename [20];
    ifstream fin;

    cerr << "Please enter the name of the input file: ";
    cin >> filename;
    fin.open (filename);

    if (!fin ) {
        cerr << "Error opening file " << filename << ". Program will exit." << endl;
        return 0;
    }

    while (fin >> heap[size++]);

    makeHeap();

    for (int i = 0; i < 10; i++)
        cout << heap[i] << " ";
    cout << endl;

    fin.close ( );

    return 0;
}

void makeHeap( )
{
    int i;

    cerr << "In makeHeap " << size << endl;

    for (i = size/2; i >= 0; i--) {
        cerr << "siftDown " << i << " " << heap[i] << endl;
        siftDown(i);
    }

    return;
}

void siftDown(int current)
{
    int child = 2 * current + 1;

    if (child >= size)
        return;

    if ((child + 1 < size) && (heap[child] < heap[child + 1]))
        child++;

    if (heap[current] < heap[child]) {

        int temp = heap[current];
        heap[current] = heap[child];
        heap[child] = temp;

        siftDown(child);
    }

    return;
}
