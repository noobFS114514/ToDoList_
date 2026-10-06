#include "Task.h"
#include <iostream>

Task::Task(std::string Name_ = std::to_string(TaskNumber),int Done_ = 0,std::string ddl_){
    TaskName = Name_;
    isDone = Done_;
    deadlineTime = ddl_;
    TaskNumber += 1;
    std::cout << "Task created." << std::endl;
    std::cout << "Current Task Number: " << TaskNumber << std::endl;
}

Task::Task(Task & ot){
    // if()
    TaskName = ot.TaskName;
    isDone = ot.isDone;
    deadlineTime = ot.deadlineTime;

}

Task::~Task(){
    TaskNumber -= 1;
    std::cout << "Task deleted." << std::endl;
}

bool Task::operator==(Task & ot){
    return (*this == ot);
}

Task & Task::operator=(Task & ot){
    if(*this == ot){return *this;}
    Task newT(ot.TaskName,ot.isDone,ot.deadlineTime);
    return newT;
}