#ifndef __STRING_H__
#define __STRING_H__

#include "LinkList.h"							// 线性链表

// 串类
class String
{
protected:
	//  串实现的数据成员:
	mutable char *strVal;						// 串值
	int length;									// 串长	

public:
	//  抽象数据类型方法声明及重载编译系统默认方法声明:
	String();									// 构造函数 
	virtual ~String();							// 析构函数
	String(const String &copy);					// 复制构造函数
	String(const char *copy);					// 从C风格串转换的构造函数
	String(LinkList<char> &copy);				// 从线性表转换的构造函数
	int Length() const;							// 求串长度			 
	bool Empty() const;							// 判断串是否为空
	String &operator =(const String &copy);		// 重载赋值运算符
	const char *CStr() const;	// 将串转换成C风格串
	char &String::operator [](int pos) const;	// 重载下标运算符
};

// 串相关操作
String Read(istream &input);					// 从输入流读入串
String Read(istream &input, char &terminalChar);
// 从输入流读入串，并用terminalChar返回串结束字符
void Write(const String &s);					// 输出串
void Concat(String &addTo, const String &addOn);
// 将串addOn连接到addTo串的后面
void Copy(String &copy, const String &original);
// 将串original复制到串copy
void Copy(String &copy, const String &original, int n);
// 将串original复制n个字符到串copy 
int Index(const String &target, const String &pattern, int pos = 0);
// 查找模式串pattern第一次在目标串target中从第pos个字符开始出现的位置
String SubString(const String &s, int pos, int len);
// 求串s的第pos个字符开始的长度为len的子串
bool operator ==(const String &first, const String &second);
// 重载关系运算符==
bool operator <(const String &first, const String &second);
// 重载关系运算符<
bool operator >(const String &first, const String &second);
// 重载关系运算符>
bool operator <=(const String &first, const String &second);
// 重载关系运算符<=
bool operator >=(const String &first, const String &second);
// 重载关系运算符>=
bool operator !=(const String &first, const String &second);
// 重载关系运算符!=




#endif