#include "terminal.hpp"

int main(){
    Terminal terminal;
    while (!terminal.close)
        terminal.run();

    return 0;
}
