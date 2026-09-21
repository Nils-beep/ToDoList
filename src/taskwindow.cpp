#include "includes.hpp"
#include "tasklist.hpp"
#include "terminal.hpp"
#include <string>
#include <variant>



void titleOutput(){
    std::ifstream myfile;
    myfile.open("title.txt");
    std::string line;
    while (getline(myfile, line))
        std::cout<< line << "\n";
    myfile.close();
}

void TaskWindow::readFile(){
    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(listFolder)){
        std::ifstream myfile;
        myfile.open(dirEntry.path());
        tasklists.push_back({dirEntry.path().stem(), LOW});
        std::string line;
        while (getline(myfile, line)){
            tasklists[tasklists.size()-1].addTask(&line);
            //std::cout << tasklists[tasklists.size()-1].tasks.back().name <<" " << tasklists[tasklists.size()-1].tasks.back().prio << "\n";
        }
        myfile.close();
    }
}
void TaskWindow::writeFile(){
    int index = 0;
    for (Tasklist list : tasklists){
        std::ofstream myfile;
        std::string path = listFolder + "/" + list.getName() + ".txt";
        myfile.open(path);
        for (Task task : *tasklists[index].getTasks()){
            if (!task.getState()){
                myfile << task.getName();
                if (task.getPrio() == HIGH)
                myfile << "!!";
                else
                    if (task.getPrio() == MEDIUM)
                        myfile << "!";
                myfile << "\n";
            }
        }
        myfile.close();
        index++;
    }
}

int TaskWindow::handleInput(){
    std::cout<<"\n" << "👂️> ";
    std::string text;
    std::getline(std::cin, text);
    if (selectedTasklist == -1){
        if (text == ""){
            std::cout << "got here\n";
            return -1;
        }
        if (isInteger(text)){
            selectedTasklist = stoi(text)-1;
            return 0;
        }
        if (text.substr(0,3) == "new"){
            text = text.substr(3, text.length());
            if (text != "")
                tasklists.push_back({text, LOW});
            return 0;
        }

    }else{
        if (text == ""){
            selectedTasklist = -1;
            return 0;
        }
        if (text.substr(0, 4) == "prio"){
            text = text.substr(4, text.length());
            tasklists[selectedTasklist].findPriority(&text);
            return 0;
        }
        if (isInteger(text)){
            tasklists[selectedTasklist].toggleTask(stoi(text)-1);
            return 0;
        }
        tasklists[selectedTasklist].addTask(&text);
    }
    return 0;
}

void TaskWindow::run(Terminal* terminal){
    CLEARSCREEN;
    titleOutput();
    if (selectedTasklist == -1)
        for (Tasklist tasklist: tasklists){
            tasklist.display();
        }
    else tasklists[selectedTasklist].display();
    int next = handleInput();
    if (next == -1){
        terminal->changeWindow(MAINWINDOW);
        writeFile();
        CLEARSCREEN;
        return;
    }
}
