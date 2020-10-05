#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rotateLeft(AVLNode<Key,Value>* current);
    void rotateRight(AVLNode<Key,Value>* current);
    void insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
    void removeFix(AVLNode<Key,Value>* n, char diff);

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight (AVLNode<Key,Value>* current)
{
    AVLNode<Key,Value>* b = current -> getLeft();
    if(current->getParent() == NULL){
        BinarySearchTree<Key, Value>::root_ = b;
        b -> setParent(NULL);
    }else{
        if(current->getParent() -> getLeft() == current){
            current -> getParent() -> setLeft(b);
        }else{
            current -> getParent() -> setRight(b);
        }
        b -> setParent(current -> getParent());
    }

    current -> setLeft(b -> getRight());
    if(b->getRight() != NULL){
        b -> getRight() -> setParent(current);
    }

    b -> setRight(current);
    current -> setParent(b);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft (AVLNode<Key,Value>* current)
{
    AVLNode<Key,Value>* b = current -> getRight();
    if(current->getParent() == NULL){
        BinarySearchTree<Key, Value>::root_ = b;
        b -> setParent(NULL);
    }else{
        if(current->getParent() -> getLeft() == current){
            current -> getParent() -> setLeft(b);
        }else{
            current -> getParent() -> setRight(b);
        }
        b -> setParent(current -> getParent());
    }

    current -> setRight(b -> getLeft()); 
    if(b->getLeft() != NULL){
        b -> getLeft() -> setParent(current);
    }

    b -> setLeft(current);
    current -> setParent(b);
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix (AVLNode<Key,Value>* p, AVLNode<Key,Value>* n){
    if(p == NULL || p-> getParent() == NULL){
        return;
    }
    AVLNode<Key,Value>* g = p -> getParent();
    if(g -> getLeft() == p){
        g -> updateBalance(-1);
        if(g -> getBalance() ==0){
            return;
        }else if(g -> getBalance() == -1){
            insertFix(g,p);
        }else if(g -> getBalance() == -2){
            if(p -> getBalance() < 0){
                rotateRight(g);
                p -> setBalance(0);
                g -> setBalance(0);
            }else if(p -> getBalance() > 0){
                rotateLeft(p);
                rotateRight(g);
                if(n -> getBalance() == -1){
                    p -> setBalance(0);
                    g -> setBalance(1);
                    n -> setBalance(0);
                }else if(n -> getBalance() == 0){
                    p -> setBalance(0);
                    g -> setBalance(0);
                    n -> setBalance(0);
                }else if(n -> getBalance() == 1){
                    p -> setBalance(-1);
                    g -> setBalance(0);
                    n -> setBalance(0);
                }
            }
        }
    }else{
        g -> updateBalance(1);
        if(g -> getBalance() ==0){
            return;
        }else if(g -> getBalance() == 1){
            insertFix(g,p);
        }else if(g -> getBalance() == 2){
            if(p -> getBalance() > 0){
                rotateLeft(g);
                p -> setBalance(0);
                g -> setBalance(0);
            }else if(p -> getBalance() < 0){
                rotateRight(p);
                rotateLeft(g);
                if(n -> getBalance() == 1){
                    p -> setBalance(0);
                    g -> setBalance(-1);
                    n -> setBalance(0);
                }else if(n -> getBalance() == 0){
                    p -> setBalance(0);
                    g -> setBalance(0);
                    n -> setBalance(0);
                }else if(n -> getBalance() == -1){
                    p -> setBalance(1);
                    g -> setBalance(0);
                    n -> setBalance(0);
                }
            }
        }
    }
}


template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    if(BinarySearchTree<Key, Value>::root_ == NULL){
        AVLNode<Key, Value>* add = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
        add-> setBalance(0);
        add -> setLeft(NULL);
        add -> setRight(NULL);
        BinarySearchTree<Key, Value>::root_ = add;
        return;
    }else{
        AVLNode<Key, Value>* current = (AVLNode<Key, Value>*)BinarySearchTree<Key, Value>::root_;
        while(current != NULL){
            if(current -> getKey() == new_item.first){
                current -> setValue(new_item.second);
                return;
            }else if(current -> getKey() > new_item.first){
                if(current -> getLeft() == NULL){
                    AVLNode<Key, Value>* add = new AVLNode<Key, Value>(new_item.first, new_item.second, current);
                    add -> setBalance(0);
                    add -> setLeft(NULL);
                    add -> setRight(NULL);
                    current -> setLeft(add);
                    if(current -> getBalance() == -1){
                        current -> setBalance(0);
                    }else if(current -> getBalance() == 1){
                        current -> setBalance(0);
                    }else if(current -> getBalance() == 0){
                        current -> updateBalance(-1);
                        insertFix(current, add);
                    }
                    return;
                }else{
                    current = current -> getLeft();
                }
            }else if(current -> getKey() < new_item.first){
                if(current -> getRight() == NULL){
                    AVLNode<Key, Value>* add = new AVLNode<Key, Value>(new_item.first, new_item.second, current);
                    add -> setBalance(0);
                    add -> setLeft(NULL);
                    add -> setRight(NULL);
                    current -> setRight(add);
                    if(current -> getBalance() == -1){
                        current -> setBalance(0);
                    }else if(current -> getBalance() == 1){
                        current -> setBalance(0);
                    }else if(current -> getBalance() == 0){
                        current -> updateBalance(1);
                        insertFix(current, add);
                    }
                    return;
                }else{
                    current = current -> getRight();
                }
            }
        }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    std::cout << "deleting " << key << std::endl;
    BinarySearchTree<Key, Value>::print();

    AVLNode<Key, Value>* current = (AVLNode<Key, Value>*) BinarySearchTree<Key, Value>::internalFind(key);
    if(current == NULL){
        return;
    }else{
        if(current -> getRight() != NULL && current -> getLeft() != NULL){
            // case for 2 children
            AVLNode<Key, Value>* pre = (AVLNode<Key, Value>*) BinarySearchTree<Key, Value>::predecessor(current);
            nodeSwap(pre, current);
        }

        AVLNode<Key, Value>* p = current -> getParent();
        char diff; 
        if(p != NULL){
            if(p -> getLeft() == current){
                diff = 1;
            }else{
                diff = -1;
            }
        }


        if(current -> getRight() == NULL && current -> getLeft() != NULL){
            //case for 1 chidlren (left)
            if(current == BinarySearchTree<Key, Value>::root_){
                BinarySearchTree<Key, Value>::root_ = current -> getLeft();
                current -> getLeft() -> setParent(NULL);
            }else{
                if(p -> getLeft() == current){
                    p -> setLeft(current -> getLeft());
                    current -> getLeft() -> setParent(current -> getParent());
                }else{
                    p -> setRight(current -> getLeft());
                    current -> getRight() -> setParent(current -> getParent());
                }
            }
        }else if(current -> getLeft() == NULL && current -> getRight() != NULL){
            //case for 1 chidlren (right)
            if(current == BinarySearchTree<Key, Value>::root_){
                BinarySearchTree<Key, Value>::root_ = current -> getRight();
                current -> getRight() -> setParent(NULL);
            }else{
                if(p-> getLeft() == current){
                    p -> setLeft(current -> getRight());
                    current -> getRight() -> setParent(current -> getParent());
                }else{
                    p -> setRight(current -> getRight());
                    current -> getRight() -> setParent(current -> getParent());
                }
            }
        }else{
            //0 children
            if(current == BinarySearchTree<Key, Value>::root_){
                BinarySearchTree<Key, Value>::root_ = NULL;
            }else{
                if(p -> getLeft() == current){
                    p -> setLeft(NULL);
                }else{
                    p -> setRight(NULL);
                }     
            }
        }
        removeFix(p, diff);
        delete current;
    }
    std::cout << "finish deleting " << key << std::endl;
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* n, char diff)
{
    if(n == NULL){
        return;
    }
    AVLNode<Key, Value>* p = n -> getParent();
    if(p == NULL){
        return;
    }
    char ndiff; 
    if(p -> getLeft() == n){
        ndiff = 1;
    }else{
        ndiff = -1;
    }
    if(diff == -1){
        if(n -> getBalance()+ diff == -2){
            AVLNode<Key, Value>* c = n -> getLeft();
            if(c -> getBalance() == -1){
                rotateRight(n);
                n -> setBalance(0);
                c -> setBalance(0);
                removeFix(p, ndiff);
            }else if(c -> getBalance() == 0){
                rotateRight(n);
                n -> setBalance(-1);
                c -> setBalance(1);
            }else if(c -> getBalance() == 1){
                AVLNode<Key, Value>* g = c -> getRight();
                rotateLeft(c);
                rotateRight(n);
                if(g -> getBalance() == 1){
                    n -> setBalance(0);
                    c -> setBalance(-1);
                    g -> setBalance(0);
                }else if(g -> getBalance() == 0){
                    n -> setBalance(0);
                    c -> setBalance(0);
                    g -> setBalance(0);
                }else if(g -> getBalance() == -1){
                    n -> setBalance(1);
                    c -> setBalance(0);
                    g -> setBalance(0);
                }
                removeFix(p, ndiff);
            }
        }else if(n -> getBalance()+ diff == -1){
            n -> setBalance(-1);
        }else if(n -> getBalance()+ diff == 0){
            n -> setBalance(0);
            removeFix(p, ndiff);
        }
    }else if(diff == 1){
        if(n -> getBalance()+ diff == 2){
            AVLNode<Key, Value>* c = n -> getRight();
            if(c -> getBalance() == 1){
                rotateLeft(n);
                n -> setBalance(0);
                c -> setBalance(0);
                removeFix(p, ndiff);
            }else if(c -> getBalance() == 0){
                rotateLeft(n);
                n -> setBalance(1);
                c -> setBalance(-1);
            }else if(c -> getBalance() == -1){
                AVLNode<Key, Value>* g = c -> getLeft();
                rotateRight(c);
                rotateLeft(n);
                if(g -> getBalance() == -1){
                    n -> setBalance(0);
                    c -> setBalance(1);
                    g -> setBalance(0);
                }else if(g -> getBalance() == 0){
                    n -> setBalance(0);
                    c -> setBalance(0);
                    g -> setBalance(0);
                }else if(g -> getBalance() == 1){
                    n -> setBalance(-1);
                    c -> setBalance(0);
                    g -> setBalance(0);
                }
                removeFix(p, ndiff);
            }else if(n -> getBalance()+ diff == 0){
                n -> setBalance(0);
                removeFix(p, ndiff);
            }else if(n -> getBalance()+ diff == 1){
                n -> setBalance(1);
            }
        }
    }

}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
