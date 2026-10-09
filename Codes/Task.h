#pragma once
#include <string>

class Task{
  friend class TaskManager;
  static int TaskNumber;
  private: 
    std::string TaskName;
    int isDone;
    int id_;
    // std::string deadlineTime;
    // int typeOfTask;
  public:
    Task(std::string Name_ = std::to_string(TaskNumber),int Done_ = 0);
    Task(Task & ot);
    ~Task();
    // bool operator==(Task & ot);
    Task &operator=(Task & ot);
};
int Task::TaskNumber = 0;