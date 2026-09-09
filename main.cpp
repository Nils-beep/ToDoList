#include <cstdio>
#include <iostream>
#include <istream>
#include <string>
#include <list>
#include <fstream>
#include <iterator>
#include <vector>


struct Task{
    std::string name;
    bool state = false;
};

std::vector<Task> tasks;
bool listMode = false;

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
    std::cout << "--------------------------------------------------------------- \n";
    for (Task task : tasks){
        if (!task.state)
            std::cout << "󰄱 ";
        else
            std::cout << " ";
        std::cout << task.name << "\n";
    }
    std::cout << "---------------------------------------------------------------\n";
}

int runner(){
    listOutput();
    std::cout << "c: create new Task \n";
    std::cout << "f: finish task \n";
    std::cout << "u: unfinish task \n";
    std::cout << "leave blank to stop \n----\n> ";

    std::string text;
    std::getline(std::cin, text);
    //clean cli
    std::cout << "\033[2J\033[H";

    // stop
    if (text == ""){
        return 1;
    }
    // new task
    if (text == "c"){
        std::string newTaskname;
        listOutput();
        std::cout << "\n󰄱 > ";
        std::getline(std::cin, newTaskname);
        if (newTaskname != "")
            tasks.push_back({newTaskname});
        std::cout << "\033[2J\033[H";
        //std::cout << newTaskname << " has been created\n";
    }
    // finish task
    if (text == "f"){
        std::string number;
        std::cout << "\033[2J\033[H";
        listOutput();
        std::cout << "\n > ";
        std::getline(std::cin, number);
        int intNumber;
        if (number != ""){
            int intNumber = std::stoi(number);
            //tasks.erase(it);
            tasks[intNumber-1].state = true;
            //std::cout << "Task " << number << " has been finished! \n";
        }
        std::cout << "\033[2J\033[H";
    }
    // unfinish task
    if (text == "u"){
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
    for (Task task : tasks){
        if (!task.state)
            myfile << task.name << "\n";
    }
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
    std::cout << "\033[2J\033[H";
    readFile();
    int result = -1;
    while (result != 1)
       result = runner();
    writeFile();
    listOutput();
    return 0;
}
