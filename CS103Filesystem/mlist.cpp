#include <iostream>
#include "mlist.h"
using namespace std;
//------------------------------------------------------------------------------
//IMPORTANT: You are not allowed to remove or add any parameters to any functions.
//NOTE: There can only be at most 3 loops in this file
//------------------------------------------------------------------------------

//Constructor, construct an empty doubly linked list.
MList::MList(){
    ntop = NULL;
    nbottom = NULL;
}

//Destructor, properly clears and deallocates everything of current list.
//simply call the clear function if you have already implemented that.
MList::~MList(){
    clear();
}

//Note: RECURSION --- This function should be implemented using recursion.
//this function properly clears and deallocates everything of current list.
//there should be no loop in this function
void MList::clear(){
    if(isEmpty()){
        return;
    }
    pop_bottom();
    clear();
}

//returns a boolean true if the list is empty, false if otherwise.
bool MList::isEmpty(){
    if(ntop == NULL){
        return 1;
    }
    return 0;
}

/*
	Add or insert a new node with d_item as its data at the top of the list.
	You need to dynamically allocate memory for the new node.
*/
void MList::push_top(Data* d_item){
    if(isEmpty()){
        Node* n_item = new Node;
        n_item -> nodeData = d_item;
        n_item -> prev = NULL;
        n_item -> next = NULL;
        ntop = n_item;
        nbottom = n_item;
    }else{
        Node* n_item = new Node;
        n_item -> nodeData = d_item;
        n_item -> prev = NULL;
        n_item -> next = ntop;
        ntop -> prev = n_item;
        ntop = n_item;
    }

}

/*
	Add or insert a new node with d_item as its data at the bottom of the list.
	You need to dynamically allocate memory for the new node.
*/
void MList::push_bottom(Data* d_item){
    if(isEmpty()){
        Node* n_item = new Node;
        n_item -> nodeData = d_item;
        n_item -> prev = NULL;
        n_item -> next = NULL;
        ntop = n_item;
        nbottom = n_item;
    }else{
        Node* n_item = new Node;
        n_item -> nodeData = d_item;
        n_item -> prev = nbottom;
        n_item -> next = NULL;
        nbottom -> next = n_item;
        nbottom = n_item;
    }  
}

/*
	Delete or remove the top node of the list.
	Once pop, you need to properly deallocate the memory for the node (not the data).
	If your list is currently empty, you don't have to do anything.
*/
void MList::pop_top(){
    if(!isEmpty()){
        if(ntop == nbottom){
            delete ntop; 
            ntop = NULL;
            ntop = NULL;
        }else{
            ntop = ntop -> next;
            delete ntop -> prev;
            ntop->prev = NULL;
        }
    }
}

/*
	Delete or remove the bottom node of the list.
	Once pop, you need to properly deallocate the memory for the node (not the data).
	If your list is currently empty, you don't have to do anything.
*/
void MList::pop_bottom(){
    if(!isEmpty()){
        if(ntop==nbottom){
            delete nbottom;
            ntop = NULL;
            nbottom = NULL;
        }else{
            nbottom = nbottom -> prev;
            delete nbottom -> next;
            nbottom->next = NULL;
        }
    }
}

/*
	Note: RECURSION --- This function should be implemented using recursion.
	Search a node in the list that has data with the same name as the parameter.
	If one is found, return the pointer to the node.
	If one is not found, return NULL.
*/
Node* MList::search(Node* start, string name){
    if(start == NULL){
        return NULL;
    }else if(start->nodeData->name == name){
        return start;
    }
    return search(start->next, name);
}


//Swapping node a with node b.
void MList::swapNode(Node* a, Node*b){
    if(a == b){
        return;
    }else if(a->next == b){
        removeNode(a);
        insertAfter(a, b);
    }else if(a->prev == b){
        removeNode(b);
        insertAfter(b, a);
    }else{
        Node* temp1 = a->prev;
        Node* temp2 = b->prev;
        removeNode(a);
        removeNode(b);
        insertAfter(a, temp2);
        insertAfter(b, temp1);
    }

}

