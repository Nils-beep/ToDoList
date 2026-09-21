#pragma once
#include "tasklist.hpp"
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
    public:
        TaskWindow(){readFile();}
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
    if (text == "")
        closeTerminal = true;
}
