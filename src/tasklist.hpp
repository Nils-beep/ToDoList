#pragma once
#include "includes.hpp"
#include <codecvt>
#include <cwchar>
#include <iterator>
#include <locale>
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
        std::string filepath;
        void sortByPriority();
    public:
        Tasklist(std::string n){
            findPriority(&n);
            name = n;
            filepath = "tasklists/" + name + ".txt";
        }
        void addTask(std::string* line){
            tasks.push_back(line);
            sortByPriority();
        }
        void toggleTask(int index){tasks[index].toggleTask();}
        void display();
        void findPriority(std::string* line);
        void deleteTasklist(){remove(filepath.c_str());}
        std::vector<Task>* getTasks(){return &tasks;};
        std::string getName(){return name;}

        bool toDelete = false;
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
    if (this->tasks.empty())
        this->prio = p;
    else this->tasks[stoi(*line)-1].changePrio(p);
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

size_t inline displayWidth(const std::string& s)
{
    size_t count = 0;

    for (unsigned char c : s) {
        if ((c & 0xC0) != 0x80)
            ++count;
    }

    return count;
}

inline void Tasklist::display(){
    const int width = 85;
    int taskNumber = 0;
    std::cout << "\n";
    for (int i=0; i<((width-name.size())/2-1); i++)
        std::cout << "-";
    if (this->toDelete)
        print(name, color_red);
    else
        print(" " +name + " ");
    for (int i=0; i<((width-name.size())/2 -1); i++)
        std::cout << "-";
    std::cout << "\n";

    for (Task task : tasks){
        taskNumber++;/*
        if (task.getPrio() == LOW)
            std::cout << "🟩 ";
        else if (task.getPrio() == MEDIUM)
                std::cout << "🟨 ";
        else std::cout << "🟥 ";*/

        if (!task.getState())
            std::cout << "󰄱 ";
        else
            std::cout << " ";

        if (this->toDelete)
            print(task.getName(), color_red);
        else
            switch (task.getPrio()){
                case LOW:
                    print(task.getName(), color_green);
                    break;
                case MEDIUM:
                    print(task.getName(), color_yellow);
                    break;
                case HIGH:
                    print(task.getName(), color_red);
                    break;
            }

        for (int i=0; i<(width-displayWidth(task.getName())-4); i++) //-x because emojis
            std::cout << " ";
        std::cout << taskNumber <<"\n";
    }
    std::cout << std::string(width,'-')+"\n";
}
