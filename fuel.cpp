// UMBC - CMSC 341 - Spring 2023 - Proj1// UMBC - CMSC 341 - Spring 2023 - Proj0
/********************************************************
** File: fuel.cpp
** Project: CMSC 341 Project 0
** Author: Matthew Green
** Date: 07/03/2021
** Email: mgreen11@umbc.edu
**
** Description: Defines the functions set in the .h file
**********************************************************/
#include "fuel.h"

FuelSys::FuelSys(){
    m_current = nullptr;  // initialize values
}

FuelSys::~FuelSys(){
    if (m_current != nullptr) { // destroy everything if system has stuff
        Tank *temp = m_current; // set pointer as trackers
        Tank *curr = temp;
        do { // loop through circular link deleting everything
            if (curr->m_pumps != nullptr) { // check if tank as any pumps
                Pump *tempPump = curr->m_pumps; // set pointer as trackers
                Pump *currPump = tempPump;
                while (currPump != nullptr) { // loop through linked list deleting every node
                    tempPump = tempPump->m_next; // move to next node
                    delete currPump; // delete current node
                    currPump = tempPump; // set curr node to next node
                }
                curr->m_pumps = nullptr; // set everything as nullptr
                tempPump = nullptr;
                currPump = nullptr;
            }
            temp = temp->m_next; // move to next node
            delete curr; // delete current node
            curr = temp; // move to next node
        } while (temp != m_current); 
        temp = nullptr; // set everything to nullptr
        curr = nullptr;
        m_current = nullptr;
    }
}

bool FuelSys::addTank(int tankID, int tankCap, int tankFuel = 0) {
    bool added = false; // create bool function for return value
    if (findTank(tankID)) { // if true tank id is already used
        cout << "Can not add tank as ID already exists" << endl;
    } else if (tankID < 0) {
        cout << "ID has to be a Whole Number" << endl;
    } else if (tankCap < MINCAP) { // tank capacity can not be less then the minimum capacity
        cout << "Tank cap is to small" << endl;
    } else if (tankFuel > tankCap) { // amount of fuel can not be greater then the capacity
        cout << "Amount of fuel cannot exceed tank capacity" << endl;
    } else if (tankFuel < 0) {
        cout << "Amount of fuel cannot be less then 0" << endl;
    } else { // add tank to linked list
        Tank *newTank = new Tank(tankID, tankCap, tankFuel); // create new tank
        if (m_current == nullptr) { // linked list list empty so this is first node in list
            m_current = newTank; // set current to new node
            newTank->m_next = newTank; // have node point back to itself to make it circular
        } else {
            newTank->m_next = m_current->m_next; // 
            m_current->m_next = newTank; // insert the new tank into the list
            m_current = newTank; // set current to new take
        }
        added = true;// set return value to true
    }
    return added;
}

bool FuelSys::removeTank(int tankID){
    bool removed = false; // create bool function for return value
    if (findTank(tankID)) { // delete if tank id exist in link list
        Tank *temp = m_current; // set tracker pointer
        if (temp == temp->m_next) { // only one node exist in link list
                if (temp->m_pumps != nullptr) { // check if any pumps exist
                    Pump *tempPump = temp->m_pumps; // set tracker pointers
                    Pump *currPump = tempPump;
                    while (currPump != nullptr) {  // loop through linked list until empty
                        tempPump = tempPump->m_next; // move pointer to next node
                        delete currPump; // delete current node
                        currPump = tempPump; // move to next node
                    }
                    temp->m_pumps = nullptr; // set values to nullptr
                    tempPump = nullptr;
                    currPump = nullptr;
                }
            delete temp; // delete tank
            m_current = nullptr; // set value to nullptr
            removed = true;
        } else { // tank has more then one node
            if (temp->m_next->m_pumps != nullptr) { // check if any pumps exist. m_next is use as findtank returns the node before the target node
                Pump *tempPump = temp->m_next->m_pumps; // set tracker pointer
                Pump *currPump = tempPump;
                while (currPump != nullptr) { // loop through linked list until empty
                    tempPump = tempPump->m_next; // move pointer to next node
                    delete currPump; // delete current node
                    currPump = tempPump; // move to next node
                }
                temp->m_next->m_pumps = nullptr;  // set values to nullptr
                tempPump = nullptr;
                currPump = nullptr;
            }
            temp = temp->m_next; // set to target node to be deleted
            m_current->m_next = temp->m_next; // isolate target node from list
            delete temp; // delete target node
            removed = true; 
        }

    }
    return removed;
}

