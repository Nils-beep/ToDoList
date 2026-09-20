#pragma once
#include "includes.hpp"
#include <cassert>
#include <vector>

class MainWindow{
    private:
    public:
        void run(){};
};
class TaskWindow{
    private:
    public:
        void run(){};
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
        Window currentWindow;

        bool close = false;
    public:
        Window* changeWindow(Window newWindow){
            currentWindow = newWindow;
            return &currentWindow;
        };
        void run(){
            switch(currentWindow){
                case MAINWINDOW:
                   mainWindow.run();
                   break;
                case TASKWINDOW:
                    taskWindow.run();
                    break;
                case TIMERWINDOW:
                    timerWindow.run();
                    break;
            }
        };
};
