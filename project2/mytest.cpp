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
#include "show.h"
#include <random>

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
        // we can change the seed by calling this function after constructor call
        // this gives us more randomness
        m_generator = std::mt19937(seedNum);
    }

    int getRandNum(){
        // this function returns integer numbers
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
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
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
    bool testNormalInsertion(Show& show);
    bool testEdgeInsertion(Show& show);
    bool testErrorInsertion(Show &show);
    bool testIfBalance(Show &show);
    bool testBSTProperty(Show &show);
    bool testNormalRemove(Show &show);
    bool testEdgeRemove(Show &show);
    bool testIfBalanceRemove(Show &show);
    bool testIfBSTPropertyRemove(Show &show);
    bool testRemoveLightOff(Show &show);
    bool testcountDrones(Show &show);
    bool testNormalFindDrone(Show &show);
    bool testErrorFindDrone(Show &show);
    bool testAssignmentOperator(Show &show);
    bool testAssignmentOperatorError(Show &show);
    bool testRemovalTime(Show &show);
    bool testInsertionTime(Show &show);

    bool Tester::errorAssignment(Show* show){
        bool result = true;

        //checks to ensure the tree is empty beforehand
        result = result && (show->m_root == nullptr);

        //assignedShow declared and initialized
        Show* assignedShow = new Show();

        //result fills show
        for (int i = 20000; i < 20010; i++) {
            show->insert(Drone(i));
        }
        *assignedShow = *show;

        //self assignment
        show = show;

        //checked to ensure show is not empty, then assignedShow ensures that everything is the same
        result = result && (show->m_root != nullptr);
        //assignmentHelper used to prove all data is the same

        //assignmentShow deleted, then reininitialized to an empty object
        delete assignedShow;
        assignedShow = new Show();

        //ensured that assignedShow is empty
        result = result && (assignedShow == nullptr);
        //show set equal to assignedShow
        *show = *assignedShow;

        //checks to ensure both are nullptrs
        result = result && (show->m_root == nullptr);
        result = result && (assignedShow == nullptr);

        delete assignedShow; //assignedShow deleted

        return result; //result returned
    }
};

