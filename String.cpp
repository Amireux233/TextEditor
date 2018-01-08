#include "String.h"
// ���༰��ز�����ʵ�ֲ���
String::String()
//  �����������ʼ���� 
{
	length = 0;									// ������Ϊ0
	strVal = NULL;								// �մ�
}

String::~String()
// ������������ٴ����ͷŴ���ռ�ÿռ�
{
	delete[]strVal;							// �ͷŴ�strVal
}

String::String(const String &copy)
// ����������ɴ�copy�����´��������ƹ��캯��
{
	length = strlen(copy.CStr());				// ����
	strVal = new char[length + 1];				// ����洢�ռ�
	strcpy(strVal, copy.CStr());				// ���ƴ�ֵ
}

String::String(const char *copy)
// �����������C���ת�������´�����ת�����캯��
{
	length = strlen(copy);						// ����
	strVal = new char[length + 1];				// ����洢�ռ� 
	strcpy(strVal, copy);						// ���ƴ�ֵ
}

String::String(LinkList<char> &copy)
// ��������������Ա�ת�������´�����ת�����캯��
{
	length = copy.Length();						// ����
	strVal = new char[length + 1];				// ����洢�ռ� 
	for (int i = 0; i < length; i++)
	{	// ���ƴ�ֵ
		copy.GetElem(i + 1, strVal[i]);
	}
	strVal[length] = '\0';						// ��ֵ��'\0'����	
}

int String::Length() const
// ������������ش�����			 
{
	return length;
}

bool String::Empty() const
// ��������������Ϊ�գ�����true�����򷵻�false
{
	return length == 0;
}

String &String::operator =(const String &copy)
// ������������ظ�ֵ�����
{
	if (&copy != this)
	{
		delete[]strVal;						// �ͷ�ԭ���洢�ռ�
		length = strlen(copy.CStr());			// ����
		strVal = new char[length + 1];			// ����洢�ռ� 
		strcpy(strVal, copy.CStr());			// ���ƴ�ֵ
	}
	return *this;
}

const char *String::CStr() const
// �������������ת����C���
{
	return (const char *)strVal;				// ��ֵ����ת��
}

char &String::operator [](int pos) const
// ��������������±������
{
	return strVal[pos];
}

void Concat(String &addTo, const String &addOn)
// �������������addOn���ӵ�addTo���ĺ���
{
	const char *cFirst = addTo.CStr();			// ָ���һ����
	const char *cSecond = addOn.CStr();			// ָ��ڶ�����
	char *copy = new char[strlen(cFirst) + strlen(cSecond) + 1];// ����洢�ռ�
	strcpy(copy, cFirst);						// ���Ƶ�һ����
	strcat(copy, cSecond);						// ���ӵڶ�����
	addTo = copy;								// ����ֵ
	delete[]copy;								// �ͷ�copy
}

String Read(istream &input)
// ��������������������봮
{
	LinkList<char> temp;						// ��ʱ���Ա�
	int size = 0;								// ��ʼ���Ա���
	char c;										// ��ʱ�ַ�
	while ((c = input.peek()) != EOF &&			// peek()����������ȡһ���ַ�
												// ������ָ�벻��
		(c = input.get()) != '\n')				// get()����������ȡһ���ַ�
												// ������ָ��ָ����һ�ַ�
	{	// ��������ַ�׷�����Ա���
		temp.Insert(++size, c);
	}
	String answer(temp);						// ���촮
	return answer;								// ���ش�
}

String Read(istream &input, char &terminalChar)
// ��������������������봮������terminalChar���ش������ַ�
{
	LinkList<char> temp;						// ��ʱ���Ա�
	int size = 0;								// ��ʼ���Ա���
	char c;										// ��ʱ�ַ�
	while ((c = input.peek()) != EOF &&			// peek()����������ȡһ���ַ�
												// ������ָ�벻��
		(c = input.get()) != '\n')				// get()����������ȡһ���ַ�
												// ������ָ��ָ����һ�ַ�
	{	// ��������ַ�׷�����Ա���
		temp.Insert(++size, c);
	}
	terminalChar = c;	// ��terminalChar���ش������ַ�
	String answer(temp);						// ���촮
	return answer;								// ���ش�
}

