#ifndef __LINEEDITOR_H__
#define __LINEEDITOR_H__

#include<iostream>
#include<fstream>
#include "DblLinkList.h"
#include "String.h"

using namespace std;
class LineEditor {
private:
	DblLinkList<String>textBuffer;
	int curLineNo;
	DblLinkList<String>textUndoBuffer;
	int CurUndoLineNo;
	ifstream inFile;
	ofstream outFile;
	StatusCode NextLine();
	StatusCode PreviousLine();
	StatusCode GotoLine();
	StatusCode InsertLine();
	StatusCode  ChangeLine();
	StatusCode FindString();
	void PrintString();
	void ReadFile();
	void WriteFile();
	
public:
	LineEditor(String inFName, String outFName);
	void run();
};
#endif

