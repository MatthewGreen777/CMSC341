// Matthew Green, SN 93970
// CMSC 341 - Spring 2023 - Project 4
#include "vdetect.h"
VDetect::VDetect(int size, hash_fn hash, prob_t probing = DEFPOLCY) {
    if (size < MINPRIME) { // size must be greater than minprime
        m_currentCap = MINPRIME; // set to minprime
    } else if (size > MAXPRIME) { // size must be less then maxprime
        m_currentCap = MAXPRIME; // set to maxprime
    } else { // size is between min and max prime
        if (isPrime(size)) { // number is a prime
            m_currentCap = size; // set size
        } else { // number is not a prime
            m_currentCap = findNextPrime(size); // set size to next prime
        }
    }
    // set all other variables
    m_hash = hash; 
    m_currProbing = probing;
    m_currentSize = 0;
    m_currNumDeleted = 0;
    m_newPolicy = probing;
    m_currentTable = new Virus[m_currentCap];
    for (int i = 0; i < m_currentCap; i++) { // initialize array
        m_currentTable[i] = EMPTY;
    }

    m_oldTable = nullptr;
    m_oldProbing = NONE;
    m_oldCap = 0;
    m_oldSize = 0;
    m_oldNumDeleted = 0;

    tableTransfer = 0;
    totalTransferred = 0;
    continuePosition = 0;
}

VDetect::~VDetect() {
    // deallocate memory 
    delete[] m_currentTable; 
    delete[] m_oldTable;
}

void VDetect::changeProbPolicy(prob_t policy) {
    m_newPolicy = policy; // policy change when rehash
}

bool VDetect::insert(Virus virus) {
    bool inserted = true;
    if ((virus.getID() > MAXID) || (virus.getID() < MINID)) { // check if virus id is valid
        inserted = false;
    }
    if (getVirus(virus.getKey(), virus.getID()) == virus) { // virus is already in table
        inserted = false;
    } else {
        int hashIndex = m_hash(virus.getKey()) % m_currentCap; // compute hash
        int numProbes = 0; // probe counter
        while ((numProbes < m_currentCap) && (inserted == true)) { // loop if probes is less than cap or until inserted
            if ((m_currentTable[hashIndex] == EMPTY) || (m_currentTable[hashIndex] == DELETED)) { // check if current slot is empty or deleted
                m_currentTable[hashIndex] = virus; // insert virus and update counters
                if (m_currentTable[hashIndex] == DELETED) { // decrease num deleted if index was deleted
                    m_currNumDeleted--;
                } else {
                    m_currentSize++; // update size
                }
                break; // escape loop
            }
            if (m_currentTable[hashIndex] == virus) { // check if current slot contains virus
                inserted = false; // pointless since this is technically checked already, but I'm leaving this in
            }
            // resolve collisiton by probing to next spot
            numProbes++;
            switch (m_currProbing) {
                case NONE:
                    inserted = false;
                    break;
                case QUADRATIC:
                    hashIndex = ((m_hash(virus.getKey()) % m_currentCap) + (numProbes * numProbes)) % m_currentCap;
                    break;
                case DOUBLEHASH:
                    hashIndex = ((m_hash(virus.getKey()) % m_currentCap + numProbes * (11- (m_hash(virus.getKey()) % 11)))) % m_currentCap;
                    break;
            }
        }
    }

    if (((lambda() >= 0.5) && (m_currentCap != MAXPRIME)) || (tableTransfer != 0)) { // rehash due to labda >= 0.5 or entire table has not been transfered
        rehashTable();
    }
    return inserted;
}

