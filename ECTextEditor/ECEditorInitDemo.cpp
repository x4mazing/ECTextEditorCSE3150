#include "ECView.h"
using namespace std;

int main(int argc, char * argv[]){

    string filepath = "";
    if(argc > 1) filepath = argv[argc - 1];

    //construct all objects
    ECTextViewImp windowImp;
    ECModel * windowModel = new ECModel(windowImp.GetRowNumInView(), filepath);
    ECController * windowController = new ECController(windowModel);
    ECView * observer = new ECView(&windowImp, windowController);

    //attach the observer to the textviewimp
    windowImp.Attach(observer);

    //set the status row before show
    windowImp.AddStatusRow("Editor:" , "", true);

    //update for loading file I/O
    observer->Update();
    windowImp.Show();
    
    //delete the model object to invoke writing
    delete windowModel, windowImp, windowController, observer;
    return 0;
}