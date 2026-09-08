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
    std::cout << "1: create new Task \n" << "---------------------------------------------- \n";

    std::string text;
    std::cin >> text;
    if (text == "0"){
        for (Task i : tasks)
            std::cout<< i.name << "\n";
    }

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
    while (true)
        runner();
}
