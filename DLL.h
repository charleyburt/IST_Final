#pragma once

#include <iostream>
#include <stdexcept>

//-----------------------------------------------------------
// class definitions
//-----------------------------------------------------------

/**
 * Class representing a templated doubly-linked list, with an
 * iterator and ability to add / remove at both ends.
 */
template <class T> class DLL {
private:
  //-------------------------------------------------------
  // inner class definition
  //-------------------------------------------------------

  /**
   * Private nested class representing nodes in the doubly-linked
   * list.
   */
  class Node {
  public:
    /**
     * Default constructor. Make a new Node with default data
     * and pointers set to zero.
     */
    Node() : data(), pPrev(0), pNext(0) {}

    /**
     * Initializing constructor. Make a new Node with the specified
     * data and pointer values.
     *
     * \param d Data value of type T for the Node.
     *
     * \param pN Pointer to the next Node in the list, or 0 if this
     * is the last Node.
     *
     * \param pP Pointer to the previous Node in the list, or 0 if
     * this is the first Node.
     */
    Node(T d, Node *pP, Node *pN) : data(d), pPrev(pP), pNext(pN) {}

    /** Type T payload of the Node. */
    T data;

    /** Pointer to the previous node in the list. */
    Node *pPrev;

    /** Pointer to the next node in the list. */
    Node *pNext;
  };

public:
  //-------------------------------------------------------
  // inner class definition
  //-------------------------------------------------------

  /**
   * Iterator for the doubly-linked list class.
   */
  class Iterator {
  public:
    /** Dereferencing operator to allow access to the node's
     * data. */
    T &operator*();

    /** Equality operator to test if this iterator is at another's
     * position. */
    bool operator==(const Iterator &other) const {
      return pCurr == other.pCurr;
    }

    /** Inequality operator to test if this iterator is not at
     * another's position. */
    bool operator!=(const Iterator &other) const {
      return pCurr != other.pCurr;
    }

    /** Increment operator to advance to next element. */
    Iterator &operator++();

    /** Decrement operator to retreat to previous element. */
    Iterator &operator--();

    // make us a friend of the outer class
    friend class DLL;

  private:
    /** Current iterator location. */
    Node *pCurr;

    /** Private constructor can't be accessed outside of DLL
     * class. */
    Iterator(Node *pC) : pCurr(pC) {}
  };

public:
  /**
   * Default constructor; create an empty list.
   */
  DLL() : pHead(0), pTail(0), n(0u) {}

  /**
   * Copy constructor; make this list just like an existing one.
   *
   * \param list Doubly-linked list to copy.
   */
  DLL(const DLL<T> &list);

  /**
   * Destructor. Destroy the list.
   */
  ~DLL() { clear(); }

  /**
   * Add an element to the front of the list.
   *
   * \param d Element to add to the list.
   */
  void addFirst(const T &d);

  /**
   * Add an element to the end of the list.
   *
   * \param d Element to add to the list.
   */
  void addLast(const T &d);

  /**
   * Get an iterator to the first element in the list.
   *
   * \return Iterator positioned at the first element.
   */
  Iterator begin() const;

  /**
   * Remove all elements from this list.
   */
  void clear();

  /**
   * Determine if the list contains a specific element.
   *
   * \param d Element to search for.
   *
   * \return index of the element if found, -1 if not found.
   */
  int contains(const T &d) const;

  /**
   * Get an iterator to the last element in the list.
   *
   * \return Iterator positioned one past the last element of the
   * list.
   */
  Iterator end() const;

  /**
   * Get the element at a specified position in the list.
   *
   * \param idx Index of element to get.
   *
   * \return Element as the specified position.
   */
  T &get(unsigned idx) const;

  /**
   * Get the first element in the list.
   *
   * \return First element in the list.
   */
  T &getFirst() const;

  /**
   * Get the last element in the list.
   *
   * \return Last element in the list.
   */
  T &getLast() const;

  /**
   * Determine if this list is empty.
   *
   * \return true if the list is empty, false otherwise.
   */
  bool isEmpty() const { return n == 0u; }

  /**
   * Remove the specified element from the list.
   *
   * \param idx Index of element to remove.
   *
   * \return Element that was in the specified position.
   */
  T remove(unsigned idx);

  /**
   * Remove the first element from the list.
   *
   * \return Element that was in the first position.
   */
  T removeFirst();

  /**
   * Remove the last element from the list.
   *
   * \return Element that was in the last position.
   */
  T removeLast();

  /**
   * Change the value at a specific location in the list.
   *
   * \param idx Index of element to change.
   *
   * \param d New value to place in the list.
   */
  void set(unsigned idx, const T &d);

  /**
   * Change the value at the first location in the list.
   *
   * \param d New value to place as the first element in the list.
   */
  void setFirst(const T &d);

  /**
   * Change the value at the last location in the list.
   *
   * \param d New value to place as the last element in the list.
   */
  void setLast(const T &d);

  /**
   * Get the number of elements in the list.
   *
   * \return Number of elements in the list.
   */
  unsigned size() const { return n; }

  /**
   * Overridden assignment operator.
   *
   * \param list List to copy.
   *
   * \return Reference to this list, for chaining.
   */
  DLL<T> &operator=(const DLL<T> &list);

  /**
   * Override of the stream insertion operator for DLL objects.
   *
   * \param out ostream object to output to, e.g., cout
   *
   * \param list DLL to output
   *
   * \return the out ostream object
   */
  friend std::ostream &operator<<(std::ostream &out, const DLL<T> &list) {

    Node *pCurr = list.pHead;

    out << "[";

    while (pCurr != 0) {
      out << pCurr->data;

      if (pCurr->pNext != 0) {
        out << ", ";
      }

      pCurr = pCurr->pNext;
    }

    out << "]";

    return out;
  }

private:
  /** Pointer to the first node in the list. */
  Node *pHead;

  /** Pointer to the last node in the list. */
  Node *pTail;

  /** Number of nodes in the list. */
  unsigned n;

  /** Private helper for copy constructor and assignment operator.
   *
   * \param list Reference to DLL to copy from.
   */
  void copy(const DLL<T> &list);
};

