#include <vector>
using namespace std;

/**
 * Performs mergesort on the provided vector using
 * the Compare object, comp, to peform ALL comparisons
 *
 * Must run in O(n*log(n))
 */
template <class T, class Compare >
void mergeSort(std::vector<T>& list, Compare comp );
template <class T, class Compare >
void mergesortHelper(std::vector<T>& list, std::vector<T>& output, int start, int end, Compare comp);
template <class T, class Compare >
void merge(std::vector<T>& list, std::vector<T>& output, int s1, int e1, int s2, int e2, Compare comp);




template <class T, class Compare >
void mergeSort(std::vector<T>& list, Compare comp )
{
	vector<T> other(list);
	mergesortHelper(other, list, 0, list.size()-1, comp);
}

template <class T, class Compare >
void mergesortHelper(std::vector<T>& list, std::vector<T>& output, int start, int end, Compare comp)
{ 
	if(start >= end){
		return;
	}
	// recursive calls
	int mid = (start+end)/2;
	mergesortHelper(list, output, start, mid, comp);
	mergesortHelper(list, output, mid+1, end, comp);
	// merge
	merge(list, output, start, mid, mid+1, end, comp);
	list = output;
}

template <class T, class Compare >
void merge(std::vector<T>& list, std::vector<T>& output, int s1, int e1, int s2, int e2, Compare comp){
	int head = s1;
	while(s1<=e1 || s2<=e2){
		if(s1 > e1 ){
			output[head] = list[s2];
			head++;
			s2++;
		}else if(s2 > e2){
			output[head] = list[s1];
			head++;
			s1++;
		}else{
			if(comp(list[s1], list[s2])){
				output[head] = list[s1];
				s1++; 				
			}else{
				output[head] = list[s2];
				s2++;
			}
			head++;
		}
	}
}