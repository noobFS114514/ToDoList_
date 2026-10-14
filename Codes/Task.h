#pragma once
#include <string>
#include <ctime>

class Task{
  friend class TaskManager;
  static int TaskNumber;
  private:
    std::string TaskName;
    int isDone;
    int id_;
    std::time_t setTime_;   // 任务添加时间
    std::time_t ddl_;       // 截止日期时间（0 表示未设置）
    // int typeOfTask;
  public:
    Task(std::string Name_ = "", int Done_ = 0);

    Task(const Task & ot);

    ~Task();
    // bool operator==(Task & ot);
    Task &operator=(const Task & ot);
};
