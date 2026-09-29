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


#define CLEARSCREEN system("clear")
#define DELETE {"del", "delete"}

const std::string listFolder = "tasklists";

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

bool inline isInteger(const std::string& s) {
    int value;
    auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), value);
    return ec == std::errc() && ptr == s.data() + s.size();
}

void inline removeSpaces(std::string* text){
    text->erase(remove_if(text->begin(), text->end(), isspace), text->end());
}

#include "colourStuff.hpp" //idk why i have to include it here I am crying
