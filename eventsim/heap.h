#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <vector>
#include <stdexcept>
using namespace std;

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
    /// Constructs an m-ary heap for any m >= 2
    Heap(int m, PComparator c = PComparator());

    /// Destructor as needed
    ~Heap();

    /// Adds an item
    void push(const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

private:
    /// Add whatever helper functions and data members you need below
    void heapify(int index);

    int n_ary; 
    vector<T> tree;
    PComparator comp; 

};


template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c)
{
    comp = c; 
    if(m<2){
        throw std::logic_error("can't have value under 2");
    }else{
        n_ary = m;
    }
    tree.push_back(0);
}


template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap(){}


template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
    tree.push_back(item);
    int loc = tree.size()-1;
    int parent = loc/n_ary;
    while(parent >= 1 && comp(tree[loc], tree[parent])){ 
        swap(tree[parent], tree[loc]);
        loc = parent;
        parent = loc/n_ary;
    }
    // for(size_t i=0; i< tree.size(); i++){
    //     cout << tree[i] << " ";
    // }
    // cout << endl;
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
    return (tree.size() - 1 == 0);
}

// We will start top() for you to handle the case of
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }
    // If we get here we know the heap has at least 1 item
    // Add code to return the top element
    return tree[1];
}


// We will start pop() for you to handle the case of
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }
    tree[1] = tree.back();
    tree.pop_back();
    heapify(1);
    // for(size_t i=0; i< tree.size(); i++){
    //     cout << tree[i] << " ";
    // }
    // cout << endl;
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(int index)
{
    if(index * n_ary > (int)tree.size()){
        return;
    }
    int smaller = (index * n_ary) - (n_ary-2);
    if(tree.size() - (smaller) > 0){
        for(size_t i = 1; i < tree.size() - (smaller); i++){
            int next = (index * n_ary) - (n_ary-2) + i; 
            if(comp(tree[next], tree[smaller])){
                smaller = next; 
            }
        }
    }
    if(comp(tree[smaller], tree[index])){ 
        swap(tree[index], tree[smaller]); 
        heapify(smaller);
    }
}



#endif

