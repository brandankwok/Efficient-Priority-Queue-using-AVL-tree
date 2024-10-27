# Priority Queue with AVL Tree Integration

Created for CMPT 225: Data Structures and Programming Assignment 3 at SFU, this project implements a custom priority queue (PQ) with integrated AVL tree indexing, providing efficient operations for managing tasks based on their priorities. The codebase is designed to demonstrate a blend of priority queue operations (via heap structures) and searchable index support (using AVL trees) to ensure both quick access to minimum elements and rapid updates by task ID. Ideal for systems where tasks must be dynamically managed, inserted, updated, and removed by both priority and ID, this project showcases data structure integration techniques and C++ programming proficiency.

## Features

- **Min-Heap Implementation**: Manages tasks by priority, where the minimum-priority task can be found or removed in constant time.
- **AVL Tree Indexing**: Maintains tasks in an AVL tree for logarithmic time complexity when inserting and updating priorities.
- **Dynamic Priority Updates**: Allows updating the priority of any task efficiently; if the task is not present, it is inserted with the given priority.
- **Heapifying and Emptiness Checking**: Offers functionality for building a heap from a list of IDs and priorities and checking if the queue is empty.

  ### Public Methods:
  - `bool isEmpty()`: Return true if PQ is empty; else false
  - `ID deleteMin()`: Remove and return a task ID with smallest priority
  - `ID findMin()`: Return a task ID with smallest priority, without removing it
  - `void insert( x, p )`: Insert task ID x with priority p
  - `void updatePriority( x, p )`: Changes priority of ID x to p (if x not in PQ, inserts x);
  - `int size()`: return the number of task IDs in the queue
  - `void makeEmpty()`: Remove all task IDs from the queue
  - `display()`: Prints the priority queue structure, showing each node’s priority, corresponding AVL tree index, and ID, followed by an in-order traversal of the AVL tree.
  ### Private Methods:
  - `swap(int *r, int *s)`: Swaps the values of two integer pointers, r and s, used for reordering priorities within the heap.
  - `swapP(typename AvlTree<ID>::AvlNode*& x, typename AvlTree<ID>::AvlNode*& y)`: Swaps two AVL tree node pointers, x and y, to update references during heap reordering.
  - `buildHeap()`: Constructs the min-heap from the current list of nodes by adjusting elements starting from non-leaf nodes down to the root.
  - `percolateDown(int index)`: Moves a node down the heap to restore the min-heap property if the node at `index` is larger than its children.
  - `percolateUp(int i)`: Moves a node up the heap to maintain the min-heap property if the node at `i` is smaller than its parent.

## Compilation and Execution

1. **Compile**:
   ```bash
   make all
2. **Run**:
   ```bash
   ./PQdemo
