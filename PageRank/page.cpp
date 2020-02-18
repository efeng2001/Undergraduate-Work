#include "page.h"

Page::Page() 
{

}

int Page:: get_id(){
    return _id;
}
    
string Page:: get_url(){
    return _url;
}

double Page:: get_rank(){
    return _rank;
}

vector <int>* Page:: get_link(){
    return &_link;
}

  
void Page:: set_id(int id){
    _id = id;
}

void Page:: set_url(string url){
    _url = url;
}

void Page:: set_rank(double rank){
    _rank = rank;
}

void Page:: add_link(int id){
    _link.push_back(id);
}
