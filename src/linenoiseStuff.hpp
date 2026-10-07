#include "linenoise.hpp"
#include <string>
#include <vector>



inline void setupLinenoise(){
linenoise::SetHistoryMaxLen(20);
linenoise::SetCompletionCallback(
    [](const char* buf, size_t pos, std::vector<linenoise::Completion>& comps) {
        std::string hintWords[] = {"delete", "switch", "swap", "new"};
        size_t start = pos;

        while (start > 0 && buf[start - 1] != ' ') start--;
        std::string word(buf + start, pos - start);
        for (std::string word : hintWords){
            if (word.find(buf) != std::string::npos)  // "commit" starts with word
                comps.push_back({word, start, pos});     // replace [start, pos)
        }
        });

// Show a hint at the right of the prompt while typing
linenoise::SetHintsCallback(
    [](const char* editBuffer, int& color, bool& bold) -> std::string {
        std::string hintWords[] = {"delete", "switch", "swap", "new"};
        if (std::string(editBuffer).find(hintWords[0]) != std::string::npos) {
            color = 35;
            return " <listnumber>";
        }

        for(std::string word: hintWords){
            for (int i = 1; i<=std::string(editBuffer).length(); i++)
                if ((word.substr(0,i).find(editBuffer) != std::string::npos) && (std::string(editBuffer) != "")){
                    color = 90;
                    return word.erase(word.find(editBuffer), std::string(editBuffer).length());
                    }
        }
        return {};
    });
}