int main() {
    Tester test;
    Show *show = new Show();
    Show *emptyShow = new Show();

    for (int i = 20000; i < 20010; i++) {
        show->insert(Drone(i));
    }
    delete emptyShow;
    emptyShow = new Show();
    *emptyShow = *show;
    emptyShow->dumpTree();
    cout << endl;
    delete show;
    delete emptyShow;
    {
        Show *newShow = new Show();

        //error case tested 
        cout << "Error Assignment Operator: \n\t";
        bool testResult = test.errorAssignment(newShow);

        delete newShow;
    }
    /*
    {
        Show show;
        cout << "\nTest Case: Normal Insertions" << endl;
        if (test.testNormalInsertion(show)) {
            cout << "Normal Insertion Passed" << endl;
        } else {
            cout << "Normal Insertion Failed" << endl;
        }
    }
    
    {
        Show show;
        cout << "\nTest Case: Edge Insertion" << endl;
        if (test.testEdgeInsertion(show)) {
            cout << "Edge Insertion Passed" << endl;
        } else {
            cout << "Edge Insertion Failed" << endl;
        }
    }
    {
        Show show;
        cout << "\nTest Case: Error Insertion" << endl;
        if (test.testErrorInsertion(show)) {
            cout << "Error Insertion Passed" << endl;
        } else {
            cout << "Error Insertion Failed" << endl;
        }
    }

    {
        Show show;
        cout << "\nTest Case: Balance" << endl;
        if (test.testIfBalance(show)) {
            cout << "Balance Passed" << endl;
        } else {
            cout << "Balance Failed" << endl;
        }
    }

    {
        Show show;
        cout << "\nTest Case: BTS Property" << endl;
        if (test.testBSTProperty(show)) {
            cout << "BST Property Passed" << endl;
        } else {
            cout << "BST Property Failed" << endl;
        }
    }

    {
        Show show;
        cout << "\nTest Case: Normal Remove" << endl;
        if (test.testNormalRemove(show)) {
            cout << "Normal Remove Passed" << endl;
        } else {
            cout << "Normal Remove Failed" << endl;
        }
    }
    {
        Show show;
        cout << "\nTest Case: Edge Remove" << endl;
        if (test.testEdgeRemove(show)) {
            cout << "Edge Remove Passed" << endl;
        } else {
            cout << "Edge Remove Failed" << endl;
        }
    }

    {
        Show show;
        cout << "\nTest Case: Balance Remove" << endl;
        if (test.testIfBalanceRemove(show)) {
            cout << "Balance Remove Passed" << endl;
        } else {
            cout << "Balance Remove Failed" << endl;
        }
    }
    {
        Show show;
        cout << "\nTest Case: BST Property Remove" << endl;
        if (test.testIfBSTPropertyRemove(show)) {
            cout << "BST Property Remove Passed" << endl;
        } else {
            cout << "BST Property Remove Failed" << endl;
        }
    }
    {
        Show show;
        cout << "\nTest Case: Remove Light Off" << endl;
        if (test.testRemoveLightOff(show)) {
            cout << "Remove Light Off Passed" << endl;
        } else {
            cout << "Remove Light Failed" << endl;
        }
    }
    {
        Show show;
        cout << "\nTest Case: Count Drones" << endl;
        if (test.testcountDrones(show)) {
            cout << "Count Drones Passed" << endl;
        } else {
            cout << "Count Drones Failed" << endl;
        }
    }
    {
        Show show;
        cout << "\nTest Case: Normal Find Drone" << endl;
        if (test.testNormalFindDrone(show)) {
            cout << "Normal Find Drone Passed" << endl;
        } else {
            cout << "Normal Find Drone Failed" << endl;
        }
    }
    {
        Show show;
        cout << "\nTest Case: Error Find Drone" << endl;
        if (test.testErrorFindDrone(show)) {
            cout << "Error Find Drone Passed" << endl;
        } else {
            cout << "Error Find Drone Failed" << endl;
        }
    }

    {
        Show show;
        cout << "\nTest Case: Assignment Operator" << endl;
        if (test.testAssignmentOperator(show)) {
            cout << "Assignment Operator Passed" << endl;
        } else {
            cout << "Assignment Operator Failed" << endl;
        }
    }
    {
        Show show;
        cout << "\nTest Case: Assignment Operator Error" << endl;
        if (test.testAssignmentOperatorError(show)) {
            cout << "Assignment Operator Error Passed" << endl;
        } else {
            cout << "Assignment Operator Error Failed" << endl;
        }
    }

    {
        Show show;
        cout << "\nTest Case: Removal Time" << endl;
        if (test.testRemovalTime(show)) {
            cout << "Removal Time Passed" << endl;
        } else {
            cout << "Removal Time Failed" << endl;
        }
    }
    {
        Show show;
        cout << "\nTest Case: Insertion Time" << endl;
        if (test.testInsertionTime(show)) {
            cout << "Insertion Time Passed" << endl;
        } else {
            cout << "Insertion Time Failed" << endl;
        }
    }
    */
    return 0;;
}

bool Tester::testNormalInsertion(Show& show) {
    Random typeGen(0,2); // set random light color
    bool pass = true;
    for (int i = 20000; i <= 21000; i++) { // insert 1000 drones
        Drone drone(i, static_cast<LIGHTCOLOR>(typeGen.getRandNum())); // drone object
        show.insert(drone); // insert drone to tree
    }    
    for (int i = 20000; i <= 21000; i++) {
        pass = pass && (show.findDrone(i)); // check that drone was added
    }
    return pass;
}

bool Tester::testEdgeInsertion(Show& show) {
    bool pass = true;
    Drone drone1(10000); // insert drone with min id
    Drone drone2(99999); // insert drone with max id
    show.insert(drone1); // insert drones
    show.insert(drone2);
    pass = pass && show.findDrone(drone1.getID()); // check that they were added
    pass = pass && show.findDrone(drone2.getID());
    return pass;
}

bool Tester::testErrorInsertion(Show& show) {
    bool pass = true;
    Drone drone1(0); // less then min id
    Drone drone2(100000); // more then max id
    show.insert(drone1); // try to add them
    show.insert(drone2);
    pass = pass && !(show.findDrone(drone1.getID())); // check to make sure they were not added
    pass = pass && !(show.findDrone(drone2.getID()));
    return pass;
}

bool Tester::testIfBalance(Show& show) {
    Random typeGen(0,2); // set random light color
    bool pass = true;    
    for (int i = 20000; i <= 21000; i++) { // insert 1000 drones
        Drone drone(i, static_cast<LIGHTCOLOR>(typeGen.getRandNum())); // drone object
        show.insert(drone); // insert drone to tree
    }  
    for (int i = 20000; i <= 21000; i++) {
        pass = pass && (show.findDrone(i)); // check that drone was added
        pass = pass && ((show.getBalance(show.betterFindDrone(i)) == 0) || (show.getBalance(show.betterFindDrone(i)) == 1) || (show.getBalance(show.betterFindDrone(i)) == -1)); // check that balance is good
    }
    return pass;
}

