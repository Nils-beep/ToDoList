#include <iostream>
#include <istream>
#include <string>
#include <list>
#include <fstream>
#include <iterator>


struct Task{
    std::string name;
    bool state = false;
};

std::list<Task> tasks;
bool listMode = false;

void listOutput(){
    int i = 0;
    for (Task task : tasks){
        std::cout << i << ": " << task.name << "\n";
    }
    std::cout << "\n\n";
}

int runner(){
    std::cout << "\n\n";
    if (not listMode)
        std::cout << "0: list Tasks (" << tasks.size() << ") \n";
    std::cout << "1: create new Task \n";
    std::cout << "2: finish task \n";
    if (not listMode)
        std::cout << "leave blank to stop \n";
    if (listMode)
        std::cout << "leave blank to go back \n";
    std::string text;
    std::getline(std::cin, text);
    std::cout << "\033[2J\033[H";

    // stop
    if (text == ""){
        if (!listMode)
            return 1;
        listMode = false;
        return 0;
    }
    // list all
    if (text == "0"){
        listOutput();
        listMode = true;
    }
    // new task
    if (text == "1"){
        listOutput();
        std::string newTaskname;
        std::getline(std::cin, newTaskname);
        if (newTaskname != "")
            tasks.push_back({newTaskname});
        std::cout << "\033[2J\033[H";
        std::cout << newTaskname << " has been created";
    }
    // finish task
    if (text == "2"){
        listOutput();
        std::string number;
        std::getline(std::cin, number);
        if (number != ""){
            int intNumber = std::stoi(number);
            auto it = std::next(tasks.begin(), intNumber);
            tasks.erase(it);
        }
    }
    return 0;
}

void readFile(){
    std::ifstream myfile;
    myfile.open("tasklist.txt");
    std::string line;
    while (getline(myfile, line))
        tasks.push_back({line});
    myfile.close();
}

void writeFile(){
    std::ofstream myfile;
    myfile.open("tasklist.txt");
    for (Task task : tasks)
        myfile << task.name << "\n";
    myfile.close();
}
void printBuh(){
    std::ifstream myfile;
    myfile.open("buh.txt");
    std::string line;
    while (getline(myfile, line))
        std::cout<< line << "\n";
    myfile.close();
}

int main(){
    readFile();
    printBuh();
    int result = -1;
    while (result != 1)
       result = runner();
    writeFile();
    return 0;
}