/*
	This function PERMANENTLY deletes a node from the list given a pointer to that node.
	You can assume that the node exists in the list - no need to search for the node.
*/
void MList::deleteNode(Node* a){
    if(ntop == nbottom){
        pop_top();
        ntop = NULL;
        nbottom = NULL;
    }else if(a == ntop){
        pop_top();
    }else if(a == nbottom){
        pop_bottom();
    }else{
        a -> prev -> next = a ->next;
        a -> next -> prev = a ->prev;
        delete a;
    }
}

/*
	Unlike the delete function above, this function does NOT permanently delete the node.
	What you need to do at the last step is to set the node's prev and next pointers to NULL.
	Again, you can assume that the node exists in the list - no need to search for the node.
	Note: this function will be useful
        when we want to insert the given node later at another position after you remove it from the list.
*/
void MList::removeNode(Node* a){
    if(ntop == nbottom){
        ntop = NULL;
        nbottom = NULL;     
    }else if(a == ntop){
        ntop = a->next;
        a -> next -> prev = NULL;
    }else if(a == nbottom){
        nbottom = a->prev;
        a -> prev -> next = NULL;
    }else{
        a -> prev -> next = a -> next;
        a -> next -> prev = a -> prev;
    }
    
    a->prev = NULL;
    a->next = NULL;
}

/*
	Insert node a after node b.
	Note: b can be NULL, Q: what does that mean?
    otherwise, you can assume that b exists in the list.
*/
void MList::insertAfter(Node *a, Node* b){
    if(isEmpty()){
        a -> next = NULL;
        a -> prev = NULL;
        ntop = a;
        nbottom = a;
    }else if(b==NULL){
        a -> next = ntop;
        a -> prev = NULL;
        ntop->prev = a;
        ntop = a;
    }else if(b == nbottom){
        a -> next = NULL;
        a -> prev = b;
        b -> next = a;
        nbottom = a;
    }else{
        a -> prev = b;
        a -> next = b->next;
        b-> next-> prev = a;
        b->next = a;

    } 
}


/*
	Note: RECURSION --- This function should be implemented using recursion.
	Implement a SELECTION SORT algorithm using recursion.
	The function takes in a start node.
	Things to keep in mind:
		1). sort should NOT be run if the list is empty.
		2). if mode = true, sort by name in alphabetical order
			(i.e., A-Za-z) based on ASCII number if mode = true
        3). if mode = false, sort by size in ascending order (low->high)
	You can search any online resources available to you (i.e. search 'selection sort')
	to understand the basic idea behind the selection sort algorithm.
    Note: 
        1). there can only be at most one loop in this function
        2). this function is private
            see sortByNameSelection and sortBySizeSelection for the calls to this function
*/
void MList::sortSelection(Node* start, bool mode){
    if(start == NULL || ntop == nbottom){
        return;
    }

    // find min
    Node* track = start;
    Node* min = start;
    while(track !=NULL){
        if(mode){
            if(track-> nodeData ->name < min-> nodeData-> name){
                min = track;
            }
        }else{
            if(track-> nodeData ->size < min-> nodeData-> size){
                min = track;
            }
        }
        track = track->next;
    }
    //swap
    swapNode(min, start); 
    sortSelection(min->next, mode);
}


