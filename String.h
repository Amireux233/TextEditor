#ifndef __STRING_H__
#define __STRING_H__

#include "LinkList.h"							// ��������

// ����
class String
{
protected:
	//  ��ʵ�ֵ����ݳ�Ա:
	mutable char *strVal;						// ��ֵ
	int length;									// ����	

public:
	//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	String();									// ���캯�� 
	virtual ~String();							// ��������
	String(const String &copy);					// ���ƹ��캯��
	String(const char *copy);					// ��C���ת���Ĺ��캯��
	String(LinkList<char> &copy);				// �����Ա�ת���Ĺ��캯��
	int Length() const;							// �󴮳���			 
	bool Empty() const;							// �жϴ��Ƿ�Ϊ��
	String &operator =(const String &copy);		// ���ظ�ֵ�����
	const char *CStr() const;	// ����ת����C���
	char &String::operator [](int pos) const;	// �����±������
};

// ����ز���
String Read(istream &input);					// �����������봮
String Read(istream &input, char &terminalChar);
// �����������봮������terminalChar���ش������ַ�
void Write(const String &s);					// �����
void Concat(String &addTo, const String &addOn);
// ����addOn���ӵ�addTo���ĺ���
void Copy(String &copy, const String &original);
// ����original���Ƶ���copy
void Copy(String &copy, const String &original, int n);
// ����original����n���ַ�����copy 
int Index(const String &target, const String &pattern, int pos = 0);
// ����ģʽ��pattern��һ����Ŀ�괮target�дӵ�pos���ַ���ʼ���ֵ�λ��
String SubString(const String &s, int pos, int len);
// ��s�ĵ�pos���ַ���ʼ�ĳ���Ϊlen���Ӵ�
bool operator ==(const String &first, const String &second);
// ���ع�ϵ�����==
bool operator <(const String &first, const String &second);
// ���ع�ϵ�����<
bool operator >(const String &first, const String &second);
// ���ع�ϵ�����>
bool operator <=(const String &first, const String &second);
// ���ع�ϵ�����<=
bool operator >=(const String &first, const String &second);
// ���ع�ϵ�����>=
bool operator !=(const String &first, const String &second);
// ���ع�ϵ�����!=




#endif