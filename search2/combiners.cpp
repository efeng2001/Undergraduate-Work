#include "combiners.h"

WebPageSet ANDWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{
    WebPageSet rtn;
    for(WebPageSet::iterator it = setA.begin(); it != setA.end(); ++it){
        if(setB.find(*it) != setB.end()){
            rtn.insert(*it);
        }
    }
    return rtn;
}

WebPageSet ORWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{
    WebPageSet rtn(setA);
    for(WebPageSet::iterator it = setB.begin(); it != setB.end(); ++it){
        if(rtn.find(*it) == rtn.end()){
            rtn.insert(*it);
        }
    }
    return rtn;
}

WebPageSet DIFFWebPageSetCombiner::combine(const WebPageSet& setA, const WebPageSet& setB)
{
    WebPageSet rtn(setA);
    for(WebPageSet::iterator it = setB.begin(); it != setB.end(); ++it){
        if(rtn.find(*it) != rtn.end()){
            rtn.erase(*it);
        }
    }
    return rtn;
}