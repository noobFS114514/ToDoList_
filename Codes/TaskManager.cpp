#include "TaskManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>

// ===== 时间工具函数 =====
namespace {

// 将 time_t 格式化为 "YYYY-MM-DD HH:MM:SS"；t<=0 视为未设置
std::string formatTime(std::time_t t){
    if(t <= 0){ return "未设置"; }
    std::tm tm = *std::localtime(&t);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
    return std::string(buf);
}

// 将 "YYYY-MM-DD HH:MM[:SS]" 解析为 time_t；解析失败返回 0
std::time_t parseTime(const std::string & s){
    std::tm tm = {};
    std::istringstream ss(s);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if(ss.fail()){
        ss.clear();
        ss.seekg(0);
        tm = std::tm{};
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");
    }
    if(ss.fail()){ return 0; }
    return std::mktime(&tm);
}

// 计算 ddl 与 now 的差值并格式化为可读文本（剩余/已逾期）
std::string formatRemain(std::time_t ddl, std::time_t now){
    long long diff = static_cast<long long>(std::difftime(ddl, now));
    bool overdue = diff < 0;
    if(overdue){ diff = -diff; }
    long long d = diff / 86400;
    long long h = (diff % 86400) / 3600;
    long long m = (diff % 3600) / 60;
    std::ostringstream oss;
    oss << (overdue ? "已逾期 " : "剩余 ");
    if(d > 0){ oss << d << "天"; }
    if(h > 0 || d > 0){ oss << h << "小时"; }
    oss << m << "分钟";
    return oss.str();
}

} // namespace

void TaskManager::addTask(std::string taskTitle){
    task_.push_back({taskTitle,0});
    std::cout << "Add the task successfully! " << std::endl;
}

void TaskManager::listTask() const {
    if(task_.empty()){
        std::cout << "You have NO tasks now. " << std::endl;
        return;
    }
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    for(const auto& t : task_){
        // [原] std::cout << t.id_ << ". [" << (t.isDone ? "X" : " ") << "]" << t.TaskName << std::endl;
        std::cout << t.id_ << ". [" << (t.isDone ? "X" : " ") << "] " << t.TaskName;
        if(t.ddl_ != 0){
            std::cout << " | ddl: " << formatTime(t.ddl_)
                      << " | " << formatRemain(t.ddl_, now);
        } else {
            std::cout << " | ddl: 未设置";
        }
        std::cout << std::endl;
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

void TaskManager::markDone(const std::string title){
    for(auto& t :task_){
        if(t.TaskName == title){
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

void TaskManager::removeTask(const std::string title){
    for(auto itr = task_.begin();itr != task_.end();itr++){
        if(itr->TaskName == title){
            task_.erase(itr);
            std::cout << "Delete the task successfully! " << std::endl;
            return;
        }
    }
    std::cout << "Task NOT FOUND. " << std::endl;
}

void TaskManager::setDeadline(int id, const std::string & ddl){
    for(auto& t : task_){
        if(t.id_ == id){
            std::time_t parsed = parseTime(ddl);
            if(parsed == 0){
                std::cout << "Invalid date format. Use: YYYY-MM-DD HH:MM" << std::endl;
                return;
            }
            t.ddl_ = parsed;
            std::cout << "Deadline set successfully. " << std::endl;
            return;
        }
    }
    std::cout << "Task NOT FOUND. " << std::endl;
}

void TaskManager::setDeadline(const std::string & title, const std::string & ddl){
    for(auto& t : task_){
        if(t.TaskName == title){
            std::time_t parsed = parseTime(ddl);
            if(parsed == 0){
                std::cout << "Invalid date format. Use: YYYY-MM-DD HH:MM" << std::endl;
                return;
            }
            t.ddl_ = parsed;
            std::cout << "Deadline set successfully. " << std::endl;
            return;
        }
    }
    std::cout << "Task NOT FOUND. " << std::endl;
}

void TaskManager::saveTaskList(const std::string & fileName) const {
    std::ofstream fout(fileName);
    for(const auto& t : task_){
        // fout << t.id_ << "|" << t.TaskName << "|" << (t.isDone ? "D" : "X") << std::endl;
        fout << t.id_ << "|" << t.TaskName << "|" << (t.isDone ? "D" : "X")
             << "|" << t.setTime_ << "|" << t.ddl_ << std::endl;
    }
}

void TaskManager::loadTaskList(const std::string & fileName){
    task_.clear();
    std::ifstream fin(fileName);
    if(!fin){
        std::cout << "Open file failed: " << fileName << std::endl;
        return;
    }

    std::string line;
    int maxId = 0;
    while(std::getline(fin,line)){
        if(line.empty()){continue;}

        // id_|TaskName|isDone|setTime|ddl（setTime/ddl 为 time_t 秒数）

        std::vector<std::string> parts;
        size_t start = 0;
        while(true){
            size_t pos = line.find('|', start);
            if(pos == std::string::npos){
                parts.push_back(line.substr(start));
                break;
            }
            parts.push_back(line.substr(start, pos - start));
            start = pos + 1;
        }

        if(parts.size() < 3){ continue; }

        Task t("", 0);
        t.id_ = std::stoi(parts[0]);
        t.TaskName = parts[1];
        t.isDone = (parts[2] == "D" ? 1 : 0);
        if(parts.size() >= 4){ t.setTime_ = static_cast<std::time_t>(std::stoll(parts[3])); }
        if(parts.size() >= 5){ t.ddl_ = static_cast<std::time_t>(std::stoll(parts[4])); }
        task_.push_back(t);
        if(t.id_ > maxId){ maxId = t.id_; }
    }
    Task::TaskNumber = maxId;
}
