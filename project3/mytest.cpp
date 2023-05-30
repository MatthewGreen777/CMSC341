// UMBC - CMSC 341 - Spring 2023 - Proj2
/********************************************************
** File: mytest.cpp
** Project: CMSC 341 Project 1
** Author: Matthew Green
** Date: 28/03/2023
** Email: mgreen11@umbc.edu
**
** Description: Does the tests
**********************************************************/
#include "cqueue.h"
#include <random>

int priorityFn1(const Order &order);// works with a MAXHEAP
int priorityFn2(const Order &order);// works with a MINHEAP

enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
class Random {
public:
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor 
            m_normdist = std::normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min,max);
        }
        else{ //the case of UNIFORMREAL to generate real numbers
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
        }
    }
    void setSeed(int seedNum){
        // we have set a default value for seed in constructor
        // we can change the seed by calling this function1 after constructor call
        // this gives us more randomness
        m_generator = std::mt19937(seedNum);
    }

    int getRandNum(){
        // this function1 returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function1 returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function1 returns 15.03
        // to round up we can use ceil function1 instead of floor
        result = std::floor(result*100.0)/100.0;
        return result;
    }
    
    private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//integer uniform distribution
    std::uniform_real_distribution<double> m_uniReal;//real uniform distribution
};

class Tester {
    public:
    bool testNormalInsertMinHeapLeftist(CQueue &queue); // done
    bool testNormalInsertMinHeapSkew(CQueue &queue, Order order);// done
    bool testNormalInsertMaxHeapLeftist(CQueue &queue); // done
    bool testNormalInsertMaxHeapSkew(CQueue &queue, Order order);
    bool testRemovalMinHeapLeftist(CQueue &queue); // done
    bool testRemovalMinHeapSkew(CQueue &queue); // done
    bool testRemovalMaxHeapLeftist(CQueue &queue); // done
    bool testRemovalMaxHeapSkew(CQueue &queue); // done
    bool testLeftistNPLValue(CQueue &queue); // done
    bool testLeftistProperty(CQueue &queue); // done
    bool testChangePriorityFunction(CQueue &queue, prifn_t function); // done
    bool testChangeHeap(CQueue &queue, HEAPTYPE heap); // done
    bool testChangePriorityandHeap(CQueue &queue, prifn_t function, HEAPTYPE heap); //done
    bool testChangeStucture(CQueue &queue, STRUCTURE structure); // done
    bool testMerge(CQueue &queue, CQueue &queue2); // done
    bool testMergeEmptyQueue(CQueue &queue, CQueue &queue2); // done
    bool testCopyConstructorNormal(CQueue &cqueue); // done
    bool testCopyConstructorEdge(CQueue &queue); // done
    bool testAssignmentOperatorNormal(CQueue &queue, CQueue &queue2); // done
    bool testAssignmentOperatorEdge(CQueue &queue, CQueue &queue2); // done
    bool testOutOfRangeException(CQueue &queue); // done
    bool testDomainErrorExceptionFunction(CQueue &queue, CQueue &queue2); // done
    bool testDomainErrorExceptionStructure(CQueue &queue, CQueue &queue2); // done
    
    bool checkMinHeapNPL(CQueue &queue, Node *node, bool n); // done
    bool checkMaxHeapNPL(CQueue &queue, Node *node, bool n); // done
    bool checkDeepCopy(Node *node, Node *node2); // done
    bool checkMinNode(CQueue &queue, Node *node); // done
    bool checkMaxNode(CQueue &queue, Node *node); // done
    void buildQueue(CQueue &CQueue);
};

