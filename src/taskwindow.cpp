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


bool eraseSubstring(std::string* line, std::string subStr, int subPos){
    int length = 0;
    std::size_t pos = std::string::npos;
    if (subPos != -1){
        int length = subStr.length();
        std::size_t pos = line->find(subStr);

        if (pos == std::string::npos)
            return false;
        std::string subString = line->substr(pos, length);
        line->erase(pos-1, length); //-1 to remove the space
    } else{

    }
    return true;
}

std::string convertText(std::string (*text)){
    std::string line = (*text).substr(0, (*text).find(" "));
    (*text).erase(0, (*text).find(" ")+1);
    if (isInteger(line))
        return "selectList";
    return line;
}

void TaskWindow::deleteList(std::string parameters){
    std::cout << parameters << "\n";
    int index = stoi(parameters);
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
        std::cout<< std::string(int(tasklistWidth/5),' ') << line << "\n";
    myfile.close();
}

void TaskWindow::readFile(){
    int listAmount = int(number_of_files_in_directory(tasklistFolder)-1);
    tasklists.resize(listAmount, Tasklist{"", 0});
    for (const auto& dirEntry : std::filesystem::directory_iterator(tasklistFolder)){
        if (dirEntry.is_directory())
            continue;
        std::ifstream myfile;
        myfile.open(dirEntry.path());
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
            if (list.toDelete){
                list.deleteTasklist();
                continue;
            }
            std::ofstream myfile;
            std::string path = tasklistFolder + "/" + list.getName() + ".txt";
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
}

int TaskWindow::handleInput(){
    linenoise::LoadHistory("history.txt");
    std::string text = "";
    std::cout << "\n";
    linenoise::Readline("> ", text);
    linenoise::AddHistory(text.c_str());
    linenoise::SaveHistory("history.txt");

    if (selectedTasklist == -1){
        if (text == "")
            return -1;
        std::string command = convertText(&text);
        commandMap[command](text);
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
        titleOutput();
        for (Tasklist tasklist: tasklists)
            tasklist.display();
        return;
    }
}