bool VDetect::remove(Virus virus) {
    bool removed = false; // variables
    int hashIndex = m_hash(virus.getKey()) % m_currentCap;
    int probes = 0;
    Virus foundVirus = getVirus(virus.getKey(), virus.getID());
    if (foundVirus == EMPTY) { // can't delete something that does not exist
        removed = false;
    } 
    if ((m_currentSize == 0) && (m_oldSize == 0)) {
        return false;
    }
    for (int i = 0; i < m_currentCap; i++) { // lopp through current table
        if ((m_currentTable[hashIndex].getID() == virus.getID()) && (m_currentTable[hashIndex].getKey() == virus.getKey())) { // index is in table
            m_currentTable[hashIndex] = DELETED; // mark as deleted
            removed = true; // change value
            m_currNumDeleted++;
            break; // escape for loop
        } else if (m_currentTable[hashIndex] == EMPTY) { // empty space so element is not in table
            break; // escape table
        }        
        probes++; // probing needed due to collition or deleted index, increase probe counter
        switch(m_currProbing) { // probe depening on policy
            case NONE:
                break;
            case QUADRATIC:
                hashIndex = (((m_hash(virus.getKey())) % m_currentCap) + (probes * probes)) % m_currentCap;
                break;
            case DOUBLEHASH:
                hashIndex = ((m_hash(virus.getKey()) % m_currentCap + probes * (11- (m_hash(virus.getKey()) % 11)))) % m_currentCap;
                break;
        }
    }
    if ((removed == false) && (m_oldTable != nullptr)) { // not in current table, check old table if exists
        probes = 0; // reset
        hashIndex = m_hash(virus.getKey()) % m_oldCap; // reset
        for (int i = 0; i < m_oldCap; i++) { // loop through old table
            if ((m_oldTable[hashIndex].getID() == virus.getID()) && (m_oldTable[hashIndex].getKey() == virus.getKey())) { // element is in old table
                m_oldTable[hashIndex] = DELETED; // mark as deleted
                removed = true; // change value
                m_oldNumDeleted++;
                break; // escape loop
            } else if (m_oldTable[hashIndex] == EMPTY) { // element not in table
                break; // escape loop
            }        
            probes++; // probing needed due to collision or deleted index, increase probe counter
            switch(m_oldProbing) { // probe depending on old policy
                case NONE:
                    break;
                case QUADRATIC:
                    hashIndex = ((m_hash(virus.getKey()) % m_oldCap) + (probes * probes)) % m_oldCap;
                    break;
                case DOUBLEHASH:
                    hashIndex = ((m_hash(virus.getKey()) % m_oldCap + probes * (11- (m_hash(virus.getKey()) % 11)))) % m_oldCap;
                    break;
            }
        }
    }

    if (((deletedRatio() >= 0.8) && (m_currentCap != MINPRIME)) || (tableTransfer != 0)) { // rehash if ratio is aboe or equal to 0.8 or table transfer has not been completed
        rehashTable(); // call function
    }
    return removed; // return bool
}

Virus VDetect::getVirus(string key, int id) const {
    Virus returnVirus = EMPTY; // variables
    int hashValue = m_hash(key) % m_currentCap;
    int probes = 0;
    for (int i = 0; i < m_currentCap; i++) { // search through current table
        if ((m_currentTable[hashValue].getID() == id) && (m_currentTable[hashValue].getKey() == key)) { // variable in table
            returnVirus = m_currentTable[hashValue]; // set return value to this
            break; // escape loop
        } else if (m_currentTable[hashValue] == EMPTY) { // virus not in table
            break; // escape loop
        }
        probes++; // collision or deleted index, increase num
        switch(m_currProbing) { // probe depending on policy
            case NONE:
                break;
            case QUADRATIC:
                hashValue = (((m_hash(key)) % m_currentCap) + (probes * probes)) % m_currentCap;
                break;
            case DOUBLEHASH:
                hashValue = ((m_hash(key) % m_currentCap + probes * (11 - (m_hash(key) % 11)))) % m_currentCap;
                break;
        }
    }

    if (m_oldTable != nullptr) { // check old table for virus if an old table exist
        probes = 0; // reset
        hashValue = m_hash(key) % m_oldCap;
        for (int i = 0; i < m_oldCap; i++) {
            if ((m_oldTable[hashValue].getID() == id) && (m_oldTable[hashValue].getKey() == key)) { // in old table
                returnVirus = m_oldTable[hashValue]; // change return value
                break; // escape loop
            } else if ((returnVirus.getID() != EMPTY.getID()) && (returnVirus.getKey() == EMPTY.getKey())) { // element not in table
                break; // escape loop
            } else {
                probes++; // collision or deleted index, increase num
                switch (m_oldProbing) {  // probe depending on old policy
                    case NONE:
                        break;
                    case QUADRATIC:
                        hashValue = (((m_hash(key) % m_oldCap)) + (probes * probes)) % m_oldCap;
                        break;
                    case DOUBLEHASH:
                        hashValue = ((m_hash(key) % m_oldCap + probes * (11 - (m_hash(key) % 11)))) % m_oldCap;
                        break;
                }
            }
        }
    }

    return returnVirus;
}

float VDetect::lambda() const {
    float loadFacter = float(m_currentSize) / float(m_currentCap);
    return loadFacter;
}

