#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  int m_; //m-ary heap
  PComparator comp_;
  std::vector<T> cont_; // vector container
  int findBestChild(int pos);
  void swap(int pos1, int pos2);
  void bubbleUp(int pos);
  void heapify(int pos); //trickle down

};

template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c){
  m_ = m;
  comp_ = c;
}
template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap(){

}
// Add implementation of member functions here
template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return cont_.size();
}
template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return cont_.empty();
}
template <typename T, typename PComparator>
int Heap<T,PComparator>::findBestChild(int pos)
{
  size_t mindex = pos*m_+1;//first child position
  if (mindex >= size()){
    return -1; // no child
  }
  // T minval = cont_[mindex];
  for (size_t i = 1; i<= m_; i++){
    if (pos*m_+i >= size()){
      break;
    }
    if (comp_(cont_[pos*m_+i], cont_[mindex])){//this is better than current best
      mindex = pos*m_+i;
    }
  }
  return mindex;
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::swap(int pos1, int pos2){
  T temp = cont_[pos1];
  cont_[pos1] = cont_[pos2];
  cont_[pos2] = temp;
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::bubbleUp(int pos){
  if (pos > 0 && comp_(cont_[pos],cont_[(pos-1)/m_])){//parent is worse than child, so swap
    swap(pos, (pos-1)/m_);
    bubbleUp((pos-1)/m_);// bubble up the parent
  }
}
template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(int pos){//trickle down
  int child = findBestChild(pos);
  if (child == -1){//node has no children
    return;
  }
  if (comp_(cont_[child],cont_[pos])){
    swap(child, pos);
    heapify(child);
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
  cont_.push_back(item);
  bubbleUp(size()-1);
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return cont_[0]; // 0-indexed heap

}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("pop on empty heap");
  }
  swap(0,size()-1);
  cont_.pop_back();
  heapify(0);


}



#endif

