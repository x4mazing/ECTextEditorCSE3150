
#ifndef ECVIEW_H
#define ECVIEW_H
#include "ECTextViewImp.h"
#include "ECController.h"
// #include "ECCommand.h"
using namespace std;

class ECView: public ECObserver{
public:
    ECView(ECTextViewImp* textViewImpIn, ECController * controllerIn): _textviewimp(textViewImpIn), _controller(controllerIn) {}
    ~ECView(){}

    //updates the view
    void Update();

    //arrowkey functions calling controller
    void callRightArrow();
    void callLeftArrow();
    void callDownArrow();
    void callUpArrow();

    //Document modifying functions calling controller
    void callEnter();
    void callBackspace();
    void callCharKey(char Key);
    void callReplace();
    void callUndo();
    void callRedo();


    //general functions
    void refreshPages();
    int getMode(){return _controller->getMode();} //returning mode
    void setMode(int x){_controller->setMode(x);} //setting mode
    void modifyStatusRow(string arg1, string arg2, bool arg3); //modify status row with args

    //find mode functions
    void enterFindMode();   //enters findmode
    void highlightSelection(TEXT_COLOR color);  //highlights occurence specified color
    void exitFindMode();    //exits findmode
    void findAddChar(int x);    //adds characters to the findmode statusbar
    void findBackspaceHandler();   //manages backspace for findmode statusbar
    void setFindKey(string in){_findkey = in;}  //sets the findkey
    void setConfirmedFindKey(string in){_confFindKey = in;} //sets the _conffindkey as findkey on enter
    string getFindKey(){return _findkey;} //returns the findkey

    //replace mode functions
    void enterReplaceMode();    //enters replace mode
    void exitReplaceMode();     //exits repalce mode
    void replaceAddChar(int x); //adds characters to replace statusbar
    void replaceBackspaceHandler(); //handles backspace in replace statusbar
    void setReplaceKey(string in){_replacekey = in;} //set replacekey
    string getReplaceKey(){return _replacekey;} //returns replacekey

private:
    ECTextViewImp * _textviewimp;
    ECController * _controller;
    string _findkey, _replacekey, _confFindKey;
    vector<vector<int>> occur;
};

#endif