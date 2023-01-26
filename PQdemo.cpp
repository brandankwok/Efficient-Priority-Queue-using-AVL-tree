#include "dsexceptions.h"
#include <algorithm>
#include <iostream> 
#include <vector>
#include "PQ.h"
#include "AvlTree.h"
using namespace std;

void testHeapify() {
    cout << "------------------ START TEST MAKE-HEAP ------------------ " << endl << endl;

    cout << "Initializing priorities 10-1 and arbitrary IDs..." << endl << endl;
    cout << "PQ before make-heap should look like: [10,9,8,7,6,5,4,3,2,1]" << endl;
    cout << endl << "Making heap..." << endl;

    vector<int> priorities;
    for (int i = 10; i > 0; i--) {
        priorities.push_back(i);
    }
    
    vector<int> ids;
    for (int j = 10; j > 0; j--) {
        ids.push_back(j*111);
    }
    
    PQ<int> q(ids, priorities);

    q.display();
    cout << endl << "------------------ END TEST MAKE-HEAP ------------------ " << endl << endl;
}

void testEmpty() {
    cout << "------------------ START TEST MAKE-EMPTY ------------------ " << endl << endl;
    cout << "Initializing priorities 1000-1 and arbitrary IDs and making the heap..." << endl << endl;
   
    vector<int> priorities;
    for (int i = 1000; i > 0; i--) {
        priorities.push_back(i);
    }
    vector<int> ids;
    for (int j = 1000; j > 0; j--) {
        ids.push_back(j*111);
    }
    PQ<int> q(ids, priorities);
    cout << "Emptying the PQ and AVL tree..." << endl;
    q.makeEmpty();

    q.display();
    cout << endl << "------------------ END TEST MAKE-EMPTY ------------------ " << endl << endl;
}

void testInsert() {

    cout << "------------------ START TEST INSERT ------------------ " << endl << endl;
    cout << "Inserting values from 20-1..." << endl;

    PQ<int> q;
    for (int i = 20; i > 0; i--) {
        q.insert(i*111, i);
    }

    q.display();

    cout << endl << "------------------ END TEST INSERT ------------------ " << endl << endl;
}

void testFindmin() {
    cout << "------------------ START TEST FIND MIN ------------------ " << endl << endl;

    cout << "Inserting values from 30-1..." << endl;
    PQ<int> q;
    for (int i = 30; i > 0; i--) {
        q.insert(i*111, i);
    }
    q.display();
    cout << endl << "Finding the ID with minimum priority..." << endl << endl;
    cout << "ID found: " << q.findMin() << endl;

    cout << endl << "------------------ END TEST FIND MIN ------------------ " << endl << endl;
}

void testUpdatePriority() {
    cout << "------------------ START TEST UPDATE PRIORITY ------------------ " << endl << endl;
    cout << "Initializing priorities 10-1 and arbitrary IDs..." << endl << endl;

    vector<int> priorities;
    for (int i = 10; i > 0; i--) {
        priorities.push_back(i);
    }
    vector<int> ids;
    for (int j = 10; j > 0; j--) {
        ids.push_back(j*111);
    }
    PQ<int> q(ids, priorities);
    q.display();

    cout << endl << "Updating ID 666 with priority 11..." << endl << endl;
    q.updatePriority(666, 11);
    q.display();
    cout << endl << "Updating ID 666 with priority 6..." << endl << endl;
    q.updatePriority(666, 6);
    q.display();
    cout << endl << "Updating ID 132 with priority 12..." << endl;
    cout << "ID 132 not in AVL tree. Inserting..." << endl << endl;
    q.updatePriority(132, 12);
    q.display();

    cout << endl << "------------------ END TEST UPDATE PRIORITY ------------------ " << endl << endl;
}

void testDeleteMin() {
    cout << "------------------ START TEST DELETE MIN ------------------ " << endl << endl;
    cout << "Inserting values from 10-1..." << endl;

    vector<int> priorities;
    for (int i = 10; i > 0; i--) {
        priorities.push_back(i);
    }
    
    vector<int> ids;
    for (int j = 10; j > 0; j--) {
        ids.push_back(j*111);
    }
    
    PQ<int> q(ids, priorities);
    q.display();
    cout << endl << "ID to be deleted is " << q.findMin() << endl;
    cout << "Deleting min..." << endl;
    q.deleteMin();
    q.display();

    cout << endl << "------------------ END TEST DELETE MIN ------------------ " << endl << endl;
}

void testEverything() {
    cout << "------------------ START TEST EVERYTHING ------------------ " << endl << endl;
    cout << "Initializing priorities 10-1 and arbitrary IDs..." << endl << endl;

    vector<int> priorities;
    for (int i = 10; i > 0; i--) {
        priorities.push_back(i);
    }
    vector<int> ids;
    for (int j = 10; j > 0; j--) {
        ids.push_back(j*111);
    }
    PQ<int> q(ids, priorities);
    q.display();

    cout << endl << "Inserting priorities 20-11 and arbitrary IDs..." << endl << endl;
    
    for (int k = 20; k > 10; k--) {
        q.insert(k*111, k);
    }
    q.display();

    cout << endl << "Updating ID 333 with priority 21..." << endl << endl;
    q.updatePriority(333, 21);
    q.display();

    cout << endl << "Finding the ID with minimum priority..." << endl;
    cout << "ID found: " << q.findMin() << endl;
    cout << "Deleting min..." << endl << endl;
    q.deleteMin();
    q.display();

    cout << endl << "Emptying the PQ and AVL tree..." << endl;
    q.makeEmpty();
    q.display();
    cout << endl << "------------------ END TEST EVERYTHING ------------------ " << endl << endl;
}

int main () {
    
    testHeapify();
    testEmpty();
    testInsert();
    testFindmin();
    testUpdatePriority();
    testDeleteMin();
    testEverything();

    return 0;
}