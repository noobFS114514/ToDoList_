#include "Task.h"
#include <iostream>
#include <chrono>

int Task::TaskNumber = 0;

Task::Task(std::string Name_, int Done_){
    TaskName = Name_;
    isDone = Done_;
    // deadlineTime = ddl_;
    setTime_ = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    ddl_ = 0; // 0 表示未设置截止时间
    TaskNumber += 1;
    id_ = TaskNumber;
}

Task::Task(const Task & ot){
    TaskName = ot.TaskName;
    isDone = ot.isDone;
    id_ = ot.id_;
    setTime_ = ot.setTime_;
    ddl_ = ot.ddl_;
}

Task::~Task(){}

// bool Task::operator==(Task & ot){
//     return (*this == ot);
// }

// Task & Task::operator=(Task & ot){
//     if(this == &ot){return *this;}
//     Task newT(ot.TaskName,ot.isDone);
//     return newT;
// }
// 修改：原实现创建局部对象 newT 并返回其引用（悬空引用，未定义行为），且未真正修改
//       赋值目标。现改为逐个成员赋值并返回 *this。
Task & Task::operator=(const Task & ot){
    if(this == &ot){return *this;}
    TaskName = ot.TaskName;
    isDone = ot.isDone;
    id_ = ot.id_;
    setTime_ = ot.setTime_;
    ddl_ = ot.ddl_;
    return *this;
}
