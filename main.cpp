#include <iostream>
#include <istream>
#include <string>
#include <fstream>
#include <vector>

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
    std::cout << "c: create new Task \n";
    std::cout << "f: finish task \n";
    std::cout << "u: unfinish task \n";
    std::cout << "p: change priority \n";
    std::cout << "leave blank to stop \n----\n> ";
}

void finishTask(){
    std::string number;
    std::cout << "\033[2J\033[H";
    listOutput();
    std::cout << "\n > ";
    std::getline(std::cin, number);
    int intNumber;
    if (number != ""){
        int intNumber = std::stoi(number);
        tasks[intNumber-1].state = true;
    }
    std::cout << "\033[2J\033[H";
}
void unfinishTask(){
    std::string number;
    std::cout << "\033[2J\033[H";
    listOutput();
    std::cout << "\n > ";
    std::getline(std::cin, number);
    int intNumber;
    if (number != ""){
        int intNumber = std::stoi(number);
        //tasks.erase(it);
        tasks[intNumber-1].state = false;
        //std::cout << "Task " << number << " has been finished! \n";
    }
    std::cout << "\033[2J\033[H";
}
void changePriority(){
    std::string line;
    std::cout << "\033[2J\033[H";
    listOutput();
    std::cout << "\n > ";
    std::getline(std::cin, line);
    Priority prio = findPrio(&line);
    std::cout << line;
    tasks[std::stoi(line)-1].prio = prio;
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
}

void createTask(){
    std::string newTaskname;
    listOutput();
    std::cout << "\n󰄱 > ";
    std::getline(std::cin, newTaskname);
    Priority prio = findPrio(&newTaskname);
    if (newTaskname != "")
        tasks.push_back({newTaskname});
    std::cout << "\033[2J\033[H";
    tasks.back().prio = prio;
    sortByPriority();

} //todo task prio on create

int handleInput(){
    std::string text;
    std::getline(std::cin, text);
    //clean cli
    std::cout << "\033[2J\033[H";

    if (text == "")
        return 1;
    if (text == "c")
        createTask();
    if (text == "f")
        finishTask();
    if (text == "u")
        unfinishTask();
    if (text == "p")
        changePriority();
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
