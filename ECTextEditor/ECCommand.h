#ifndef ECCOMMAND_H
#define ECCOMMAND_H
#include "ECModel.h"

//template command class used for executing
class ECCommand
{
public:
    ECCommand() {}
    virtual ~ECCommand() {};
    virtual void execute() = 0;
    virtual void unexecute() = 0;
};

//Command History to keep track of additions and etc.
class ECCommandHistory{
public:
    ECCommandHistory(){}
    ~ECCommandHistory();

    //commands for execute, unexecute, reexecute from history
    void executeHist(ECCommand *command);
    void unexecute();
    void reexecute();

private:
    vector<ECCommand *> _executedHistory, _undoneHistory;
};

//command class for enter
class CommandEnterKey : public ECCommand{
public:
    CommandEnterKey(ECModel * modelIn): _model(modelIn){}
    ~CommandEnterKey(){}
    void execute();
    void unexecute();
private:
    ECModel * _model;
    //PARAMS KEY:
    //params[0] = page, params[1] = cursorX, params[2] = cursorY,
    //params[3] = flag, params[4] = undone bool
    vector<int> params;
};

//command class for backspace
class CommandBackspaceKey : public ECCommand{
public:
    CommandBackspaceKey(ECModel * modelIn): _model(modelIn){}
    ~CommandBackspaceKey(){}
    void execute();
    void unexecute();
private:
    ECModel * _model;
    //PARAMS KEY:
    //params[0] = page, params[1] = cursorX, params[2] = cursorY,
    //params[3] = flag, params[4] = undone bool 
    vector<int> params;
};

//command class for character entry
class CommandCharacterKey : public ECCommand{
public:
    CommandCharacterKey(ECModel * modelIn, char keyIn): _model(modelIn), key(keyIn){}
    ~CommandCharacterKey(){}
    void execute();
    void unexecute();
private:
    ECModel * _model;
    //PARAMS KEY:
    //params[0] = page, params[1] = cursorX, params[2] = cursorY,
    //params[3] = flag, params[4] = undone bool
    vector<int> params;
    char key;
};

//command class for replace
class CommandReplace : public ECCommand{
public:
    CommandReplace(ECModel * modelIn, string findIn, string replaceIn)
    : _model(modelIn), find(findIn), replace(replaceIn){}
    ~CommandReplace(){}
    void execute();
    void unexecute();
private:
    ECModel * _model;
    //phrases for finding and replacing
    string find, replace;
};


#endif