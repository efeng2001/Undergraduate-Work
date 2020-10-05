#include <iostream>
#include <stdexcept>
#include "todolist.h"
using namespace std;


DailyTodoList::DailyTodoList()
{
    data_ = new Item * [5];
    cap_ = 5;
    priorityHead_ = NULL;
    // [TO BE COMPLETED]
    //===========================
    // Add any addition code here
    for(size_t i=0; i< cap_; i++){
        data_[i] =  NULL;
    }
}

DailyTodoList::~DailyTodoList()
{
    for(size_t i=0; i< numDays(); i++){
        for(size_t j=numItemsOnDay(i)-1; j>= 0 ; j--){
            cout << numItemsOnDay(i) <<endl;
            cout << i << " " << j << endl;
            remove(i, j);
        }
    }
    delete[] data_;
}



void DailyTodoList::push_back(size_t dayIndex, const std::string& val, bool highPriority)
{
    if (dayIndex < cap_)
    {
        this->insert(dayIndex, this->numItemsOnDay(dayIndex), val, highPriority);
    }
    else 
    {
        this->insert(dayIndex, 0, val, highPriority);
    }
    
}

void DailyTodoList::insert(size_t dayIndex, size_t loc, const std::string& val, bool highPriority)
{
    if(dayIndex > numDays()){
        resize(dayIndex);
    }

    if(loc > numItemsOnDay(dayIndex)){
        throw std::out_of_range("location beyond current day's to-do list");
    }

    Item* add;
    Item* temp = data_[dayIndex];
    for(size_t i=1; i<loc; i++){
        temp = temp -> nextItem;
    }

    if(temp == NULL){ 
        add = new Item(val, NULL, NULL);
        data_[dayIndex] = add;
    }else if(loc == 0){
        Item* next = temp;
        add = new Item(val, next, NULL);
        data_[dayIndex] = add;
    }else{
        Item* next = temp -> nextItem;
        add = new Item(val, next, NULL);
        temp -> nextItem = add;
    }
    

    if(highPriority){
        Item* priority = priorityHead_;
        if(priority == NULL){
            priorityHead_ = add;
        }else{
            for(size_t i=1; i <numPriorityItems(); i++){
                priority = priority ->nextPriorityItem; 
            }
            priority -> nextPriorityItem = add;
        }
    }
}

void DailyTodoList::remove(size_t dayIndex, size_t loc)
{
    if(dayIndex > numDays()){
        throw std::out_of_range("day out of range");
    }
    if(loc > numItemsOnDay(dayIndex)){
        throw std::out_of_range("location beyond current day's to-do list");
    }

    Item* rmv;

    if(loc == 0){
        rmv =  data_[dayIndex]; 
        data_[dayIndex] = NULL;
    }else{
        Item* temp = data_[dayIndex];
        for(size_t i=1; i<loc; i++){
            temp = temp -> nextItem;
        }
        rmv = temp -> nextItem;
        temp -> nextItem = temp -> nextItem -> nextItem;
    }

    Item* priority = priorityHead_;
    if(priority == rmv && priority -> nextPriorityItem == NULL){
        rmv =  priorityHead_;
        priorityHead_ = NULL;
    }else if(priority == rmv){
        rmv = priority;
        priorityHead_ = priority -> nextPriorityItem;
    }else{
        while(priority -> nextPriorityItem != NULL){
            if(priority -> nextPriorityItem == rmv){
                priority -> nextPriorityItem = priority ->nextPriorityItem -> nextPriorityItem;
            }
            priority = priority -> nextPriorityItem;
        }
    }
    delete rmv;
}

size_t DailyTodoList::numDays() const
{
    return cap_;
}

size_t DailyTodoList::numItemsOnDay(size_t dayIndex) const
{
    if(dayIndex > numDays()){
        throw std::out_of_range("day out of range");
    }

    size_t size = 0;
    Item* count = data_[dayIndex];
    while(count!= NULL){
        count = count -> nextItem; 
        size++;
    }
    return size;
}

bool DailyTodoList::empty(size_t dayIndex) const
{
    Item* count = data_[dayIndex];
    if(count->nextItem == NULL){
        return true;
    }
    return false;
}

const std::string& DailyTodoList::getNormalVal(size_t dayIndex, size_t loc) const
{
    if(dayIndex > numDays()){
        throw std::out_of_range("day out of range");
    }
    if(loc > numItemsOnDay(dayIndex)){
        throw std::out_of_range("location beyond current day's to-do list");
    }

    Item* rtn = data_[dayIndex];
    for(size_t i=0; i<loc ; i++){
        rtn = rtn -> nextItem;
    }
    return rtn -> val;
}

std::string& DailyTodoList::getNormalVal(size_t dayIndex, size_t loc)
{
    if(dayIndex > numDays()){
        throw std::out_of_range("day out of range");
    }
    if(loc > numItemsOnDay(dayIndex)){
        throw std::out_of_range("location beyond current day's to-do list");
    }

    Item* rtn = data_[dayIndex];
    for(size_t i=0; i<loc ; i++){
        rtn = rtn -> nextItem;
    }
    return rtn -> val;
}

size_t DailyTodoList::numPriorityItems() const
{
    size_t size = 0;
    Item* count = priorityHead_;
    while(count != NULL){
        count = count -> nextPriorityItem; 
        size++;
    }
    return size;
}

const std::string& DailyTodoList::getPriorityVal(size_t priorityLoc) const
{
    if(priorityLoc > numPriorityItems()){
        throw std::out_of_range("priorityLoc is invalid");
    }

    Item* rtn = priorityHead_;
    for(size_t i=0; i<priorityLoc; i++){
        rtn = rtn -> nextPriorityItem;
    }
    return rtn -> val;
}

void DailyTodoList::resize(size_t size)
{
    Item** temp = new Item*[size*2];

    for(size_t i=0; i<size*2; i++){
        if(i< cap_){
            temp[i] = data_[i];
        }else{
            temp[i] = NULL;
        }    
    }

    delete[] data_;
    data_ = temp;
    cap_ = size*2;
}
