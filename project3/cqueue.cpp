// CMSC 341 - Spring 2023 - Project 3
#include "cqueue.h"
CQueue::CQueue(prifn_t priFn, HEAPTYPE heapType, STRUCTURE structure) { // overloaded constructor
  m_heap = nullptr;
  m_priorFunc = priFn;
  m_heapType = heapType;
  m_structure = structure;
  m_size = 0;
}

CQueue::~CQueue() { // destructor
  clear();
}

void CQueue::clear() { // destructor helper
    betterClear(m_heap); // clear with helper
}

CQueue::CQueue(const CQueue& rhs) { // copy constructor
  m_heap = helpDeepCopy(rhs.m_heap); // call helper
  m_size = rhs.m_size; // set all other variable
  m_heapType = rhs.m_heapType;
  m_priorFunc = rhs.m_priorFunc;
  m_structure = rhs.m_structure;
}

CQueue& CQueue::operator=(const CQueue& rhs) { // assignment operator
    if (this == &rhs) { // self assignment
      return *this;
    } else if (rhs.m_heap == nullptr) { // rhs is empty, just clear it
      this->clear();
      m_size = rhs.m_size;
      m_heapType = rhs.m_heapType;
      m_priorFunc = rhs.m_priorFunc;
      m_structure = rhs.m_structure;
    } else {
      clear();
      m_heap = helpDeepCopy(rhs.m_heap);
      m_size = rhs.m_size;
      m_heapType = rhs.m_heapType;
      m_priorFunc = rhs.m_priorFunc;
      m_structure = rhs.m_structure;
    }
  return *this;
}

void CQueue::mergeWithQueue(CQueue& rhs) { // merge queue with same type
  if ((this->m_structure != rhs.m_structure) || (this->m_priorFunc != rhs.m_priorFunc) || (this->m_heapType != rhs.m_heapType)) { // exception for different stucture or priority function
    throw domain_error("Not Same Type");
  } else if (this == &rhs) { //  throw error if try to self merge
    cout << "Can't merge with self" << endl;
  } else {
    if (rhs.m_structure == SKEW) { // merge skews
      m_heap = mergeSkewQueues(m_heap, rhs.m_heap);
      m_size = m_size + rhs.m_size;
    } else if (rhs.m_structure == LEFTIST) { // merge leftitst
      m_heap = mergeLeftistQueues(m_heap, rhs.m_heap);
      m_size = m_size + rhs.m_size;
    }
  }
  rhs.m_heap = nullptr; // clear rhs
}

void CQueue::insertOrder(const Order& order) { 
  if ((order.m_customerID < MINCUSTID) || (order.m_customerID > MAXCUSTID) ||(order.m_orderID < MINORDERID) || (order.m_orderID > MAXORDERID) || (order.m_membership < TIER1) || (order.m_membership > TIER6) || (order.m_item < COFFEE) || (order.m_item > ICEDTEA) || (order.m_count < ONE) || (order.m_count > DOZEN) || (order.m_points < MINPOINTS) || (order.m_points > MAXPOINTS)) { // does not meet requirements
    throw out_of_range("Not in range");
  } else {
    if (m_structure == LEFTIST) { // insert to leftitst type
      m_heap = mergeLeftistQueues(m_heap, new Node(order));
      m_size++; // increase size
    } else if (m_structure == SKEW) { // insert to skew type
      m_heap = mergeSkewQueues(m_heap, new Node(order)); 
      m_size++; // incease size
    }
  }
} 

int CQueue::numOrders() const {
  return m_size;
}

prifn_t CQueue::getPriorityFn() const {
  return m_priorFunc;
}

Order CQueue::getNextOrder() {// remove highest priority node from list
  Order order;
  if (m_heap == nullptr) {
    throw out_of_range("Empty");
  } else {
    Node *temp = m_heap;// isolate
    order = temp->m_order;
    if (m_structure == LEFTIST) { // leftist type
      m_heap = mergeLeftistQueues(m_heap->m_right, m_heap->m_left); // merge left and right children of root to isolate the root
      m_size--; // decrease size
      delete temp; // delete temp
      temp = nullptr; // set to nullptr
    } else if (m_structure == SKEW) { // skew type
      m_heap = mergeSkewQueues(m_heap->m_right, m_heap->m_left); // merge left and right children of root to isolate the root
      m_size--; // decrease size
      delete temp; // delete temp
      temp = nullptr; // set to nullptr
    }
  }
  return order;
}

