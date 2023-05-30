// UMBC - CMSC 341 - Spring 2023 - Proj1// UMBC - CMSC 341 - Spring 2023 - Proj0
/********************************************************
** File: mytest.cpp
** Project: CMSC 341 Project 0
** Author: Matthew Green
** Date: 07/03/2021
** Email: mgreen11@umbc.edu
**
** Description: Tests all the functions in fuel.cpp
**********************************************************/

#include "fuel.h"
#include <random>
using namespace std;
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
    bool normalAddTank(FuelSys &system);
    bool wrongAddTank(FuelSys &system);
    bool normalRemoveTank(FuelSys &system);
    bool nonRemoveTank(FuelSys &system);
    bool normalFindTank(FuelSys &system);
    bool noFindTank(FuelSys &system);
    bool normalTotalFuel(FuelSys &system);
    bool noTotalFuel(FuelSys &system);
    bool normalAddPump(FuelSys &system);
    bool duplicateAddPump(FuelSys &system);
    bool normalRemovePump(FuelSys &system);
    bool noRemovePump(FuelSys &system);
    bool normalDrain(FuelSys &system);
    bool noDrain(FuelSys &system);
    bool testOverloadedAssignmentOperator(FuelSys &system);
    void createSys(FuelSys &system);
    void secretTest();
};

