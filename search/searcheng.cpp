#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "searcheng.h"

using namespace std;
std::string extract_extension(const std::string& filename);


WebPageSet AndWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{
    WebPageSet rtn;
    for(WebPageSet::iterator it = setA.begin(); it != setA.end(); ++it){
        if(setB.find(*it) != setB.end()){
            rtn.insert(*it);
        }
    }
    return rtn;
}

WebPageSet OrWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{
    WebPageSet rtn(setA);
    for(WebPageSet::iterator it = setB.begin(); it != setB.end(); ++it){
        if(rtn.find(*it) == rtn.end()){
            rtn.insert(*it);
        }
    }
    return rtn;
}

WebPageSet DiffWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{
    WebPageSet rtn(setA);
    for(WebPageSet::iterator it = setB.begin(); it != setB.end(); ++it){
        if(rtn.find(*it) != rtn.end()){
            rtn.erase(*it);
        }
    }
    return rtn;
}

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

std::string extract_extension(const std::string& filename)
{
    size_t idx = filename.rfind(".");
    if (idx == std::string::npos) {
        return std::string();
    }
    return filename.substr(idx + 1);
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

    if(extension == ""){
        noExtensionParser_ -> parse(filename, terms, outlinks);
    }else if(extensions_.find(extension) != extensions_.end()){
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



