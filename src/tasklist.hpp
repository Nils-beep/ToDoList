#include "includes.hpp"
#include <vector>

class Task{
    Task(std::string n, bool s, Priority p){
        name = n; state = s; prio = p;
    }
    private:
        std::string name;
        bool state;
        Priority prio;
    public:
        void changePrio(Priority p){prio = p;}
        void toggleTask(){state = !state;}

        Priority getPrio(){return prio;}

};

class Tasklist{
    Tasklist(std::string n, Priority p){name = n; prio = p;}
    private:
        std::string name;
        Priority prio;
        std::vector<Task> tasks;
    public:
        void addTask(std::string n, Priority p){tasks.push_back();}

}
