#include "ECModel.h"

using namespace std;

ECModel :: ECModel(int maxRowsIN, string filepathIN):
_cursorX(0), _cursorY(0), _currPage(0), _maxRows(maxRowsIN), _filepath(filepathIN){
    
    //checking to see if a file name was defined
    if(_filepath.length() > 0){
        addPage();
        ifstream file(_filepath);
        string buffer = "";

        //converting text lines to rowvector
        for(int counter = 0; getline(file, buffer); counter++){
            if(counter == _maxRows - 1){
                counter = 0;
                addPage();
                _currPage++;
            }
            addRow(buffer);
        }
        //reseting doc to first page and if the filepath was empty initialize
        _currPage = 0;
        if(_rowVector[_currPage].size() == 0){
            addRow("");
        }
    }

    //if no filename was provided start with empty document
    else{
        addPage();
        addRow("");
    }
}
ECModel :: ~ECModel(){
    //on destruction of the program write to file
    ofstream file;

    //check to see if the filename was defined
    if(_filepath.length() == 0){
        file.open("NewFile.txt", fstream::out);
    }
    else{
        file.open(_filepath, fstream::out);
    }
    //intialize filestream

    //iterate through all rows and write back to the file.
    for(int i = 0; i < _rowVector.size(); i++){
        for(auto x : _rowVector[i]){
            //write to the file along with newline
            file << x << endl;
        }
    }
    //close the filestream
    file.close();
}

//====================MODIFYING-FUNCTIONS====================
int ECModel :: enterKey(){

    //prepping variables
    string moveString;
    int flag = -1;

    //preps to move the rest of the string to next line if cursor is in the middle of a line
    if(_cursorX < getCurrRowLen()){
        moveString = _rowVector[_currPage][_cursorY].substr(_cursorX, getCurrRowLen() - _cursorX);
        _rowVector[_currPage][_cursorY].erase(_cursorX, getCurrRowLen() - _cursorX);
    }

    //checks to see if the cursor is within the page
    if(_cursorY+1 < _maxRows - 1){

        //insert string to the next row
        auto it = _rowVector[_currPage].begin() + _cursorY + 1;
        _rowVector[_currPage].insert(it, moveString);

        //adjusting the values
        _cursorY++;
        _cursorX = 0;
        flag = 0;
    }

    //checks to see if a new page needs to be created
    else if(_cursorY+1 >= _maxRows - 1){

        //applying the newline
        addPage();
        _currPage++;
        auto it = _rowVector[_currPage].begin();
        _rowVector[_currPage].insert(it, moveString);
        
        //adjust the values
        _cursorY = 0;
        _cursorX = 0;
        flag = 1;
    }

    //check to see if there is page overflow
    if(getCurrPageSize() + 1 > _maxRows){
        //true: shift all page rows down by one to next pages
        shiftRowsDown();

        //add two to the flag variable to signify the use of shift
        flag += 2;
    }

    //if the last page is still empty after shifting operation delete it
    if(_rowVector.back().empty()){
        _rowVector.pop_back();
    }

    return flag;
}

int ECModel :: backspaceKey(){
    //if the cursor is at the very left, on backspace append line to prev line
    if(_cursorX == 0 && _cursorY > 0){
        _cursorX = _rowVector[_currPage][_cursorY - 1].size();

        //append the line to above line 
        _rowVector[_currPage][_cursorY - 1].append(_rowVector[_currPage][_cursorY]);

        //erase the copied line
        auto it = _rowVector[_currPage].begin() + _cursorY;
        _rowVector[_currPage].erase(it);

        //adjust cursor and line positions
        _cursorY--;
        if(getNumPages() > 1){
            shiftRowsUp();
        }
        return 0;
    }
    //if the backspace occurs at the beginning of a page
    else if(_currPage > 0 && _cursorY == 0 && _cursorX == 0){

        //create a temp string for row and cut
        string tempstring = _rowVector[_currPage].front();
        _rowVector[_currPage].erase(_rowVector[_currPage].begin());
        shiftRowsUp();
        //adjust the cursor
        --_currPage;
        _cursorY = getCurrPageSize() - 1 ;
        _cursorX = getCurrRowLen();

        //place the temp string at the end of the previous page
        _rowVector[_currPage].back() += tempstring;

        //if there is an empty page from shifting remove it
        if(_rowVector.back().empty()){
            _rowVector.pop_back();
        }
    
        return 1;
    }
    //if the backspace occurs in the middle of a line remove from the middle of the string
    else if(_cursorX > 0 && _cursorY >= 0){
        //store the character being removed and then remove it
        char tempchar = _rowVector[_currPage][_cursorY][_cursorX - 1];
        _rowVector[_currPage][_cursorY].erase(_cursorX - 1, 1);

        //adjust cursor
        _cursorX --;

        //send it back as a flag for undo/redo
        return tempchar;
    }
    return -1;
}
int ECModel :: characterKey(char key){
    //casting a character to a string
    string tempstring;
    tempstring += key;
    
    //insert character at the current page and cursor location
    _rowVector[_currPage][_cursorY].insert(_cursorX, tempstring);
    _cursorX++;
    return key;
}

