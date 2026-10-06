#include <string>

class Task{
  static int TaskNumber;
  private: 
    std::string TaskName;
    int isDone;
    std::string deadlineTime;
    // int typeOfTask;
  public:
    Task(std::string Name_ = std::to_string(TaskNumber),int Done_ = 0,std::string ddl_);
    Task(Task & ot);
    ~Task();
    bool operator==(Task & ot);
    Task &operator=(Task & ot);
};
int Task::TaskNumber = 0;