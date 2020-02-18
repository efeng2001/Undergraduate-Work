#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include "gitint.h"

using namespace std;

/*********************** Messages to use for errors ***************************/
const std::string INVALID_COMMAND = "Invalid command";
const std::string INVALID_OPTION = "Invalid option";
const std::string INVALID_COMMIT_NUMBER = "Invalid commit number";
const std::string LOG_COMMIT_STARTER = "Commit: ";



// Class implementation
GitInt::GitInt()
{
    map<string, int> map;
    commits_.push_back(CommitObj("", map, NULL) );
}

GitInt::~GitInt()
{
    while(!commits_.empty()){
        commits_.pop_back();
    }
}


void GitInt::print_menu() const
{
    cout << "Menu:                          " << endl;
    cout << "===============================" << endl;
    cout << "create   filename int-value    " << endl;
    cout << "edit     filename int-value    " << endl;
    cout << "display  (filename)            " << endl;
    cout << "display  commit-num            " << endl;
    cout << "add      file1 (file2 ...)     " << endl;
    cout << "commit   \"log-message\"       " << endl;
    cout << "tag      (-a tag-name)         " << endl;
    cout << "log                            " << endl;
    cout << "checkout commit-num/tag-name   " << endl;
    cout << "diff                           " << endl;
    cout << "diff     commit                " << endl;
    cout << "diff     commit-n commit-m     " << endl;
}


bool GitInt::process_command(std::string cmd_line)
{
    bool quit = false;
    std::stringstream ss(cmd_line);
    std::string cmd;
    ss >> cmd;
    if (ss.fail()) throw std::runtime_error(INVALID_COMMAND);

    if (cmd == "quit") {
        quit = true;
    }
    // Continue checking/processing commands
    else if(cmd == "create"){
        string filename;
        int value;
        ss >> filename >> value;
        if(ss.fail()){
            throw std::runtime_error(INVALID_COMMAND);
        }
        
        if(filename.size()<4){
            throw std::invalid_argument(INVALID_OPTION);
        }else if(filename.substr(filename.size()-4, filename.size()-1) != ".txt"){
            throw std::invalid_argument(INVALID_OPTION);
        }else if(files.find(filename) != files.end()){
            throw std::invalid_argument(INVALID_OPTION);
        }else{
            create(filename, value);
        }
    }else if(cmd == "edit"){
        string filename;
        int value;
        ss >> filename >> value; 
        if(ss.fail()){
            throw std::runtime_error(INVALID_COMMAND);
        }
        if(files.find(filename) == files.end()){
            throw std::invalid_argument(INVALID_OPTION);
        }else{
            edit(filename, value);
        }
    }else if(cmd == "display"){
        string filename;
        CommitIdx num;
        ss >> num;
        if(!ss.fail()){
            display_commit(num);
        }else{
            ss.clear();
            ss >> filename;
            if(ss.fail()){
                display_all();
            }else{
                if(files.find(filename) != files.end()){
                    display(filename);
                }else{
                    throw std::invalid_argument(INVALID_OPTION);
                }
            }
        }
    }else if(cmd == "add"){
        string filename;
        ss >> filename;
        if(ss.fail()){
            throw std::invalid_argument(INVALID_COMMAND);
        }
        while(!ss.fail()){
            if(files.find(filename) == files.end()){
                throw std::invalid_argument(INVALID_COMMAND);
            }else{
                add(filename);
            }
            ss.clear();
            ss >> filename;
        }
    }else if(cmd == "commit"){
        string message;
        getline(ss, message);
        if(ss.fail()){
            throw std::runtime_error(INVALID_COMMAND);
        }else if(message.size() <4){
            throw std::runtime_error(INVALID_COMMAND);
        }else if(message[0] != '\"' && message[message.size()-1] != '\"'){
            throw std::runtime_error(INVALID_COMMAND);
        }else{
            commit(message.substr(2, message.size()-3));
        }
    }else if(cmd == "tag"){
        string string;
        ss >> string;
        if(ss.fail()){
            tags();
        }else{ 
            if(string != "-a"){
                throw std::runtime_error(INVALID_COMMAND);
            }else if(tags_.find(string) != tags_.end()){
                throw std::invalid_argument(INVALID_OPTION);
            }else{
                ss >> string;
                create_tag(string, head);
            }
        }
    }else if(cmd == "log"){
        log();
    }else if(cmd == "checkout"){
        string tag; 
        CommitIdx num;
        ss >> num;
        if(ss.fail()){
            ss.clear();
            ss >> tag;
            if(ss.fail()){
                throw std::runtime_error(INVALID_COMMAND);
            }else if(!checkout(tag)){
                throw std::invalid_argument(INVALID_OPTION);
            }        
        }else{
            checkout(num);
        }
    }else if(cmd == "diff"){
        CommitIdx from;
        CommitIdx to;
        ss >> from; 
        if(ss.fail()){
            diff(head);
        }else{
            ss.clear();
            ss >> to;
            if(ss.fail()){
                if(valid_commit(from)){
                    diff(from);
                }else{
                    throw std::invalid_argument(INVALID_OPTION);
                }
            }else if(from < to|| !valid_commit(from) || !valid_commit(to)){
                throw std::invalid_argument(INVALID_OPTION);
            }else{
                diff(from, to);
            }
        }
    }else {
        throw std::runtime_error(INVALID_COMMAND);
    }
    return quit;
}

