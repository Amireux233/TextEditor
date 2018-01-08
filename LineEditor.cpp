#include "LineEditor.h"
LineEditor::LineEditor( String inFName, String outFName) {
	inFile.open(inFName.CStr(), ios::in);
	outFile.open(outFName.CStr(), ios::out);
	curLineNo = 0;
	CurUndoLineNo = 0;
}
StatusCode LineEditor::NextLine() {
	if (curLineNo + 1 != textBuffer.Length()) {
		curLineNo++;
		return SUCCESS;
	}
	else {
		return OVER_FLOW;
	}
}
StatusCode LineEditor::PreviousLine() {
	if (curLineNo - 1 != 0) {
		curLineNo--;
		return SUCCESS;
	}
	else {
		return OVER_FLOW;
	}
}
StatusCode LineEditor::GotoLine() {
	cout << "请输入行号：";
	int temp;
	cin >> temp;
	if (temp > 0 && temp <= textBuffer.Length()) {
		curLineNo = temp;
		return SUCCESS;
	}
	else {
		return FAIL;
	}
}
StatusCode LineEditor::InsertLine() {
	cout << "请输入行号";
	int tempLine;
	cin >> tempLine;
	if (tempLine > 0 && tempLine <= textBuffer.Length() + 1) {
		cout << "请输入要插入的字符串";
		while (cin.get() != '\n');
		String text = Read(cin);
		textBuffer.Insert(tempLine, text);
		return SUCCESS;
	}
	else {
		return FAIL;
	}
	cout << '\n';
}

StatusCode LineEditor::ChangeLine() {
	char answer;  //用户回答字符
	bool initialResponse = true;   //初始回答

	do {  //循环直到用户输入恰当的回答为止
		if (initialResponse) {
			cout << "替换当前行c(urrent)或替换所有行a(ll)：";
		}
		else {
			cout << "用c或a回答";
		}

		cin >> answer;
		while (cin.get()!= '\n');
		answer = tolower(answer);
		initialResponse = false;
	} while (answer != 'c'&&answer != 'a');
	cout << "输入要被替换的指定文本串：";
	String strOld = Read(cin);
	cout << "请输入新文本串：";
	String strNew = Read(cin);
	int count = 0;
	for (int row = 1; row <= textBuffer.Length(); row++) {
		if (answer == 'c'&&row != curLineNo) {
			continue;
		}

		String strRow;
		textBuffer.GetElem(row, strRow);
		int lenRow = strRow.Length();
		int lenOld = strOld.Length();
		int index = Index(strRow, strOld,0);
		String newLine;
		String tmpstr;
		if (index == -1) {
			break;
		}
		Copy(newLine, strRow, index);
		while (index != -1) {	
			Concat(newLine, strNew);
			String substr = SubString(strRow, index + lenOld, lenRow - index - lenOld);
			Concat(newLine, substr);
			textBuffer.SetElem(row, newLine);
			count++;
			tmpstr = newLine;
			index = Index(tmpstr, strOld);
			if (index == -1)
				break;
			Copy(newLine, tmpstr, index);
		}
	}
	if (count == 0) {
		return FAIL;
	}
	else {
		return SUCCESS;
	}
}

void LineEditor::PrintString() {
	for (int i = 1; i <= textBuffer.Length(); i++) {
		String temp;
		textBuffer.GetElem(i, temp);
		for (int i = 0; i < temp.Length(); i++) {
			cout << temp[i];
		}
		cout << '\n';
	}

}

void LineEditor::ReadFile() {
	String temp;
	while (!inFile.fail()) {
		temp=Read(inFile);
		if (temp.Length() != 0) {
			textBuffer.Insert(++curLineNo, temp);
			cout << temp.CStr() << endl;
		}	
	}
	inFile.close();
}

void LineEditor::WriteFile() {
	if (!outFile.fail()) {
		for (int i = 1; i <= textBuffer.Length(); i++) {
			String temp;
			textBuffer.GetElem(i, temp);
			for (int i = 0; i < temp.Length(); i++) {
				outFile << temp[i];
			}
			outFile << '\n';
		}
	}
	outFile.close();
}

