#include <string>

class Task{
  private:
    std::string TaskName;
    int TaskId;
    bool isDone;
    std::string deadlineTime;
    int typeOfTask;
  public:
    Task();
    Task(Task & ot);
    ~Task();
};