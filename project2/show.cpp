// UMBC - CMSC 341 - Spring 2023 - Proj2
/********************************************************
** File: show.cpp
** Project: CMSC 341 Project 2
** Author: Matthew Green
** Date: 28/03/2023
** Email: mgreen11@umbc.edu
**
** Description: Defines the functions set in the .h file
**********************************************************/
#include "show.h"
Show::Show(){
    m_root = nullptr;
}
Show::~Show(){
    clear(); // clear tree
}
void Show::insert(const Drone& aDrone){
    if ((aDrone.m_id < MINID) || (aDrone.m_id > MAXID)) { // check that id is in range
        cout << "ID has to be between minID and maxID" << endl;
    } else {
        if (!(findDrone(aDrone.m_id))) {
            m_root = betterInsert(m_root, aDrone); // call helper function
        }
    }
}

void Show::clear(){ 
    betterClear(m_root); // clear tree with helper function
}

void Show::remove(int id){
    if (findDrone(id)) { // check that id exists
        m_root = betterRemove(m_root, id); // call helper function
    }
}

void Show::dumpTree() const {dump(m_root);}
void Show::dump(Drone* aDrone) const{
    if (aDrone != nullptr){
        cout << "(";
        dump(aDrone->m_left);//first visit the left child
        cout << aDrone->m_id << ":" << aDrone->m_height;//second visit the node itself
        dump(aDrone->m_right);//third visit the right child
        cout << ")";
    }
}

// Uses Morris traversal which is a way of traversing a tree without using recursion or a stack
// Links are created as successors and nodes are printed using these links
// Changes are reverted back to restore tree
// This initaizes a pointer as root and while the pointer is not nullptr, check if curr has a left child
// If curr does not have a left child, print curr and update it to point to the node on the right of curr
// else make curr the right child of the rightmost node in curr's left subtree
// update curr to this left node
void Show::listDrones() const {
    Drone* temp = m_root; // trackers
    Drone* prev = temp;
    if (temp == nullptr) { // nothing
        return;
    } else { // something
        while (temp != nullptr) {
            if (temp->m_left == nullptr) {
                cout << temp->getID() << ":" << temp->getStateStr() << ":" << temp->getTypeStr() << endl;
                temp = temp->m_right;
            } else {
                prev = temp->m_left;
                while ((prev->m_right != nullptr) && (prev->m_right != temp)) {
                    prev = prev->m_right;
                }
                if (prev->m_right == nullptr) {
                    prev->m_right = temp;
                    temp = temp->m_left;
                } else {
                    prev->m_right = nullptr;
                    cout << temp->getID() << ":" << temp->getStateStr() << ":" << temp->getTypeStr() << endl;
                    temp = temp->m_right;
                }
            }
        }
    }
}

bool Show::setState(int id, STATE state){
    bool pass = false; // return value
    Drone *temp = m_root; // tracker 
    while ((temp != nullptr) && ((id <= temp->m_id) || (id >= temp->m_id))) { // traverse tree
        if (temp->m_id == id) { // id exists in tree
            temp->setState(state); // set state
            pass = true;
            break; // stop loop
        } else if (id <= temp->m_id) { // go to left
            temp = temp->m_left;
        } else if (id >= temp->m_id) { // go to right
            temp = temp->m_right;
        } 
    }
    return pass;
}

void Show::removeLightOff(){
    Drone* temp = m_root;
    do { // keep looping until temp is nullptr, this means that the entire tree has be gone through and nothing has the lightoff state
        temp = findLightOffDrone(); // call helper funciton
        if ((temp != nullptr) && (temp->m_state == LIGHTOFF)) { // check that temp is not nullptr and that the state is off
            remove(temp->m_id);
        }
    } while (temp != nullptr);
}


bool Show::findDrone(int id) const {    
    bool found = false; // create boolean
    Drone *temp = m_root; // tracker 
    while ((temp != nullptr) && ((id <= temp->m_id) || (id >= temp->m_id))) { // traverse tree
        if (temp->m_id == id) { // id exists in tree
            found = true;
            break; // stop loop
        } else if (id <= temp->m_id) { // go to left
            temp = temp->m_left;
        } else if (id >= temp->m_id) { // go to right
            temp = temp->m_right;
        } 
    }
    return found;
}

