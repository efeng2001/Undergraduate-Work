#include "expr-reader.h"
#include "expr-ops.h"
#include <iostream>

using namespace std;
/*-----------------------------------------------------------------------------
 *  Implement the following functions below.
 *  Processing of each (sub)expression must be recursive (i.e. loops
 *    may only be used to iterate through the child vector of the given node).
 *  You may define recursive helper functions to adapt the function signatures.
 *    However, only exprPrinter likely needs a helper function.
 ----------------------------------------------------------------------------*/

void exprPrinter(std::ostream& ostr, Node* n)
{
	if(n->children.empty()){
		ostr << n->val << " ";
		return;
	}else{
		ostr << "( ";
		exprPrinter(ostr, (n->children)[0]);
		for(size_t i = 1; i < (n->children).size(); i++){
			ostr << n->val << " ";
			exprPrinter(ostr, n->children[i]);
		}
		ostr << ") ";
	}
}


int exprSolver(Node* n)
{
    /* Should never be called on NULL expression -- Do Not Modify */
    if(n == NULL ) {
        throw std::logic_error("Can't solve a NULL expression");
    }else if(n->children.empty()){
		return stoi(n->val);
	}else{
		int rtn = exprSolver(n->children[0]); 
		for(size_t i = 1; i < (n->children).size(); i++){
			if(n->val == "+"){
				rtn += exprSolver(n->children[i]); 
			}else if(n->val == "-"){
				rtn -= exprSolver(n->children[i]); 
			}else if(n->val == "/"){
				rtn /= exprSolver(n->children[i]); 
			}else if(n->val == "*"){
				rtn *= exprSolver(n->children[i]); 
			}
		}
		return rtn;
	}
}

bool exprIsValid(Node* n)
{
	if(n->children.empty()){
		for (size_t i = 0; i < n->val.length(); i++){
	   		if (isdigit((n->val)[i]) == false) {
	        	return false; 
	   		}
	    }
	    return true;
	}else{
		bool rtn = true;
		for(size_t i=0; i<n->children.size();i++){
			if(!exprIsValid(n->children[i])){
				rtn = false;
			}
		}
		return rtn;
	}
}
