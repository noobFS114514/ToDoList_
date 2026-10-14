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
    Task(std::string Name_ = "", int Done_ = 0);

    Task(const Task & ot);

    ~Task();
    // bool operator==(Task & ot);
    Task &operator=(const Task & ot);
};
