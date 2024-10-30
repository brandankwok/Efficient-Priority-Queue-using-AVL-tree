#ifndef PQ_H
#define PQ_H

#include "dsexceptions.h"
#include "AvlTree.h"
#include <cmath>
#include <algorithm>
#include <iostream> 
#include <vector>
using namespace std;
// PQ class
//
// Template parameter: ID
// Constructors:
// PQ --> constructs a new empty queue
// PQ( tasks, array ) --> constructs a new queue with a given set of task IDs and array 
// ******************PUBLIC OPERATIONS*********************
// void insert( x, p )       --> Insert task ID x with priority p 
// ID findMin( )  --> Return a task ID with smallest priority, without removing it 
// ID deleteMin( )   --> Remove and return a task ID with smallest priority 
// void updatePriority( x, p )   --> Changes priority of ID x to p (if x not in PQ, inserts x);
// bool isEmpty( )   --> Return true if empty; else false
// int size() --> return the number of task IDs in the queue 
// void makeEmpty( )  --> Remove all task IDs (and their array)
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename ID>
// ID is the type of task IDs to be used; the type must be Comparable (i.e., have < defined), so IDs can be AVL Tree keys.
class PQ {

  public:
    
    // Constructor
    // Initializes a new empty PQ
    PQ() {}
    // Constructor
    // Initializes a new PQ with a given set of tasks IDs and array  
    //      priority[i] is the priority for ID task[i] 
    PQ( const vector<ID> & tasks, const vector<int> & array ) { 
      int length = array.size();

      for (int i = 0; i < length; i++) {
        nodes.push_back(PQnode());
        nodes[i].priority = array[i];
        void* ptr = tree.insert(tasks[i], i);
        typename AvlTree<ID>::AvlNode* z = (typename AvlTree<ID>::AvlNode*) ptr;
        nodes[i].pointer = z;
      }
      buildHeap();
    } 

    ~PQ() {
      makeEmpty();
    }
						     
    // Emptiness check 
    bool isEmpty() const { return size() == 0;}

    // Deletes and Returns a task ID with minimum priority
    //    Throws exception if queue is empty
    const ID & deleteMin() {

       if( isEmpty( ) )
          throw UnderflowException{ };

      int length = size();
      ID min_id = nodes[0].pointer->id_num;
      swap(&nodes[0].priority, &nodes[length-1].priority);
      swap(&nodes[0].pointer->index, &nodes[length-1].pointer->index);
      swapP(nodes[0].pointer, nodes[length-1].pointer);
      tree.remove(nodes[length-1].pointer->id_num);
      nodes.pop_back();
      
      percolateDown(0);

      return min_id;
    }

    // Returns an ID with minimum priority without removing it
    //     Throws exception if queue is empty
    const ID & findMin() const {

      if( isEmpty( ) )
          throw UnderflowException{ };

      return nodes[0].pointer->id_num;
    }

    // Insert ID x with priority p.
    void insert( const ID & x, int p ) {
      
      nodes.push_back(PQnode());
      int length = nodes.size();
      int index = length-1;
      nodes[index].priority = p;

      void* ptr = tree.insert(x, index);
      typename AvlTree<ID>::AvlNode* z = (typename AvlTree<ID>::AvlNode*) ptr;
      nodes[index].pointer = z;

      percolateUp(index);
    }

    // Update the priority of ID x to p
    //    Inserts x with p if not in the queue

    // search AVL tree for ID x and update heap with priority p in O(logn) time
    void updatePriority( const ID & x, int p ) {
        if (tree.contains(x) == false) {
          insert(x, p);
        }
        else {
          int index = tree.findIndex(x);
          if (nodes[index].priority < p) {
            nodes[index].priority = p;
            percolateDown(index);
          }
          else {
            nodes[index].priority = p;
            percolateUp(index);
          }
        }
    }

    // Return the number of task IDs in the queue
    int size() const {
      return nodes.size();
    }

    // Delete all IDs from the PQ
    void makeEmpty() {
      int length = nodes.size();
      
      for (int i = 0; i < length; i++) {
        nodes.pop_back();
      }
      tree.makeEmpty();
    }

    void display() 
    {
      int length = nodes.size();
      cout << "PQ output mapping to AVL output:" << endl << endl;
      if (length == 0) {
        cout << "Empty PQ" << endl;
      }
      else if (length > 0) {
        for( int i = 0; i < length; i++){
          cout << "PQ Index: " << i << "  Priority: " << nodes[i].priority << " ------------>>>" << "  AVL Index: " << nodes[i].pointer->index <<  "  ID: " << nodes[i].pointer->id_num << endl;
        }
      }
      
      cout << endl << "Tree in-order output: " << endl << endl;
      tree.printTree();
    }

  private:

    struct PQnode {
      int priority;
      typename AvlTree<ID>::AvlNode* pointer;
    };

    AvlTree<ID> tree;
    vector<PQnode> nodes;

    void swap(int *r, int *s)
    {
      int temp = *r;
      *r = *s;
      *s = temp;
      return;
    }

    void swapP(typename AvlTree<ID>::AvlNode*& x, typename AvlTree<ID>::AvlNode*& y) {
      typename AvlTree<ID>::AvlNode* temp = x;
      x = y;
      y = temp;
    }

    void buildHeap() {
      int length = nodes.size();
      for(int i = floor(length / 2 - 1); i >= 0; i--) {
        percolateDown( i );
      }
    }

    void percolateDown(int index) {
      int length = nodes.size();
      int i = index, left, right, smallest;

      while (2 * i + 1 < length) {
	left = 2 * i + 1;
	right = 2 * i + 2;
	smallest = i;

	if (left < length && nodes[left].priority < nodes[smallest].priority) {
	  smallest = left;
	}
	if (right < length && nodes[right].priority < nodes[smallest].priority) {
	  smallest = right;
	}

	if (smallest != i) {
	  swap(&nodes[smallest].priority, &nodes[i].priority);
	  swap(&nodes[smallest].pointer->index, &nodes[i].pointer->index);
	  swapP(nodes[smallest].pointer, nodes[i].pointer);
	  i = smallest;
	} 
	else {
	  break;
	}
      }    
    }

    void percolateUp(int i) {

      int index = i;
     
      int parent = floor((i-1)/2);

      while (index > 0 && nodes[index].priority < nodes[parent].priority) {
          swap(&nodes[index].priority, &nodes[parent].priority);
          swap(&nodes[index].pointer->index, &nodes[parent].pointer->index);
          swapP(nodes[index].pointer, nodes[parent].pointer);
          index = floor((index-1)/2);
          parent = floor((index-1)/2);
      }
    }

};
#endif