const Show& Show::operator=(const Show & rhs) {
    if (this == &rhs) { // protect against self assingment
    cout << "1" << endl;
        return *this;
    } else if (rhs.m_root == nullptr) { // assign to empty object, just destory
    cout << "2" << endl;
        this->clear();
    } else {
    cout << "3" << endl;
        this->clear(); // destroy any memory that may have been used
        copyTree(this->m_root, rhs.m_root); // use helper fuction
    }
    return *this;
}

// Uses Morris traversal which is a way of traversing a tree without using recursion or a stack
// counter will be updated
// Changes are reverted back to restore tree
// This initaizes a pointer as root and whil the pointer is not nullptr, check if curr has a left child
// If curr does not have a left child, print curr and update it to point to the node on the right of curr
// else make curr the right child of the rightmost node in curr's left subtree
// update curr to this left node
int Show::countDrones(LIGHTCOLOR aColor) const{
    Drone* temp = m_root; // trackers
    Drone* prev = temp;
    int num = 0; // counter
    if (temp == nullptr) { // nothing
        return 0;
    } else { // something
        while (temp != nullptr) {
            if (temp->m_left == nullptr) { // no left
                if (temp->m_type == aColor) { // increase num
                    num = num + 1; 
                }
                temp = temp->m_right;
            } else {
                prev = temp->m_left;
                while ((prev->m_right != nullptr) && (prev->m_right != temp)) {
                    prev = prev->m_right;
                }
                if (prev->m_right == nullptr) {
                    prev->m_right = temp;
                    temp = temp->m_left;
                } else {
                    prev->m_right = nullptr;
                    if (temp->m_type == aColor) {
                        num = num + 1;
                    }
                    temp = temp->m_right;
                }
            }
        }
    }
    return num;
}

// Hleper Functions 

Drone* Show::betterInsert(Drone* root, const Drone& aDrone) {
    if (root == nullptr) { // insert node
        Drone* insertDrone = new Drone(aDrone.m_id, aDrone.getType(), aDrone.getState()); // allocate memory
        root = insertDrone; // add to tree
    } else if (aDrone.m_id < root->m_id) { // go to left node
        root->m_left = betterInsert(root->m_left, aDrone);
    } else if (aDrone.m_id > root->m_id) { // go to right node
        root->m_right = betterInsert(root->m_right, aDrone);
    }  else {
        return root; // return root, should not happen as this only happens if id already exists and we already check for that in a different function before calling this
    }
    
    if ((root->m_left != nullptr) || (root->m_right != nullptr)) { // update height if one childe is occupied
        root->setHeight(1 + max(height(root->m_left), height(root->m_right)));
    }

    int balanceFactor = getBalance(root); // see if rotation needs to happen
    if (balanceFactor > 1) { // left rotation
        if (aDrone.m_id < root->m_left->m_id) { // left left roation
        return rotateRight(root);
        } else if (aDrone.m_id > root->m_left->m_id) { // left right rotation
        root->m_left = rotateLeft(root->m_left);
        return rotateRight(root);
        }
    }
  if (balanceFactor < -1) { // right rotation
    if (aDrone.m_id > root->m_right->m_id) { // right right notation
      return rotateLeft(root);
    } else if (aDrone.m_id < root->m_right->m_id) { // right left rotation
      root->m_right = rotateRight(root->m_right);
      return rotateLeft(root);
    }
  }
    return root;
}


Drone* Show::betterRemove(Drone* root, int id) {
   if (root == nullptr) {
    return nullptr;
   } else {
        if (root->m_id == id) { // node with id found
            if ((root->m_left == nullptr) && (root->m_right == nullptr)) { // has no children
                delete root;
                return nullptr;
            } else if (root->m_left == nullptr) { // only has a right child
                Drone *temp = root->m_right;
                delete root;
                return temp;
            } else if (root->m_right == nullptr) { // only has a left child
                Drone *temp = root->m_left;
                delete root;
                return temp;
            } else { // has both a left and right child
                Drone *minRight;
                Drone *temp = root->m_right;
                while (temp->m_left != nullptr) { // get smallest id in right subtree
                    temp = temp->m_left;
                }
                minRight = temp; 
                root->m_id = minRight->m_id; // swap values
                root->m_type = minRight->m_type;
                root->m_state = minRight->m_state;
                root->m_right = betterRemove(root->m_right, minRight->m_id);
            }
        } else { // not at id
            if (id < root->m_id) { // go left
                root->m_left = betterRemove(root->m_left, id);
            } else if (id > root->m_id) { // go right
                root->m_right = betterRemove(root->m_right, id);
            }
        }
   }

    if ((root->m_left != nullptr) || (root->m_right != nullptr)) { // update height if one child is occupied
        root->setHeight(1 + max(height(root->m_left), height(root->m_right)));
    }
    int balanceFactor = getBalance(root); // see if rotation needs to happen
    if (balanceFactor > 1) { // left left
        if (getBalance(root->m_left) >= 0) {
            return rotateRight(root);
        } else { // left right
            root->m_left = rotateLeft(root->m_left);
            return rotateRight(root);
        }
    }
    if (balanceFactor < -1) {
        if (getBalance(root->m_right) <= 0) { // right right
            return rotateLeft(root);
        } else { // right left
            root->m_right = rotateRight(root->m_right);
            return rotateLeft(root);
        }
    }
    return root;
}

