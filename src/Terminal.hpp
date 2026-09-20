enum Window{
    MainWindow = 0,
    TaskWindow = 1,
    TimerWindow = 2,
};

class Terminal {
    private:
        Window currentWindow = MainWindow;
        bool close = false;
    public:
        Window* changeWindow(Window newWindow){
            currentWindow = newWindow;
            return &currentWindow;
        };
        Window getCurrentWindow(){
            return currentWindow;
        };
};