/*
	Note: RECURSION --- This function should be implemented using recursion.
	Implement an INSERTION SORT algorithm using recursion.
	The function takes in a start node.
	Things to keep in mind:
		1). sort should NOT be run if the list is empty.
		2). we are trying to sort by name in alphabetical order
			(i.e., A-Za-z) based on ASCII number.
	You can search any online resources available to you (i.e. search 'insertion sort')
	to understand the basic idea behind the insertion sort algorithm.
	The gif from the wikipedia page of this algorithm is the easiest to understand in my opinion
	Link: https://en.wikipedia.org/wiki/Insertion_sort
    Note: 
        1). there can only be at most one loop in this function
        2). this function is private, see sortByNameInsertion for the call to this function
*/
void MList::sortInsertion(Node* start){
    if(start == NULL || ntop == nbottom){
        return;
    }
    
    Node* temp = start;
    Node* track = start -> prev;
    while(track !=NULL && start-> nodeData ->name < track-> nodeData-> name){
        track = track->prev;
    }
    //insert
    removeNode(start);
    insertAfter(start, track);
    sortInsertion(temp->next);
}


/*
	Note: RECURSION --- This function should be implemented using recursion.
	Traverse and print our list from node n to the top.
	we will seperate each node printed by the passed-in delimiter.
	If a node you encounter is a folder type, do

		cout<<....name.....<<delim;

	If a node you encounter is a file type, do

		cout<<....name.....<<"("<<..size..<<")"<<delim;

	Note: please do NOT include <<endl; (aka newline)
	Example output (assume that the delimiter is a single space):
    
		folder1 file1(0) folder2 file2(0)

    There should be no loop in this function
	See printBtT function for the call to this function.
    This function is private
*/
void MList::traverseToTop(Node* n, string delim){
    if(n == NULL){
        return;
    }
    if(n-> nodeData -> isFolder){
        cout << n-> nodeData -> name << delim;
    }else if(!n-> nodeData -> isFolder){
        cout << n-> nodeData -> name << "("<< n->nodeData -> size <<")" << delim;
    }
    traverseToTop(n->prev, delim);
}

/*
	Note: RECURSION --- This function should be implemented using recursion.
	Traverse and print our list from node n to the bottom.
	we will seperate each node printed by the passed-in delimiter.
	If a node you encounter is a folder type, do

		cout<<....name.....<<delim;

	If a node you encounter is a file type, do

		cout<<....name.....<<"("<<..size..<<")"<<delim;

	Note: please do NOT include <<endl; (aka newline)
	Example output (assume that the delimiter is a single space):
    
		folder1 file1(0) folder2 file2(0)

    There should be no loop in this function
	See printTtB function for the call to this function.
    This function is private
*/
void MList::traverseToBottom(Node* n,string delim){
    if(n == NULL){
        return;
    }
    if(n-> nodeData -> isFolder){
        cout << n-> nodeData -> name << delim;
    }else if(!n-> nodeData -> isFolder){
        cout << n-> nodeData -> name << "("<< n->nodeData -> size <<")" << delim;
    }
    traverseToBottom(n->next, delim);
}

//------------------------------------------------------------------------------
//FUNCTIONS BELOW ARE COMPLETE, PLEASE DON'T CHANGE ANYTHING HERE
//------------------------------------------------------------------------------

//getting the pointer to the top node.
Node* MList::top(){
	return ntop;
}

//getting the pointer to the bottom node.
Node* MList::bottom(){
	return nbottom;
}

//call traverseToBottom to print all item in the list from bottom node to top node
//the list of items is separated by a given delimiter
void MList::printBtT(string delim){
	//create a temp pointer to hold bottom
	Node* tmp = nbottom;
	traverseToTop(tmp,delim);
}

//call traverseToBottom to print all item in the list from top node to bottom node
//the list of items is separated by a given delimiter
void MList::printTtB(string delim){
	Node* tmp = ntop;
	traverseToBottom(tmp,delim);
}

//call sortSelection function, mode = true = sort by name
//public member
void MList::sortByNameSelection(){
    bool mode = true;
    Node *tmp = ntop;
    sortSelection(tmp,mode);
}

//call sortSelection function, mode = false = sort by size
//public member
void MList::sortBySizeSelection(){
    bool mode = false;
    Node *tmp = ntop;
    sortSelection(tmp,mode);
}

//call sortInsertion function
//public member
void MList::sortByNameInsertion(){
    Node *tmp = ntop;
    sortInsertion(tmp);
}