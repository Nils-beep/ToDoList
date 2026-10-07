#include "includes.hpp"
#include "terminal.hpp"
#include <filesystem>

int main(){
    setupLinenoise();
    commandWordsinitializer();
    std::string folderPath = pathToData + "/Tasker";
    if (!std::filesystem::exists(folderPath))
        std::filesystem::create_directory(folderPath);
    Terminal terminal;
    while (!terminal.close)
        terminal.run();

    return 0;
}
