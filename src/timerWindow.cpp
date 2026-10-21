#include "terminal.hpp"
#include "includes.hpp"
#include <fstream>

TimerWindow::TimerWindow(){
    //system("notify-send test");
    createTimer("");
}


void TimerWindow::createTimer(std::string arguments){
    system("notify-send test");
    const std::string filePath = "/etc/systemd/system/";
    arguments = "test";
    std::ofstream file(filePath+arguments+".timer");
    file <<"[Unit]\n"
        <<"Description=test timer\n\n"
        <<"[Timer]\n"
        <<"OnBootSec=15min\n"
        <<"OnUnitActiveSec=1w\n\n"
        <<"[Install]\n"
        <<"WantedBy=timers.target";
    file.close();
}
