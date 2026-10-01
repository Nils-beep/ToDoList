#pragma once
#include "includes.hpp"
#include <iterator>
#include <codecvt>
#include <string>
#include <cwchar>
#include <vector>
#include <locale>



Priority inline prioHelper(std::string* line){
    Priority p = LOW;
    const char prioChar = '!';
    std::string::size_type pos = line->find(prioChar);
    if (pos != std::string::npos){
        p = MEDIUM;
        line->erase(pos, 1);
        pos = line->find(prioChar);
        if (pos != std::string::npos){
            p = HIGH;
            line->erase(pos, 1);
        }
    }
    return p;
}

enum paramIndex{
    mainData,
    extraInfo,
    hiddenState,
    withDate
};

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
        bool hidden = false;
        int index;
        void sortByPriority();
    public:
        Tasklist(std::string n, int index){
            findPriority(&n);
            name = n;
            filepath = "tasklists/" + name + ".txt";
            this->index = index;
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
        void setName(std::string name){this->name = name;}
        void toggleHidden(){hidden = !hidden;};
        bool getHidden(){return hidden;}
        int getIndex(){return index;}
        void setIndex(int index){this->index = index;}

        bool toDelete = false;
};

inline void Task::findPriority(std::string* line){
    this->prio = prioHelper(line);
}
inline void Tasklist::findPriority(std::string* line){
    Priority p = prioHelper(line);
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

    int taskNumber = 0;
    std::cout << "\n";
    for (int i=0; i<((tasklistWidth-displayWidth(name))/2-3); i++)
        std::cout << "-";
    if (this->toDelete)
        print(" "+ to_string(index+1) + ". " + name+" ", color_red);
    else
        print(" "+ to_string(index+1) + ". " + name + " ");
    //without the double->rounding it sometimes has 1 - to little
    for (int i=0; i<(round(double(tasklistWidth-displayWidth(name))/2) -2); i++)
        std::cout << "-";
    std::cout << "\n";
    if (!this->hidden || (selectedTasklist != -1)){
        for (Task task : tasks){
            taskNumber++;
            if (taskNumber>9){
                std::cout<< "| " << taskNumber  << "";
            }else std::cout<< "| " << taskNumber << " ";
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
            for (int i=0; i<(tasklistWidth-displayWidth(task.getName())-7); i++) //-x because emojis
                std::cout << " ";
            std::cout <<"|\n";
        }
    }else std::cout<< "|"<< std::string((tasklistWidth)/2-displayWidth("🦚 hidden 🦚")/2-3,' ')
            << "🦚 hidden 🦚" << std::string(tasklistWidth/2-displayWidth("🦚 hidden 🦚")/2-1,' ')+"|\n";
    std::cout << std::string(tasklistWidth,'-')+"\n";
}
