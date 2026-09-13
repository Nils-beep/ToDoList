#include <cctype>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <fstream>
#include <variant>
#include <vector>
#include <bits/stdc++.h>
#include <filesystem>
#include <cassert>
#include <ranges>
#include <vector>

#define  clearScreen std::cout << "\033[2J\033[H";

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;


enum Priority{
    LOW,
    MEDIUM,
    HIGH,
};

struct Task{
    std::string name = "";
    bool state = false;
    Priority prio = LOW;
};

struct TaskList{
    std::string name;
    std::vector<Task> tasks;
};

std::vector<TaskList> tasklists;
TaskList selectedTasks;
int listChosen = -1;


Priority findPrio(std::string* line){
    Priority prio = LOW;
    int pos = line->find("!");
    if (pos != -1){
        prio = MEDIUM;
        line->erase(pos, 1);
        pos = line->find("!");
        if (pos != -1){
            prio = HIGH;
            line->erase(pos, 1);
        }
    }
    return prio;
}
void sortByPriority(TaskList* tasklist){
    std::vector<Task>sortedList;
    for (Task task : tasklist->tasks){
        if (task.prio == HIGH)
            sortedList.push_back(task);
    }
    for (Task task : tasklist->tasks){
        if (task.prio == MEDIUM)
            sortedList.push_back(task);
    }
    for (Task task : tasklist->tasks){
        if (task.prio == LOW)
            sortedList.push_back(task);
    }
    tasklist->tasks = sortedList;
    sortedList.clear();
}

void titleOutput(){
    std::ifstream myfile;
    myfile.open("title.txt");
    std::string line;
    while (getline(myfile, line))
        std::cout<< line << "\n";
    myfile.close();
}
void listOutput(TaskList* tasklist){
    int taskNumber = 0;
    std::cout << "--------------------------------------------------------------- \n";
    for (Task task : tasklist->tasks){
        taskNumber++;
        if (task.prio == LOW)
            std::cout << "🟩 ";
        else if (task.prio == MEDIUM)
                std::cout << "🟨 ";
        else std::cout << "🟥 ";

        if (!task.state)
            std::cout << "󰄱 ";
        else
            std::cout << " ";

        std::cout << task.name;
        for (int i=0; i<(60-task.name.length()); i++)
            std::cout << " ";
        std::cout << taskNumber <<"\n";
    }
    std::cout << "---------------------------------------------------------------\n";
}
void inputLine(){
    std::cout <<"\n > ";
}

void changePriority(int index, Priority prio){
    selectedTasks.tasks[index-1].prio = prio; //was .name before
    sortByPriority(&selectedTasks);
}

void createTask(std::string name){
    Priority prio = findPrio(&name);
    selectedTasks.tasks.push_back({name, false, prio});
    sortByPriority(&selectedTasks);
}

int chooseList(){
    clearScreen;
    titleOutput();
    int listIndex;
    std::string string;

    for (TaskList list : tasklists)
        listOutput(&list);
    inputLine();
    std::getline(std::cin, string);
    if (string == "")
        return 1;
    listIndex = std::stoi(string);
    if ((listIndex > tasklists.size()) || (listIndex <= 0))
        return -1;
    selectedTasks = tasklists[listIndex-1];
    clearScreen
    return 0;
}

int handleInput(){
    std::string text;
    std::getline(std::cin, text);
    //text.erase(std::remove (text.begin(), text.end(), ' '), text.end());
    //clean cli
    clearScreen;
    listOutput(&selectedTasks);
    if (text == ""){
        listChosen = -1;
        return 0;
    }
    int commaPos = text.find(",");
    if (!(commaPos == std::variant_npos)){
        std::string first = text.substr(0,commaPos);
        std::string second = text.substr(commaPos+1);
        Priority prio = findPrio(&second);
        changePriority(std::stoi(first), prio);
    }
    else{
        if (!std::isdigit(text[0]))
            createTask(text);
        else{
            int index = std::stoi(text);
            selectedTasks.tasks[index-1].state = !selectedTasks.tasks[index-1].state;
        }
    }
    return 0;
}
int runner(){
    titleOutput();
    if (listChosen==-1){
        listChosen = chooseList();
        return listChosen;
    }
    clearScreen;
    titleOutput();
    listOutput(&selectedTasks);
    inputLine();

    return handleInput();
}

void readFile(){
    for (const auto& dirEntry : recursive_directory_iterator("tasklists")){
        std::ifstream myfile;
        myfile.open(dirEntry.path());
        tasklists.push_back({});
        std::string line;
        while (getline(myfile, line)){
            Priority prio = findPrio(&line);
            tasklists[tasklists.size()-1].tasks.push_back({line, false, prio});
            std::cout << tasklists[tasklists.size()-1].tasks.back().name <<" " << tasklists[tasklists.size()-1].tasks.back().prio << "\n";
        }
    myfile.close();
    }
}
/*void writeFile(){
    std::ofstream myfile;
    myfile.open("tasklist.txt");
    for (Task task : tasks){
        if (!task.state){
            myfile << task.name;
            if (task.prio == HIGH)
                myfile << "!!";
            else
                if (task.prio == MEDIUM)
                    myfile << "!";
        myfile << "\n";
        }
    }
    myfile.close();
    }*/

int main(){
    clearScreen;
    readFile();
    while (runner() != 1);
    //writeFile();
    //listOutput();
    return 0;
}
