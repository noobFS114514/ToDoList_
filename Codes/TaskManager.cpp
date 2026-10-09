#pragma once

#include "TaskManager.h"
#include <iostream>
#include <fstream>

void TaskManager::addTask(std::string taskTitle = ""){
    task_.push_back({taskTitle,0});
    std::cout << "Add the task successfully! " << std::endl;
}

void TaskManager::listTask() const {
    if(task_.empty()){
        std::cout << "You have NO tasks now. " << std::endl;
        return;
    }
    for(const auto& t : task_){
        std::cout << t.id_ << ". [" << (t.isDone ? "X" : " ") << "]" << t.TaskName << std::endl;
    }
}


void TaskManager::markDone(int id){
    for(auto& t :task_){
        if(t.id_ == id){
            t.isDone = 1;
            std::cout << "Had marked 'Finished'. " << std::endl;
            return;
        }
    }
    std::cout << "Task NOT FOUND. " << std::endl;
}

void TaskManager::removeTask(int id){
    for(auto itr = task_.begin();itr != task_.end();itr++){
        if(itr->id_ == id){
            task_.erase(itr);
            std::cout << "Delete the task successfully! " << std::endl;
            return;
        }
    }
    std::cout << "Task NOT FOUND. " << std::endl;
}

void TaskManager::saveTaskList(const std::string & fileName) const {
    std::ofstream fout(fileName);
    for(const auto& t : task_){
        fout << t.id_ << "|" << t.TaskName << "|" << (t.isDone ? "D" : "X") << std::endl;
    }
}

void TaskManager::loadTaskList(const std::string & fileName){
    task_.clear();
    std::ifstream fin(fileName);
    if(!fin){return;}

    std::string line;
    while(std::getline(fin,line)){
        if(line.empty()){continue;}

        // id_|TaskName|isDone

        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);

        Task t;
        t.id_ = std::stoi(line.substr(0,p1));
        t.TaskName = line.substr(p1 + 1,p2 - p1 -1);
        t.isDone = (line.substr(p2 + 1) == "D" ? 1 : 0);
        task_.push_back(t);
    }
}