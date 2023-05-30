// Matthew Green, SN 93970
// CMSC 341 - Spring 2023 - Project 4
#include "vdetect.h"
#include <random>
#include <vector>
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
class Tester{
    public:
        bool testInsertion(VDetect &table, vector<Virus> &dataList);
        bool testGetVirusError(VDetect &table, vector<Virus> &dataList);
        bool testGetVirusNonColliding(VDetect &table, vector<Virus> &dataList);
        bool testGetVirusColliding(VDetect &table, vector<Virus> &dataList);
        bool testRemoveNonColliding(VDetect &table, vector<Virus> &dataList);
        bool testRemoveColliding(VDetect &table, vector<Virus> &dataList);
        bool testRehashInsert(VDetect &table, vector<Virus> &dataList);
        bool testRehashInsertComplete(VDetect &table, vector<Virus> &dataList);
        bool testRehashRemove(VDetect &table, vector<Virus> &dataList);
        bool testRehashRemoveComplete(VDetect &table, vector<Virus> &dataList);
};

unsigned int hashCode(const string str);
string sequencer(int size, int seedNum);

int main(){
    Tester test;
    // block code
    {
        VDetect table(MAXPRIME, hashCode, DOUBLEHASH);
        vector<Virus> dataList;
        cout << "\nTest Case: Test the insertion operation in the hash table" << endl;
        if (test.testInsertion(table, dataList)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        VDetect table(MAXPRIME, hashCode, DOUBLEHASH);
        vector<Virus> dataList;
        cout << "\nTest Case: Test the find operation (getVirus(...) function) for an error case, the Virus object does not exist in the database" << endl;
        if (test.testGetVirusError(table, dataList)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        VDetect table(MAXPRIME, hashCode, DOUBLEHASH);
        vector<Virus> dataList;
        cout << "\nTest Case: Test the find operation (getVirus(...) function) with a few non-colliding keys" << endl;
        if (test.testGetVirusNonColliding(table, dataList)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        VDetect table(MAXPRIME, hashCode, DOUBLEHASH);
        vector<Virus> dataList;
        cout << "\nTest Case: Test the find operation (getVirus(...) function) with a number of colliding keys without triggering a rehash. This also tests whether the insertion works correctly with colliding data" << endl;
        if (test.testGetVirusColliding(table, dataList)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        VDetect table(MAXPRIME, hashCode, DOUBLEHASH);
        vector<Virus> dataList;
        cout << "\nTest Case: Test the remove operation with a few non-colliding keys" << endl;
        if (test.testRemoveNonColliding(table, dataList)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        VDetect table(MAXPRIME, hashCode, DOUBLEHASH);
        vector<Virus> dataList;
        cout << "\nTest Case: Test the remove operation with a number of colliding keys without triggering a rehash" << endl;
        if (test.testRemoveColliding(table, dataList)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        VDetect table(MINPRIME, hashCode, DOUBLEHASH);
        vector<Virus> dataList;
        cout << "\nTest Case: Test the rehashing is triggered after a descent number of data insertion" << endl;
        if (test.testRehashInsert(table, dataList)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        VDetect table(MINPRIME, hashCode, DOUBLEHASH);
        vector<Virus> dataList;
        cout << "\nTest Case: Test the rehash completion after triggering rehash due to load factor, i.e. all live data is transferred to the new table and the old table is removed" << endl;
        if (test.testRehashInsertComplete(table, dataList)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        VDetect table(5113, hashCode, DOUBLEHASH);
        vector<Virus> dataList;
        cout << "\nTest Case: Test the rehashing is triggered after a descent number of data removal" << endl;
        if (test.testRehashRemove(table, dataList)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    {
        VDetect table(5113, hashCode, DOUBLEHASH);
        vector<Virus> dataList;
        cout << "\nTest Case: Test the rehash completion after triggering rehash due to delete ratio, i.e. all live data is transferred to the new table and the old table is removed" << endl;
        if (test.testRehashRemoveComplete(table, dataList)) {
            cout << "Test Passed" << endl;
        } else {
            cout << "Test Failed" << endl;
        }
    }
    return 0;
}

bool Tester::testInsertion(VDetect &table, vector<Virus> &dataList) {
    bool pass = true;
    Random RndID(MINID,MAXID);
    unsigned int hashIndex;
    int numLoop = 50;
    for (int i = 0; i < numLoop; i++) { // insert elements
        Virus dataObj = Virus(sequencer(5, i), RndID.getRandNum()); // make virus
        hashIndex = hashCode(dataObj.getKey()) % table.m_currentCap;
        for (long unsigned int j = 0; j < dataList.size(); j++) { // check that hash is not in tabe
            while (hashIndex == (hashCode(dataList.at(j).getKey()) % table.m_currentCap)) { // hash is in table
                dataObj = Virus(sequencer(5, j + i), RndID.getRandNum()); // get new element
                j = 0; // restart for loop
            }
        }
        dataList.push_back(dataObj); // add to vector
        table.insert(dataObj); // add to table
        pass = pass && (table.m_currentSize == (i + 1)); // table size change
    }
    pass = pass && (table.m_currentSize == numLoop);
    pass = pass && (table.m_currNumDeleted == 0);
    pass = pass && (table.m_oldTable == nullptr);
    for (long unsigned int i = 0; i < dataList.size(); i++) { // check that elemnt is in correct location
        hashIndex = hashCode(dataList.at(i).getKey()) % table.m_currentCap;
        pass = pass && (table.m_currentTable[hashIndex] == dataList.at(i));
        if (pass == false) {
            break;
        }
    }
    for (int i = 0; i < numLoop; i++) { // collision
        Virus dataObj = Virus(sequencer(5, i), RndID.getRandNum());
        hashIndex = hashCode(dataObj.getKey()) % table.m_currentCap;
        for (long unsigned int j = 0; j < dataList.size(); j++) {
            while ((dataObj.getKey() != dataList.at(j).getKey()) && (dataObj.getID() == dataList.at(j).getID())) {
                dataObj = Virus(sequencer(5, j + i), RndID.getRandNum());
                j = 0;
            }
        }
        if (table.m_currProbing != NONE) {
            dataList.push_back(dataObj); // add to vector
            table.insert(dataObj); // add to table
            pass = pass && (table.m_currentSize == (numLoop + i + 1)); // table size change
    }
        }
    pass = pass && (table.m_currentSize == (numLoop + numLoop));
    pass = pass && (table.m_currNumDeleted == 0);
    pass = pass && (table.m_oldTable == nullptr);
    for (long unsigned int i = 0; i < dataList.size(); i++) { // does stuff
        if ((int) i < numLoop) { // make sure stuff is in correct position
            hashIndex = hashCode(dataList.at(i).getKey()) % table.m_currentCap;
            pass = pass && (table.m_currentTable[hashIndex] == dataList.at(i));
        } else { // make sure stuff is not in calculated position due to collision
            hashIndex = hashCode(dataList.at(i).getKey()) % table.m_currentCap;
            pass = pass && !(table.m_currentTable[hashIndex] == dataList.at(i));
        }
        if (pass == false) {
            break;
        }
    }
    return pass;
}

bool Tester::testGetVirusError(VDetect &table, vector<Virus> &dataList) {
    bool pass = true;    
    Random RndID(MINID,MAXID);
    int numLoop = 20;
    int num = 0;
    for (int i = 0; i < numLoop; i++) { // insert elements
        Virus dataObj = Virus(sequencer(5, i), RndID.getRandNum()); // make virus
        for (long unsigned int j = 0; j < dataList.size(); j++) { // check that hash is not in tabe
            while (dataObj.getKey() == (dataList.at(j).getKey())) { // hash is in table
                dataObj = Virus(sequencer(5, j + i), RndID.getRandNum()); // get new element
                j = 0; // restart for loop
            }
        }
        dataList.push_back(dataObj); // add to vector
        table.insert(dataObj); // add to table
        pass = pass && (table.m_currentSize == (i + 1)); // table size change
    }
    pass = pass && (table.m_currentSize == numLoop);
    pass = pass && (table.m_currNumDeleted == 0);
    pass = pass && (table.m_oldTable == nullptr);
    for (int i = 0; i < 5; i++) {
        Virus dataObj = Virus(sequencer(5, i), RndID.getRandNum()); // make virus        
        for (long unsigned int j = 0; j < dataList.size(); j++) { // check that hash is not in tabe
            while (dataObj.getKey() == (dataList.at(j).getKey())) { // hash is in table 
                dataObj = Virus(sequencer(5, j + i + num), RndID.getRandNum()); // get new element
                j = 0; // restart for loop
                num++;
            }
        }
        pass = pass && (table.getVirus(dataObj.getKey(), dataObj.getID()) == EMPTY);
        if (pass == false) {
            break;
        }
    }
    return pass;
}

bool Tester::testGetVirusNonColliding(VDetect &table, vector<Virus> &dataList) {
    bool pass = true;
    Random RndID(MINID,MAXID);
    unsigned int hashIndex;
    int numLoop = 50;
    for (int i = 0; i < numLoop; i++) { // insert elements
        Virus dataObj = Virus(sequencer(5, i), RndID.getRandNum()); // make virus
        hashIndex = hashCode(dataObj.getKey()) % table.m_currentCap;
        for (long unsigned int j = 0; j < dataList.size(); j++) { // check that hash is not in tabe
            while (dataObj.getKey() == (dataList.at(j).getKey())) { // hash is in table
                dataObj = Virus(sequencer(5, j + i), RndID.getRandNum()); // get new element
                j = 0; // restart for loop
            }
        }
        dataList.push_back(dataObj); // add to vector
        table.insert(dataObj); // add to table
        pass = pass && (table.m_currentSize == (i + 1)); // table size change
    }
    pass = pass && (table.m_currentSize == numLoop);
    pass = pass && (table.m_currNumDeleted == 0);
    pass = pass && (table.m_oldTable == nullptr);
    for (long unsigned int i = 0; i < dataList.size(); i++) { // check that elemnt is in correct location
        hashIndex = hashCode(dataList.at(i).getKey()) % table.m_currentCap;
        pass = pass && (table.m_currentTable[hashIndex] == dataList.at(i));
        if (pass == false) {
            break;
        }
    }

    for (long unsigned int i = 0; i < dataList.size(); i++) { // check stuff
        Virus virus = dataList.at(i); // make sure stuff is somehwere
        hashIndex = hashCode(dataList.at(i).getKey()) % table.m_currentCap;
        pass = pass && !(table.getVirus(virus.getKey(), virus.getID()) == EMPTY);
        pass = pass && (table.m_currentTable[hashIndex] == table.getVirus(virus.getKey(), virus.getID()));
    }
    return pass;
}

bool Tester::testGetVirusColliding(VDetect &table, vector<Virus> &dataList) {
    bool pass = true;
    Random RndID(MINID,MAXID);
    unsigned int hashIndex;
    int numLoop = 50;
    for (int i = 0; i < numLoop; i++) { // insert elements
        Virus dataObj = Virus(sequencer(5, i), RndID.getRandNum()); // make virus
        hashIndex = hashCode(dataObj.getKey()) % table.m_currentCap;
        for (long unsigned int j = 0; j < dataList.size(); j++) { // check that hash is not in tabe
            while (dataObj.getKey() == (dataList.at(j).getKey())) { // hash is in table
                dataObj = Virus(sequencer(5, j + i), RndID.getRandNum()); // get new element
                j = 0; // restart for loop
            }
        }
        dataList.push_back(dataObj); // add to vector
        table.insert(dataObj); // add to table
        pass = pass && (table.m_currentSize == (i + 1)); // table size change
    }
    pass = pass && (table.m_currentSize == numLoop);
    pass = pass && (table.m_currNumDeleted == 0);
    pass = pass && (table.m_oldTable == nullptr);
    for (long unsigned int i = 0; i < dataList.size(); i++) { // check that elemnt is in correct location
        hashIndex = hashCode(dataList.at(i).getKey()) % table.m_currentCap;
        pass = pass && (table.m_currentTable[hashIndex] == dataList.at(i));
        if (pass == false) {
            break;
        }
    }
    for (int i = 0; i < numLoop; i++) { // collision
        Virus dataObj = Virus(sequencer(5, i), RndID.getRandNum());
        hashIndex = hashCode(dataObj.getKey()) % table.m_currentCap;
        for (long unsigned int j = 0; j < dataList.size(); j++) {
            while ((dataObj.getKey() != dataList.at(j).getKey()) && (dataObj.getID() == dataList.at(j).getID())) {
                dataObj = Virus(sequencer(5, j + i), RndID.getRandNum());
                j = 0;
            }
        }
        dataList.push_back(dataObj); // add to vector
        table.insert(dataObj); // add to table
        pass = pass && (table.m_currentSize == (numLoop + i + 1)); // table size change
    }
    for (long unsigned int i = 0; i < dataList.size(); i++) { // checks for stuff due to collision 
        Virus virus = dataList.at(i);
        if ((int) i < numLoop) {
            hashIndex = hashCode(dataList.at(i).getKey()) % table.m_currentCap;
            pass = pass && !(table.getVirus(virus.getKey(), virus.getID()) == EMPTY);
            pass = pass && (table.m_currentTable[hashIndex] == table.getVirus(virus.getKey(), virus.getID()));
        } else {
            hashIndex = hashCode(dataList.at(i).getKey()) % table.m_currentCap;
            pass = pass && !(table.getVirus(virus.getKey(), virus.getID()) == EMPTY);
            pass = pass && !(table.m_currentTable[hashIndex] == table.getVirus(virus.getKey(), virus.getID()));
        }   
        if (pass == false) {
            break;
        }
    }
    return pass;
}

bool Tester::testRemoveNonColliding(VDetect &table, vector<Virus> &dataList) {
    bool pass = true;
    Random RndID(MINID,MAXID);
    unsigned int hashIndex;
    int numLoop = 50;
    for (int i = 0; i < numLoop; i++) { // insert elements
        Virus dataObj = Virus(sequencer(5, i), RndID.getRandNum()); // make virus
        hashIndex = hashCode(dataObj.getKey()) % table.m_currentCap;
        for (long unsigned int j = 0; j < dataList.size(); j++) { // check that hash is not in tabe
            while (dataObj.getKey() == (dataList.at(j).getKey())) { // hash is in table
                dataObj = Virus(sequencer(5, j + i), RndID.getRandNum()); // get new element
                j = 0; // restart for loop
            }
        }
        dataList.push_back(dataObj); // add to vector
        table.insert(dataObj); // add to table
        pass = pass && (table.m_currentSize == (i + 1)); // table size change
    }
    pass = pass && (table.m_currentSize == numLoop);
    pass = pass && (table.m_currNumDeleted == 0);
    pass = pass && (table.m_oldTable == nullptr);
    for (long unsigned int i = 0; i < dataList.size(); i++) { // check that elemnt is in correct location
        hashIndex = hashCode(dataList.at(i).getKey()) % table.m_currentCap;
        pass = pass && (table.m_currentTable[hashIndex] == dataList.at(i));
        if (pass == false) {
            break;
        }
    }
    for (int i = 0; i < 10; i++) { // removes some stuff
        pass = pass && (table.remove(dataList.at(i)));
        pass = pass && (table.getVirus(dataList.at(i).getKey(), dataList.at(i).getID()) == EMPTY);
        pass = pass && (table.m_currentTable[hashCode(dataList.at(i).getKey()) % table.m_currentCap] == DELETED);
    }
    return pass;
}

bool Tester::testRemoveColliding(VDetect &table, vector<Virus> &dataList) {
    bool pass = true;
    Random RndID(MINID,MAXID);
    unsigned int hashIndex;
    int numLoop = 50;
    for (int i = 0; i < numLoop; i++) { // insert elements
        Virus dataObj = Virus(sequencer(5, i), RndID.getRandNum()); // make virus
        hashIndex = hashCode(dataObj.getKey()) % table.m_currentCap;
        for (long unsigned int j = 0; j < dataList.size(); j++) { // check that hash is not in tabe
            while (dataObj.getKey() == (dataList.at(j).getKey())) { // hash is in table
                dataObj = Virus(sequencer(5, j + i), RndID.getRandNum()); // get new element
                j = 0; // restart for loop
            }
        }
        dataList.push_back(dataObj); // add to vector
        table.insert(dataObj); // add to table
        pass = pass && (table.m_currentSize == (i + 1)); // table size change
    }
    pass = pass && (table.m_currentSize == numLoop);
    pass = pass && (table.m_currNumDeleted == 0);
    pass = pass && (table.m_oldTable == nullptr);
    for (long unsigned int i = 0; i < dataList.size(); i++) { // check that elemnt is in correct location
        hashIndex = hashCode(dataList.at(i).getKey()) % table.m_currentCap;
        pass = pass && (table.m_currentTable[hashIndex] == dataList.at(i));
        if (pass == false) {
            break;
        }
    }
    for (int i = 0; i < numLoop; i++) { // collision
        Virus dataObj = Virus(sequencer(5, i), RndID.getRandNum());
        hashIndex = hashCode(dataObj.getKey()) % table.m_currentCap;
        for (long unsigned int j = 0; j < dataList.size(); j++) {
            while ((dataObj.getKey() != dataList.at(j).getKey()) && (dataObj.getID() == dataList.at(j).getID())) {
                dataObj = Virus(sequencer(5, j + i), RndID.getRandNum());
                j = 0;
            }
        }
        dataList.push_back(dataObj); // add to vector
        table.insert(dataObj); // add to table
        pass = pass && (table.m_currentSize == (numLoop + i + 1)); // table size change
    }
    for (int i = 0; i < 50; i++) { // remove stuff, some collision stuff some not
        if (i < 25) {
            pass = pass && (table.remove(dataList.at(i)));
            pass = pass && (table.getVirus(dataList.at(i).getKey(), dataList.at(i).getID()) == EMPTY);
            pass = pass && (table.m_currentTable[hashCode(dataList.at(i).getKey()) % table.m_currentCap] == DELETED);
        } else {
            hashIndex = table.getIndex(dataList.at(dataList.size() - i));
            pass = pass && (table.remove(dataList.at(dataList.size() - i)));
            pass = pass && (table.getVirus(dataList.at(dataList.size() - i).getKey(), dataList.at(dataList.size() - i).getID()) == EMPTY);
            pass = pass && (table.m_currentTable[hashIndex] == DELETED);
        }
    }
    return pass;
}

bool Tester::testRehashInsert(VDetect &table, vector<Virus> &dataList) {
    bool pass = true;
    Random RndID(MINID,MAXID);
    vector<Virus> added;
    int numLoop = ceil (0.5 * table.m_currentCap);
    int numTransfer = 0;
    unsigned int hashIndex;
    for (int i = 0; i < numLoop; i++) { // insert elements
        Virus dataObj = Virus(sequencer(5, i), RndID.getRandNum()); // make virus
        hashIndex = hashCode(dataObj.getKey()) % table.m_currentCap;
            int add = 0;
        for (long unsigned int j = 0; j < dataList.size(); j++) { // check that hash is not in tabe
            while (hashIndex == (hashCode(dataList.at(j).getKey()) % table.m_currentCap)) { // hash is in table
                dataObj = Virus(sequencer(5, j + i + add), RndID.getRandNum()); // get new element
                hashIndex = hashCode(dataObj.getKey()) % table.m_currentCap;
                add++;
                j = 0; // restart for loop
            }
        }
        dataList.push_back(dataObj); // add to vector
        table.insert(dataObj); // add to table
        if (table.m_oldTable == nullptr) {
            pass = pass && (table.m_currentSize == (i + 1)); // table size change
        } else {
            pass = pass && (table.m_currentSize == (table.totalTransferred + (table.tableTransfer - 1)));
        }
    }
    for (int i = 0; i < table.m_oldCap; i++) { // count stuff
        if ((table.m_oldTable[i] == EMPTY) || (table.m_oldTable[i] == DELETED)) {

        } else {
            numTransfer++; // tracker of num elemetns transfered or something
        }
    }
    int numDeleted = 0;
    for (int i = 0; i < table.m_oldCap; i++) {
        if (table.m_oldTable[i] == DELETED) {
            numDeleted++;
        }
    }
    int needToTransfer = table.m_oldSize - numDeleted; // elements that still need to be transferred
    pass = pass && (needToTransfer == numTransfer);
    for (int i = 0; i < table.m_currentCap; i++) { // loop for some reason, looks like to add to vector
        if ((table.m_currentTable[i] == EMPTY) || (table.m_currentTable[i] == DELETED)) {

        } else {
            added.push_back(table.m_currentTable[i]);
        }
    }
    for (long unsigned int i = 0; i < added.size(); i++) { // loop to make sure stuff is deleted
        hashIndex = hashCode(added.at(i).getKey()) % table.m_oldCap;
        pass = pass && (table.m_oldTable[hashIndex] == DELETED);
    }
    return pass;
}

bool Tester::testRehashInsertComplete(VDetect &table, vector<Virus> &dataList) {
    bool pass = true;
    Random RndID(MINID,MAXID);
    int numLoop = ceil (0.5 * table.m_currentCap) + 3;
    for (int i = 0; i < numLoop; i++) { // insert elements
        Virus dataObj = Virus(sequencer(5, i), RndID.getRandNum()); // make virus
        for (long unsigned int j = 0; j < dataList.size(); j++) { // check that hash is not in tabe
            while (dataObj.getKey() == (dataList.at(j).getKey())) { // hash is in table
                dataObj = Virus(sequencer(5, j + i), RndID.getRandNum()); // get new element
                j = 0; // restart for loop
            }
        }
        dataList.push_back(dataObj); // add to vector
        table.insert(dataObj); // add to table        
        if (table.m_oldTable == nullptr) {
            pass = pass && (table.m_currentSize == (i + 1)); // table size change
        } else {
            pass = pass && (table.m_currentSize == (table.totalTransferred + (table.tableTransfer - 1)));
        }
    }
    for (long unsigned int i = 0; i < dataList.size(); i++) { // make sure everythin is in table
        if ((table.getVirus(dataList.at(i).getKey(), dataList.at(i).getID()) == EMPTY) || (table.getVirus(dataList.at(i).getKey(), dataList.at(i).getID()) == DELETED)) {
            pass = false;
            break;
        }
    }
    pass = pass && (table.tableTransfer == 0);
    pass = pass && (table.m_oldTable == nullptr);
    pass = pass && (table.m_currentSize == numLoop);
    return pass;
}

bool Tester::testRehashRemove(VDetect &table, vector<Virus> &dataList) {
    bool pass = true;
    Random RndID(MINID,MAXID);
    int numLoop = 300;
    for (int i = 0; i < numLoop; i++) { // insert elements
        Virus dataObj = Virus(sequencer(5, i), RndID.getRandNum()); // make virus
        dataList.push_back(dataObj); // add to vector
        table.insert(dataObj); // add to table        
        if (table.m_oldTable == nullptr) {
            pass = pass && (table.m_currentSize == (i + 1)); // table size change
        } else {
            pass = pass && (table.m_currentSize == (table.totalTransferred + (table.tableTransfer - 1)));
        }
    }
    pass = pass && (table.m_currentSize == numLoop);
    pass = pass && (table.m_currNumDeleted == 0);
    pass = pass && (table.m_oldTable == nullptr);
    for (int i = 0; i < (numLoop * 0.8); i++) {
        pass = pass && (table.remove(dataList.at(i)));
    }
    pass = pass && (table.m_oldTable != nullptr);
    pass = pass && (table.m_oldNumDeleted == (numLoop * 0.8));
    pass = pass && (table.m_currentSize == (floor ((numLoop - numLoop * 0.8) *0.25)));
    pass = pass && (table.m_currentCap == (table.findNextPrime(4 * (table.m_oldSize - table.m_oldNumDeleted))));
    return pass;
}

bool Tester::testRehashRemoveComplete(VDetect &table, vector<Virus> &dataList) {
    bool pass = true;
    Random RndID(MINID,MAXID);
    vector<Virus> deleted;
    int numLoop = 300;
    for (int i = 0; i < numLoop; i++) { // insert elements
        Virus dataObj = Virus(sequencer(5, i), RndID.getRandNum()); // make virus
        dataList.push_back(dataObj); // add to vector
        table.insert(dataObj); // add to table        
        if (table.m_oldTable == nullptr) {
            pass = pass && (table.m_currentSize == (i + 1)); // table size change
        } else {
            pass = pass && (table.m_currentSize == (table.totalTransferred + (table.tableTransfer - 1)));
        }
    }
    pass = pass && (table.m_currentSize == numLoop);
    pass = pass && (table.m_currNumDeleted == 0);
    pass = pass && (table.m_oldTable == nullptr);
    int j = 0;
    for (int i = 0; i < (numLoop * 0.8) + 3; i++) {
        if (table.tableTransfer < 1) {
            pass = pass && (table.remove(dataList.at(i)));
        } else if ((table.tableTransfer == 1 && (deleted.size() == 0))) {
            for (int j = 0; j < table.m_oldCap; j++) {
                if ((table.m_oldTable[j] == EMPTY || (table.m_oldTable[j] == DELETED))) {

                } else {
                    deleted.push_back(table.m_oldTable[j]);
                }
            }
            pass = pass && (deleted.size() == (floor (((numLoop - (numLoop * .8)) - ((numLoop - (numLoop * .8)) * .25)))));
            pass = pass && (table.remove(deleted.at(j)));
            j++;
        } else {
            pass = pass && (table.remove(deleted.at(j + (((numLoop - (numLoop * .8)) * .25)))));
            j++;
        }
    }
    pass = pass && (table.tableTransfer == 0);
    pass = pass && (table.m_oldTable == nullptr);
    pass = pass && (table.m_currentSize == (numLoop - (numLoop * 0.8) - 2));
    return pass;
}

unsigned int hashCode(const string str) {
   unsigned int val = 0 ;
   const unsigned int thirtyThree = 33 ;  // magic number from textbook
   for (long unsigned int i = 0 ; i < str.length(); i++)
      val = val * thirtyThree + str[i] ;
   return val ;
}

string sequencer(int size, int seedNum){
    //this function returns a random DNA sequence
    string sequence = "";
    Random rndObject(0,3);
    rndObject.setSeed(seedNum);
    for (int i=0;i<size;i++){
        sequence = sequence + ALPHA[rndObject.getRandNum()];
    }
    return sequence;
}