void Write(const String &s)
// ��������������
{
	cout << s.CStr() << endl;					// �����ֵ
}

void Copy(String &copy, const String &original)
// �������������original���Ƶ���copy
{
	const char *cOriginal = original.CStr();// ��ʼ��
	char *cCopy = new char[strlen(cOriginal) + 1];// ����洢�ռ�
	strcpy(cCopy, cOriginal);					// ���ƴ�
	copy = cCopy;								// ����ֵ
	delete[]cCopy;								// �ͷŴ�cCopy
}

void Copy(String &copy, const String &original, int n)
// �������������original����n���ַ�����copy 
{
	const char *cOriginal = original.CStr();// ��ʼ��
	int len = (int)strlen(cOriginal) < n ? (int)strlen(cOriginal) : n;//Ŀ�괮��
	char *cCopy = new char[len + 1];			// ����洢�ռ�
	strncpy(cCopy, cOriginal, n);				// ���ƴ�
	cCopy[len] = '\0';							// ��ֵ��'\0'����
	copy = cCopy;								// ����ֵ
	delete[]cCopy;								// �ͷŴ�cCopy
}

int Index(const String &target, const String &pattern, int pos)
// ������������ƥ��ɹ�������ģʽ��pattern��һ����Ŀ�괮target�дӵ�pos
//	���ַ���ʼ���ֵ�λ��, ���򷵻�-1
{
	const char *cTarget = target.CStr();		// Ŀ�괮
	const char *cPattern = pattern.CStr();		// ģʽ��
	const char *ptr = strstr(cTarget + pos, cPattern);	// ģʽƥ��
	if (ptr == NULL)
	{	// ƥ��ʧ��	
		return -1;
	}
	else
	{	// ƥ��ɹ�	
		return ptr - cTarget;
	}
}

String SubString(const String &s, int pos, int len)
// ��ʼ��������s���ڣ�0 <= pos < s.Length()��0 <= len <= s.Length() - pos
// ������������ش�s�ĵ�pos���ַ���ʼ�ĳ���Ϊlen���Ӵ�
{
	if (0 <= pos && pos < s.Length() && 0 <= len)
	{	// ���ش�s�ĵ�pos���ַ���ʼ�ĳ���Ϊlen���Ӵ�
		len = (len < s.Length() - pos) ? len : (s.Length() - pos);// �Ӵ���
		char *sub = new char[len + 1];			// ����洢�ռ�
		const char *str = s.CStr();				// ����C���
		strncpy(sub, str + pos, len);			// ���ƴ�
		sub[len] = '\0';						// ��ֵ��'\0'����
		String tem(sub);						// ���ɴ�����
		return tem;
	}
	else
	{	// ���ؿմ�
		String tem("");							// ���ɿմ�����
		return tem;
	}
}

bool operator ==(const String &first, const String &second)
// ������������ع�ϵ�����==
{
	return strcmp(first.CStr(), second.CStr()) == 0;
}

bool operator <(const String &first, const String &second)
	// ������������ع�ϵ�����<
{
	return strcmp(first.CStr(), second.CStr()) < 0;
}

bool operator >(const String &first, const String &second)
// ������������ع�ϵ�����>
{
	return strcmp(first.CStr(), second.CStr()) > 0;
}

bool operator <=(const String &first, const String &second)
// ������������ع�ϵ�����<=
{
	return strcmp(first.CStr(), second.CStr()) <= 0;
}

bool operator >=(const String &first, const String &second)
// ������������ع�ϵ�����>=
{
	return strcmp(first.CStr(), second.CStr()) >= 0;
}

bool operator !=(const String &first, const String &second)
// ������������ع�ϵ�����!=
{
	return strcmp(first.CStr(), second.CStr()) != 0;
}