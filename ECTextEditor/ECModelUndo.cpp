#include "ECModel.h"
using namespace std;

void ECModel :: undoEnter(vector<int> &params){
    int flag = params[3];
    //apply undone parameters
    applyParams(params);

    //call backspace to undo any enter
    backspaceKey();

    //if flag was tripped call shift
    if(flag == 2 || flag== 3){
        shiftRowsUp();
    }
    //set the params to current parameters
    setUndoParams(params);
}
void ECModel :: undoChar(vector<int> &params){

    //apply undone parameters 
    applyParams(params);

    //call backspace at character addition event
    backspaceKey();

    //set the params to current parameters
    setUndoParams(params);
}
void ECModel :: undoBackspace(vector<int> &params){
    int page = params[0], paramx = params[1], paramy = params[2], flag = params[3];
    //apply undone parameters 
    applyParams(params);

    //if the backspace took place at the beginning of a line 
    if(flag == 0 || flag == 1){
        //call enter function
        enterKey();
    }
    //if the backspace removed a character
    else if(flag != 0){
        string replacestring(1, static_cast<char>(flag));
        _rowVector[page][paramy].insert(paramx, replacestring);
        _cursorX = paramx + 1;
        _cursorY = paramy;
        _currPage = page;
    }

    //set the params to current parameters
    setUndoParams(params);
}