StatusCode LineEditor::FindString() {
	char answer;
	bool initialResponse = true;

	do {
		if (initialResponse) {
			cout << "从第一行开始f(irst)或从当前行开始c(urrent)：";
		}
		else {
			cout << "用f或c回答：";
		}

		cin >> answer;
		answer = tolower(answer);
		initialResponse = false;
	} while (answer != 'f'&&answer != 'c');
	if (answer == 'f')curLineNo = 1;

	int index;
	cout << "输入被查找的文本串：";
	while (cin.get() != '\n');
	String searchString = Read(cin);
	String curLine;
	int count = 0;
	textBuffer.GetElem(curLineNo, curLine);
	while ((index = Index(curLine, searchString)) != -1) {
		cout << curLineNo << "：" << curLine.CStr() << endl;
		count++;
		if (curLineNo < textBuffer.Length()) {
			curLineNo++;
			textBuffer.GetElem(curLineNo, curLine);
		}
		else {
			break;
		}
	}

	if (count == 0) {
		return FAIL;
	}
	else {
		return SUCCESS;
	}
	cout << endl;
}


void LineEditor::run() {
	char userCommand;

	do {
		String tempString;
		String curLine;
		cout << "??";
		cin >> userCommand;
		userCommand = tolower(userCommand);

		if (userCommand != 'u'&&userCommand != 'h'&&userCommand != '?'&&userCommand != 'v') {
			textUndoBuffer = textBuffer;
			CurUndoLineNo = curLineNo;
		}
		switch (userCommand)
		{
		case'b':
			if (textBuffer.Empty()) {
				cout << "警告：文本缓存空" << endl;
			}
			else {
				curLineNo = 1;
			}
			break;
		case'c':
			if (textBuffer.Empty()) {
				cout << "警告：文本缓存空" << endl;
			}
			else {
				if (ChangeLine() != SUCCESS) {
					cout << "未找到指定字符串";
				}
			}
			break;
		case'd':
			if (textBuffer.Delete(curLineNo, tempString) != SUCCESS) {
				cout << "错误：删除失败" << endl;
			}
			break;
		case'e':
			if (textBuffer.Empty()) {
				cout << "警告：文本缓存空" << endl;
			}
			else {
				curLineNo = textBuffer.Length();
			}
			break;
		case'f':
			if (textBuffer.Empty()) {
				cout << "警告：文本缓存空" << endl;
			}
			else {
				if (FindString() != SUCCESS) {
					cout << "未找到指定字符串";
				}
			}
			break;
		case'g':
			if (GotoLine() != SUCCESS) {
				cout << "警告：没有那样的行" << endl;
			}
			break;
		case'?':
		case'h':
			cout << "有效命令：b(egin)  c(hange)  d(elete)  e(nd）" << endl
				<< "f(ind)  g(oto)  h(elp)  i(nsert)  n(ext)  p(rior) " << endl
				<< "q(uit)  r(ead)  u(ndo)  v(iew)  w(rite)" << endl;
			break;
		case'i':
			if (InsertLine() != SUCCESS)
				cout << "错误：插入行错误" << endl;
			break;
		case'n':
			if (NextLine() != SUCCESS)
				cout << "警告：当前行已经是最后一行" << endl;
			break;
		case'p':
			if (PreviousLine() != SUCCESS)
				cout << "警告：当前行已经是第一行" << endl;
			break;
		case'q':
			break;
		case'r':
			ReadFile();
			break;
		case'u':
			Swap(textUndoBuffer, textBuffer);
			Swap(CurUndoLineNo, curLineNo);
			break;
		case'w':
			if (textBuffer.Empty())
				cout << "警告：文本缓存空" << endl;
			else
				WriteFile();
			break;
		case'v':
			if (textBuffer.Empty())
				cout << "警告：文本缓存空" << endl;
			else
				PrintString();
			break;
		}
	} while (userCommand != 'q');
}