void GitInt::create(const std::string& filename, int value)
{
    files[filename] = value;
}

void GitInt::edit(const std::string& filename, int value)
{
    files[filename] = value;
}

void GitInt::display(const std::string& filename) const
{
    cout << filename << " : " << files.find(filename) ->second << endl;
}

void GitInt::display_all() const
{
    display_helper(files);
}

void GitInt::add(std::string filename)
{
    staged_.insert(filename);
}

void GitInt::commit(std::string message)
{
    map<string, int> innerMap;
    map<string, int> totalDif = buildState(head, 0);
    for(set<string>::iterator it = staged_.begin(); it != staged_.end(); ++it){
        if(files[*it] - totalDif[*it] !=0){
            innerMap[*it] = files[*it] - totalDif[*it];
        }
    }
    staged_.clear();
    commits_.push_back(CommitObj(message, innerMap, head));
    head = commits_.size()-1;
}

void GitInt::create_tag(const std::string& tagname, CommitIdx commit)
{
    tags_[tagname] = commit;
    list.push_back(tagname);
}

void GitInt::tags() const
{
    for(int i=list.size()-1; i>=0; i--){
        cout << list[i] << endl;
    }
}

bool GitInt::checkout(CommitIdx commitIndex)
{
    if(valid_commit(commitIndex)){
        head = commitIndex;
        //change files
        files.clear();
        files = buildState(commitIndex ,0);
        return true;
    }
    throw std::invalid_argument(INVALID_COMMAND);
    return false;
}

bool GitInt::checkout(std::string tag)
{
    if(tags_.find(tag) != tags_.end()){
        head = tags_[tag];    
        // change files
        files.clear();
        files = buildState(tags_[tag],0);
        return true;
    }
    return false;
}

void GitInt::log() const
{
    for(CommitIdx i = head; i!=0; i = commits_[i].parent_){
        log_helper(i, commits_[i].msg_);
    }
}

void GitInt::diff(CommitIdx to) const
{
    if(head ==0){
        display_helper(files);
    }else{
        map<string, int>fmap = buildState(to);
        map<string, int>print;
        for(map<string, int>::const_iterator it = files.begin(); it!= files.end(); ++it){
            if(fmap.find(it->first) == print.end()){
                    print[it->first] = it->second;
                }else{
                    if(it->second - fmap[it->first]!=0){
                        print[it->first] = it->second - fmap[it->first];
                    }
                }
        }
        display_helper(print);
    }
}

void GitInt::diff(CommitIdx from, CommitIdx to) const
{
    map<string, int>fmap = buildState(from);
    map<string, int>smap = buildState(to);
    map<string, int>print;
    for(map<string, int>::const_iterator it = fmap.begin(); it!= fmap.end(); ++it){
        if(smap.find(it->first) == print.end()){
                print[it->first] = it->second;
            }else{
                if(it->second - smap[it->first]!=0){
                        print[it->first] = it->second - smap[it->first];
                    }
            }
    }
    display_helper(print);
}

bool GitInt::valid_commit(CommitIdx commit) const
{
    return((CommitIdx)commits_.size() > commit && commit > 0);
}

map<string, int> GitInt::buildState(CommitIdx from, CommitIdx to) const
{
    map<string, int> rtn; 
    for(CommitIdx i = from; i!=to; i= commits_[i].parent_){
        for(map<string, int>::const_iterator it = commits_[i].diffs_.begin(); it!= commits_[i].diffs_.end(); ++it){
            if(rtn.find(it->first) == rtn.end()){
                rtn[it->first] = it->second;
            }else{
                rtn[it->first] += it->second;
            }
        }
    }
    return rtn;
}

void GitInt::display_commit(CommitIdx commit) const
{
    if ( false == valid_commit(commit) ) {
        throw std::invalid_argument(INVALID_COMMIT_NUMBER);
    }
    display_helper(commits_[commit].diffs_);
}


void GitInt::display_helper(const std::map<std::string, int>& dat) const
{
    for (std::map<std::string, int>::const_iterator cit = dat.begin();
            cit != dat.end();
            ++cit) {
        std::cout << cit->first << " : " << cit->second << std::endl;
    }
}


void GitInt::log_helper(CommitIdx commit_num, const std::string& log_message) const
{
    std::cout << LOG_COMMIT_STARTER << commit_num << std::endl;
    std::cout << log_message << std::endl << std::endl;

}

