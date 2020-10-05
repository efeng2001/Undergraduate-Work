#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include "md_parser.h"
#include "util.h"

using namespace std;

typedef enum { NORMALTEXT, LINKTEXT, ISLINK, LINKURL } PARSE_STATE_T;


void MDParser::parse(std::string filename, std::set<std::string>& allSearchableTerms, std::set<std::string>& allOutgoingLinks)
{
    // Attempts to open the file.
    ifstream wfile(filename.c_str());
    if(!wfile) {
        throw invalid_argument("Bad webpage filename in MDParser::parse()");
    }

    // Remove any contents of the sets before starting to parse.
    allSearchableTerms.clear();
    allOutgoingLinks.clear();

    // The initial state is parsing a normal term.
    PARSE_STATE_T state = NORMALTEXT;

    // Initialize the current term and link as empty strings.
    string term = "";
    string link = "";

    // Get the first character from the file.
    char c = wfile.get();

    // Continue reading from the file until input fails.
    while(!wfile.fail())
    {
        // Logic for parsing a normal term.
        if(state == NORMALTEXT)
        {
            // ADD YOUR CODE HERE
            if(isalnum(c)){
                term += c;
            }else{
                if(term != "")
                {
                    term = conv_to_lower(term);
                    allSearchableTerms.insert(term);
                }
                term = "";
            }

            if(c =='[')
            {
                state = LINKTEXT;
            }
        }
        // Logic for parsing a link.
        else if (state == LINKTEXT)
        {
            // ADD YOUR CODE HERE
            if(isalnum(c)){
                term += c;
            }else{
                if(term != "")
                {
                    term = conv_to_lower(term);
                    allSearchableTerms.insert(term);
                }
                term = "";
            }

            if(c==']'){
                state = ISLINK;
            }
        }
        else if( state == ISLINK )
        {
            // ADD YOUR CODE HERE
            if(isalnum(c)){
                term += c;
            }else{
                term = "";
            }

            if(c =='(')
            {
                state = LINKURL;
            }else {
                state = NORMALTEXT;
            }
        }
        // Else we are in the LINKURL state.
        else
        {
            // ADD YOUR CODE HERE
            if(c != ')'){
                link += c;
            }else{
                allOutgoingLinks.insert(link);
                link = "";
                state = NORMALTEXT;
            }
        }
        // Attempt to get another character from the file.
        c = wfile.get();
    }
    // ADD ANY REMAINING CODE HERE
    if(term != "")
    {
        term = conv_to_lower(term);
        allSearchableTerms.insert(term);
    }
    // Close the file.
    wfile.close();
}

std::string MDParser::display_text(std::string filename)
{
    // Attempts to open the file.
    ifstream wfile(filename.c_str());
    if (!wfile) {
        throw std::invalid_argument("Bad webpage filename in TXTParser::parse()");
    }
    std::string retval;

    // The initial state is parsing a normal term.
    PARSE_STATE_T state = NORMALTEXT;

    char c = wfile.get();

    // Continue reading from the file until input fails.
    while (!wfile.fail()) {
        // Logic for parsing a normal term.
        if (state == NORMALTEXT)
        {
            // The moment we hit a bracket, we input our current working term
            // into the allSearchableTerms set, reset the current term, and move into
            // parsing a link.
            if (c == '[')
            {
                state = LINKTEXT;
            }
            retval += c;
        }
        // Logic for parsing a link.
        else if (state == LINKTEXT)
        {
            // When we hit the closing bracket, then we must be finished getting the link.
            if (c == ']')
            {
                state = ISLINK;
            }
            retval += c;
        }
        else if (state == ISLINK) {
            if (c == '(') {
                state = LINKURL;
            }
            else
            {
                state = NORMALTEXT;
                retval += c;
            }
        }
        // Else we are in the LINKURL state.
        else
        {
            // When we hit a closing parenthese then we are done, and the link can be inserted.
            if (c == ')')
            {
                state = NORMALTEXT;
            }
        }
        c = wfile.get();
    }
    return retval;
}


void MDParser::crawl(const std::map<std::string, PageParser*>& parsers, std::string filename, std::set<std::string>& processed, std::ostream& ofile){
    string file;
    stack<string> list;
    set<string> links;
    set<string> temp;

    list.push(filename);
    parse(filename, temp, links);

    while(!list.empty()){
        ofile <<  list.top() << endl;
        list.pop();
        for(set<string>::iterator it= links.begin(); it!=links.end(); ++it){
            if(processed.find(*it)==processed.end()){
                processed.insert(*it);
                list.push(*it);    
                // add helper
                crawl_helper(parsers, *it, processed, ofile, list); 
            }
        }
    }
}

void MDParser::crawl_helper(const std::map<std::string, PageParser*>& parsers, std::string filename, std::set<std::string>& processed, std::ostream& ofile, std::stack<std::string>& stack){
    set<string> links;
    set<string> temp;

    string extension = extract_extension(filename);

    if(parsers.find(extension) != parsers.end()){
        parsers.find(extension) -> second -> parse(filename, temp, links);
        ofile <<  stack.top() << endl;
        stack.pop();

        for(set<string>::iterator it= links.begin(); it!=links.end(); ++it){
            if(processed.find(*it)==processed.end()){
                processed.insert(*it);
                stack.push(*it); 
                crawl_helper(parsers, *it, processed, ofile, stack); 
            }
        }
    }else{
        ofile <<  stack.top() << endl;
        stack.pop();
    }
}

