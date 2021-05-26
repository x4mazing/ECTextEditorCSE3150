#include "ECView.h"

    //this function will handle any button presses.
    void ECView :: Update(){
        int lastKeyPressed = _textviewimp->GetPressedKey();

        //inital state: normal editor
        if(getMode() == 0){

            //calls key functions in view depending on last pressed key
            if(lastKeyPressed == ENTER){
                callEnter();
            }
            else if(lastKeyPressed == BACKSPACE){
                callBackspace();
            }
            else if(lastKeyPressed == CTRL_Z){
                callUndo();
            }
            else if(lastKeyPressed == CTRL_Y){
                callRedo();
            }
            else if(lastKeyPressed == CTRL_F){
                enterFindMode();
            }
            else if(lastKeyPressed == ARROW_RIGHT){
                callRightArrow();
            }
            else if(lastKeyPressed == ARROW_LEFT){
                callLeftArrow();
            }
            else if(lastKeyPressed == ARROW_DOWN){
                callDownArrow();
            }
            else if(lastKeyPressed == ARROW_UP){
                callUpArrow();
            }
            //character key case
            else if(lastKeyPressed > 31 && lastKeyPressed < 127){
                callCharKey(lastKeyPressed);
            }
        }

        //if ctrl-f is pressed enter find mode.
        else if(getMode() == 1){
            if(lastKeyPressed == ESC){
                exitFindMode();
            }
            else if(lastKeyPressed == BACKSPACE){
                findBackspaceHandler();
            }
            else if(lastKeyPressed == ENTER){
                //this key is necessary as the regular find key updates w/o enter
                highlightSelection(TEXT_COLOR_WHITE);
                setConfirmedFindKey(getFindKey());
                highlightSelection(TEXT_COLOR_RED);
            }
            else if(lastKeyPressed == CTRL_Z){
                highlightSelection(TEXT_COLOR_WHITE);
                callUndo();
            }
            else if(lastKeyPressed == CTRL_Y){
                highlightSelection(TEXT_COLOR_WHITE);
                callRedo();
            }
            //ENTER REPLACEMENT MODE IF '/'
            else if(lastKeyPressed == 47){
                enterReplaceMode();
            }
            //if alpha-numeric is entered
            else if(lastKeyPressed > 31 && lastKeyPressed < 127){
                //add char into the find portion of the status bar
                findAddChar(lastKeyPressed);
            }
        }

        //enter replacement mode if '/' is entered while in find mode
        else if(getMode() == 2){
            if(lastKeyPressed == ESC){
                exitReplaceMode();
            }
            else if(lastKeyPressed == BACKSPACE){
                replaceBackspaceHandler();
            }
            else if(lastKeyPressed == ENTER){
                callReplace();
            }
            else if(lastKeyPressed == CTRL_Z){
                callUndo();
            }
            else if(lastKeyPressed == CTRL_Y){
                callRedo();
            }
            //if alpha-numeric is entered
            else if(lastKeyPressed > 31 && lastKeyPressed < 127){
                //add char into the replace portion of the status bar
                replaceAddChar(lastKeyPressed);
            }
        }
        //refreshing the pages: setting the cursor positions and page
        refreshPages();
    }

//GENERAL VIEW FUNCTIONS

//refreshes the page view
void ECView :: refreshPages(){
    _textviewimp->InitRows();
    _textviewimp->SetCursorX(_controller->getModel()->getCursorX());
    _textviewimp->SetCursorY(_controller->getModel()->getCursorY());

    for(string s : _controller->getModel()->getPage()){
        _textviewimp->AddRow(s);
    }
}

//helper function to maintain the status row 
void ECView :: modifyStatusRow(string arg1, string arg2, bool arg3){
    _textviewimp->ClearStatusRows();
    _textviewimp->AddStatusRow(arg1, arg2, arg3);
}

//================TEXT EDITOR FUNCTIONS================
void ECView :: callEnter(){
    //call controller's action
    _controller->actionEnter();
}
void ECView :: callBackspace(){
    //call controller's action
    _controller->actionBackspace();
}
void ECView :: callRightArrow(){
    //call controller's action
    _controller->actionRightArrow();
}
void ECView :: callLeftArrow(){
    //call controller's action
    _controller->actionLeftArrow();
}
void ECView :: callDownArrow(){
    //call controller's action
    _controller->actionDownArrow();
}
void ECView :: callUpArrow(){
    //call controller's action
    _controller->actionUpArrow();
}
void ECView :: callCharKey(char key){
    //call controller's action
    _controller->actionCharKey(key);
}
void ECView :: callUndo(){
    //call controller's action
    _controller->actionUndo();
}
void ECView :: callRedo(){
    //call controller's action
    _controller->actionRedo();
}
//============================END============================


//====================FIND MODE FUNCTIONS====================
void ECView :: highlightSelection(TEXT_COLOR color){
    //takes in a color and then highlights the current occurences of find/replace
    if(_confFindKey.size() > 0){
        occur = _controller->getModel()->findCoordinates(_confFindKey);
        for(auto x: occur){
            _textviewimp->SetColor(x[0], x[1], x[2], color);
        }
    }
}
void ECView :: enterFindMode(){
    //modifies the view and status bar to find mode
    modifyStatusRow("Find: " , "", true);
    _controller->setMode(1);
}
void ECView :: exitFindMode(){
    //exits find mode by changing all text back to white and modifying status row
    highlightSelection(TEXT_COLOR_WHITE);
    modifyStatusRow("Editor: " , " ", true);
    setFindKey("");
    setMode(0);
}
void ECView :: findAddChar(int x){
    //make temporary string
    string input;
    input += x;

    //update current findkey with added char
    setFindKey(getFindKey() += input);
    modifyStatusRow("Find: " + getFindKey(),"", true);
}
void ECView :: findBackspaceHandler(){
    
    //update findkey and modify status row
    string tempstring = getFindKey();
    if(tempstring.length() > 0) tempstring.pop_back(); 
    setFindKey(tempstring);
    modifyStatusRow("Find: " + getFindKey(),"", true);
}
//==========================END=========================


//================REPLACE MODE FUNCTIONS================
void ECView :: enterReplaceMode(){
    //modify the status row and set the mode to 2 for replace mode
    modifyStatusRow("Replace: " , " ", true);
    setMode(2);
}
void ECView :: exitReplaceMode(){
    //modify the status row and set the mode to 1 for find mode
    modifyStatusRow("Find: " + getFindKey(), " ", true);
    setReplaceKey("");
    setMode(1);
}
void ECView :: replaceAddChar(int x){
    //make temporary string
    string input;
    input += x;

    //update current replacekey with new char
    setReplaceKey(getReplaceKey() += input);
    modifyStatusRow("Replace: " + getReplaceKey(), "" , true);
}
void ECView :: replaceBackspaceHandler(){
    
    //update current replacekey
    string tempstring = getReplaceKey();
    if(tempstring.length() > 0) tempstring.pop_back(); 
    setReplaceKey(tempstring);
    modifyStatusRow("Replace: " + getReplaceKey(),"", true);
}
void ECView :: callReplace(){
    //change color back to white before performing replace
    highlightSelection(TEXT_COLOR_WHITE);

    //call replace action
    _controller -> actionReplace(_confFindKey, _replacekey);

    //change what key to search for in highlighting after replace
    _confFindKey = _replacekey;
    _findkey = _confFindKey;
    _replacekey = "";

    //highlight replacement
    highlightSelection(TEXT_COLOR_GREEN);

    //go back to find mode by setting mode and status row
    _controller->setMode(1);
    modifyStatusRow("Find: " + _confFindKey, "", true);
}