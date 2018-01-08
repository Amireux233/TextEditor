// Text Editor2.0.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "LineEditor.h"


int main()
{
	cout << "please input inputfile name(eg. file_in.txt)";
	String inFileName = Read(cin);
	cout << "please iuput outputfile name(eg. file_out.txt)";
	String outFileName = Read(cin);
	LineEditor a = LineEditor(inFileName, outFileName);
	cout << "File buffer is empty,please use command r to read file to buffer" << endl;
	a.run();
}