bool Tester::testBSTProperty(Show& show) {
    Random typeGen(0,2); // set random light color
    bool pass = true;    
    for (int i = 20000; i <= 21000; i++) { // insert 1000 drones
        Drone drone(i, static_cast<LIGHTCOLOR>(typeGen.getRandNum())); // drone object
        show.insert(drone); // insert drone to tree
    }  
    for (int i = 20000; i <= 21000; i++) {
        pass = pass && (show.findDrone(i)); // check that drone was added
        if (show.betterFindDrone(i)->getLeft() != nullptr) { // check that left child is less then parent
            pass = pass && (show.betterFindDrone(i)->getID() > show.betterFindDrone(i)->getLeft()->getID());
        }
        if (show.betterFindDrone(i)->getRight() != nullptr) { // check that right child is greater then parent
            pass = pass && (show.betterFindDrone(i)->getID() < show.betterFindDrone(i)->getRight()->getID());
        }
    }
    return pass;
}

bool Tester::testNormalRemove(Show& show) {
    Random typeGen(0,2); // set random light color
    bool pass = true;
    for (int i = 20000; i <= 21000; i++) { // insert 1000 drones
        Drone drone(i, static_cast<LIGHTCOLOR>(typeGen.getRandNum())); // drone object
        show.insert(drone); // insert drone to tree
    }    
    for (int i = 20000; i <= 21000; i++) {
        pass = pass && (show.findDrone(i)); // check that drone was added
    }
    for (int i = 0; i <= 21000; i++) {
        if (i % 2 != 0) { // remove half the tree
            show.remove(i); // remove node
            pass = pass && !(show.findDrone(i)); // make sure that node is no longer in tree
        }
    }
    return pass;
}

bool Tester::testEdgeRemove(Show& show) {
    bool pass = true;
    Drone drone(30000);
    Drone drone2(30001);
    show.insert(drone);
    pass = pass && show.findDrone(drone.getID());
    show.remove(drone.getID()); // remove when only one node exist in tree
    pass = pass && !(show.findDrone(drone.getID())); // node should not be intree
    pass = pass && (show.m_root == nullptr); // check that root is nullptr
    show.remove(drone.getID()); // remove when no nodes exist
    pass = pass && (show.m_root == nullptr); // root shuld remain nullptr
    show.insert(drone);
    show.insert(drone2);
    pass = pass && show.findDrone(drone.getID()); // delete root node and replace when two nodes exist
    pass = pass && show.findDrone(drone2.getID()); 
    show.remove(drone.getID());
    pass = pass && !(show.findDrone(drone.getID()));
    pass = pass && ((show.m_root != nullptr) && (show.m_root->getID() == drone2.getID()));
    return pass;
}

bool Tester::testIfBalanceRemove(Show& show) {
    Random typeGen(0,2); // set random light color
    bool pass = true;
    for (int i = 20000; i <= 21000; i++) { // insert 1000 drones
        Drone drone(i, static_cast<LIGHTCOLOR>(typeGen.getRandNum())); // drone object
        show.insert(drone); // insert drone to tree
    }    
    for (int i = 20000; i <= 21000; i++) {
        pass = pass && (show.findDrone(i)); // check that drone was added
    }
    for (int i = 20000; i <= 21000; i++) {
        if (i % 2 != 0) { // remove half the tree
            show.remove(i);
        }
    }
    for (int i = 20000; i <= 21000; i++) {
        if (i % 2 == 0) { // check that the half that was not removed remained and is balanced
            pass = pass && show.findDrone(i);        
            pass = pass && ((show.getBalance(show.betterFindDrone(i)) == 0) || (show.getBalance(show.betterFindDrone(i)) == 1) || (show.getBalance(show.betterFindDrone(i)) == -1)); // check that balance is good
        } else { // check that the half that was removed is not in the tree
            pass = pass && !(show.findDrone(i));
        }
    }
    return pass;
}

