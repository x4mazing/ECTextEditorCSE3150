#include "ECCommand.h"
#include <vector>

//Command History to keep track of additions and etc.

//=================COMMAND HISTORY IMPLMENTATION===================//
ECCommandHistory :: ~ECCommandHistory() {
    //destroy history of command and undone commands
    for(auto x : _executedHistory){
        delete x;
        _executedHistory.pop_back();
    }
    for(auto x : _undoneHistory){
        delete x;
        _undoneHistory.pop_back();
    }
}
void ECCommandHistory :: executeHist(ECCommand * command){
    //if the undone histroy has anything in it, remove it
    while(_undoneHistory.empty() != true){
        delete _undoneHistory.back();
        _undoneHistory.pop_back();
    }
    //store the command to history and execute
    _executedHistory.push_back(command);
    command->execute();
}
//pop from executed history and pushback to undone history and unexecute
void ECCommandHistory :: unexecute(){
    //if the history is not empty unexecute the last command
    if(_executedHistory.empty() != true){
        _executedHistory.back()->unexecute();

        //push it back to the undone history and pop from the executed history
        _undoneHistory.push_back(_executedHistory.back());
        _executedHistory.pop_back();
    }
}
//popback from undonehistory and execute
void ECCommandHistory :: reexecute(){
    //if the undone history is not empty, execute last thing undone
    if(_undoneHistory.empty() != true){
        _undoneHistory.back()->execute();
        
        //store in in executed history and pop from undone history
        _executedHistory.push_back(_undoneHistory.back());
        _undoneHistory.pop_back();
    }
}
//===========================END============================//

//=============COMMAND-SUBTYPE IMPLMENTATIONS===============//
void CommandEnterKey :: execute(){
    //if the command has already been undone set paramters back
    if(!params.empty()&& params.back() == 1){
        _model->SetCurrPage(params[0]);
        _model->SetCursorX(params[1]);
        _model->SetCursorY(params[2]);
    }
    
    //clear parameters call the function and store parameters
    params.clear();
    int flag = _model->enterKey();
    params = _model->setParams();
    params.push_back(flag);
    params.push_back(0);
}
void CommandEnterKey :: unexecute(){
    _model->undoEnter(params);
}

void CommandBackspaceKey :: execute(){
    //if the command has already been undone set paramters back
    if(!params.empty()&& params.back() == 1){
        _model->SetCurrPage(params[0]);
        _model->SetCursorX(params[1]);
        _model->SetCursorY(params[2]);
    }

    //clear parameters call the function and store parameters
    params.clear();    
    int flag = _model->backspaceKey();
    params = _model->setParams();
    params.push_back(flag);
    params.push_back(0);
}
void CommandBackspaceKey :: unexecute(){
    _model->undoBackspace(params);
}
void CommandCharacterKey :: execute(){
    //if the command has already been undone set paramters back
    if(!params.empty()&& params.back() == 1){
        _model->SetCurrPage(params[0]);
        _model->SetCursorX(params[1]);
        _model->SetCursorY(params[2]);
    }
    //clear parameters call the function and store parameters
    params.clear();
    int flag = _model->characterKey(key);
    params = _model->setParams();
    params.push_back(flag);
    params.push_back(0);
}
void CommandCharacterKey :: unexecute(){
    //call the undo function for character
    _model->undoChar(params);
}
void CommandReplace :: execute(){
    //call model for replaceing
    _model->replaceEvent(find, replace);
}
void CommandReplace :: unexecute(){
    //call model for replaceing but swap replace and find
    _model->replaceEvent(replace, find);
}
//=========================END=========================