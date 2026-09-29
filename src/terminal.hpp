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
        int selectedTasklist = -1;
        std::vector<Tasklist> tasklists;
        int handleInput();
        void readFile();
        bool findAndRemoveString(std::string* line, std::vector<std::string> words);
        void deleteList(std::vector<std::string> parameters);
        std::map<std::string, std::function<void(std::vector<std::string>)>> commandMap;

    public:
        TaskWindow(){
            readFile();
            auto deleteCommand = [this](std::vector<std::string> parameters){
                deleteList(parameters);
            };
            auto returnCommand = [this](std::vector<std::string> parameters){
                selectedTasklist = -1;
            };
            auto selectCommand = [this](std::vector<std::string> parameters){
                int index = stoi(parameters[0]) - 1;
                if ((index >= 0) && (index < tasklists.size()))
                    selectedTasklist = index;
            };
            auto createListCommand = [this](std::vector<std::string> parameters){
                switch (tasklists.size()){
                    case 1:
                        tasklists.push_back(parameters[0]);
                        break;
                    case 2:
                        tasklists.push_back(parameters[0]);
                        tasklists.back().findPriority(&parameters[1]);
                        break;
                }
                tasklists.push_back(parameters[0]);
            };
            commandMap["delete"] = deleteCommand;
            commandMap["del"] = deleteCommand;
            commandMap[""] = returnCommand;
            commandMap["selectList"] = selectCommand;
            commandMap["new"] = createListCommand;
        }
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

void inline MainWindow::run(){
    std::string text;
    std::getline(std::cin, text);
    if (text == ""){
        closeTerminal = true;
    }
}
