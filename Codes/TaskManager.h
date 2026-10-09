#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Task.h"

class TaskManager{
  private:
    std::vector<Task> task_;
    int taskNumber;
  public:
    void addTask(std::string taskTitle = "");
    void listTask() const;
    void markDone(int id);
    // void markDone(const std::string title);
    void removeTask(int id);
    // void removeTask(const std::string title);
    void saveTaskList(const std::string & fileName) const;
    void loadTaskList(const std::string & fileName);
};