int main() {
    Tester test;
    {
        // test to add tank
        FuelSys sys;
        cout << "Test case, Adding a Tank to a FuelSys: tries adding a tank to a fuelsys which should be added" << endl;
        if (test.normalAddTank(sys)) {
            cout << "Adding a Tank to a FuelSys passed" << endl;

        } else {
            cout << "Adding a Tank to a FuelSys failed" << endl;
        }
    }
    {
        // test to add negative id tank
        FuelSys sys;
        cout << "\nTest case, Adding a Negative ID Tank to a FuelSys: tries adding a negative fuel tank ID to a fuelsys which should not be added" << endl;
        if (test.wrongAddTank(sys)) {
            cout << "Adding a Negative ID Tank to a FuelSys passed" << endl;
        } else {
            cout << "Adding a Negative ID Tankt to a FuelSys failed" << endl;
        }
    }
    {
        // test to remove a tank
        FuelSys sys;
        cout << "\nTest case, Remove Tank From a FuelSys: tries removing a tank from a fuelsys which should remove it from the fuelsys" << endl;
        if (test.normalRemoveTank(sys)) {
            cout << "Remove Tank From a FuelSys passed" << endl;
        } else {
            cout << "Remove Tank From a FuelSys failed" << endl;
        }
    }
    {
        // test to remove a tank that does not exist
        FuelSys sys;
        cout << "\nTest case, Remove Non-Existant Tank From FuelSys: tries to remove a tankk that does not exist, nothing should happen" << endl;
        if (test.nonRemoveTank(sys)) {
            cout << "Remove Non-Existant Tank From FuelSys passed" << endl;
        } else {
            cout << "Remove Non-Existant Tank From FuelSys failed" << endl;
        }
    }
    {
        // test to find tank
        FuelSys sys;
        cout << "\nTest case, Find a Tank in FuelSys: attempt to find a tank in a fuelsys" << endl;
        if (test.normalFindTank(sys)) {
            cout << "Find a Tank in FuelSys passed" << endl;
        } else {
            cout << "Find a Tank in a FuelSys failed" << endl;
        }
    }
    {
        // test to find tank that does not exist
        FuelSys sys;
        cout << "\nTest case, Find a Non-Existant Tank in FuelSys: attempt to find a non-existant tank in fuelsys which should return nothing" << endl;
        if (test.noFindTank(sys)) {
            cout << "Find Non-Existant Tank in FuelSys passed" << endl;
        } else {
            cout << "Find Non-Existant Tank in FuelSys failed" << endl;
        }
    }
    {
        // test to output total fuel count
        FuelSys sys;
        cout << "\nTest case, Output Total Fuel of FuelSys: tries to output the sum of all fuel in fuelsys" << endl;
        if (test.normalTotalFuel(sys)) {
            cout << "Output Total Fuel of FuelSys passed" << endl;
        } else {
            cout << "Output Total Fuel of FuelSys failed" << endl;
        }
    }
    {
        // test to output total fuel if all tanks are 0
        FuelSys sys;
        cout << "\nTest case, Output Total Fuel of FuelSys at 0: tries to output the sum of all fuel in fuelsys when all tanks are 0" << endl;
        if (test.noTotalFuel(sys)) {
            cout << "Output Total Fuel of FuelSys at 0 passed" << endl;
        } else {
            cout << "Output Total Fuel of FuelSys at 0 failed" << endl;
        }
    }
    {
        // test to add pump 
        FuelSys sys;
        cout << "\nTest case, Try Adding Pump to Tank: tries adding a pump to a tank" << endl;
        if (test.normalAddPump(sys)) {
            cout << "Try Adding Pump to a Tank passed" << endl;
        } else {
            cout << "Try Adding Pump to a Tank failed" << endl;
        }
    }
    {
        // test to add duplicate pump
        FuelSys sys;
        cout << "\nTest case, Try Adding Duplicate Pump to Tank: tries adding a duplicate pump to a tank which should faile" << endl;
        if (test.duplicateAddPump(sys)) {
            cout << "Try Adding Duplicate Pump to Tank passed" << endl;
        } else {
            cout << "Try Adding Duplicate Pump to a Tank failed" << endl;
        }
    }
    {
        // test to remove pump
        FuelSys sys;
        cout << "\nTest case, Try Removing Pump from Tank: tries to remove a pump from a tank" << endl;
        if (test.normalRemovePump(sys)) {
            cout << "Try Removing Pump from Tank passed" << endl;
        } else {
            cout << "Try Removing Pump from Tank failed" << endl;
        }
    }
    {
        // test to remove nonexistant pump
        FuelSys sys;
        cout << "\nTest case, Try Removing Non-Existing Pump from Tank: tries to remove a non-existant pump from a tank which should fail" << endl;
        if (test.noRemovePump(sys)) {
            cout << "Try Removing Non-Existing Pump from Tank passed" << endl;
        } else {
            cout << "Try Removing Non-Existing Pump from Tank failed" << endl;
        }
    }
    {
        // test for drain
        FuelSys sys;
        cout << "\nTest case, Try Drain From One Tank to Another: tries to transfer fuel from one tank to antoehr tank" << endl;
        if (test.normalDrain(sys)) {
            cout << "Try Drain From One Tank to Another passed" << endl;
        } else {
            cout << "Try Drain From One Tank to Another failed" << endl;
        }
    }
    {
        // test for wrong drain
        FuelSys sys;
        cout << "\nTest case, Try Drain From One Tank to Another Incorrectly: tries to incorrectly transfer fuel from one tank to another" << endl;
        if (test.noDrain(sys)) {
            cout << "Try Drain From One Tank to Antother Incorrectly passed" << endl;
        } else {
            cout << "Try Drin from on Tank to Another Incorrectly failed" << endl;
        }   
    }
    {
        // test overloaded opperator
        FuelSys sys;
        cout << "\nTest case, Try to Use the Overloaded Assignment Operator: tries to use the assignment operator" << endl;
        if (test.testOverloadedAssignmentOperator(sys)) {
            cout << "Try to Use the Overloaded Assignment Operator passed" << endl;
        } else {
            cout << "Try to Use the Overloaded Assignment Operator failed" << endl;
        }
    }
    return 0;
}

// test adding a tank to the system
bool Tester::normalAddTank(FuelSys &system) {
    // test adding two tanks in the link list
    bool pass = true;
    pass = pass && (system.m_current == nullptr); // current should be nullptr as there is nothing in list
    pass = pass && (system.addTank(1, MINCAP, MINCAP)); // add tank to list
    pass = pass && (system.findTank(1)); // see if tank is in list
    pass = pass && (system.m_current == system.m_current->m_next); // next should equal itself has it only has one node
    pass = pass && (system.addTank(2, MINCAP, MINCAP)); // add another tank to list
    pass = pass && (system.findTank(2)); // see if tank is in list
    pass = pass && (system.m_current->m_next != system.m_current); // next node should not be itself anymore as there are two nodes
    pass = pass && (system.m_current == system.m_current->m_next->m_next); // the next next node should be itself as there are two nodes
    return pass;
}

// test trying to add a tank to the system, but it should not be inserted
bool Tester::wrongAddTank(FuelSys &system) {
    bool pass = true;
    createSys(system); // create a pre-generated system
    pass = pass && !(system.addTank(3,MINCAP, MINCAP)); // tries adding a duplicate
    pass = pass && !(system.addTank(-4, MINCAP, MINCAP)); // tries adding a negative ID
    pass = pass && !(system.addTank(10, MINCAP-1, MINCAP)); // tries adding capcity less then mincap
    pass = pass && !(system.addTank(20, MINCAP, MINCAP+1)); // tries adding tankfuel greater then capacity
    return pass;

}

