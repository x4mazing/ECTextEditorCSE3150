#ifndef ECCONTROLLER_H
#define ECCONTROLLER_H
#include "ECCommand.h"

class ECController{

public:
    ECController(ECModel * modelIn): _model(modelIn), _mode(0){}
    ~ECController(){}
    
    ECModel * getModel(){return _model;}

    //controller methods that create an object and invokes command history
    void actionEnter();    
    void actionBackspace();    
    void actionCharKey(char Key);  
    void actionUndo(); 
    void actionRedo(); 
    void actionReplace(string find, string replace);   

    //controller methods that do not invoke command history or command
    void actionRightArrow();
    void actionLeftArrow();
    void actionDownArrow();
    void actionUpArrow();

    //setting the window mode
    void setMode(int x){_mode = x;}
    int getMode(){return _mode;}
    

private:
    int _mode;
    ECModel * _model;
    ECCommandHistory _commandHistoryPtr;
};

#endif