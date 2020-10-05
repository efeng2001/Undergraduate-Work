#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <queue>
#include "pageparser.h"
#include "md_parser.h"
#include "txt_parser.h"
#include "util.h"

using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 3) {
        cout << "Must provide an index file and output file" << endl;
        return 1;
    }

    // ---------------------- [TO BE COMPLETED] -------------------------------

    ifstream ifile(argv[1]);
    if(ifile.fail()) {
        cerr << "Unable to open seed file: " << argv[1] << endl;
    }

    ofstream ofile(argv[2]);
    if(ofile.fail()) {
        cerr << "Unable to open index file: " << argv[2] << endl;
    }

    
    set<string> processed;
    map<string, PageParser*> extensions_;

    extensions_[""] = new TXTParser;
    extensions_["md"] = new MDParser;
    extensions_["txt"] = new TXTParser;

    string filename;

    while(ifile >> filename) {
    	if(processed.find(filename) == processed.end()){
    		processed.insert(filename);
    		string extension = extract_extension(filename);
	    	if(extensions_.find(extension) != extensions_.end()){
	    		extensions_.find(extension) -> second -> crawl(extensions_, filename, processed, ofile);
	    	}
    	}
    }
    
    // You may add cleanup code here if necessary
    ifile.close();

    return 0;
}