void ECModel :: replaceEvent(string findstring, string replacestring){

    //do nothing if the replace string is empty
    if(replacestring.size() == 0){
        return;
    }
    //creating the placeholder string to avoid infinite loop
    string redacting="";
    for(auto x : replacestring){
        redacting += "#";
    }
    //iterate all of the rows in the page
    for(int i = 0; i < _rowVector[_currPage].size(); i++){
        string currentrow = _rowVector[_currPage][i]; 
        string editrow = _rowVector[_currPage][i]; 
        
        //iterating each row and eliminating any occurences in a edit row and reflect changes
        while(editrow.find(findstring) != string::npos){
            int startpos = editrow.find(findstring);
            int length = findstring.size();
            currentrow.replace(startpos, length, replacestring);
            editrow.replace(startpos, length, redacting);
        }
        
        //apply the copy to the actual document
        _rowVector[_currPage][i] = currentrow;
    }
}
//==========================END==========================

//=====================MISC OPERATIONS===================

//finds the coordinates of the inputted string for highlighting
vector<vector<int>> ECModel::findCoordinates(string stringIn){
    //data struct
    vector<vector<int>> stringCoord;

    //temp variables
    int location = 0;

    //iterate all of the rows
    for(int i = 0; i < _rowVector[_currPage].size(); i++){
        string stringCopy(_rowVector[_currPage][i]);

        //find and remove if found for each occurence
        while(stringCopy.find(stringIn) != string::npos){
            location = stringCopy.find(stringIn);

            //store location found
            int tempend = location + stringIn.length() - 1;
            stringCoord.push_back({i, location, tempend});

            //iterate length of string in and replace starting at location
            for(int i = 0; i < stringIn.size(); i++){
                stringCopy[location + i] = '#';
            }
        }
    }
    return stringCoord;
}

void ECModel :: shiftRowsDown(){
    //saving the current page before shifting operation
    int bookmark = _currPage;

    //while there is still overflow
    while(getCurrPageSize() + 1 > _maxRows){

        //make a copy and pop the back of the page
        string stringcopy = _rowVector[_currPage].back();
        _rowVector[_currPage].pop_back();

        //check to see if the maximum number of pages reached, add page if true
        if(_currPage == getNumPages() - 1){
            addPage();
        }

        //insert string copy to the beginning of the page
        auto iter = _rowVector[_currPage + 1].begin();
        _rowVector[++_currPage].insert(iter, stringcopy);
    }
    //restore page location before shifting operation
    _currPage = bookmark;
}

void ECModel :: shiftRowsUp(){

    //if there is more pages after the event, shift pages 
    
    int bookmark = _currPage;

    //while there is still overflow
    while(getCurrPageSize() < _maxRows && _currPage < getNumPages() - 1){
        
        //make a copy and erase the front of the next page
        string stringcopy = _rowVector[_currPage + 1].front();
        auto iter1 = _rowVector[_currPage + 1].begin();
        _rowVector[_currPage + 1].erase(iter1);

        if(_rowVector.back().empty()){
            _rowVector.pop_back();
        }

        //insert string copy to the end of the page
        _rowVector[_currPage].push_back(stringcopy);
        _currPage++;
    }

    //there is an issue when there is only one line left at the end
    _currPage = bookmark;
}
vector<int> ECModel :: setParams(){
    //setting the parameters according to the key below
    //params[0] = page, params[1] = cursorX, params[2] = cursorY, params[3] = flag, param[4] undone flag
    vector<int> tempvect{_currPage, _cursorX, _cursorY};
    return tempvect;
}
void ECModel :: applyParams(vector<int> &params){
    //unpacking variables
    int page = params[0], paramx = params[1], paramy = params[2], flag = params[3];
    
    //setting parameters to undo parameters
    _currPage = page;
    _cursorX = paramx;
    _cursorY = paramy;
}
void ECModel :: setUndoParams(vector<int> &params){
    //reset history parameters to new parameters and trip undone flag
    params[0] = _currPage;
    params[1] = _cursorX;
    params[2] = _cursorY;
    params.back() = 1;
}
//=============================END=============================