bool FuelSys::findTank(int tankID){
    bool found = false; // create bool function for return value
    Tank *temp = m_current;  // set tracker pointer
    if (temp == nullptr) { // list is empty
        cout << "There are no tanks" << endl;
    } else if (tankID == temp->m_tankID) { // node wanted to be found is the current one
        do { // loop until list until second to last node, do-while loop so loop goes through once
            temp = temp->m_next;
        } while (temp->m_next != m_current);
        m_current = temp; // set current to temp, which is node before target node
        found = true;
    } else { // target node is somewhere in the middle
        while (temp->m_next != m_current) {  // loop until returning to start
            if (temp->m_next->m_tankID == tankID) { // target node is found
                m_current = temp; // sets current to node before target node
                found = true; 
                break; // breaks out of while loop, alternative could be early return
            }
            temp = temp->m_next; // moves on to next node
        }
    }
    return found;
}

bool FuelSys::addPump(int tankID, int pumpID, int targetTank){
    bool added = false; // create bool function for return value
    if (pumpID < 0) {
        cout << "Pump ID must be a whole number" << endl;
    } else if (tankID == targetTank) {
        cout << "Target tank can not be tank ID" << endl;
    } else if (findTank(targetTank) && findTank(tankID)) { // make sure that node exists
        Pump *newPump = new Pump(pumpID,targetTank); // creates new pump
        if (m_current->m_next->m_pumps == nullptr) { // no pump exists in tank
            m_current->m_next->m_pumps = newPump; // set pumps to new pump which is the first element in list
            added = true;
        } else { // list already has some elements
            Pump *temp = m_current->m_next->m_pumps; // tracker pointer
            while (temp->m_next != nullptr) { // goes through link list
                if (temp->m_pumpID == pumpID) { // checks all nodes except last one if pumpID exists
                    cout << "Can not add pump as ID is already in use" << endl;
                    delete newPump; // delete pump as it is not being added
                    break;
                } 
                temp = temp->m_next; // move to next pump in list
            }
            if ((temp->m_pumpID == pumpID) && (temp->m_next == nullptr)) { // check the last node if pumpID is it
                cout << "Can not add pump as ID is already in use" << endl;
                delete newPump; // delete pump as it is not being added
            } else if (temp->m_next == nullptr) { // otherwise add it the new pump to the link list
                newPump->m_next = m_current->m_next->m_pumps;
                m_current->m_next->m_pumps = newPump;
                added = true;
            }
        }
    }
    return added;
}

bool FuelSys::removePump(int tankID, int pumpID){
    bool removed = false; // create bool function for return value
    if (findTank(tankID)) { // make sure that tank exist
        if (m_current->m_next->m_pumps != nullptr) { // check if there are any pumps
            Pump *temp = m_current->m_next->m_pumps; // tracker
            Pump *prev = temp;
            while (temp != nullptr) { // go through link list
                if (temp->m_pumpID == pumpID) { // pump id exist in list
                    if ((temp == m_current->m_next->m_pumps)) { // target pump is first in list
                        m_current->m_next->m_pumps = temp->m_next; // change the head of list
                        delete temp; // delete node
                        removed = true;
                    } else if (temp->m_next == nullptr) { // target pump is last in list
                        delete temp; // delete node
                        temp = nullptr; // set to nullptr
                        removed = true;
                    } else { // target pump is in middle of list
                        prev->m_next = temp->m_next;
                        delete temp;; // delete node
                        removed = true;
                    }
                    break;
                }
                prev = temp;
                temp = temp->m_next; // go to next element in list
            }
        }
    }
    return removed;
}