bool Tester::testIfBSTPropertyRemove(Show& show) {
    Random typeGen(0,2); // set random light color
    bool pass = true;
    for (int i = 20000; i <= 21000; i++) { // insert 1000 drones
        Drone drone(i, static_cast<LIGHTCOLOR>(typeGen.getRandNum())); // drone object
        show.insert(drone); // insert drone to tree
    }    
    for (int i = 20000; i <= 21000; i++) {
        pass = pass && (show.findDrone(i)); // check that drone was added
    }
    for (int i = 20000; i <= 21000; i++) {
        if (i % 2 != 0) { // remove half the tree
            show.remove(i);
        }
    }
    for (int i = 20000; i <= 21000; i++) {
        if (i % 2 == 0) { // check that the half that was not delted keeps BST properties
            pass = pass && show.findDrone(i);   
            if (show.betterFindDrone(i)->getLeft() != nullptr) { // check that left child is less then parent
                pass = pass && (show.betterFindDrone(i)->getID() > show.betterFindDrone(i)->getLeft()->getID());
            }
            if (show.betterFindDrone(i)->getRight() != nullptr) { // check that right child is greater then parent
                pass = pass && (show.betterFindDrone(i)->getID() < show.betterFindDrone(i)->getRight()->getID());
            }       
        } else { // check that the half that was removed is not there
            pass = pass && !(show.findDrone(i));
        }
    }
    return pass;
}

bool Tester::testRemoveLightOff(Show& show) {
    Random typeGen(0,2); // set random light color
    bool pass = true;
    for (int i = 20000; i <= 21000; i++) { // insert 1000 drones
        Drone drone(i, static_cast<LIGHTCOLOR>(typeGen.getRandNum())); // drone object
        show.insert(drone); // insert drone to tree
    }    
    for (int i = 20000; i <= 21000; i++) {
        pass = pass && (show.findDrone(i)); // check that drone was added
    }
    for (int i = 20000; i <= 21000; i++) {
        if (i % 2 != 0) { // set half the tree to have light off
            show.setState(i, LIGHTOFF);
        }
    }
    show.removeLightOff(); // remove light off nodes
    for (int i = 20000; i <= 21000; i++) {
        if (i % 2 == 0) { // these nodes should have remained
            pass = pass && show.findDrone(i);
        } else { // these nodes should have been removed
            pass = pass && !(show.findDrone(i));
        }
    }
    return pass;
}

bool Tester::testcountDrones(Show& show) {
    Random typeGen(0,2); // set random light color
    int numDrone = 0; // counter
    bool pass = true;
    for (int i = 20000; i <= 21000; i++) { // insert 1000 drones
        Drone drone(i, static_cast<LIGHTCOLOR>(typeGen.getRandNum())); // drone object
        show.insert(drone); // insert drone to tree
    }    
    for (int i = 20000; i <= 21000; i++) {
        pass = pass && (show.findDrone(i)); // check that drone was added
        if (i % 2 != 0) { // set half node to green
            show.betterFindDrone(i)->setType(GREEN);
            numDrone++;
        } else { // set half node to blue
            show.betterFindDrone(i)->setType(BLUE);
        }
    }
    pass = pass && (show.countDrones(GREEN) == numDrone); // check that there are the number of green that was set
    return pass;
}

bool Tester::testNormalFindDrone(Show& show) {
    Random typeGen(0,2); // set random light color
    bool pass = true;
    for (int i = 20000; i <= 21000; i++) { // insert 1000 drones
        Drone drone(i, static_cast<LIGHTCOLOR>(typeGen.getRandNum())); // drone object
        show.insert(drone); // insert drone to tree
    }    
    for (int i = 20000; i <= 21000; i++) {
        pass = pass && (show.findDrone(i)); // check that drone was added
    }
    pass = pass && !(show.findDrone(30000)); // should return false
    pass = pass && !(show.findDrone(19999)); // should return false
    return pass;
}

bool Tester::testErrorFindDrone(Show& show) {
    Random typeGen(0,2); // set random light color
    bool pass = true;
    pass = pass && !(show.findDrone(20350)); // no drone should exist
    for (int i = 20000; i <= 21000; i++) { // insert 1000 drones
        Drone drone(i, static_cast<LIGHTCOLOR>(typeGen.getRandNum())); // drone object
        show.insert(drone); // insert drone to tree
    }    
    for (int i = 20000; i <= 21000; i++) {
        pass = pass && (show.findDrone(i)); // check that drone was added
    }
    pass = pass && !(show.findDrone(30000)); // should return false
    pass = pass && !(show.findDrone(19999)); // should return false
    return pass;
}

