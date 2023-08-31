# ---------------------- imports

import sys

import numpy as np


# ---------------------- stack

class Heap:

    heap_size = 100
    size = 0

    def __init__(self):
        self.heap = np.zeros(self.heap_size, np.int32)
        return

    def add(self, item):
        self.heap[self.size] = item
        self.size += 1
        return

    def get(self, index):
        return self.heap[index]

    def siftdown(self, current):

        child = 2 * current + 1

        if child >= self.size:
            return

        if (child + 1 < self.size) and (self.heap[child] < self.heap[child + 1]):
            child += 1

        if self.heap[current] < self.heap[child]:

            temp = self.heap[current]
            self.heap[current] = self.heap[child]
            self.heap[child] = temp

            self.siftdown(child)

        return

    def makeheap(self):

        print("In makeHeap", self.size)

        for i in range(self.size // 2, -1, -1):
            print("siftdown", i, self.heap[i])
            self.siftdown(i)

        return

# ---------------------- main


def main():
    h = Heap()

    print("Please enter the name of the input file:", file=sys.stderr)
    filename = sys.stdin.readline()
    filename = filename.rstrip("\n")

    try:
        f = open(filename, "r")
    except OSError:
        print("Error opening file ", filename, ". Program will exit.", sep="")
        return

    for line in f:
        h.add(int(line.rstrip("\n")))

    h.makeheap()

    for i in range(10):
        print(h.get(i), end=" ")
    print()

    return 0


# ---------------------- execute main

if __name__ == '__main__':
    sys.exit(main())