int FuelSys::totalFuel() const{
    int totalFuel = 0; // create bool function for return value
    Tank *temp = m_current; // tracker node
    if (m_current != nullptr) { // check if tanks exist
        do { // loop through list until back to current
            totalFuel = totalFuel + temp->m_tankFuel; // add to total
            temp = temp->m_next; // move to next node
        } while (temp != m_current);
    }
    return totalFuel;
}
bool FuelSys::drain(int tankID, int pumpID, int fuel){
    bool drained = false; // create bool function for return value
    if (fuel <= 0) {
        cout << "Can not transfer less then 0 fuel" << endl;
    } else if (findTank(tankID)) { // make sure that the origin tank exist
        if (m_current->m_next->m_pumps != nullptr) { // make sure that origin tank has pumps
            Tank *tempTank = m_current->m_next; // trackers
            Pump *tempPump = m_current->m_next->m_pumps;
            while (tempPump != nullptr) { // go through linked list looking for pump
                if (tempPump->m_pumpID == pumpID) {
                    break;
                }
                tempPump = tempPump->m_next; // go to next element 
            }
            if (tempPump == nullptr) {
                cout << "Pump does not exist" << endl;
            }   else if (tempPump->m_pumpID == pumpID) { // transfer if pump exists
                    if (findTank(tempPump->m_pumpID)) {  // make sure transfer tank exist
                        if (m_current->m_next->m_tankFuel < m_current->m_next->m_tankCapacity) { // transfer if target tank is not at capacity
                            int fuelHave = tempTank->m_tankFuel; // int to calulate amount of current fuel
                            int fuelWant = (m_current->m_next->m_tankCapacity - m_current->m_next->m_tankFuel); // calculate amount of fuel that can be transfer
                            if (fuelWant <= fuel) { // fuel being transfered is greater then or equal to the capacity of tank
                                if (fuelHave > fuelWant) { // amount of fuel in tank is more then the capacity of fuel wanted
                                    tempTank->m_tankFuel = tempTank->m_tankFuel - fuelWant; // change value of fuel in both tank
                                    m_current->m_next->m_tankFuel = m_current->m_next->m_tankCapacity;
                                    cout << "Target tank reached capacity so not all fuel could be transfered" << endl;
                                } else if (fuelHave < fuel) { // amount of fuel in tank is less then the capacity of fuel wanted
                                    tempTank->m_tankFuel = 0; // change value of fuel in both tank
                                    m_current->m_next->m_tankFuel = m_current->m_next->m_tankFuel + fuelHave;
                                    cout << "Target tank could not reach capacity as transfer tank did not have enough" << endl;
                                } else { // amount of fuel in tank is the capcity of fuel wanted
                                    tempTank->m_tankFuel = 0; // change value of fuel in both tank
                                    m_current->m_next->m_tankFuel = m_current->m_next->m_tankCapacity;
                                    cout << "Target tank is full and transfer tank is empty" << endl;
                                }
                            } else { // fuel being transfer is less then the capacity of the tank
                                if (fuelHave < fuel) { // amount of fuel in tank is less then the capacity of fuel wanted
                                    tempTank->m_tankFuel = 0; // change value of fuel in both tank
                                    m_current->m_next->m_tankFuel = m_current->m_next->m_tankFuel + fuelHave;
                                    cout << "Target tank could not reach capacity as transfer tank did not have enough" << endl;
                                } else { // fuel being transfered is the amount request
                                    tempTank->m_tankFuel = tempTank->m_tankFuel - fuel; // change value of fuel in both tank
                                    m_current->m_next->m_tankFuel = m_current->m_next->m_tankFuel + fuel;
                                    cout << "Target tank gained fuel desired" << endl;
                                }
                            }
                            drained = true;
                        } else {
                            cout << "Target tank is already full" << endl;
                        }
                    } 
                } else {
                cout << "Pump does not exist" << endl;
            }
        }
    } else {
        cout << "Tank does not exist" << endl;
    }
    return drained;
}

bool FuelSys::fill(int tankID, int fuel){
    bool filled = false; // create bool function for return value
    if (fuel <= 0) {
        cout << "Cannot add less then 0 fuel" << endl;
    } else if (findTank(tankID)) { // check if target tank exists
        int maxFuel = m_current->m_next->m_tankCapacity - m_current->m_next->m_tankFuel;
        if (fuel > maxFuel) {
            m_current->m_next->m_tankFuel = m_current->m_next->m_tankCapacity; // adds amount of fuel to tank
            filled = true;
        } else {
            m_current->m_next->m_tankFuel = m_current->m_next->m_tankFuel + fuel; // adds amount of fuel to tank
            filled = true;
        }
    }
    return filled;
}