//-----------------------------------------------------------
// function implementations
//-----------------------------------------------------------

/*
 * Implementation of the Iterator dereferencing operator.
 */
template <class T> T &DLL<T>::Iterator::operator*() {
  if (pCurr == 0) {
    throw std::out_of_range("Dereferencing null Iterator in "
                            "DLL::Iterator::operator*()");
  }

  return pCurr->data;
}

/*
 * Implementation of assignment operator.
 */
template <class T> DLL<T> &DLL<T>::operator=(const DLL<T> &list) {
  copy(list);

  return *this;
}

/*
 * Copy constructor implementation.
 */
template <class T> DLL<T>::DLL(const DLL<T> &list) : pHead(0), pTail(0), n(0u) {
  copy(list);
}

/*
 * Implementation of the Iterator increment operator.
 */
template <class T> typename DLL<T>::Iterator &DLL<T>::Iterator::operator++() {
  if (pCurr == 0) {
    throw std::out_of_range("Iterating past end of list in "
                            "DLL::Iterator::operator++()");
  }

  pCurr = pCurr->pNext;

  return *this;
}

/*
 * Implementation of the Iterator decrement operator.
 */
template <class T> typename DLL<T>::Iterator &DLL<T>::Iterator::operator--() {
  if (pCurr == 0) {
    throw std::out_of_range("Iterating past end of list in "
                            "DLL::Iterator::operator--()");
  }

  pCurr = pCurr->pPrev;

  return *this;
}

/*
 * Implementation of the DLL addFirst method.
 */
template <class T> void DLL<T>::addFirst(const T &d) {
  Node *pN = new Node(d, 0, pHead);

  if (pHead == 0) {
    // empty list case
    pHead = pTail = pN;
  } else {
    // non-empty list case
    pHead = pN;
    pHead->pNext->pPrev = pHead;
  }

  n++;
}

/*
 * Implementation of the DLL addLast method.
 */
template <class T> void DLL<T>::addLast(const T &d) {
  Node *pN = new Node(d, pTail, 0);

  if (pHead == 0) {
    // empty list case
    pHead = pTail = pN;
  } else {
    // non-empty list case
    pTail = pN;
    pTail->pPrev->pNext = pTail;
  }

  n++;
}

/*
 * Get iterator to the first node.
 */
template <class T> typename DLL<T>::Iterator DLL<T>::begin() const {
  return Iterator(pHead);
}

/*
 * Implementation of the DLL clear method.
 */
