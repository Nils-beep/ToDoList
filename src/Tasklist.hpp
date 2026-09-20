#include "imports.hpp"

enum Priority{
    LOW,
    MEDIUM,
    HIGH,
};

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
        
}
