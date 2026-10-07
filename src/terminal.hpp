#pragma once
#include "includes.hpp"
#include "tasklist.hpp"
#include <functional>
#include <map>
#include <string>
#include <utility>
#include <vector>

class Terminal;

class MainWindow{
    private:

    public:
        bool closeTerminal = false;
        void run();
};
class TaskWindow{
    private:
        std::vector<Tasklist> tasklists;
        int handleInput();
        void readFile();
        bool findAndRemoveString(std::string* line, std::vector<std::string> words);
        void deleteList(std::string parameters);
        std::map<std::string, std::function<void(std::string)>> commandMap;

    public:
        TaskWindow();
        bool close;
        void run(Terminal* terminal);
        void writeFile();
};
class TimerWindow{
    private:
    public:
        void run(){};
};

class Terminal {
    private:
        MainWindow mainWindow;
        TaskWindow taskWindow;
        TimerWindow timerWindow;
        Window currentWindow = TASKWINDOW;

    public:
        bool close = false;
        Window* changeWindow(Window newWindow){
            currentWindow = newWindow;
            return &currentWindow;
        };
        void run(){
            switch(currentWindow){
                case MAINWINDOW:
                   mainWindow.run();
                   close = mainWindow.closeTerminal;
                   break;
                case TASKWINDOW:
                    taskWindow.run(this);
                    break;
                case TIMERWINDOW:
                    timerWindow.run();
                    break;
            }
        };
};

inline TaskWindow::TaskWindow(){
    readFile();
    auto deleteCommand = [this](std::string parameters){
        deleteList(parameters);
    };
    auto returnCommand = [this](std::string parameters){
        selectedTasklist = -1;
    };
    auto selectCommand = [this](std::string parameters){
        int index = stoi(parameters.substr(0,parameters.find(" ")));
        if ((index >= 0) && (index < tasklists.size()))
            selectedTasklist = index;
    };
    auto createListCommand = [this](std::string parameters){
        std::string listName = parameters.substr(0,parameters.find(" "));
        parameters = parameters.substr(parameters.find(" ")+1); //this should only leave hidden //todo dates and shit
        tasklists.push_back({listName, int(tasklists.size())});
        if (parameters == "-h")
            tasklists[tasklists.size()-1].toggleHidden();
    };
    auto hideListCommand = [this](std::string parameters){
        tasklists[stoi(parameters)-1].toggleHidden();
    };
    auto swapListsCommand = [this](std::string parameters){
        std::cout << parameters << "\n";
        int list1 = stoi(parameters.substr(0,parameters.find(" ")))-1;
        std::cout << parameters << "     " << list1 << "\n";
        parameters = parameters.substr(parameters.find(" ")+1);
        int list2 = stoi(parameters)-1;
        std::cout << parameters << "     " << list2 << "\n";
        Tasklist tasklist = tasklists[list1];
        tasklists[list1] = tasklists[list2];
        tasklists[list2] = tasklist;
        tasklists[list1].setIndex(list1);
        tasklists[list2].setIndex(list2);
    };

    commandMap["delete"] = deleteCommand;
    commandMap["del"] = deleteCommand;
    commandMap["remove"] = deleteCommand;
    commandMap[""] = returnCommand;
    commandMap["selectList"] = selectCommand;
    commandMap["new"] = createListCommand;
    commandMap["create"] = createListCommand;
    commandMap["hide"] = hideListCommand;
    commandMap["swap"] = swapListsCommand;
    commandMap["switch"] = swapListsCommand;
}

void inline MainWindow::run(){
    closeTerminal = true;
    return;
    std::string text;
    std::getline(std::cin, text);
    if (text == ""){

    }
}