template <class T> void DLL<T>::clear() {
  Node *pCurr = pHead;

  while (pCurr != 0) {
    Node *pT = pCurr;
    pCurr = pCurr->pNext;
    delete pT;
  }

  pHead = pTail = 0;
  n = 0u;
}

/*
 * Search for an element in the list.
 */
template <class T> int DLL<T>::contains(const T &d) const {
  Node *pCurr = pHead;
  int i = 0;

  while (pCurr != 0) {
    if (pCurr->data == d) {
      return i;
    }
    pCurr = pCurr->pNext;
    i++;
  }

  return -1;
}

/*
 * Copy helper method implementation.
 */
template <class T> void DLL<T>::copy(const DLL<T> &list) {
  clear();

  for (DLL<T>::Iterator i = list.begin(); i != list.end(); ++i) {
    addLast(*i);
  }
}

/*
 * Get iterator to the end of the list.
 */
template <class T> typename DLL<T>::Iterator DLL<T>::end() const {
  return Iterator(0);
}

/*
 * Get specified element from the list.
 */
template <class T> T &DLL<T>::get(unsigned idx) const {
  if (idx >= n) {
    throw std::out_of_range("Index beyond end of list in "
                            "DLL::get()");
  }

  Node *pCurr = pHead;
  for (unsigned i = 0u; i < idx; i++) {
    pCurr = pCurr->pNext;
  }

  return pCurr->data;
}

/*
 * Get the first element in the list.
 */
template <class T> T &DLL<T>::getFirst() const {
  if (n == 0) {
    throw std::out_of_range("Empty list in DLL::getFirst()");
  }

  return pHead->data;
}

/*
 * Get the last element in the list.
 */
template <class T> T &DLL<T>::getLast() const {
  if (n == 0) {
    throw std::out_of_range("Empty list in DLL::getLast()");
  }

  return pTail->data;
}

/*
 * Remove specified element.
 */
template <class T> T DLL<T>::remove(unsigned idx) {
  if (idx >= n) {
    throw std::out_of_range("Remove past list bounds in "
                            "DLL::remove()");
  }

  if (idx == 0u) {
    return removeFirst();
  } else if (idx == (n - 1u)) {
    return removeLast();
  } else {
    Node *pCurr = pHead;
    for (unsigned i = 0u; i < idx; i++) {
      pCurr = pCurr->pNext;
    }
    T d = pCurr->data;

    pCurr->pPrev->pNext = pCurr->pNext;
    pCurr->pNext->pPrev = pCurr->pPrev;

    delete pCurr;

    return d;
  }
}

/*
 * Remove first element from list.
 */
template <class T> T DLL<T>::removeFirst() {
  if (n == 0) {
    throw std::out_of_range("Empty list in DLL::removeFirst()");
  }
  n--;
  T d = pHead->data;
  Node *pT = pHead;

  pHead = pHead->pNext;
  if (pHead != 0) {
    pHead->pPrev = 0;
  }

  if (n == 0) {
    pHead = pTail = 0;
  }

  delete pT;

  return d;
}

/*
 * Remove last element from list.
 */
template <class T> T DLL<T>::removeLast() {
  if (n == 0) {
    throw std::out_of_range("Empty list in DLL::removeLast()");
  }
  n--;
  Node *pT = pTail;
  T d = pTail->data;

  pTail = pTail->pPrev;
  if (pTail != 0) {
    pTail->pNext = 0;
  }

  if (n == 0) {
    pHead = pTail = 0;
  }

  delete pT;

  return d;
}

/*
 * Change element at a specified index.
 */
template <class T> void DLL<T>::set(unsigned idx, const T &d) {
  if (idx >= n) {
    throw std::out_of_range("Access past end of list in "
                            "DLL::set()");
  }

  Node *pCurr = pHead;
  for (unsigned i = 0; i < idx; i++) {
    pCurr = pCurr->pNext;
  }

  pCurr->data = d;
}

/*
 * Change element at the head of the list.
 */
template <class T> void DLL<T>::setFirst(const T &d) {
  if (pHead == 0) {
    throw std::out_of_range("Set into front of empty list in "
                            "DLL::setFirst()");
  }

  pHead->data = d;
}

/*
 * Change element at the tail of the list.
 */
template <class T> void DLL<T>::setLast(const T &d) {
  if (pTail == 0) {
    throw std::out_of_range("Set into end of empty list in "
                            "DLL::setLast()");
  }

  pTail->data = d;
}
