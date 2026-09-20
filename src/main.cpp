

#define clearScreen std::cout << "\033[2J\033[H";

const std::string listFolder = "tasklists";

struct TaskList{
    std::string name;
    std::vector<Task> tasks;
};

std::vector<TaskList> tasklists;
std::vector<std::string> filesToDelete;
int selectedTasklist;
int listChosen = -1;

Priority findPrio(std::string* line){
    Priority prio = LOW;
    int pos = line->find("!");
    if (pos != -1){
        prio = MEDIUM;
        line->erase(pos, 1);
        pos = line->find("!");
        if (pos != -1){
            prio = HIGH;
            line->erase(pos, 1);
        }
    }
    return prio;
}
void sortByPriority(){
    std::vector<Task>sortedList;
    for (Task task : tasklists[selectedTasklist].tasks){
        if (task.prio == HIGH)
            sortedList.push_back(task);
    }
    for (Task task : tasklists[selectedTasklist].tasks){
        if (task.prio == MEDIUM)
            sortedList.push_back(task);
    }
    for (Task task : tasklists[selectedTasklist].tasks){
        if (task.prio == LOW)
            sortedList.push_back(task);
    }
    tasklists[selectedTasklist].tasks = sortedList;
    sortedList.clear();
}

void titleOutput(){
    std::ifstream myfile;
    myfile.open("title.txt");
    std::string line;
    while (getline(myfile, line))
        std::cout<< line << "\n";
    myfile.close();
}
void listOutput(){
    int taskNumber = 0;
    std::cout << "\n";
    std::cout << "-------------------------------- " << tasklists[selectedTasklist].name<<" --------------------------------\n";
    for (Task task : tasklists[selectedTasklist].tasks){
        taskNumber++;
        if (task.prio == LOW)
            std::cout << "🟩 ";
        else if (task.prio == MEDIUM)
                std::cout << "🟨 ";
        else std::cout << "🟥 ";

        if (!task.state)
            std::cout << "󰄱 ";
        else
            std::cout << " ";

        std::cout << task.name;
        for (int i=0; i<(60-task.name.length()+tasklists[selectedTasklist].name.length()+1 -1); i++)
            std::cout << " ";
        std::cout << taskNumber <<"\n";
    }
    std::cout << std::string(tasklists[selectedTasklist].name.length()+1,'-')<< "-----------------------------------------------------------------\n";
}
void inputLine(){
    std::cout <<"\n > ";
}

void fullListOutput(){
    clearScreen;
    titleOutput();
    selectedTasklist = 0;
    for (TaskList list : tasklists){
        listOutput();
        selectedTasklist++;
    }
}
void fullListSort(){
    selectedTasklist = 0;
    for (TaskList list : tasklists){
        sortByPriority();
        selectedTasklist++;
    }
}

void changePriority(int index, Priority prio){
    tasklists[selectedTasklist].tasks[index-1].prio = prio; //was .name before
    sortByPriority();
}

void createTask(std::string name){
    Priority prio = findPrio(&name);
    tasklists[selectedTasklist].tasks.push_back({name, false, prio});
    sortByPriority();
}

void createList(std::string name){
    name.erase(0,1);
    std::cout << "works";
    tasklists.push_back({name});
}

void deleteList(){
    std::string filePath = listFolder + "/" + tasklists[selectedTasklist].name + ".txt";
    std::remove((filePath.c_str()));
    tasklists.erase(tasklists.begin()+selectedTasklist);
    listChosen = -1;
    selectedTasklist = 0; //so we don't get an invalid value
}

void handleEmptyList(){
    for (Task task : tasklists[selectedTasklist].tasks)
        if (task.state == false) return;
    deleteList();
}

int chooseList(){
    clearScreen;
    titleOutput();
    int listIndex;
    std::string string;
    selectedTasklist = 0;
    for (TaskList list : tasklists){
        listOutput();
        selectedTasklist++;
    }
    inputLine();
    std::getline(std::cin, string);
    if (string == "")
        return 1;

    if (string[0] == '/'){
        createList(string);
        return 0;
    }
    listIndex = std::stoi(string);
    if ((listIndex > tasklists.size()) || (listIndex <= 0))
        return -1;
    selectedTasklist = listIndex-1;
    clearScreen
    return 0;
}

int handleInput(){
    std::string text;
    std::getline(std::cin, text);
    clearScreen;
    listOutput();
    if (text == ""){
        listChosen = -1;
        return 0;
    }
    int commaPos = text.find(",");
    if (!(commaPos == std::variant_npos)){
        std::string first = text.substr(0,commaPos);
        std::string second = text.substr(commaPos+1);
        Priority prio = findPrio(&second);
        changePriority(std::stoi(first), prio);
    }
    else{
        if (!std::isdigit(text[0]))
            createTask(text);
        else{
            int index = std::stoi(text);
            tasklists[selectedTasklist].tasks[index-1].state = !tasklists[selectedTasklist].tasks[index-1].state;
            //handleEmptyList();
        }
    }
    return 0;
}
int runner(){
    titleOutput();
    if (listChosen==-1){
        listChosen = chooseList();
        return listChosen;
    }
    clearScreen;
    titleOutput();
    listOutput();
    inputLine();

    return handleInput();
}

void readFile(){
    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(listFolder)){
        std::ifstream myfile;
        myfile.open(dirEntry.path());
        tasklists.push_back({});
        std::string line;
        tasklists.back().name = dirEntry.path().stem();
        while (getline(myfile, line)){
            Priority prio = findPrio(&line);
            tasklists[tasklists.size()-1].tasks.push_back({line, false, prio});
            //std::cout << tasklists[tasklists.size()-1].tasks.back().name <<" " << tasklists[tasklists.size()-1].tasks.back().prio << "\n";
        }
        myfile.close();
    }
}
void writeFile(){
    int index = 0;
    for (TaskList list : tasklists){
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

int main(){
    if (!std::filesystem::exists(listFolder))
        std::filesystem::create_directory(listFolder);
    clearScreen;
    readFile();
    while (runner() != 1);
    writeFile();
    fullListOutput();
    return 0;
}