//test removing a tank
bool Tester::normalRemoveTank(FuelSys &system) {
    bool pass = true;
    pass = pass && (system.addTank(1, MINCAP, MINCAP)); // add tank to list
    pass = pass && (system.removeTank(1)); // remove tank from list
    pass = pass && (system.m_current == nullptr); // current should be nullptr as we deleted the only node in list
    createSys(system); // create a pre-generated system
    pass = pass && (system.findTank(3)); // make sure that node is in list
    pass = pass && (system.removeTank(3)); // remove node from list
    return pass;

}

// test trying to remove a tank that does not exist
bool Tester::nonRemoveTank(FuelSys &system) {
    bool pass = true;
    pass = pass && !(system.removeTank(1)); // try to remove a node when list is empty
    createSys(system); // create a pre-generated system
    pass = pass && !(system.removeTank(100)); // try to remove a node that does not exist
    return pass;

}

// test trying to find a valid tank
bool Tester::normalFindTank(FuelSys &system) {
    bool pass = true;
    pass = pass && (system.addTank(1, MINCAP, MINCAP)); // add tank to list
    pass = pass && ((system.findTank(1)) && (system.m_current == system.m_current->m_next)); // try to find tank and see if next node is itself as there is only one node
    pass = pass && (system.removeTank(1)); // remove tank from list
    createSys(system); // create pre-generated system
    pass = pass && (system.findTank(2)); // find tank in middle of list
    return pass;

}

// test trying to find a tank that does not exist
bool Tester::noFindTank(FuelSys &system) {
    bool pass = true;
    pass = pass && !(system.findTank(2)); // try to find node in empty list
    createSys(system); 
    pass = pass && !(system.findTank(10)); // try to find non-existant tank in list
    Tank *temp = system.m_current; // tracker
    system.findTank(99); // try to find non-existant tank in list, should not find and current should stay the same
    pass = pass && (system.m_current == temp); // value of current should not change
    return pass;

}

// test if total fuel works correctly
bool Tester::normalTotalFuel(FuelSys &system) {
    bool pass = true;
    int target = 0; // how much fuel should be in all tanks
    pass = pass && (system.addTank(1, MINCAP, MINCAP)); // add tank 
    pass = pass && (system.addTank(2, MINCAP, MINCAP)); // ad tank
    target = MINCAP + MINCAP; // get how much fuel should be in a tank
    pass = pass && (target == system.totalFuel()); // see if tank total fuel is equal to target
    pass = pass && (system.addTank(3, MINCAP, 500)); // add another tank
    target = target + 500; // increase target to account for new tank
    pass = pass && (target == system.totalFuel()); // see if tank total fuel is equal to target
    pass = pass && (system.removeTank(2)); // remove a tank
    target = target - MINCAP; // change target value to account for deleting a tank
    pass = pass && (target == system.totalFuel()); // see if tank total fuel is equal to target
    return pass;

}

// test if total fuel works if there is no fuel
bool Tester::noTotalFuel(FuelSys &system) {
    bool pass = true;
    int target = 0; // how much fuel should be in all tanks
    pass = pass && !(system.totalFuel()); // nothing should exist as there are no tanks
    pass = pass && (system.addTank(1, MINCAP, 0)); // add a tank with no fuel
    pass = pass && (system.addTank(2, MINCAP, 0)); // add a tank with no fuel
    pass = pass && (system.addTank(3, MINCAP, 0)); // add a tank with no fuel
    pass = pass && (target == system.totalFuel()); // see if tank total fuel is equal to target
    pass = pass && (system.removeTank(2)); // remove a tank
    pass = pass && (target == system.totalFuel()); // see if value of total fuel changed
    return pass;

}

