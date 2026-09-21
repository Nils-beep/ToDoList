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