float VDetect::deletedRatio() const {
    float deletedFacter = float(m_currNumDeleted) / float(m_currentSize);
    return deletedFacter;
}

void VDetect::dump() const {
    cout << "Dump for the current table: " << endl;
    if (m_currentTable != nullptr)
        for (int i = 0; i < m_currentCap; i++) {
            cout << "[" << i << "] : " << m_currentTable[i] << endl;
        }
    cout << "Dump for the old table: " << endl;
    if (m_oldTable != nullptr)
        for (int i = 0; i < m_oldCap; i++) {
            cout << "[" << i << "] : " << m_oldTable[i] << endl;
        }
}

bool VDetect::isPrime(int number){
    bool result = true;
    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0) {
            result = false;
            break;
        }
    }
    return result;
}

int VDetect::findNextPrime(int current){
    //we always stay within the range [MINPRIME-MAXPRIME]
    //the smallest prime starts at MINPRIME
    if (current < MINPRIME) current = MINPRIME-1;
    for (int i=current; i<MAXPRIME; i++) { 
        for (int j=2; j*j<=i; j++) {
            if (i % j == 0) 
                break;
            else if (j+1 > sqrt(i) && i != current) {
                return i;
            }
        }
    }
    //if a user tries to go over MAXPRIME
    return MAXPRIME;
}

ostream& operator<<(ostream& sout, const Virus &virus ) {
    if (!virus.m_key.empty())
        sout << virus.m_key << " (ID " << virus.m_id << ")";
    else
        sout << "";
  return sout;
}

bool operator==(const Virus& lhs, const Virus& rhs){
    return ((lhs.m_key == rhs.m_key) && (lhs.m_id == rhs.m_id));
}

