#pragma once

#include <iostream>
#include <stdexcept>
#include "DLL.h"

//-----------------------------------------------------------
// class definitions
//-----------------------------------------------------------

/**
 * Class representing a simple, templated stack, using a doubly-linked
 * list as the underyling data structure.
 */
template <class T> class Stack {
public:
  /**
   * Default constructor. Make a new, empty stack.
   */
  Stack() {}

  /**
   * Copy constructor. Make this Stack just like an existing one.
   *
   * \param stack Stack to copy from.
   */
  Stack(const Stack<T> &stack);

  /**
   * Remove all elements from this stack.
   */
  void clear() { list.clear(); }

  /**
   * Determine if the stack is empty.
   *
   * \return True if the stack is empty, false if it has elements.
   */
  bool isEmpty() { return list.isEmpty(); }

  /**
   * Get a reference to the top element on the stack, without removing
   * it.
   *
   * \return Reference to the element at he top of the stack.
   */
  T &peek() const;

  /**
   * Pop the top element from the stack.
   *
   * \return Element of type T that was at the top of the stack.
   */
  T pop();

  /**
   * Push a new item onto the stack.
   *
   * \param a Element of type T to push onto the stack.
   */
  void push(const T &a) { list.addFirst(a); }

  /**
   * Get the number of elements in the stack.
   *
   * \return Number of elements in the stack.
   */
  unsigned size() { return list.size(); }

  /**
   * Overloaded assignment operator.
   *
   * \param stack Stack to copy.
   *
   * \return Reference to this stack, for chaining.
   */
  Stack<T> &operator=(const Stack<T> &stack);

  /**
   * Override of the stream insertion operator for Stack objects.
   *
   * \param out ostream object to output to, e.g., cout
   *
   * \param stack Stack to output
   *
   * \return the out ostream object
   */
  friend std::ostream &operator<<(std::ostream &out, const Stack<T> &stack) {

    out << stack.list;
    return out;
  }

private:
  /**
   * Doubly-linked list used as the underlying data structure for the
   * stack.
   */
  DLL<T> list;

  /**
   * Private helper for copy constructor and assignment operator.
   *
   * \param stack
   */
  void copy(const Stack<T> &stack);
};

//-----------------------------------------------------------
// function implementations
//-----------------------------------------------------------

/*
 * Copy constructor implementation.
 */
template <class T> Stack<T>::Stack(const Stack<T> &stack) { copy(stack); }

/*
 * Copy helper fucntion implementation.
 */
template <class T> void Stack<T>::copy(const Stack<T> &stack) {
  clear();
  list = stack.list;
}

/*
 * Peek function implementation.
 */
template <class T> T &Stack<T>::peek() const {
  if (list.isEmpty()) {
    throw std::out_of_range("Empty stack in Stack::peek()");
  }
  return list.getFirst();
}

/*
 * Pop function implementation.
 */
template <class T> T Stack<T>::pop() {
  if (list.isEmpty()) {
    throw std::out_of_range("Empty stack in Stack::pop()");
  }
  return list.removeFirst();
}

/*
 * Overloaded assignment operator implementation.
 */
template <class T> Stack<T> &Stack<T>::operator=(const Stack<T> &stack) {
  copy(stack);
  return *this;
}
