/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(nullptr);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode * toDelete = head_;
  while (toDelete != nullptr)
  {
    ListNode * temp = toDelete -> next;
    delete toDelete;
    toDelete = temp;
  }
  length_ = 0;
  head_ = nullptr;
  tail_ = nullptr;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if (head_ == nullptr)
  {
    head_ = newNode;
    tail_ = newNode;
  }
  else 
  {
    newNode -> next = head_;
    head_ -> prev = newNode;
    head_ = newNode;
  }

  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;
  if (head_ == NULL) {
    head_ = newNode;
  }
  if (tail_ != NULL) {
    tail_ -> next = newNode;
  }

  tail_ = newNode;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if (start == nullptr || splitPoint >= length_)  return nullptr;
  if (splitPoint <= 0) return start;

  ListNode * curr = start;
  for (int i = 0; i < splitPoint; i++) {
    curr = curr->next;
  }

  curr->prev->next = nullptr;

  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode * curNode = head_;
  for (int i = 1; i <= length_; i++)
  {
    if (i % 3 == 0)
    {
      ListNode * temp3 = curNode;
      ListNode * temp2 = curNode->prev;
      ListNode * temp1 = curNode->prev->prev;

      temp1->next = temp3->next;
      if (i != length_)  temp3->next->prev = temp1;
      temp2->prev = temp1->prev;
      if (i != 3) temp1->prev->next = temp2;
      temp3->next = temp1;
      temp1->prev = temp3;
      
      curNode = temp1;
      if (i == 3) head_ = temp2;
      if (i == length_)  tail_ = temp1;
    }
    curNode = curNode->next;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
    if(head_ == nullptr || tail_ == nullptr) return;
  if(startPoint == endPoint) return;

  //Obtain a copy of original pointers.
  ListNode *temp = nullptr;
  ListNode *curr = startPoint;
  ListNode *original_start = startPoint;
  ListNode *original_start_prev = startPoint->prev;
  ListNode *original_end = endPoint;
  ListNode *original_end_next = endPoint->next;

  //Swap next and prev for all nodes between start and end.
  while(curr != endPoint) 
  {
    temp = curr->prev;
    curr->prev = curr->next;
    curr->next = temp;
    curr = curr->prev;
  }

  //Connect swapped nodes to other nodes.
  temp = curr->prev;
  curr->prev = original_start_prev;
  curr->next = temp;
  endPoint = original_start;
  endPoint->next = original_end_next;

  //Identify if swap occurs in between.
  if(original_start_prev == nullptr)
  {
    head_ = curr;
  } 
  else {
    original_start_prev->next = original_end;
  }
  if(original_end_next == nullptr) 
  {
    tail_ = endPoint;
  } 
  else {
    original_end_next->prev = original_start;
  }
/*   if (startPoint == head_)  head_ = endPoint;
  if (endPoint == tail_)  tail_ = startPoint;
  
  ListNode * curHead = startPoint;
  ListNode * curTail = endPoint;
  while (curHead != endPoint)
  {
    curTail->next->prev = curHead->prev;
    curHead->prev->next = curTail->next;
    curTail->next = curTail->next->next;
    curTail->next->prev = curTail;
    curHead->prev = curHead->prev->next;
    curHead->prev->next = curHead;
    curHead = curHead->prev;
  } */
  
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if(length_ == 0 || length_ == 1) return;
  ListNode *startPoint = head_;
  ListNode *endPoint = head_;

  while(endPoint != nullptr)
  {
    for(int i = 0; i < n - 1; i++) 
    {
      if(endPoint->next == nullptr)
      {
        reverse(startPoint, endPoint);
        return;
      }
      endPoint = endPoint->next;
    }
    reverse(startPoint, endPoint);
    if(endPoint->next == nullptr) return;
    else 
    {
      startPoint = endPoint->next;
      endPoint = startPoint;
    }
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2

  if (first == nullptr) return second;
  if (second == nullptr)  return first;

  ListNode * head = second;
  if (first->data < second->data) 
  {
    head = first;
    first = first->next;
  }
  else // (first->data > second->data) 
  {
    // head = second;
    second = second->next;
  }
  ListNode * tail = head;
  while (first != nullptr && second != nullptr)
  {
    if (first->data < second->data)
    {
      tail->next = first;
      tail = first;
      first = first->next;
    }
    else 
    {
      tail->next = second;
      tail = second;
      second = second->next;
    }
  }
  if (first != nullptr) tail->next = first;
  else tail->next = second;
  return head;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(chainLength == 0 || chainLength == 1) return start;
  ListNode * left_half = start;
  ListNode * right_half = split(start, chainLength / 2);
  left_half = mergesort(left_half, chainLength / 2);
  right_half = mergesort(right_half, chainLength -  chainLength / 2);
  return merge(left_half, right_half);
}