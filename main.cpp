#include <cctype>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <fstream>
#include <variant>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>

enum Priority{
    LOW,
    MEDIUM,
    HIGH,
};

struct Task{
    std::string name;
    bool state = false;
    Priority prio = LOW;
};

std::vector<Task> tasks;
bool listMode = false;

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
void sortByPriority(){
    std::vector<Task>sortedList;
    for (Task task : tasks){
        if (task.prio == HIGH)
            sortedList.push_back(task);
    }
    for (Task task : tasks){
        if (task.prio == MEDIUM)
            sortedList.push_back(task);
    }
    for (Task task : tasks){
        if (task.prio == LOW)
            sortedList.push_back(task);
    }
    tasks = sortedList;
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
void listOutput(){
    titleOutput();
    int taskNumber = 0;
    std::cout << "--------------------------------------------------------------- \n";
    for (Task task : tasks){
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
void choiceOutput(){
    std::cout <<"\n > ";
}

void changePriority(int index, Priority prio){
    tasks[index-1].prio = prio;
    sortByPriority();
}


void createTask(std::string name){
    Priority prio = findPrio(&name);
    tasks.push_back({name, false, prio});
    sortByPriority();
}

int handleInput(){
    std::string text;
    std::getline(std::cin, text);
    //text.erase(std::remove (text.begin(), text.end(), ' '), text.end());

    //clean cli
    std::cout << "\033[2J\033[H";
    if (text == "")
        return 1;
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
            tasks[index-1].state = !tasks[index-1].state;
        }
    }
    return 0;
}
int runner(){
    listOutput();
    choiceOutput();

    return handleInput();
}

void readFile(){
    std::ifstream myfile;
    myfile.open("tasklist.txt");
    std::string line;
    while (getline(myfile, line)){
        Priority prio = findPrio(&line);
        tasks.push_back({line});
        tasks.back().prio = prio;
    }
    myfile.close();
}
void writeFile(){
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
}

int main(){
    std::cout << "\033[2J\033[H";
    readFile();
    //sortByPriority();
    int result = -1;
    while (result != 1)
       result = runner();
    writeFile();
    listOutput();
    return 0;
}
