#include <iostream>
#include <istream>
#include <string>
#include <list>


struct Task{
    std::string name;
    bool state = false;
};

std::list<Task> tasks;

int runner(){
    std::cout << "0: list Tasks (" << tasks.size() << ") \n";
    std::cout << "1: create new Task \n";
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

    return 0;
}

int main(){
    std::cout << "Task programm started BUH \n" ;
    tasks.push_back({"woah"});
    int result = -1;
    while (result != 1)
       result = runner();
    return 0;
}