bool Tester::testAssignmentOperator(Show& show) {
    Random typeGen(0,2); // set random light color
    bool pass = true;
    Show show2; // show for operator
    Show show3;
    for (int i = 20000; i <= 21000; i++) { // insert 1000 drones
        Drone drone(i, static_cast<LIGHTCOLOR>(typeGen.getRandNum())); // drone object
        show.insert(drone); // insert drone to tree
    }    
    for (int i = 20000; i <= 21000; i++) {
        pass = pass && (show.findDrone(i)); // check that drone was added
    }
    show2 = show; // assignemnt operator
    pass = pass && (&show2 != &show); // check that memory location is different
    for (int i = 20000; i <= 21000; i++) { // check that everything has same value, but different location
        pass = pass && (show2.betterFindDrone(i)->getID() == show.betterFindDrone(i)->getID());
        pass = pass && (&*show2.betterFindDrone(i) != &*show.betterFindDrone(i));
    }
    show = show3; // set to empty object
    pass = pass && (&show != &show3); // check for different memory location
    pass = pass && ((show.m_root == nullptr) && (show3.m_root == nullptr)); // check that both are nullptr
    return pass;
}

bool Tester::testAssignmentOperatorError(Show& show) {
    bool pass = true;
    Show show2;
    show2 = show;
    pass = pass && (&show2 != &show); // empty object
    pass = pass && ((show2.m_root == nullptr) && (show.m_root == nullptr));
    return pass;
}

bool Tester::testRemovalTime(Show& show) {
    Random typeGen(0,2); // set random light color
    int numDeleted = 0; // counter
    double time[5];
    double deletedNodes[5]; // array to hold how many nodes were removed
    double T = 0.0;//stores running times
    double measureTime = 0.0;
    clock_t start, stop;//stores the clock ticks while running the program
    bool pass = true;
    for (int i = 0; i < 5; i++) {
        for (int j = 10000; j < (10000 + (1000 * pow(2, i))); j++) { // insert drones
            Drone drone(j, static_cast<LIGHTCOLOR>(typeGen.getRandNum())); // drone object
            show.insert(drone); // insert drone to tree
        }
        for (int j = 10000; j < (10000 + (1000 * pow(2, i))); j++) { // insert drones
            if (j % 2 != 0) { // remove half nodes
                start = clock();
                show.remove(j);
                stop = clock();
                numDeleted++; // increase number
                T = (stop - start) + T;
            }
        }
        show.clear(); // destroy tree
        measureTime = T/CLOCKS_PER_SEC;
        deletedNodes[i] = numDeleted; // add number to array
        time[i] = measureTime;
        T = 0.0;
        measureTime = 0.0;
        numDeleted = 0; // reset number
    }
    for (int i = 0; i < 4; i++) { // check that remove fits time
    double T1 = deletedNodes[i] / time[i];
    double T2 = deletedNodes[i + 1] / time[i + 1];
    if (!(((1.1 - 0.4) < (T2 / T1)) && ((T2 / T1) < (1.1 + 0.4)))) {
            pass = false;
        }
    }
    return pass;
}

bool Tester::testInsertionTime(Show& show) {
    Random typeGen(0,2); // set random light color
    int numInsert = 0; // counter
    double time[5];
    double insertedNodes[5]; // array to hold how many nodes were inserted
    double T = 0.0;//stores running times
    double measureTime = 0.0;
    clock_t start, stop;//stores the clock ticks while running the program
    bool pass = true;
    for (int i = 0; i < 5; i++) {
        for (int j = 10000; j < (10000 + (1000 * pow(2, i))); j++) { // insert drones
            Drone drone(j, static_cast<LIGHTCOLOR>(typeGen.getRandNum())); // drone object
            start = clock();
            show.insert(drone); // insert drone to tree
            stop = clock();
            T = (stop - start) + T;
            numInsert++;
        }
        show.clear(); // destroy tree
        measureTime = T/CLOCKS_PER_SEC;
        insertedNodes[i] = numInsert; // add number 
        time[i] = measureTime;
        T = 0.0;
        measureTime = 0.0;
        numInsert = 0; // reset counter
    }
    for (int i = 0; i < 4; i++) { // check that insert fits time
        double T1 = insertedNodes[i] / time[i];
        double T2 = insertedNodes[i + 1] / time[i + 1];
        if (!(((1.1 - 0.4) < (T2 / T1)) && ((T2 / T1) < (1.1 + 0.4)))) {
            pass = false;
        }
    }
    return pass;
}