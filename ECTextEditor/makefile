editor: ECTextViewImp.o ECModel.o ECCommand.o ECView.o ECController.o ECEditorInitDemo.o ECModelUndo.o ECModelArrowKeys.o
	g++ ECTextViewImp.o ECModel.o ECCommand.o ECView.o ECController.o ECEditorInitDemo.o ECModelUndo.o ECModelArrowKeys.o -o editor

ECTextViewImp.o: ECTextViewImp.cpp
	g++ -c ECTextViewImp.cpp

ECModel.o: ECModel.cpp
	g++ -c ECModel.cpp

ECCommand.o: ECCommand.cpp
	g++ -c ECCommand.cpp
	
ECController.o: ECController.cpp
	g++ -c ECController.cpp

ECView.o: ECView.cpp
	g++ -c ECView.cpp

ECEditorInitDemo.o: ECEditorInitDemo.cpp
	g++ -c ECEditorInitDemo.cpp
	
ECModelUndo.o: ECModelUndo.cpp
	g++ -c ECModelUndo.cpp

ECModelArrowKeys.o: ECModelArrowKeys.cpp
	g++ -c ECModelArrowKeys.cpp

clean:
	$(RM) *.o editor