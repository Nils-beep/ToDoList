#pragma once
#include <bits/stdc++.h>
#include <filesystem>
#include <functional>
#include <map>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <variant>
#include <cassert>
#include <codecvt>
#include <cstdlib>
#include <string>
#include <cctype>
#include <string>
#include <ranges>
#include <locale>
#include <vector>
#include <vector>
#include <cwchar>
#include <list>
#include "linenoise.hpp"
#include "linenoiseStuff.hpp"

#define CLEARSCREEN system("clear")
#define DELETE {"del", "delete"}

const std::string pathToData = std::getenv("XDG_DATA_HOME");
const std::string tasklistFolder = pathToData + "/Tasker";

const int parameterAmount = 5;
const int tasklistWidth = 80;

inline int selectedTasklist = -1;

enum paramIndex{
    mainData,
    extraInfo,
    hiddenState,
    withDate
};

enum Window{
    MAINWINDOW,
    TASKWINDOW,
    TIMERWINDOW,
};

enum Priority{
    LOW,
    MEDIUM,
    HIGH,
};

inline std::string deleteCommands[] = {"delete", "destroy", "remove"};
inline std::string makeCommands[] = {"new", "create", "make"};
inline std::string selectCommands[] = {"select", "choose", "pick"};
inline std::string hideCommands[] = {"hide", "show"};
inline std::vector<std::string> commandWords;

void inline commandWordsinitializer(){
    commandWords.insert(commandWords.end(), std::begin(deleteCommands), std::end(deleteCommands));
    commandWords.insert(commandWords.end(), std::begin(makeCommands), std::end(makeCommands));
    commandWords.insert(commandWords.end(), std::begin(selectCommands), std::end(selectCommands));
    commandWords.insert(commandWords.end(), std::begin(hideCommands), std::end(hideCommands));
}

bool inline isInteger(const std::string& s) {
    int value;
    auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), value);
    return ec == std::errc() && ptr == s.data() + s.size();
}

void inline removeSpaces(std::string* text){
    text->erase(remove_if(text->begin(), text->end(), isspace), text->end());
}

std::size_t inline number_of_files_in_directory(std::filesystem::path path)
{
    using std::filesystem::directory_iterator;
    return std::distance(directory_iterator(path), directory_iterator{});
}

#include "colourStuff.hpp" //idk why i have to include it here I am crying
