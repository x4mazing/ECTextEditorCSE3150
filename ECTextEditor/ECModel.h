
#ifndef ECMODEL_H
#define ECMODEL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class ECModel{ //actual object
public:

    //object constructor and destructor
    ECModel(int maxRowsIN, string filepathIN);
    ~ECModel();

    //callable functions for editor manipulation--------------------------------
    void addPage() { _rowVector.push_back({}); }
    void addRow(string s) { _rowVector[_currPage].push_back(s); }

    //return cursor position
    int getCursorX() { return _cursorX; }
    int getCursorY() { return _cursorY; }

    //returns a page as vector of strings 
    vector<string> getPage() { return _rowVector[_currPage]; }

    //returns the total number of pages
    int getNumPages(){return _rowVector.size();}
    
    //returns number of rows in the page
    int getCurrPageSize(){return _rowVector[_currPage].size();}

    //return the length of the current row
    int getCurrRowLen(){return _rowVector[_currPage][_cursorY].size();}

    //returns the index of the last row in the page
    int getLastRowindex(){return getCurrPageSize() - 1;}

    //modifying functions------------------------------------------
    int enterKey();
    int backspaceKey();
    int characterKey(char key);
    void replaceEvent(string findstring, string replacestring);

    //undo fucntions: separate cpp
    void undoEnter(vector<int> &params);
    void undoBackspace(vector<int> &params);
    void undoChar(vector<int> &params);


    //arrowkey functions: seperate cpp
    void leftKey();
    void rightKey();
    void upKey();
    void downKey();

    //setter functions for outside classes
    void SetCursorX(int x){_cursorX = x;}
    void SetCursorY(int y){_cursorY = y;}
    void SetCurrPage(int x){_currPage = x;}

    //finds the coordinates of the inputted string for highlighting
    vector<vector<int>> findCoordinates(string stringIn);
    
    //returns the parameters cursor x, cursor y, currpage etc for undo/redo
    vector<int>setParams();

    //helper functions for applying and setting undo object paramters
    void applyParams(vector<int> &vector);
    void setUndoParams(vector<int> &vector);

    //shifts all rows down if there is space
    void shiftRowsDown();

    //shifts all rows up if there is space
    void shiftRowsUp();


private:
    //contains all pages and rows
    vector<vector<string>> _rowVector;

    //filepath specifed at runtime
    string _filepath;

    //parameters for the view
    int _cursorX, _cursorY, _currPage, _maxRows;
};

#endif