int main() {
    Tester test;
    prifn_t function1 = priorityFn1;
    prifn_t function2 = priorityFn2;
    HEAPTYPE min = MINHEAP;
    HEAPTYPE max = MAXHEAP;
    STRUCTURE leftist = LEFTIST;
    STRUCTURE skew = SKEW;    
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    {
        CQueue queue(function1, min, leftist);
        cout << "\nTest Case: Min-Heap Insertion in Leftist" << endl;
        if (test.testNormalInsertMinHeapLeftist(queue)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }    
    {
        CQueue queue(function1, min, skew);
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()), static_cast<COUNT>(countGen.getRandNum()), static_cast<MEMBERSHIP>(membershipGen.getRandNum()), pointsGen.getRandNum(), customerIdGen.getRandNum(), orderIdGen.getRandNum());
        cout << "\nTest Case: Min-Heap Insertion in Skew" << endl;
        if (test.testNormalInsertMinHeapSkew(queue, anOrder)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        CQueue queue(function1, max, leftist);
        cout << "\nTest Case: Max-Heap Insertion in Leftist" << endl;
        if (test.testNormalInsertMaxHeapLeftist(queue)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }    
    {
        CQueue queue(function1, max, skew);
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()), static_cast<COUNT>(countGen.getRandNum()), static_cast<MEMBERSHIP>(membershipGen.getRandNum()), pointsGen.getRandNum(), customerIdGen.getRandNum(), orderIdGen.getRandNum());
        cout << "\nTest Case: Max-Heap Insertion in Skew" << endl;
        if (test.testNormalInsertMaxHeapSkew(queue, anOrder)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        CQueue queue(function1, min, leftist);
        cout << "\nTest Case: Min-Heap Removal in Leftist" << endl;
        if (test.testRemovalMinHeapLeftist(queue)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        CQueue queue(function1, min, skew);
        cout << "\nTest Case: Min-Heap Removal in Slew" << endl;
        if (test.testRemovalMinHeapSkew(queue)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        CQueue queue(function1, max, leftist);
        cout << "\nTest Case: Max-Heap Removal in Leftist" << endl;
        if (test.testRemovalMaxHeapLeftist(queue)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        CQueue queue(function1, max, skew); 
        cout << "\nTest Case: Max-Heap Removal in Skew" << endl;
        if (test.testRemovalMaxHeapSkew(queue)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        CQueue queue(function1, min, leftist);
        cout << "\nTest Case: Left Value NPL" << endl;
        if (test.testLeftistNPLValue(queue)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        CQueue queue(function1, min, leftist);
        cout << "\nTest Case: Leftist Property Maintained" << endl;  
        if (test.testLeftistProperty(queue)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        } 
    }
    {
        CQueue queue(function1, min, leftist);
        cout << "\nTest Case: Change Priority Function" << endl;
        if (test.testChangePriorityFunction(queue, function2)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        CQueue queue(function1, min, leftist);
        cout << "\nTest Case: Change Heaptype" << endl;
        if (test.testChangeHeap(queue, max)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        CQueue queue(function1, min, leftist);
        cout << "\nTest Case: Change Priority Function and Heaptype" << endl;
        if (test.testChangePriorityandHeap(queue, function2, max)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }    
    {
        CQueue queue(function1, min, skew);
        cout << "\nTest Case: Change Structure" << endl;
        if (test.testChangeStucture(queue, leftist)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }    
    {
        CQueue queue(function1, min, leftist);
        CQueue queue2(function1, min, leftist);
        cout << "\nTest Case: Merge Queues" << endl;
        if (test.testMerge(queue, queue2)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        CQueue queue(function1, min, leftist);
        CQueue queue2(function1, min, leftist);
        cout << "\nTest Case: Merge Empty Queues" << endl;
        if (test.testMergeEmptyQueue(queue, queue2)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        CQueue queue(function1, min, leftist);
        cout << "\nTest Case: Copy Constructor Normal" << endl;
        if (test.testCopyConstructorNormal(queue)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        } 
    }
    {
        CQueue queue(function1, min, leftist);
        cout << "\nTest Case: Copy Constructor Edge" << endl;
        if (test.testCopyConstructorEdge(queue)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        } 
    }
    {
        CQueue queue(function1, min, leftist);
        CQueue queue2(function1, min, leftist);
        cout << "\nTest Case: Assignment Operator Normal" << endl;
        if (test.testAssignmentOperatorNormal(queue, queue2)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        CQueue queue(function1, min, leftist);
        CQueue queue2(function1, min, leftist);
        cout << "\nTest Case: Assignment Operator Edge" << endl;
        if (test.testAssignmentOperatorEdge(queue, queue2)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        CQueue queue(function1, min, leftist);
        cout << "\nTest Case: Out of Range Exception" << endl;
        if (test.testOutOfRangeException(queue)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        } 
    }
    {
        CQueue queue(function1, min, leftist);
        CQueue queue2(function1, max, leftist);
        cout << "\nTest Case: Domain Error Exception Due to Heaptype" << endl;
        if (test.testDomainErrorExceptionFunction(queue, queue2)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        } 
    }
    {
        CQueue queue(function1, min, leftist);
        CQueue queue2(function1, min, skew);
        cout << "\nTest Case: Domain Error Exception Due to Strucutre" << endl;
        if (test.testDomainErrorExceptionStructure(queue, queue2)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }  
    }
    return 0;
}











bool Tester::testNormalInsertMinHeapLeftist(CQueue &queue) { // done
    bool run = true;
    try {
        buildQueue(queue); // insert nodes through helper
        Node* node = queue.m_heap;
        run = run && checkMinHeapNPL(queue, node, run); // check npl
        run = run && checkMinNode(queue, queue.m_heap);

    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testNormalInsertMinHeapSkew(CQueue &queue, Order order) { // done
    bool run = true;
    try {
        buildQueue(queue); // insert nodes through helper
        Node* node = queue.m_heap;
        Node* node2 = queue.m_heap->m_left;
        Node* node3 = queue.m_heap->m_right;
        int total = queue.m_size;
        run = run && (checkMinNode(queue, queue.m_heap));
        queue.insertOrder(order);
        if (node != queue.m_heap) {
            run = run && (queue.m_size == (total +1));
            run = run && checkMinNode(queue, queue.m_heap);
        } else {
            run = run && (queue.m_size == (total + 1));
            run = run && checkMinNode(queue, queue.m_heap);
            run = run && checkMinNode(queue, queue.m_heap);
            run = run && (node2 == queue.m_heap->m_right);
            run = run && (node3 == queue.m_heap->m_left);
        }
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testNormalInsertMaxHeapLeftist(CQueue &queue) { // done
    bool run = true;
    try {
        buildQueue(queue); // insert nodes through helper
        Node* node = queue.m_heap;
        run = run && checkMaxHeapNPL(queue, node, run);
        run = run && checkMaxNode(queue, queue.m_heap);
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testNormalInsertMaxHeapSkew(CQueue &queue, Order order) { // done
    bool run = true;
    try {
        buildQueue(queue); // insert nodes through helper
        Node* node = queue.m_heap;
        Node* node2 = queue.m_heap->m_left;
        Node* node3 = queue.m_heap->m_right;
        int total = queue.m_size;
        run = run && (checkMaxNode(queue, queue.m_heap));
        queue.insertOrder(order);
        if (node != queue.m_heap) {
            run = run && (queue.m_size == (total +1));
            run = run && checkMaxNode(queue, queue.m_heap);
        } else {
            run = run && (queue.m_size == (total + 1));
            run = run && checkMaxNode(queue, queue.m_heap);
            run = run && (node2 == queue.m_heap->m_right);
            run = run && (node3 == queue.m_heap->m_left);
        }
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testRemovalMinHeapLeftist(CQueue &queue) { // done
    bool run = true;
    try {
        buildQueue(queue); // insert nodes through helper
        Node *temp = queue.m_heap;
        int size = queue.m_size;
        run = run && (queue.m_size == size);
        run = run && (temp == queue.m_heap);
        queue.getNextOrder();
        run = run && !(temp == queue.m_heap);
        run = run && (checkMinHeapNPL(queue, queue.m_heap, run)); // check npl
        run = run && (checkMinNode(queue, queue.m_heap));
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testRemovalMinHeapSkew(CQueue &queue) { // done
    bool run = true;
    try {
        buildQueue(queue); // insert nodes through helper
        Node *temp = queue.m_heap;
        int size = queue.m_size;
        run = run && (queue.m_size == size);
        run = run && (temp == queue.m_heap);
        run = run && (checkMinNode(queue, queue.m_heap));
        queue.getNextOrder();
        run = run && !(temp == queue.m_heap);
        run = run && (queue.m_size == (size - 1));
        run = run && (checkMinNode(queue, queue.m_heap));
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testRemovalMaxHeapLeftist(CQueue &queue) { // done
    bool run = true;
    try {
        buildQueue(queue); // insert nodes through helper
        Node *temp = queue.m_heap;
        int size = queue.m_size;
        run = run && (queue.m_size == size);
        run = run && (temp == queue.m_heap);
        queue.getNextOrder();
        run = run && !(temp == queue.m_heap);
        run = run && (checkMaxHeapNPL(queue, queue.m_heap, run));
        run = run && (checkMaxNode(queue, queue.m_heap));
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testRemovalMaxHeapSkew(CQueue &queue) { // done
    bool run = true;
    try {
        buildQueue(queue); // insert nodes through helper
        Node *temp = queue.m_heap;
        int size = queue.m_size;
        run = run && (queue.m_size == size);
        run = run && (temp == queue.m_heap);
        queue.getNextOrder();
        run = run && !(temp == queue.m_heap);
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testLeftistNPLValue(CQueue &queue) { // done
    bool run = true;
    try {
        buildQueue(queue); // insert nodes through helper
        Node *temp = queue.m_heap;
        run = run && checkMinHeapNPL(queue, temp, run); // check npl
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testLeftistProperty(CQueue &queue) { // done
    bool run = true;
    try {
        buildQueue(queue); // insert nodes through helper
        run = run && (checkMinHeapNPL(queue, queue.m_heap, run)); // check npl
        run = run && (checkMinNode(queue, queue.m_heap));
        queue.setPriorityFn(queue.m_priorFunc, MAXHEAP);  // change heap
        run = run && (checkMaxHeapNPL(queue, queue.m_heap, run));
        run = run && (checkMaxNode(queue, queue.m_heap));
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testChangePriorityFunction(CQueue &queue, prifn_t function) { // done
    bool run = true;
    try {
        buildQueue(queue); // insert nodes through helper
        int num = queue.m_size;
        run = run && (checkMinHeapNPL(queue, queue.m_heap, run)); // check npl
        run = run && (checkMinNode(queue, queue.m_heap));
        queue.setPriorityFn(function, queue.m_heapType); // change priority
        run = run && (num == queue.m_size); // compares size
        run = run && (checkMinHeapNPL(queue, queue.m_heap, run)); // check npl
        run = run && (checkMinNode(queue, queue.m_heap));
        queue.setPriorityFn(function, MAXHEAP); // change heap
        run = run && (checkMaxHeapNPL(queue, queue.m_heap, run));
        run = run && (checkMaxNode(queue, queue.m_heap));
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testChangeHeap(CQueue &queue, HEAPTYPE heap) { // done
    bool run = true;
    try {
        buildQueue(queue); // insert nodes through helper
        int num = queue.m_size;
        run = run && (queue.m_heapType != heap);
        run = run && (checkMinHeapNPL(queue, queue.m_heap, run)); // check npl
        run = run && (checkMinNode(queue, queue.m_heap));
        queue.setPriorityFn(queue.m_priorFunc, heap); // change priority
        run = run && (num == queue.m_size); // compares size
        run = run && (queue.m_heapType == heap);
        run = run && (checkMaxHeapNPL(queue, queue.m_heap, run));
        run = run && (checkMaxNode(queue, queue.m_heap));
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testChangePriorityandHeap(CQueue &queue, prifn_t function, HEAPTYPE heap) { // done
    bool run = true;
    try {
        buildQueue(queue); // insert nodes through helper
        int num = queue.m_size;
        run = run && (queue.m_priorFunc != function) && (queue.m_heapType != heap);
        run = run && (checkMinHeapNPL(queue, queue.m_heap, run)); // check npl
        run = run && (checkMinNode(queue, queue.m_heap));
        queue.setPriorityFn(function, heap); // change priority
        run = run && (num == queue.m_size); // compares size
        run = run && (queue.m_priorFunc == function) && (queue.m_heapType == heap);
        run = run && (checkMaxHeapNPL(queue, queue.m_heap, run));
        run = run && (checkMaxNode(queue, queue.m_heap));
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testChangeStucture(CQueue &queue, STRUCTURE structure) { // done
    bool run = true;
    try {
        buildQueue(queue); // insert nodes through helper
        int num = queue.m_size;
        run = run && (queue.m_structure != structure);
        queue.setStructure(structure); // tries to change structure
        run = run && (num == queue.m_size); // compares size
        run = run && (queue.m_structure == structure);
        run = run && (checkMinHeapNPL(queue, queue.m_heap, run)); // check npl
        run = run && (checkMinNode(queue, queue.m_heap));
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testMerge(CQueue &queue, CQueue &queue2) { // done
    bool run = true;
    try {
        buildQueue(queue); // insert nodes through helper
        buildQueue(queue2); // insert nodes through helper
        int total = queue.m_size + queue2.m_size;
        queue.mergeWithQueue(queue2); // tries to merge queues
        run = run && (total == queue.m_size);
        run = run && (checkMinHeapNPL(queue, queue.m_heap, run)); // check npl
        run = run && (checkMinNode(queue, queue.m_heap));
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testMergeEmptyQueue(CQueue &queue, CQueue &queue2) { //done
    bool run = true;
    try {
        queue.mergeWithQueue(queue2); // tries to merge queues
        run = run && (queue.m_heap == nullptr);
        run = run && (queue.m_size == 0);
        run = run && (checkMinHeapNPL(queue, queue.m_heap, run)); // check npl
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testCopyConstructorNormal(CQueue &queue) { //done
    bool run = true;
    try {
        buildQueue(queue); // insert nodes through helper
        CQueue queue2(queue);
        run = run && (queue2.m_size == queue.m_size);
        if ((queue2.m_size == queue.m_size) && (queue2.m_heap != nullptr) && (queue.m_heap != nullptr)) {
            run = run && checkDeepCopy(queue.m_heap, queue2.m_heap);  
        } else {
            run = false;
        }
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testCopyConstructorEdge(CQueue &queue) { //done
    bool run = true;
    try {
        CQueue queue2(queue);
        run = run && (queue2.m_size == queue.m_size);
        if ((queue2.m_size == queue.m_size) && (queue2.m_heap != nullptr) && (queue.m_heap != nullptr)) {
            run = run && checkDeepCopy(queue.m_heap, queue2.m_heap);  
        }      
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testAssignmentOperatorNormal(CQueue &queue, CQueue &queue2) { //done
    bool run = true;
    try {
        buildQueue(queue); // insert nodes through helper
        queue2 = queue;
        run = run && (queue2.m_size == queue.m_size);
        if ((queue2.m_size == queue.m_size) && (queue2.m_heap != nullptr) && (queue.m_heap != nullptr)) {
            run = run && checkDeepCopy(queue.m_heap, queue2.m_heap);  
        } else {
            run = false;
        }
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testAssignmentOperatorEdge(CQueue &queue, CQueue &queue2) { //done
    bool run = true;
    try {
        buildQueue(queue); // insert nodes through helper
        queue = queue2;
        if ((queue2.m_size == queue.m_size) && (queue2.m_heap == nullptr) && (queue.m_heap == nullptr)) {
            run = run && checkDeepCopy(queue.m_heap, queue2.m_heap);  
        } else {
            run = false;
        }
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testOutOfRangeException(CQueue &queue) { //done
    bool run = false;
    try {
        buildQueue(queue); // insert nodes through helper
        Order order(COFFEE, ONE, TIER5, -5, -5, -5);
        queue.insertOrder(order);
    } catch(out_of_range const&) {
        run = true;
    } catch (domain_error const&) {
        run = false;
    }
    return run;
}

bool Tester::testDomainErrorExceptionFunction(CQueue &queue, CQueue &queue2) { //done
    bool run = false;
    try {
        buildQueue(queue); // insert nodes through helper
        buildQueue(queue2); // insert nodes through helper
        queue.mergeWithQueue(queue2); // tries to merge queues
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = true;
    }
    return run;
}

bool Tester::testDomainErrorExceptionStructure(CQueue &queue, CQueue &queue2) { // done
    bool run = false;
    try {
        buildQueue(queue); // insert nodes through helper
        buildQueue(queue2); // insert nodes through helper
        queue.mergeWithQueue(queue2); // tries to merge queues
    } catch(out_of_range const&) {
        run = false;
    } catch (domain_error const&) {
        run = true;
    }
    return run;
}

bool Tester::checkMinHeapNPL(CQueue &queue, Node *node, bool n) { //done
    if (queue.m_structure != LEFTIST) { // does not run function if not leftist
        return true;
    }
    if (node == nullptr) { // end of route 
        return n;
    }
    checkMinHeapNPL(queue, node->m_left, n); // recurssion
    checkMinHeapNPL(queue, node->m_right, n); // recurssion

    if ((node->m_left != nullptr) && (node->m_right != nullptr)) { // three different scenarios
        if (node->m_left->m_npl < node->m_right->m_npl) { // checks npl
            n = false;
        }
        if (queue.getPriority(node) > queue.getPriority(node->m_left)) { // checks that priority is correct
            n = false;
        }
        if (queue.getPriority(node) > queue.getPriority(node->m_right)) { // checks that priority is correct
            n = false;
        }
    }
    if ((node->m_left == nullptr) && (node->m_right != nullptr)) {
        if (node->m_left->m_npl < node->m_right->m_npl) { // checks npl
            n = false;
        }
        if (queue.getPriority(node) > queue.getPriority(node->m_right)) { // checks that priority is correct
            n = false;
        }
    }
    if ((node->m_right == nullptr) && (node->m_left != nullptr)) {
        if (queue.getPriority(node) > queue.getPriority(node->m_left)) { // checks that priority is correct
            n = false;
        }
    }
    return n;
}

bool Tester::checkMaxHeapNPL(CQueue &queue, Node *node, bool n) { //done, exact same as above but for max instead of min
    if (queue.m_structure != LEFTIST) {
        return true;
    }
    if (node == nullptr) {
        return n;
    }
    checkMinHeapNPL(queue, node->m_left, n);
    checkMinHeapNPL(queue, node->m_right, n);

    if ((node->m_left != nullptr) && (node->m_right != nullptr)) {
        if (node->m_left->m_npl < node->m_right->m_npl) {
            n = false;
        }
        if (queue.getPriority(node) < queue.getPriority(node->m_left)) {
            n = false;
        }
        if (queue.getPriority(node) < queue.getPriority(node->m_right)) {
            n = false;
        }
    }
    if ((node->m_left == nullptr) && (node->m_right != nullptr)) {
        if (node->m_left->m_npl < node->m_right->m_npl) {
            n = false;
        }
        if (queue.getPriority(node) < queue.getPriority(node->m_right)) {
            n = false;
        }
    }
    if ((node->m_right == nullptr) && (node->m_left != nullptr)) {
        if (queue.getPriority(node) < queue.getPriority(node->m_left)) {
            n = false;
        }
    }
    return n;
}

bool Tester::checkDeepCopy(Node *node, Node *node2) { // done
    Node *curr1 = node; // trackers
    Node *curr2 = node2;

    while ((curr1 != nullptr) && (curr2 != nullptr)) { // morris traversal
        if ((curr1->m_order.m_count != curr2->m_order.m_count) && (curr1->m_order.m_customerID && curr2->m_order.m_customerID) && (curr1->m_order.m_item != curr2->m_order.m_item) && (curr1->m_order.m_membership != curr2->m_order.m_membership) && (curr1->m_order.m_orderID != curr2->m_order.m_orderID) && (curr1->m_order.m_points != curr2->m_order.m_points) && (curr1 != curr2)) { // if everything does not line up return false
            return false;
        }
        if ((curr1->m_left == nullptr) && (curr2->m_left == nullptr)) {
            if ((curr1->m_order.m_count != curr2->m_order.m_count) && (curr1->m_order.m_customerID && curr2->m_order.m_customerID) && (curr1->m_order.m_item != curr2->m_order.m_item) && (curr1->m_order.m_membership != curr2->m_order.m_membership) && (curr1->m_order.m_orderID != curr2->m_order.m_orderID) && (curr1->m_order.m_points != curr2->m_order.m_points) && (curr1 != curr2)) { // if everything does not line up return false
                return false;
            }
            curr1 = curr1->m_right; // go right
            curr2 = curr2->m_right;
        } else {
            Node* current1 = curr1->m_left; // more trackers
            Node* current2 = curr2->m_left;
            while ((current1->m_right && current1->m_right != curr1) && (current2->m_right && current2->m_right != curr2)) {
                current1 = current1->m_right; // go right
                current2 = current2->m_right;
            }
            if ((current1->m_right == curr1) && (current2->m_right == curr2)) {
                current1->m_right = nullptr;
                current2->m_right = nullptr;
                curr1 = curr1->m_right; // go right
                curr2 = curr2->m_right;
            } else {
                if ((curr1->m_order.m_count != curr2->m_order.m_count) && (curr1->m_order.m_customerID && curr2->m_order.m_customerID) && (curr1->m_order.m_item != curr2->m_order.m_item) && (curr1->m_order.m_membership != curr2->m_order.m_membership) && (curr1->m_order.m_orderID != curr2->m_order.m_orderID) && (curr1->m_order.m_points != curr2->m_order.m_points) && (curr1 != curr2)) { // if everything does not line up return false
                    return false;
                }
                current1->m_right = curr1;
                current2->m_right = curr2;
                curr1 = curr1->m_left; // go left
                curr2 = curr2->m_left;
            }
        }
    } // read cqueue.cpp for more detail on implementation
    return true;
}

bool Tester::checkMinNode(CQueue &queue, Node *node) { // done
    bool run = true; // bool
    Node *curr = node; // tracker

    while (curr != nullptr) { // morris
        if (queue.getPriority(node) > queue.getPriority(curr)) { // checks priority is in order
            return false;
        }
        if (curr->m_left == nullptr) {
            if (queue.getPriority(node) > queue.getPriority(curr)) { // checks priority is in order
                return false;
            }
            curr = curr->m_right; // go right
        } else {
            Node* current1 = curr->m_left; // tracker (I know its not really used as a tracker)
            while (current1->m_right && current1->m_right != curr) { // checks priority is in order
                current1 = current1->m_right; // go right
            }
            if (current1->m_right == curr) {
                current1->m_right = nullptr;
                curr = curr->m_right; // go right
            } else {
                if (queue.getPriority(node) > queue.getPriority(curr)) { // checks priority is in order
                    return false;
                }
                current1->m_right = curr;
                curr = curr->m_left; // go left
            }
        }
    }
    return run;
}

bool Tester::checkMaxNode(CQueue &queue, Node *node) { // done, exact same as abov but for max instead of min
    bool run = true;    
    Node *curr = node;

    while (curr != nullptr) {
        if (queue.getPriority(node) < queue.getPriority(curr)) {
            run = false;
        }
        if (curr->m_left == nullptr) {
            if (queue.getPriority(node) < queue.getPriority(curr)) {
                run = false;
            }
            curr = curr->m_right;
        } else {
            Node* current1 = curr->m_left;
            while (current1->m_right && current1->m_right != curr) {
                current1 = current1->m_right;
            }
            if (current1->m_right == curr) {
                current1->m_right = nullptr;
                curr = curr->m_right;
            } else {
                if (queue.getPriority(node) < queue.getPriority(curr)) {
                    run = false;
                }
                current1->m_right = curr;
                curr = curr->m_left;
            }
        }
    }
    return run;
}

void Tester::buildQueue(CQueue &queue) { // build queue
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    for (int i = 0; i < 10000; i++) { // insert large amount of orders
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()), static_cast<COUNT>(countGen.getRandNum()), static_cast<MEMBERSHIP>(membershipGen.getRandNum()), pointsGen.getRandNum(), customerIdGen.getRandNum(), orderIdGen.getRandNum());
        queue.insertOrder(anOrder);
    }
}

int priorityFn1(const Order &order) {
    //this function1 works with a MAXHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [0-5003]
    //the highest priority would be 3+5000 = 5003
    //the lowest priority would be 0+0 = 0
    //the larger value means the higher priority
    int priority = static_cast<int>(order.getCount()) + order.getPoints();
    return priority;
}

int priorityFn2(const Order &order) {
    //this funcction works with a MINHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [0-10]
    //the highest priority would be 0+0 = 0
    //the lowest priority would be 5+5 =10
    //the smaller value means the higher priority
    int priority = static_cast<int>(order.getItem()) + static_cast<int>(order.getMemebership());
    return priority;
}