// rotate node left
Drone* Show::rotateLeft(Drone* x) {
    Drone* y = x->m_right;
    Drone* temp = y->m_left;
    y->m_left = x;
    x->m_right = temp;
    // update heights
    x->setHeight(max(height(x->m_left), height(x->m_right)) + 1);
    y->setHeight(max(height(y->m_left), height(y->m_right)) + 1);
    return y;
}

// rotate node right
Drone* Show::rotateRight(Drone* y) {
    Drone* x = y->m_left;
    Drone* temp = x->m_right;
    x->m_right = y;
    y->m_left = temp;
    // update heights
    y->setHeight(max(height(y->m_left), height(y->m_right)) + 1);
    x->setHeight(max(height(x->m_left), height(x->m_right)) + 1);
    return x;
}

Drone* Show::findLightOffDrone() { // Morris Traversal, go above for how it is done
    Drone* temp = m_root; // trackers
    Drone* prev = temp;
    Drone *returnNode = nullptr;
    if (temp == nullptr) { // nothing
        return 0;
    } else { // something
        while (temp != nullptr) {
            if (temp->m_left == nullptr) { // no left
                if (temp->m_state == LIGHTOFF) { // set return node
                    returnNode = temp;
                }
                temp = temp->m_right;
            } else {
                prev = temp->m_left;
                while ((prev->m_right != nullptr) && (prev->m_right != temp)) {
                    prev = prev->m_right;
                }
                if (prev->m_right == nullptr) {
                    prev->m_right = temp;
                    temp = temp->m_left;
                } else {
                    prev->m_right = nullptr;
                    if (temp->m_state == LIGHTOFF) {
                        returnNode = temp;
                    }
                    temp = temp->m_right;
                }
            }
        }
    }
    return returnNode;
}

Drone* Show::betterFindDrone(int id) {
    Drone *temp = m_root; // tracker 
    while ((temp != nullptr) && ((id <= temp->m_id) || (id >= temp->m_id))) { // traverse tree
        if (temp->m_id == id) { // id exists in tree
            break;
        } else if (id <= temp->m_id) { // go to left
            temp = temp->m_left;
        } else if (id >= temp->m_id) { // go to right
            temp = temp->m_right;
        } 
    }
    return temp;
}

// get integer to know if ballance needs to be done
int Show::getBalance(Drone* aDrone) {
    if (aDrone == nullptr) {
        return 0;
    }
    return height(aDrone->m_left) - height(aDrone->m_right);
}

// get height of node, mostly for nullptr
int Show::height(Drone* aDrone) {
    if (aDrone == nullptr) {
        return 0;
    } return aDrone->getHeight();
}

// get the max of two integor
int Show::max(int a, int b) {
    return (a >b) ? a : b;
}

// clear the tree
void Show::betterClear(Drone* aDrone) {
    if (aDrone != nullptr) {
        betterClear(aDrone->m_left); // destroy left subtree
        betterClear(aDrone->m_right); // destroy right subtree
        delete aDrone; // dealocate memory
        aDrone = nullptr; // set to nullptr
    }
    m_root = nullptr;
}

// deep copy tree
void Show::copyTree(Drone *&lhs, Drone *rhs) {
    if (rhs == nullptr) {
        lhs = nullptr;
    } else {
        if (lhs == nullptr) {
            Drone* insertDrone = new Drone(rhs->m_id, rhs->m_type, rhs->m_state); // create drone
            insertDrone->m_height = rhs->m_height; // set drone height
            lhs = insertDrone; // insert drone
        } 
        copyTree(lhs->m_left, rhs->m_left); // recursively add left child
        copyTree(lhs->m_right, rhs->m_right); // recursevly add right child
    }

}