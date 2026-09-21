#pragma once
#include "includes.hpp"
#include <string>
#include <vector>

class Task{
    private:
        std::string name;
        bool state = false;
        Priority prio;
        void findPriority(std::string* line);
    public:
        Task(std::string* line){
            findPriority(line);
            name = *line;
        }
        void changePrio(Priority p){prio = p;}
        void toggleTask(){state = !state;}
        Priority getPrio(){return prio;}
        bool getState(){return state;}
        std::string getName(){return name;}
};

class Tasklist{
    private:
        std::string name;
        Priority prio;
        std::vector<Task> tasks;
        void sortByPriority();
    public:
        Tasklist(std::string n, Priority p){name = n; prio = p;}
        void addTask(std::string* line){
            tasks.push_back(line);
            sortByPriority();
        }
        void toggleTask(int index){tasks[index].toggleTask();}
        void display();
        void findPriority(std::string* line);
        std::vector<Task>* getTasks(){return &tasks;};
        std::string getName(){return name;}
};

inline void Task::findPriority(std::string* line){
    Priority p = LOW;
    std::string::size_type pos = line->find("!");
    if (pos != std::string::npos){
        p = MEDIUM;
        line->erase(pos, 1);
        pos = line->find("!");
        if (pos != std::string::npos){
            p = HIGH;
            line->erase(pos, 1);
        }
    }
    this->prio = p;
}
inline void Tasklist::findPriority(std::string* line){
    Priority p = LOW;
    std::string::size_type pos = line->find("!");
    if (pos != std::string::npos){
        p = MEDIUM;
        line->erase(pos, 1);
        pos = line->find("!");
        if (pos != std::string::npos){
            p = HIGH;
            line->erase(pos, 1);
        }
    }
    this->tasks[stoi(*line)-1].changePrio(p);
}

inline void Tasklist::sortByPriority(){
    std::vector<Task>sortedList;
    for (Task task : tasks){
        if (task.getPrio() == HIGH)
            sortedList.push_back(task);
    }
    for (Task task : tasks){
        if (task.getPrio() == MEDIUM)
            sortedList.push_back(task);
    }
    for (Task task : tasks){
        if (task.getPrio() == LOW)
            sortedList.push_back(task);
    }
    tasks = sortedList;
    sortedList.clear();
}
inline void Tasklist::display(){
    int taskNumber = 0;
    std::cout << "\n";
    std::cout << "-------------------------------- " << name<<" --------------------------------\n";
    for (Task task : tasks){
        taskNumber++;
        if (task.getPrio() == LOW)
            std::cout << "🟩 ";
        else if (task.getPrio() == MEDIUM)
                std::cout << "🟨 ";
        else std::cout << "🟥 ";

        if (!task.getState())
            std::cout << "󰄱 ";
        else
            std::cout << " ";

        std::cout << task.getName();
        for (int i=0; i<(60-task.getName().length()+name.length()+1 -1); i++)
            std::cout << " ";
        std::cout << taskNumber <<"\n";
    }
    std::cout << std::string(name.length()+1,'-')<< "-----------------------------------------------------------------\n";
}
