#include "ECController.h"

//========================MODIFYING COMMANDS========================
void ECController::actionEnter(){
    //create a new object of type enter and pass to command history for execution
    CommandEnterKey * enterPtr = new CommandEnterKey(_model);
    _commandHistoryPtr.executeHist(enterPtr);
};
void ECController::actionBackspace(){
    //create a new object of type backspace and pass to command history for execution
    CommandBackspaceKey * backspacePtr = new CommandBackspaceKey(_model);
    _commandHistoryPtr.executeHist(backspacePtr);        
};
void ECController::actionCharKey(char keyIn){
    //create a new object of type characterkey and pass to command history for execution
    CommandCharacterKey * CharKeyPtr = new CommandCharacterKey(_model, keyIn);
    _commandHistoryPtr.executeHist(CharKeyPtr);
};
void ECController :: actionReplace(string find, string replace){
    //create a new object of type replace and pass to command history for execution
    CommandReplace * replacevent = new CommandReplace(_model, find, replace);
    _commandHistoryPtr.executeHist(replacevent);
};
void ECController::actionUndo(){
    //call unexecute from command history when this undo is called
    _commandHistoryPtr.unexecute();
};
void ECController::actionRedo(){
    //call rexecute from command history when this redo is called
    _commandHistoryPtr.reexecute();
};
//================================END================================

//=================ARROW-KEY FUNCTIONS=================
void ECController::actionRightArrow(){
    //call arrow movement from model
    _model->rightKey();
};
void ECController::actionLeftArrow(){
    //call arrow movement from model
    _model->leftKey();
};
void ECController::actionDownArrow(){
    //call arrow movement from model
    _model->downKey();
};
void ECController::actionUpArrow(){
    //call arrow movement from model
    _model->upKey();
};
//=========================END=========================