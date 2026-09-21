#include "tasklist.hpp"
#include "terminal.hpp"


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
/*void TaskWindow::writeFile(){
    int index = 0;
    for (Tasklist list : tasklists){
        std::ofstream myfile;
        std::string path = listFolder + "/" + list.name + ".txt";
        myfile.open(path);
        for (Task task : tasklists[index].tasks){
            if (!task.state){
                myfile << task.name;
                if (task.prio == HIGH)
                myfile << "!!";
                else
                    if (task.prio == MEDIUM)
                        myfile << "!";
                myfile << "\n";
            }
        }
        myfile.close();
        index++;
    }
}
*/

int TaskWindow::handleInput(){
    std::cout << "👂️>";
    std::string text;
    std::getline(std::cin, text);
    std::cout << "text=[" << text << "] selected=" << selectedTasklist << "\n";
    if ((text == "") && (selectedTasklist == -1)){
        std::cout << "got here\n";
        return -1;
    }
    if (text == ""){
        selectedTasklist = -1;
        return 0;
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
        CLEARSCREEN;
        return;
    }
}
