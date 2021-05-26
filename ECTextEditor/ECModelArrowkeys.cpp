#include "ECModel.h"
using namespace std;
void ECModel :: leftKey(){

    //if bounding the cursor left
    if(_cursorX - 1 >= 0 ){
        _cursorX--;
    }
    //changing pages on left key press
    else if(_cursorY == 0 && _cursorX == 0 && _currPage != 0){
        _currPage--;
        _cursorY = getCurrPageSize() - 1;
        _cursorX = _rowVector[_currPage][_cursorY].size();
    }
    //wrapping the cursor around to previous row
    else if(_cursorX - 1 <= -1  && _cursorY >= 1){
        _cursorY --;
        _cursorX = getCurrRowLen();
    }

}
void ECModel :: rightKey(){

    //bounding cursor movement right
    if(_cursorX + 1 <= getCurrRowLen()){
        _cursorX++;
    }
    //changing pages on right key press
    else if(_cursorY == getCurrPageSize()-1 && _cursorX + 1 > getCurrRowLen() 
    && _currPage < getNumPages() - 1){
        if(getNumPages() > 1 && _currPage < getNumPages() - 1){
            _currPage++;
            _cursorX = 0;
            _cursorY = 0;
        }
    }
    //moving the cursor down to the next row on end
    else if(_cursorX == getCurrRowLen() && _cursorY + 1 < getCurrPageSize()){
        if(_cursorY < getCurrPageSize()-1){
            _cursorY++;
            _cursorX = 0;   
        }
    }
}
void ECModel :: upKey(){
    //check if cursor is at the end of page
    if(_cursorY - 1 >= 0){

        //check to see if the cursor is within the row
        if(_cursorX > _rowVector[_currPage][_cursorY-1].size()){
            _cursorX = _rowVector[_currPage][_cursorY-1].size();
        }
        _cursorY--;
    }

    //else if the cursor is at the beginning and checking for other pages
    else if(_cursorY - 1 < 0 && _currPage - 1 >= 0){
        _currPage --;

        _cursorY = getCurrPageSize()-1;
        _cursorX = getCurrRowLen();
    }
}
void ECModel :: downKey(){
    //check to see if the cursor is in the page still 
    if(_cursorY + 1 <= getCurrPageSize() - 1 && _cursorY + 1 < _maxRows - 1){
        //if current row is larger than next row, set the cursor to end of next row
        if(_cursorX > _rowVector[_currPage][_cursorY + 1].size()){
            _cursorX = _rowVector[_currPage][_cursorY + 1].size();
        }
        _cursorY = _cursorY + 1;
    }
    //checking the see if cursor is at last row to display new page
    else if(_cursorY + 1 > getCurrPageSize() - 1 && _currPage < _rowVector.size()-1){
        _currPage++;
        _cursorY = 0;
        _cursorX = 0;
    }
}