void CQueue::setPriorityFn(prifn_t priFn, HEAPTYPE heapType) {
  if ((heapType != MINHEAP) && (heapType != MAXHEAP)) {
    return;
  }
  CQueue newQueue(priFn, heapType, this->m_structure);
  int temp = this->m_size;
  for (int i = 0; i < temp; i++) {
    newQueue.insertOrder(this->getNextOrder());
  }
  *this = newQueue;
}

/*
void CQueue::setPriorityFn(prifn_t priFn, HEAPTYPE heapType) {
  m_priorFunc = priFn; // set priority function
  m_heapType = heapType; // set heaptype
  if (m_structure == SKEW) {
    m_heap = mergeLeftistQueues(nullptr, m_heap);
  } else if (m_structure == LEFTIST) {
    m_heap = mergeLeftistQueues(nullptr, m_heap);
  }
  reBuildHeap(m_heap); // rebuild tree
}
*/

void CQueue::setStructure(STRUCTURE structure) {
  if ((structure != SKEW) && (structure != LEFTIST)) {
    return;
  }
  CQueue newQueue(this->m_priorFunc, this->m_heapType, structure);
  int temp = this->m_size;
  for (int i = 0; i < temp; i++) {
    newQueue.insertOrder(this->getNextOrder());
  }
  *this = newQueue;
/*
  m_structure = structure; // change structure
  if (m_structure == SKEW) {
    m_heap = mergeLeftistQueues(nullptr, m_heap);
  } else if (m_structure == LEFTIST) {
    m_heap = mergeLeftistQueues(nullptr, m_heap);
  }
  reBuildHeap(m_heap); // rebuild tree
  */
}

STRUCTURE CQueue::getStructure() const {
  return m_structure;
}

HEAPTYPE CQueue::getHeapType() const {
  return m_heapType;
}

// Morris Traversal for preorder 
void CQueue::printOrdersQueue() const {
  Node *curr = m_heap;
  while (curr != nullptr) {
    // If m_left child is null, print the current node data. Move to
    // m_right child.
    if (curr->m_left == NULL) {
      cout << "[" << getPriority(curr) << "] " << curr->getOrder() << endl;
      curr = curr->m_right;
    }
    else {
      // Find inorder predecessor
      Node* current = curr->m_left;
      while (current->m_right && current->m_right != curr) {
        current = current->m_right;
      }
      // If the m_right child of inorder predecessor already points to
      // this node
      if (current->m_right == curr) {
        current->m_right = NULL;
        curr = curr->m_right;
      }
      // If m_right child doesn't point to this node, then print this
      // node and make m_right child point to this node
      else {
        cout << "[" << getPriority(curr) << "] " << curr->getOrder() << endl;
        current->m_right = curr;
        curr = curr->m_left;
      }
    }
  }
}

void CQueue::dump() const {
  if (m_size == 0) {
    cout << "Empty heap.\n" ;
  } else {
    dump(m_heap);
  }
  cout << endl;
}

void CQueue::dump(Node *pos) const {
  if ( pos != nullptr ) {
    cout << "(";
    dump(pos->m_left);
    if (m_structure == SKEW)
        cout << m_priorFunc(pos->m_order) << ":" << pos->m_order.getOrderID();
    else
        cout << m_priorFunc(pos->m_order) << ":" << pos->m_order.getOrderID() << ":" << pos->m_npl;
    dump(pos->m_right);
    cout << ")";
  }
}

ostream& operator<<(ostream& sout, const Order& order) {
  sout << "Order ID: " << order.getOrderID() 
        << ", customer ID: " << order.getCustomerID()
        << ", # of points: " << order.getPoints()
        << ", membership tier: " << order.getTierString()
        << ", item ordered: " << order.getItemString()
        << ", quantity: " << order.getCountString();
  return sout;
}

ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getOrder();
  return sout;
}

Node* CQueue::mergeLeftistQueues(Node *node, Node *node2) { // helper function to merge leftist heap
  if (node == nullptr) { // return node2 if node is empty
    return node2;
  }
  if (node2 == nullptr) { // return node if node2 is empty
    return node;
  }
  if (m_heapType == MINHEAP) { // minheap type
    if (min(node, node2) == node) { // node is smaller value
      return mergeLeftHelp(node, node2); // call helper
    } else if (min(node, node2) == node2) { // node2 is smaller value
      return mergeLeftHelp(node2, node); // call helper
    }
  } else if(m_heapType == MAXHEAP) { // maxheap type
    if (max(node, node2) == node) { // node is larger value
      return mergeLeftHelp(node, node2); // call helper
    } else if (max(node, node2) == node2) { // node2 is larger value
      return mergeLeftHelp(node2, node); // call helper
    }
  }
  return m_heap; // return node
}