// test if adding a pump works
bool Tester::normalAddPump(FuelSys &system) {
    bool pass = true;
    pass = pass && (system.addTank(1, MINCAP, MINCAP)); // add tank
    pass = pass && (system.addTank(2, MINCAP, MINCAP)); // add tank
    pass = pass && (system.addTank(3, MINCAP, MINCAP)); // add tank
    pass = pass && (system.m_current->m_pumps == nullptr); // m_pump should be null
    pass = pass && (system.addPump(1, 1, 2)); // add pump
    pass = pass && (system.m_current->m_next->m_pumps->m_pumpID == 1); // checks that m_pump is pump added
    pass = pass && (system.addPump(1, 2, 2)); // add pump
    pass = pass && (system.m_current->m_next->m_pumps->m_pumpID == 2); // checks that m_pump is pump added
    pass = pass && (system.addPump(1, 3, 3)); // add pump
    pass = pass && (system.m_current->m_next->m_pumps->m_pumpID == 3); // checks that m_pump is pump added
    pass = pass && (system.addPump(1, 4, 3)); // add pump
    pass = pass && (system.m_current->m_next->m_pumps->m_pumpID == 4); // checks that m_pump is pump added
    return pass;

}

// test if adding a pump does not work if trying to add duplicate ID
bool Tester::duplicateAddPump(FuelSys &system) {
    bool pass = true;
    createSys(system);
    pass = pass && !(system.addPump(2, 2, 3)); // try adding duplicate pump
    pass = pass && !(system.addPump(2, 9, 2)); // try ading pump to itself
    pass = pass && !(system.addPump(9, 1, 3)); // try adding pump to tank that does not exist
    return pass;

}

// test trying removing a pump
bool Tester::normalRemovePump(FuelSys &system) {
    bool pass = true;
    pass = pass && !(system.removePump(1, 3)); // try removing pump from tank that does not exist
    pass = pass && (system.addTank(1, MINCAP, MINCAP));
    pass = pass && !(system.removePump(1, 3)); // try to remove pump that does not exist from tank
    pass = pass && (system.removeTank(1)); // remove tank
    createSys(system); // create pre-existing system
    pass = pass && (system.findTank(2)); // go to tank
    pass = pass && (system.m_current->m_next->m_pumps->m_next->m_pumpID == 3); // check if pump exist
    pass = pass && (system.removePump(2, 3)); // remove pump
    pass = pass && (system.findTank(2)); // go to tank
    pass = pass && (system.m_current->m_next->m_pumps->m_next->m_pumpID != 3); // check if tank got removed
    pass = pass && (system.findTank(1)); // go to tank
    pass = pass && (system.m_current->m_next->m_pumps->m_pumpID == 4); // check that this is first node in list
    pass = pass && (system.removePump(1, 4)); // remove pump, this is the last pump;
    pass = pass && (system.m_current->m_next->m_pumps->m_pumpID != 4);
    return pass;

}

// test trying removing a pump that does not exist
bool Tester::noRemovePump(FuelSys &system) {
    bool pass = true;
    createSys(system);
    pass = pass && !(system.removePump(8, 1)); // try removing pump from tank that does not exist
    pass = pass && !(system.removePump(2, 10)); // try removing pump tht does not exist from tank
    pass = pass && (system.addTank(9,MINCAP, MINCAP)); // add pump
    pass = pass && !(system.removePump(9, 1)); // try removing pump from tank that has no pumps    
    return pass;

}

// test if drain works correctly
bool Tester::normalDrain(FuelSys &system) {
    bool pass = true;    
    pass = pass && (system.addTank(1, DEFCAP, MINCAP)); // add tank
    pass = pass && (system.addTank(2, DEFCAP, MINCAP)); // add tank
    pass = pass && (system.addPump(2, 1, 1)); // add pump
    pass = pass && (system.findTank(1)); // get certain tank
    pass = pass && (system.m_current->m_next->m_tankFuel == MINCAP); // check tank fuel
    pass = pass && (system.m_current->m_tankFuel == MINCAP); // check tank fuel
    pass = pass && (system.drain(2, 1, 500)); // transfer fuel
    pass = pass && (system.findTank(1)); // get certain tank
    pass = pass && (system.m_current->m_next->m_tankFuel == (MINCAP + 500));
    pass = pass && (system.m_current->m_tankFuel == (MINCAP - 500));
    pass = pass && (system.drain(2, 1, MINCAP)); // transfer fuel, not enough fuel to be transfered
    pass = pass && (system.m_current->m_next->m_tankFuel == (MINCAP + MINCAP));
    pass = pass && (system.m_current->m_tankFuel == (0));
    pass = pass && (system.fill(2, DEFCAP)); // fill tank to top
    pass = pass && (system.drain(2, 1, MINCAP)); // transfer fuel, should be too much
    pass = pass && (system.findTank(1)); // get certain tank
    pass = pass && (system.m_current->m_next->m_tankFuel == (DEFCAP)); // see if fuel is correct
    pass = pass && (system.m_current->m_tankFuel == (DEFCAP - 1000)); // see if fuel is correct
    return pass;

}

