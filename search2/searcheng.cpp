#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "searcheng.h"
#include "util.h"

using namespace std;


SearchEng::SearchEng(PageParser* noExtensionParser)
{
    if (NULL == noExtensionParser)
    {
        throw std::invalid_argument("default parser cannot be NULL");
    }
    this->noExtensionParser_ = noExtensionParser;

    // Add additional code if necessary


}

SearchEng::~SearchEng()
{
    delete noExtensionParser_;
    extensions_.clear();
    pages_.clear();
    terms_.clear();
}

void SearchEng::register_parser(const std::string& extension, PageParser* parser)
{
    if(extensions_.find(extension) == extensions_.end()){
        extensions_[extension] = parser;
    }
}

WebPage* SearchEng::retrieve_page(const std::string& page_name) const
{
    if(pages_.find(page_name) != pages_.end()){
        return pages_.find(page_name) -> second;
    }
    return NULL;
}

void SearchEng::display_page(std::ostream& ostr, const std::string& page_name) const
{
    if(pages_.find(page_name) == pages_.end())
    {
        throw std::invalid_argument("page doesn't exist");
    }else if(extensions_.find(extract_extension(page_name)) == extensions_.end()){
        throw std::logic_error("no parser registered for this extension");
    }else{
        ostr << extensions_.find(extract_extension(page_name)) -> second -> display_text(page_name);
    }
}

WebPageSet SearchEng::search(const std::vector<std::string>& terms, WebPageSetCombiner* combiner) const
{
    WebPageSet set;
    if(terms_.find(terms[0]) != terms_.end()){
        set = *(terms_.find(terms[0])-> second);
    }
    for(size_t i=1; i<terms.size(); i++){
        if(terms_.find(terms[i]) != terms_.end()){
            WebPageSet temp = *(terms_.find(terms[i])-> second);
            set = combiner->combine(*(terms_.find(terms[i])-> second), set);
        }
    }
    return set;
}


void SearchEng::read_pages_from_index(const std::string& index_file)
{
    ifstream ifile(index_file.c_str());
    if(ifile.fail()) {
        cerr << "Unable to open index file: " << index_file << endl;
    }

    // Parse all the files
    string filename;
    while(ifile >> filename) {
#ifdef DEBUG
        cout << "Reading " << filename << endl;
#endif
        read_page(filename);
    }
    ifile.close();
}


void SearchEng::read_page(const std::string& filename)
{
    StringSet terms;
    StringSet outlinks;
    WebPage* page;
    string extension = extract_extension(filename);

    if(pages_.find(filename) == pages_.end()){
        pages_[filename] = new WebPage(filename);
    }
    page = pages_[filename];

    if(extensions_.find(extension) != extensions_.end()){
        extensions_[extension] -> parse(filename, terms, outlinks);
    }else{
        throw std::logic_error("extension without parser");
    }

    page -> all_terms(terms);

    for(StringSet::iterator it = outlinks.begin(); it!= outlinks.end(); ++it){
        if(pages_.find(*it) == pages_.end()){
            pages_[*it] = new WebPage(*it);
        }
        page -> add_outgoing_link(pages_[*it]);
        pages_[*it] -> add_incoming_link(page);
    }

    for(StringSet::iterator it = terms.begin(); it!= terms.end(); ++it){
        if(terms_.find(*it) == terms_.end()){
            terms_[*it] = new WebPageSet;
        }
        terms_[*it] -> insert(page);
    }
}

std::vector<std::pair<WebPage*, double>> SearchEng::pageRank(const WebPageSet& in_pages)
{
    WebPageSet temp = in_pages;
    std::vector<std::pair<WebPage*, double>> rtn;
    map<WebPage*, double> numLinks; 
    double n = in_pages.size(); 
    for(WebPageSet::iterator it = temp.begin(); it != temp.end(); ++it){
        if((*it)->incoming_links().find(*it) != (*it)->incoming_links().end()){
            (*it)->add_incoming_link(*it);
        }

        if((*it)->outgoing_links().find(*it) != (*it)->outgoing_links().end()){
            (*it)->add_outgoing_link(*it);
        }

        double count = 0;
        for (auto& p : (*it)->outgoing_links())
        {
            if(in_pages.find(p) != in_pages.end()){
                count++;
            }
            numLinks[*it] = count;
        }
        cout << endl;

        rtn.push_back(make_pair((*it), double(1/n)));
    }

    vector<std::pair<WebPage*, double>> vecTemp = rtn;
    for(size_t t=0; t<20; t++){
        for(size_t i=0; i<rtn.size(); i++){
            cout << "this file: " << rtn[i].first -> filename() << endl;
            double sum = 0;
            for(size_t j=0; j<vecTemp.size(); j++){
                WebPageSet out_links = vecTemp[j].first -> outgoing_links();
                if(out_links.find(rtn[i].first) != out_links.end()){
                    sum += (vecTemp[j].second)/(numLinks.find(vecTemp[j].first)->second);
                }
            }
            rtn[i].second = (0.85 * sum)  + (0.15/n);
        }
        vecTemp = rtn;
        cout << t << endl;
        for (auto& p : rtn)
        {
            cout << p.first->filename() << " : " << p.second << std::endl;
        }
        cout << endl;
    }
    return rtn;
}