Node* CQueue::mergeSkewQueues(Node *node, Node *node2) { // helper function to merge skews heap
  Node *temp = nullptr; // mover
  if (node == nullptr) { // return node2 if node is empty
    return node2;
  }
  if (node2 == nullptr) { // return node if node2 is empty
    return node;
  }
  if (m_heapType == MINHEAP) { // minheap type
    if (min(node, node2) == node2) { // node2 is smaller value
      temp = node; // set temp to node
      node = node2; // change where node points to node2
      node2 = temp; // change where node2 points to temp (where node used to be)
    } 
    temp = node->m_left; // change where temp points
    node->m_left = node->m_right; // change where m_left of node points
    node->m_right = temp; // change where m_right of node points (this and above actions is to swap the children to keep the skew heap properties)
    node->m_left = mergeSkewQueues(node2, node->m_left); // call helepr function
  } else if (m_heapType == MAXHEAP) { // maxheap type
    if (max(node, node2) == node2) { // node2 is larger value
      temp = node; // same as above, just for maxheap instead of minheap
      node = node2;
      node2 = temp;
    }       
    temp = node->m_left;
    node->m_left = node->m_right;
    node->m_right = temp;
    node->m_left = mergeSkewQueues(node2, node->m_left);
  }
  return node; // return node
}

Node *CQueue::mergeLeftHelp(Node *node, Node *node2) { // helper function for merging left heaps
  if (node->m_left == nullptr) { // m_left is empty
    node->m_left = node2;
  } else {
    node->m_right = mergeLeftistQueues(node->m_right, node2); // call helper to insert if it r3eaches a nullptr
    if (node->m_left->m_npl < node->m_right->m_npl) { // npl is unbalanced
      swap(node); // call helper to swap children
    }
    node->m_npl = node->m_right->m_npl + 1; // recalculate npl
  }
  return node;
}

Node* CQueue::min(Node *a, Node *b) { // helper function to get lesser of two values
  if (getPriority(a) == getPriority(b)) {  // a and b have the same priority value
    return a;
  }
  return (getPriority(a) < getPriority(b)) ? a : b;
}

Node* CQueue::max(Node *a, Node *b) { // helper function to get grater of two values
  if (getPriority(a) == getPriority(b)) { // a and b have the same priortiy value
    return a;
  }
  return (getPriority(a) > getPriority(b)) ? a :b;
}

Node* CQueue::helpDeepCopy(Node *node) { // helper for deep copy
  if (node != nullptr) {
    Node *newNode = new Node(node->getOrder()); // new node
    newNode->setNPL(node->getNPL()); // set node npl
    newNode->m_left = helpDeepCopy(node->m_left); // add left
    newNode->m_right = helpDeepCopy(node->m_right); // add right
    return newNode; // return node
  }
  return nullptr; // return nullptr at end
}

int CQueue::getPriority(Node *node) const {
  return m_priorFunc(node->getOrder());
}

void CQueue::swap(Node *node) { // helper function to swap nodes
  Node *temp = node->m_left; // temp node
  node->m_left = node->m_right; // change left to right
  node->m_right = temp; // change right to temp (which is left)
}

void CQueue::reBuildHeap(Node *node) { // helper funtion to rebuild heap
  int size = m_size; // get size for array
  Order **orders = new Order*[size]; // create dynamic array
  for (int i = 0; i < size; i++) { // loop to add elements to array
    if (i < (size - 1)) { 
      orders[i] = new Order(m_heap->m_order); // add to array
      getNextOrder(); // pop highest priority from tree
    } else { // can't use getnextorder if i = size - 1 problems happens
      orders[i] = new Order(m_heap->m_order); // add to array
    }
  }
  clear(); // make sure that tree was cleared
  for (int i = 0; i < size; i++) { // readd orders to tree
    insertOrder(*orders[i]); // insert orders
  }
  for (int i = 0; i < size; i++) { // delete allocated memory
    delete orders[i];
  }
  delete[] orders;
}

// clear the tree
void CQueue::betterClear(Node* node) {
    if (node != nullptr) {
        betterClear(node->m_left); // destroy m_left subtree
        betterClear(node->m_right); // destroy m_right subtree
        delete node; // dealocate memory
        node = nullptr; // set to nullptr
        m_size--;
    }
    m_heap = nullptr;
}
