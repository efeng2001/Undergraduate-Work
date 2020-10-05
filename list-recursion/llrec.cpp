#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot)
{	
	if(head == NULL){
		return;
	}
	Node* temp = head -> next;
	if(head->val <= pivot){
		if(smaller ==NULL){
			smaller = head;
			head = NULL;
			smaller -> next = NULL;
			llpivot(temp, smaller ,larger, pivot);
		}else{
			smaller -> next = head;
			head -> next = NULL;
			llpivot(temp, head ,larger, pivot);
		}
	}else if(head->val > pivot){
		if(larger ==NULL){
			larger = head;
			head = NULL;
			larger -> next = NULL;
			llpivot(temp, smaller ,larger, pivot);
		}else{
			larger -> next = head;
			head -> next = NULL;
			llpivot(temp, smaller ,head, pivot);
		}
	}	
}
