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
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <cwchar>
#include <locale>
#include <codecvt>


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

using namespace std;

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h> // for displaying colors
#endif // Windows

string inline get_textcolor_code(const int textcolor) { // Linux only
    switch(textcolor) {
        case  0: return "30"; // color_black      0
        case  1: return "34"; // color_dark_blue  1
        case  2: return "32"; // color_dark_green 2
        case  3: return "36"; // color_light_blue 3
        case  4: return "31"; // color_dark_red   4
        case  5: return "35"; // color_magenta    5
        case  6: return "33"; // color_orange     6
        case  7: return "37"; // color_light_gray 7
        case  8: return "90"; // color_gray       8
        case  9: return "94"; // color_blue       9
        case 10: return "92"; // color_green     10
        case 11: return "96"; // color_cyan      11
        case 12: return "91"; // color_red       12
        case 13: return "95"; // color_pink      13
        case 14: return "93"; // color_yellow    14
        case 15: return "97"; // color_white     15
        default: return "37";
    }
}
string inline get_backgroundcolor_code(const int backgroundcolor) { // Linux only
    switch(backgroundcolor) {
        case  0: return  "40"; // color_black      0
        case  1: return  "44"; // color_dark_blue  1
        case  2: return  "42"; // color_dark_green 2
        case  3: return  "46"; // color_light_blue 3
        case  4: return  "41"; // color_dark_red   4
        case  5: return  "45"; // color_magenta    5
        case  6: return  "43"; // color_orange     6
        case  7: return  "47"; // color_light_gray 7
        case  8: return "100"; // color_gray       8
        case  9: return "104"; // color_blue       9
        case 10: return "102"; // color_green     10
        case 11: return "106"; // color_cyan      11
        case 12: return "101"; // color_red       12
        case 13: return "105"; // color_pink      13
        case 14: return "103"; // color_yellow    14
        case 15: return "107"; // color_white     15
        default: return  "40";
    }
}

struct Color {
    int r;
    int g;
    int b;
};

constexpr Color color_red    {235, 105, 120};
constexpr Color color_green  {120, 220, 145};
constexpr Color color_yellow {245, 205, 95};

constexpr Color color_pink   {235, 135, 190};
constexpr Color color_gray   {180, 180, 180};
constexpr Color color_white  {245, 245, 245};

std::string inline get_print_color(const Color& color) {
    return "\033[38;2;" +
           std::to_string(color.r) + ";" +
           std::to_string(color.g) + ";" +
           std::to_string(color.b) + "m";
}

std::string inline get_print_color(const Color& text, const Color& background) {
    return "\033[38;2;" +
           std::to_string(text.r) + ";" +
           std::to_string(text.g) + ";" +
           std::to_string(text.b) +
           ";48;2;" +
           std::to_string(background.r) + ";" +
           std::to_string(background.g) + ";" +
           std::to_string(background.b) + "m";
}

void inline print_color(const Color& textcolor) {
#ifdef __linux__
    std::cout << get_print_color(textcolor);
#endif
}

void inline print_color(const Color& textcolor, const Color& backgroundcolor) {
#ifdef __linux__
    std::cout << get_print_color(textcolor, backgroundcolor);
#endif
}

void inline print_color_reset() {
#ifdef __linux__
    std::cout << "\033[0m";
#endif
}

void inline println(const std::string& s = "") {
    std::cout << s << '\n';
}

void inline print(const std::string& s = "") {
    std::cout << s;
}

void inline print(const std::string& s, const Color& textcolor) {
    print_color(textcolor);
    std::cout << s;
    print_color_reset();
}

void inline print(
    const std::string& s,
    const Color& textcolor,
    const Color& backgroundcolor
) {
    print_color(textcolor, backgroundcolor);
    std::cout << s;
    print_color_reset();
}

void inline print_no_reset(
    const std::string& s,
    const Color& textcolor
) {
    print_color(textcolor);
    std::cout << s;
}

void inline print_no_reset(
    const std::string& s,
    const Color& textcolor,
    const Color& backgroundcolor
) {
    print_color(textcolor, backgroundcolor);
    std::cout << s;
}
