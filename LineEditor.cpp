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
	cout << "�������кţ�";
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
	cout << "�������к�";
	int tempLine;
	cin >> tempLine;
	if (tempLine > 0 && tempLine <= textBuffer.Length() + 1) {
		cout << "������Ҫ������ַ���";
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
	char answer;  //�û��ش��ַ�
	bool initialResponse = true;   //��ʼ�ش�

	do {  //ѭ��ֱ���û�����ǡ���Ļش�Ϊֹ
		if (initialResponse) {
			cout << "�滻��ǰ��c(urrent)���滻������a(ll)��";
		}
		else {
			cout << "��c��a�ش�";
		}

		cin >> answer;
		while (cin.get()!= '\n');
		answer = tolower(answer);
		initialResponse = false;
	} while (answer != 'c'&&answer != 'a');
	cout << "����Ҫ���滻��ָ���ı�����";
	String strOld = Read(cin);
	cout << "���������ı�����";
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
			cout << "�ӵ�һ�п�ʼf(irst)��ӵ�ǰ�п�ʼc(urrent)��";
		}
		else {
			cout << "��f��c�ش�";
		}

		cin >> answer;
		answer = tolower(answer);
		initialResponse = false;
	} while (answer != 'f'&&answer != 'c');
	if (answer == 'f')curLineNo = 1;

	int index;
	cout << "���뱻���ҵ��ı�����";
	while (cin.get() != '\n');
	String searchString = Read(cin);
	String curLine;
	int count = 0;
	textBuffer.GetElem(curLineNo, curLine);
	while ((index = Index(curLine, searchString)) != -1) {
		cout << curLineNo << "��" << curLine.CStr() << endl;
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
				cout << "���棺�ı������" << endl;
			}
			else {
				curLineNo = 1;
			}
			break;
		case'c':
			if (textBuffer.Empty()) {
				cout << "���棺�ı������" << endl;
			}
			else {
				if (ChangeLine() != SUCCESS) {
					cout << "δ�ҵ�ָ���ַ���";
				}
			}
			break;
		case'd':
			if (textBuffer.Delete(curLineNo, tempString) != SUCCESS) {
				cout << "����ɾ��ʧ��" << endl;
			}
			break;
		case'e':
			if (textBuffer.Empty()) {
				cout << "���棺�ı������" << endl;
			}
			else {
				curLineNo = textBuffer.Length();
			}
			break;
		case'f':
			if (textBuffer.Empty()) {
				cout << "���棺�ı������" << endl;
			}
			else {
				if (FindString() != SUCCESS) {
					cout << "δ�ҵ�ָ���ַ���";
				}
			}
			break;
		case'g':
			if (GotoLine() != SUCCESS) {
				cout << "���棺û����������" << endl;
			}
			break;
		case'?':
		case'h':
			cout << "��Ч���b(egin)  c(hange)  d(elete)  e(nd��" << endl
				<< "f(ind)  g(oto)  h(elp)  i(nsert)  n(ext)  p(rior) " << endl
				<< "q(uit)  r(ead)  u(ndo)  v(iew)  w(rite)" << endl;
			break;
		case'i':
			if (InsertLine() != SUCCESS)
				cout << "���󣺲����д���" << endl;
			break;
		case'n':
			if (NextLine() != SUCCESS)
				cout << "���棺��ǰ���Ѿ������һ��" << endl;
			break;
		case'p':
			if (PreviousLine() != SUCCESS)
				cout << "���棺��ǰ���Ѿ��ǵ�һ��" << endl;
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
				cout << "���棺�ı������" << endl;
			else
				WriteFile();
			break;
		case'v':
			if (textBuffer.Empty())
				cout << "���棺�ı������" << endl;
			else
				PrintString();
			break;
		}
	} while (userCommand != 'q');
}