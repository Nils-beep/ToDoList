#pragma once
#include <cctype>
#include <iostream>
#include <istream>
#include <list>
#include <sstream>
#include <string>
#include <fstream>
#include <variant>
#include <vector>
#include <bits/stdc++.h>
#include <filesystem>
#include <cassert>
#include <ranges>
#include <vector>

#define CLEARSCREEN std::cout << "\033[2J\033[H";
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