// there's probably some way to do this by calling addTank and addPump, but I was to tired to find a way
const FuelSys &FuelSys::operator=(const FuelSys &rhs){
    if (this == &rhs) { // protect against self assignment
        return *this;
    } else if (rhs.m_current == nullptr) { // if trying to assign to empty object, just destroy object
        this->~FuelSys();
    } else {
        this->~FuelSys(); // destory object to delete any memory that might be used
        Tank *temp = rhs.m_current->m_next; // tracker 
        do { // loop through link list
            Tank *newTank = new Tank(temp->m_tankID, temp->m_tankCapacity, temp->m_tankFuel); // create new tank
            if (this->m_current == nullptr) { // first tank in list
                this->m_current = newTank;
                newTank->m_next = this->m_current;
                if (temp->m_pumps != nullptr) { // check if pump exist
                    Pump *tempPump = temp->m_pumps; // tracker
                    do { // loop through pump list
                        Pump *newPump = new Pump(tempPump->m_pumpID, tempPump->m_target); // create new pump
                        if (this->m_current->m_pumps == nullptr) {
                            this->m_current->m_pumps = newPump;
                        } else {
                            Pump *newTempPump = this->m_current->m_pumps; // tracker
                            while (newTempPump->m_next != nullptr) { // travel to end of list to add new pump
                                newTempPump = newTempPump->m_next; // move to next node
                            }
                            newTempPump->m_next = newPump; // add pump to list
                        }
                        tempPump = tempPump->m_next; // move to next node to be added to pump list
                    } while (tempPump != nullptr);
                } 
            } else { // not first tank
                    newTank->m_next = m_current->m_next;
                    m_current->m_next = newTank;
                    m_current = newTank;
                if (temp->m_pumps != nullptr) { // check if pumps exist
                    Pump *tempPump = temp->m_pumps; // tracker
                    do { // loop through pump list
                        Pump *newPump = new Pump(tempPump->m_pumpID, tempPump->m_target); // create new pump
                        if (this->m_current->m_pumps == nullptr) { // first pump in list
                            this->m_current->m_pumps = newPump;
                        } else { // not first pump
                            Pump *newTempPump = this->m_current->m_pumps;
                            while (newTempPump->m_next != nullptr) { // travel to end of list to add new pump
                                newTempPump = newTempPump->m_next; // move to next node
                            }
                            newTempPump->m_next = newPump; // add pump to list
                        }
                        tempPump = tempPump->m_next; // move to next node to be added to pump list
                    } while (tempPump != nullptr);
                }
            }
            temp = temp->m_next; // move to next node
        } while (temp != rhs.m_current->m_next);
    }
    return *this;
}

// Not my stuff
void FuelSys::dumpSys() const{
    if (m_current != nullptr){
        Tank* tempTank = m_current->m_next;//we start at front item
        //we continue visting nodes until we reach the cursor
        while(m_current != nullptr && tempTank != m_current){
            cout << "Tank " << tempTank->m_tankID << "(" << tempTank->m_tankFuel << " kg)" << endl;
            // now dump the targets for all pumps in this tank
            // we need to traverse the list of pumps
            dumpPumps(tempTank->m_pumps);
            tempTank = tempTank->m_next;
        }
        //at the end we visit the cursor (current)
        //this also covers the case that there is only one item
        cout << "Tank " << m_current->m_tankID << "(" << m_current->m_tankFuel << " kg)" << endl;
        dumpPumps(tempTank->m_pumps);
        cout << "The current tank is " << m_current->m_tankID << endl;
    }
    else
        cout << "There is no tank in the system!\n\n";
}

void FuelSys::dumpPumps(Pump* pumps) const{
    // this traverses the linked list to the end
    Pump* tempPump = pumps;
    while (tempPump != nullptr){
        cout << " => pump " << tempPump->m_pumpID << "(To tank " << tempPump->m_target << ")" << endl;
        tempPump = tempPump->m_next;
    }
}