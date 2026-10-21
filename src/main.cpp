#include "includes.hpp"
#include "terminal.hpp"
#include <filesystem>
#include <string>

int main(int argc, char** argv){
    if (!std::filesystem::exists("history.txt")){
        std::ofstream file("history.txt");
        file.close();
    }
    setupLinenoise();
    commandWordsinitializer();
    std::string folderPath = pathToData + "/Tasker";
    if (!std::filesystem::exists(folderPath))
        std::filesystem::create_directory(folderPath);
    Terminal terminal;
    std::string arg1 = "";
    if (argc == 2)
        arg1 = argv[1];
    if (arg1 == "timers")
        terminal.changeWindow(TIMERWINDOW);
    while (!terminal.close)
        terminal.run();

    return 0;
}
