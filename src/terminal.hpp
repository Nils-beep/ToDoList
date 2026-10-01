#pragma once
#include "tasklist.hpp"
#include <functional>
#include <map>
#include <string>
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
        void deleteList(std::string parameters[parameterAmount]);
        std::map<std::string, std::function<void(std::string[parameterAmount])>> commandMap;

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
    auto deleteCommand = [this](std::string parameters[parameterAmount]){
        deleteList(parameters);
    };
    auto returnCommand = [this](std::string parameters[parameterAmount]){
        selectedTasklist = -1;
    };
    auto selectCommand = [this](std::string parameters[parameterAmount]){
        int index = stoi(parameters[mainData]) - 1;
        if ((index >= 0) && (index < tasklists.size()))
            selectedTasklist = index;
    };
    auto createListCommand = [this](std::string parameters[parameterAmount]){
        tasklists.push_back({parameters[mainData], int(tasklists.size())});
        if (parameters[hiddenState] == "true")
            tasklists[tasklists.size()-1].toggleHidden();
    };
    commandMap["delete"] = deleteCommand;
    commandMap["del"] = deleteCommand;
    commandMap["remove"] = deleteCommand;
    commandMap[""] = returnCommand;
    commandMap["selectList"] = selectCommand;
    commandMap["new"] = createListCommand;
}

void inline MainWindow::run(){
    std::string text;
    std::getline(std::cin, text);
    if (text == ""){
        closeTerminal = true;
    }
}
