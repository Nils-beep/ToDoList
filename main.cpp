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

int runner(){
    std::cout << "0: list Tasks (" << tasks.size() << ") \n";
    std::cout << "1: create new Task \n";
    std::cout << "2: finish task \n";
    std::cout << "leave blank to stop \n";

    std::string text;
    std::getline(std::cin, text);

    // stop
    if (text == "")
        return 1;

    // list all
    if (text == "0"){
        for (Task i : tasks)
            std::cout<< i.name << "\n";
    }
    // new task
    if (text == "1"){
        std::string newTaskname;
        std::getline(std::cin, newTaskname);
        if (newTaskname != "")
            tasks.push_back({newTaskname});
    }
    if (text == "2"){
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

int main(){
    readFile();
    int result = -1;
    while (result != 1)
       result = runner();
    writeFile();
    return 0;
}
