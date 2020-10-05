#include "cmdhandler.h"
#include "util.h"
#include <vector>
using namespace std;

QuitHandler::QuitHandler()
{

}

QuitHandler::QuitHandler(Handler* next)
    : Handler(next)
{

}

bool QuitHandler::canHandle(const std::string& cmd) const
{
    return cmd == "QUIT";

}

Handler::HANDLER_STATUS_T QuitHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    return HANDLER_QUIT;
}

PrintHandler::PrintHandler()
{

}

PrintHandler::PrintHandler(Handler* next)
    : Handler(next)
{

}

bool PrintHandler::canHandle(const std::string& cmd) const
{
    return cmd == "PRINT";
}

Handler::HANDLER_STATUS_T PrintHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    try {
        eng->display_page(ostr, name);
    }
    catch (std::exception& e) {
        return HANDLER_ERROR;
    }
    return HANDLER_OK;
}

IncomingHandler::IncomingHandler()
{

}

IncomingHandler::IncomingHandler(Handler* next)
    : Handler(next)
{

}

bool IncomingHandler::canHandle(const std::string& cmd) const
{
    return cmd == "INCOMING";

}

Handler::HANDLER_STATUS_T IncomingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;
    WebPage* page;
    WebPageSet set;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }

    try{
        page = eng -> retrieve_page(name);
    }catch(std::exception& e){
        return HANDLER_ERROR;
    }

    set = page -> incoming_links();
    ostr << set.size() << endl;
    for(WebPageSet::iterator it = set.begin(); it!= set.end(); ++it){
        ostr << (*it) -> filename() << endl;
    }

    return  HANDLER_OK;
}

OutgoingHandler::OutgoingHandler()
{

}

OutgoingHandler::OutgoingHandler(Handler* next)
    : Handler(next)
{

}

bool OutgoingHandler::canHandle(const std::string& cmd) const
{
    return cmd == "OUTGOING";

}

Handler::HANDLER_STATUS_T OutgoingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;
    WebPage* page;
    WebPageSet set;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }

    try{
        page = eng -> retrieve_page(name);
    }catch(std::exception& e){
        return HANDLER_ERROR;
    }

    set = page -> outgoing_links();
    ostr << set.size() << endl;
    for(WebPageSet::iterator it = set.begin(); it!= set.end(); ++it){
        ostr << (*it) -> filename() << endl;
    }

    return  HANDLER_OK;
}

AddHandler::AddHandler()
{

}

AddHandler::AddHandler(Handler* next)
    : Handler(next)
{

}

bool AddHandler::canHandle(const std::string& cmd) const
{
    return cmd == "AND";
}

Handler::HANDLER_STATUS_T AddHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    vector<string> list;
    string name;
    WebPageSetCombiner* combiner = new AndWebPageSetCombiner;

    if (!(instr >> name)) {
        return HANDLER_OK;
    }
    list.push_back(name);

    while(instr >> name){
        list.push_back(name);
    }

    WebPageSet set = eng -> search(list, combiner);
    display_hits(set, ostr);

    return HANDLER_OK;
}

OrHandler::OrHandler()
{

}

OrHandler::OrHandler(Handler* next)
    : Handler(next)
{

}

bool OrHandler::canHandle(const std::string& cmd) const
{
    return cmd == "OR";
}

Handler::HANDLER_STATUS_T OrHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    vector<string> list;
    string name;
    WebPageSetCombiner* combiner = new OrWebPageSetCombiner;

    if (!(instr >> name)) {
        return HANDLER_OK;
    }
    list.push_back(name);

    while(instr >> name){
        list.push_back(name);
    }

    WebPageSet set = eng -> search(list, combiner);
    display_hits(set, ostr);

    return HANDLER_OK;
}

DiffHandler::DiffHandler()
{

}

DiffHandler::DiffHandler(Handler* next)
    : Handler(next)
{

}

bool DiffHandler::canHandle(const std::string& cmd) const
{
    return cmd == "DIFF";
}

Handler::HANDLER_STATUS_T DiffHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    vector<string> list;
    string name;
    WebPageSetCombiner* combiner = new DiffWebPageSetCombiner;

    if (!(instr >> name)) {
        return HANDLER_OK;
    }
    list.push_back(name);

    while(instr >> name){
        list.push_back(name);
    }

    WebPageSet set = eng -> search(list, combiner);
    display_hits(set, ostr);

    return HANDLER_OK;}


