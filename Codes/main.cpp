#include "Task.h"
#include "TaskManager.h"
#include <iostream>
#include <string>

int main(){
    TaskManager manager;
    int choice = 0;
    std::string input;

    // Main Loop
    do{
        std::cout << "\n===== ToDoList Menu =====" << std::endl;
        std::cout << "1. Add Task" << std::endl;
        std::cout << "2. List Tasks" << std::endl;
        std::cout << "3. Mark Done" << std::endl;
        std::cout << "4. Remove Task" << std::endl;
        std::cout << "5. Save to file" << std::endl;
        std::cout << "6. Load from file" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Please choose: ";
        std::cin >> choice;
        std::cin.ignore(); 

        switch(choice){
            case 1:{
                std::cout << "Enter task title: ";
                std::getline(std::cin, input);
                manager.addTask(input);
                break;
            }
            case 2:{
                manager.listTask();
                break;
            }
            case 3:{
                int id = 0;
                std::cout << "Enter task id: ";
                std::cin >> id;
                std::cin.ignore();
                manager.markDone(id);
                break;
            }
            case 4:{
                int id = 0;
                std::cout << "Enter task id: ";
                std::cin >> id;
                std::cin.ignore();
                manager.removeTask(id);
                break;
            }
            case 5:{
                manager.saveTaskList("TaskList.txt");
                std::cout << "Saved to TaskList.txt." << std::endl;
                break;
            }
            case 6:{
                manager.loadTaskList("TaskList.txt");
                std::cout << "Loaded from TaskList.txt." << std::endl;
                break;
            }
            case 0:{
                std::cout << "Bye." << std::endl;
                break;
            }
            default:{
                std::cout << "Invalid choice." << std::endl;
            }
        }
    }while(choice != 0);

    return 0;
}
