#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Task.h"

class TaskManager{
  private:
    std::vector<Task> task_;
  public:
    void addTask(std::string taskTitle = "");
    void listTask() const;
    void markDone(int id);
    void markDone(const std::string title);
    void removeTask(int id);
    void removeTask(const std::string title);
    void setDeadline(int id, const std::string & ddl);
    void setDeadline(const std::string & title, const std::string & ddl);
    void saveTaskList(const std::string & fileName) const;
    void loadTaskList(const std::string & fileName);
};
