#include "web.h"
#include <iostream>

Web::Web() 
{ 

}

Web::~Web() 
{ 

}

bool Web::read_graph(const char *filename) 
{ 
    int num, id, olinks;
    double rank;
    string url;
    ifstream input(filename);
    if(input.fail()){
        return 0;
    }
    
    
    input >> num;
    if(input.fail()){
        return 0;
    }
    
    for(int i=0; i<num; i++){
        Page p; 
        input >> id; 
        if(input.fail()){
            return 0;
        }

        input >> url; 
        if(input.fail()){
            return 0;
        }

        input >> rank; 
        if(input.fail()){
            return 0;
        }

        string s;
        getline(input, s);
        getline(input, s);
        if(input.fail()){
            return 0;
        }

        stringstream ss(s);
        while( ss >> olinks){ 
            p.add_link(olinks);
        }

        p.set_id(id);
        p.set_url(url);
        p.set_rank(rank);
        _list.push_back(p);
    }
    input.close();
    return 1;
}

bool Web::write_graph(const char *filename)
{ 
    ofstream output(filename);
    if(output.fail()){
        return 0;
    }
    
    output << _list.size() << endl;
    
    for(unsigned int i=0; i<_list.size(); i++){
        Page p = _list[i];
        output << p.get_id() << endl;
        output << '\t' << p.get_url() << endl;
        output << '\t' << p.get_rank() << endl;
        output << '\t';
        for(unsigned int j=0; j<p.get_link()->size(); j++){
            output << p.get_link()->at(j) << " ";
        }
        output << endl;
    }
    output.close();
    
    return 1;
}

void Web::calculate_rank(int S,int N)
{
    vector<int> rtn;
    //initializing a walker vector and a temp vector
    for(unsigned i=0; i<_list.size();i++){
        _walkers.push_back(N/_list.size());
        rtn.push_back(0);
    }
    
    for(int i=0; i<S; i++){
        for(unsigned j=0; j<_list.size();j++){
            for(int k=0; k<_walkers[j]; k++){
                vector<int>* link = _list[j].get_link();
                rtn[(link->at(rand()%(link->size())))]++;
            }
        }
        
        for(unsigned j=0; j<_list.size();j++){
            _walkers[j] = rtn[j];
            rtn[j]=0;
        }
    }
    
    for(unsigned int i=0; i<_list.size();i++){
        _list[i].set_rank(_walkers[i]/(double)N);
    }
    
}