void VDetect::rehashTable() {
    if (tableTransfer == 0) { // first transfer
        m_oldProbing = m_currProbing; // set old probing policy
        m_currProbing = m_newPolicy; // set current probing policy to whatever the new one is
        int newSize = findNextPrime(4 * (m_currentSize - m_currNumDeleted)); // set new table size
        Virus* newTable = new Virus[newSize]; // create array
        for (int i = 0; i < newSize; i++) { // initialize array
            newTable[i] = EMPTY;
        }
        int numTransferred = 0; // keep track of element transferred
        int toTransfer = floor (0.25 * (m_currentSize - m_currNumDeleted)); // number of elemetns to transfer to new table

        while (numTransferred != toTransfer) { // loop until number of transferred element reaches requirement, 25%
            if ((m_currentTable[continuePosition] == EMPTY) || (m_currentTable[continuePosition] == DELETED)) { // skip empty or deleted spots
                // do nothing
            } else { // index has something
                bool inserted = true;  // variables
                int hashIndex = m_hash(m_currentTable[continuePosition].getKey()) % newSize;
                int numProbes = 0;
                while ((numProbes < m_currentCap) && (inserted == true)) { // loop until inserted
                    if ((newTable[hashIndex] == EMPTY) || (newTable[hashIndex] == DELETED)) { // check if current slot is empty or deleted
                        newTable[hashIndex] = m_currentTable[continuePosition]; // insert virus to new table
                        m_currentTable[continuePosition] = DELETED; // delete elemnt in old table
                        numTransferred++; // increase value
                        break; // escape loop
                    }      
                    numProbes++;// resolve collisiton by probing to next spot
                    switch (m_currProbing) {
                        case NONE:
                            inserted = false;
                            break;
                        case QUADRATIC:
                            hashIndex = ((m_hash(m_currentTable[continuePosition].getKey()) % newSize) + (numProbes * numProbes)) % newSize;
                            break;
                        case DOUBLEHASH:
                            hashIndex = ((m_hash(m_currentTable[continuePosition].getKey()) % newSize + numProbes * (11- (m_hash(m_currentTable[continuePosition].getKey()) % 11)))) % newSize;
                            break;
                    }
                }
            }
            continuePosition = continuePosition + 1; // increase position in old table
        }
        // chage values
        m_oldTable = m_currentTable;
        m_oldCap = m_currentCap;
        m_oldSize = m_currentSize;
        m_oldNumDeleted = m_currNumDeleted;
        m_oldProbing = m_currProbing;

        m_currentTable = newTable;
        m_currentCap = newSize;
        m_currentSize = numTransferred;
        m_currNumDeleted = 0;
        totalTransferred = numTransferred;
    } else { // not first transfer
        int numTransferred = 0; // read above comments, just same 
        int toTransfer = floor (0.25 * (m_oldSize - m_oldNumDeleted));
        while ((numTransferred != toTransfer) && (continuePosition < m_oldCap)) {
            if ((m_oldTable[continuePosition] == EMPTY) || (m_oldTable[continuePosition] == DELETED)) {
                // do nothing
            } else {
                bool inserted = true;
                int hashIndex = m_hash(m_oldTable[continuePosition].getKey()) % m_currentCap;
                int numProbes = 0;
                while ((numProbes < m_currentCap) && (inserted == true)) {
                    if ((m_currentTable[hashIndex] == EMPTY) || (m_currentTable[hashIndex] == DELETED)) {
                        m_currentTable[hashIndex] = m_oldTable[continuePosition];
                        m_oldTable[continuePosition] = DELETED;
                        numTransferred++;
                        break;
                    }
                    numProbes++;
                    switch (m_currProbing) {
                        case NONE:
                            inserted = false;
                            break;
                        case QUADRATIC:
                            hashIndex = ((m_hash(m_oldTable[continuePosition].getKey()) % m_currentCap) + (numProbes * numProbes)) % m_currentCap;
                            break;
                        case DOUBLEHASH:
                            hashIndex = ((m_hash(m_oldTable[continuePosition].getKey()) % m_currentCap + numProbes * (11- (m_hash(m_oldTable[continuePosition].getKey()) % 11)))) % m_currentCap;
                            break;
                    }
                }
            }
            continuePosition = continuePosition + 1;
        }
        m_currentSize = m_currentSize + numTransferred; // incrase current table size
        totalTransferred = totalTransferred + numTransferred; // update total tranferred
    }
    tableTransfer++; // keep track of how many transferred happend, 
    if (tableTransfer > 3) { // final transferred happened 
        int add = (m_oldSize - m_oldNumDeleted) - totalTransferred; // number that still needs to be transferred
        if (totalTransferred != (m_oldSize - m_oldNumDeleted)) { // do this if we still need to transfer stuff
            int numNeeded = (m_oldSize - m_oldNumDeleted) - totalTransferred; // number that still need to be trasnferred
            while ((numNeeded >= 0) && (continuePosition < m_oldCap)) { // loop until everything else has been transferred
                if ((m_oldTable[continuePosition] == EMPTY) || (m_oldTable[continuePosition] == DELETED)) { // everything in this loop is same as above
                    // do nothing
                } else {
                    bool inserted = true;
                    int hashIndex = m_hash(m_oldTable[continuePosition].getKey()) % m_currentCap;
                    int numProbes = 0;
                    while ((numProbes < m_currentCap) && (inserted = true)) {
                        if ((m_currentTable[hashIndex] == EMPTY) || (m_currentTable[hashIndex] == DELETED)) {
                            m_currentTable[hashIndex] = m_oldTable[continuePosition];
                            m_oldTable[continuePosition] = DELETED;
                            numNeeded--;
                            break;
                        }
                        numProbes++; // resolve collisiton by probing to next spot
                        switch (m_currProbing) {
                            case NONE:
                                inserted = false;
                                break;
                            case QUADRATIC:
                                hashIndex = ((m_hash(m_oldTable[continuePosition].getKey()) % m_currentCap) + (numProbes * numProbes)) % m_currentCap;
                                break;
                            case DOUBLEHASH:
                                hashIndex = (((m_hash(m_oldTable[continuePosition].getKey()) % m_currentCap) + (numProbes * (11- (m_hash(m_oldTable[continuePosition].getKey()) % 11))))) % m_currentCap;
                                break;
                        }
                    }
                }
                continuePosition = continuePosition + 1;
            }
        }
        m_currentSize = m_currentSize + add; // update
        tableTransfer = 0; // reset everything to do with old table or computing new table
        totalTransferred = 0;
        continuePosition = 0;
        delete[] m_oldTable;
        m_oldTable = nullptr;    
        m_oldCap = 0;
        m_oldSize = 0;
        m_oldNumDeleted = 0;
    }
}

int VDetect::getIndex(Virus virus) {
    int location = -1;
    if (getVirus(virus.getKey(), virus.getID()) == EMPTY) {
        // do nothing
    } else {
        for (int i = 0; i < m_currentCap; i++) {
            if ((m_currentTable[i].getKey() == virus.getKey()) && (m_currentTable[i].getID() == virus.getID())) {
                location = i;
            }
        }
    }
    return location;
}