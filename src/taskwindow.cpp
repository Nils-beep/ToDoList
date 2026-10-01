#include "includes.hpp"
#include "tasklist.hpp"
#include "terminal.hpp"
#include <algorithm>
#include <cstring>
#include <filesystem>
#include <iterator>
#include <list>
#include <variant>
#include <cstddef>
#include <string>
#include <vector>


bool eraseSubstring(std::string* line, std::string subStr){
    int length = subStr.length();
    std::size_t pos = line->find(subStr);

    if (pos == std::string::npos)
        return false;
    std::string subString = line->substr(pos, length);
    line->erase(pos-1, length); //-1 to remove the space
    return true;
}
//return value is the command
// 0: base info name or index
// 1: always priorities TODO convert them here
// 2: -h hidden   erguhi -h
std::string convertText(std::string (*text)[parameterAmount]){
    std::string line = (*text)[mainData];
    if (isInteger(line))
        return "selectList";
    std::string command = line.substr(0, line.find(" "));
    line = line.substr(line.find(" ")+1);
    if (eraseSubstring(&line, "-h"))
        (*text)[hiddenState] = "true";
    (*text)[mainData] = line;
    return command;
}

void TaskWindow::deleteList(std::string parameters[5]){
    std::cout << parameters[mainData] << "\n";
    int index = stoi(parameters[mainData]);
    tasklists[index-1].toDelete = !tasklists[index-1].toDelete;
    return;
}

bool TaskWindow::findAndRemoveString(std::string* line, std::vector<std::string> words){
    for (std::string word : words){
        size_t pos = line->find(word);
        if (pos != std::string::npos){
            removeSpaces(line);
            if (isInteger(line->substr(word.length(), line->length()-word.length()+1))){
                line->erase(pos, word.length());
                return true;
            }
        }
    }
    return false;
}

void titleOutput(){
    std::ifstream myfile;
    myfile.open("title.txt");
    std::string line;
    while (getline(myfile, line))
        std::cout<< line << "\n";
    myfile.close();
}

void TaskWindow::readFile(){
    int listAmount = int(number_of_files_in_directory(listFolder));
    tasklists.resize(listAmount, Tasklist{"", 0});
    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(listFolder)){
        std::ifstream myfile;
        myfile.open(dirEntry.path());
        //tasklists.push_back({dirEntry.path().stem()});
        std::string line;
        getline(myfile, line);
        int index = stoi(line.substr(0, line.find(",")));
        bool hidden = stoi(line.substr(2, line.find(",")));
        tasklists[index].setName(dirEntry.path().stem());
        tasklists[index].setIndex(index);
        if (hidden)
            tasklists[index].toggleHidden();
        while (getline(myfile, line)){
            tasklists[index].addTask(&line);
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
            myfile << index <<"," << list.getHidden() << ",\n";
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
    for (Tasklist list : tasklists)
        if (list.toDelete) list.deleteTasklist();
}

int TaskWindow::handleInput(){
    std::cout<<"\n" << "👂️> ";
    std::string text;
    std::getline(std::cin, text);
    if (selectedTasklist == -1){
        if (text == ""){
            return -1;
        }

        std::string arguments[5] = {"-","-","-","-","-"};
        std::cout << arguments[3] << "\n";
        arguments[0] = text;
        std::string command = convertText(&arguments);
        commandMap[command](arguments);
        return 0;
    }
    else{
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
    //CLEARSCREEN;
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