// test if drain fals if tank does not exist
bool Tester::noDrain(FuelSys &system) {
    bool pass = true;    
    pass = pass && (system.addTank(1, DEFCAP, MINCAP)); // add tank
    pass = pass && (system.addTank(2, DEFCAP, MINCAP)); // add tank
    pass = pass && (system.addPump(2, 1, 1)); // add pump
    pass = pass && (system.findTank(1)); // get certain tank
    pass = pass && (system.m_current->m_next->m_tankFuel == MINCAP); // check tank fuel
    pass = pass && (system.m_current->m_tankFuel == MINCAP); // check tank fuel
    pass = pass && !(system.drain(2, 2, 500)); // tries to drain from pump that does not exist
    pass = pass && (system.removeTank(1)); // removes tank
    pass = pass && !(system.drain(2, 1, 500)); // tries to drain to a tank that was removed
    return pass;

}

// test if overloaded operation works
bool Tester::testOverloadedAssignmentOperator(FuelSys &system) {
    bool pass = true;
    FuelSys system2; // create second system
    createSys(system); 
    pass = pass && (system2.addTank(1, MINCAP, MINCAP)); // add tank
    pass = pass && (system2.addTank(2, MINCAP, MINCAP)); // add tank
    pass = pass && (system2.addPump(1, 1, 2)); // add pump
    pass = pass && (system2.addPump(1, 2, 2)); // add pump
    pass = pass && (system2.addPump(2, 1, 1)); // add pump
    pass = pass && (system2.addPump(2, 2, 1)); // add pump
    system2 = system;
    pass = pass && (&system2 != &system); // make sure deep copy was made as both would have different memory addresses 
    pass = pass && (&system2.m_current->m_pumps != &system.m_current->m_pumps); // make sure deep copy was made as both would have different memory addresses 
    pass = pass && (&system2.m_current != &system.m_current); // make sure deep copy was made as both would have different memory addresses 
    pass = pass && (system2.m_current->m_tankID == system.m_current->m_tankID); // make sure that all variable are equal to one another
    pass = pass && (system2.m_current->m_tankCapacity == system.m_current->m_tankCapacity); // make sure that all variable are equal to one another
    pass = pass && (system2.m_current->m_tankFuel == system.m_current->m_tankFuel); // make sure that all variable are equal to one another
    pass = pass && (system2.m_current->m_pumps->m_pumpID == system.m_current->m_pumps->m_pumpID); // make sure that all variable are equal to one another
    pass = pass && (system2.m_current->m_pumps->m_target == system.m_current->m_pumps->m_target); // make sure that all variable are equal to one another
    return pass;

}

// helper function to create a system
void Tester::createSys(FuelSys &system) {
    int numTanks = 5; // number of tanks
    Random randFuel(MINCAP,DEFCAP); // random amount of start fuel
    Random randTank(1,numTanks); // random tank number for pump
    for (int i=1;i<=numTanks;i++){ // add tanks to list
        system.addTank(i,DEFCAP,randFuel.getRandNum());
    }
    for (int i=1;i<=numTanks;i++){ // add shel to list
        int rand = randTank.getRandNum();; // radomize pump number
        while (rand == i) { // pump number can't be own tank
            rand = randTank.getRandNum();
        }
        system.addPump(i,1,rand);rand = randTank.getRandNum();; // add pump
        while (rand == i) {
            rand = randTank.getRandNum();
        }
        system.addPump(i,2,rand);rand = randTank.getRandNum();;
        while (rand == i) {
            rand = randTank.getRandNum();
        }
        system.addPump(i,3,rand);rand = randTank.getRandNum();;
        while (rand == i) {
            rand = randTank.getRandNum();
        }
        system.addPump(i,4,rand);rand = randTank.getRandNum();;
        while (rand == i) {
            rand = randTank.getRandNum();
        }
    }
}

// secret test in case you actually see this
void Tester::secretTest() {
    cout << "this is a secret test" << endl;
    cout << "if you see this, then you are really good" << endl;
    cout << "this test is mostly here because I finished the project early" << endl;
    cout << "the last date this secret test was editied was on 2/16/2023" << endl << endl;;
    cout << "this project was a lot less tedious compared to the first one" << endl;

}