#ifndef PAGE_H
#define PAGE_H
#include <string>
using std::string;
#include<vector>
using std::vector;
class Page { 
public:
  Page();
  //setters and getters
    int get_id();
    string get_url();
    double get_rank();
    vector <int>* get_link();
  
    void set_id(int id);
    void set_url(string url);
    void set_rank(double rank);
    void add_link(int id);
private:
  //Data members: id, url, pagerank, links , .. etc
    int _id;
    string _url;
    double _rank;
    vector <int> _link;
};  
#endif
