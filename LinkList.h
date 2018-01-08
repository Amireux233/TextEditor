#ifndef __LINK_LIST_H__
#define __LINK_LIST_H__

#include "utility.h"					// ʵ�ó��������
#include "node.h"						// �����ģ��

// ����������ģ��
template <class ElemType>
class LinkList
{
protected:
	//  ����ʵ�ֵ����ݳ�Ա:
	Node<ElemType> *head;				// ͷ���ָ��
	mutable int curPosition;			// ��ǰλ�õ����
	mutable Node<ElemType> * curPtr;	// ָ��ǰλ�õ�ָ��
	int count;							// Ԫ�ظ���

										// ��������ģ��:
	Node<ElemType> *GetElemPtr(int position) const;	// ����ָ���position������ָ��
	void Init();						// ��ʼ�����Ա�

public:
	//  �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
	LinkList();							// �޲����Ĺ��캯��ģ��
	virtual ~LinkList();				// ��������ģ��
	int Length() const;				    // �����Ա���			 
	bool Empty() const;					// �ж����Ա��Ƿ�Ϊ��
	void Clear();						// �����Ա����
	void Traverse(void(*visit)(const ElemType &)) const;	// �������Ա�
	int GetCurPosition() const;								// ���ص�ǰλ��
	StatusCode GetElem(int position, ElemType &e) const;	// ��ָ��λ�õ�Ԫ��	
	StatusCode SetElem(int position, const ElemType &e);	// ����ָ��λ�õ�Ԫ��ֵ
	StatusCode Delete(int position, ElemType &e);			// ɾ��Ԫ��		
	StatusCode Insert(int position, const ElemType &e);	// ����Ԫ��
	LinkList(const LinkList<ElemType> &copy); // ���ƹ��캯��ģ��
	LinkList<ElemType> &operator =(const LinkList<ElemType> &copy); // ���ظ�ֵ�����
};


// ������ģ���ʵ�ֲ���

template<class ElemType>
Node<ElemType> *LinkList<ElemType>::GetElemPtr(int position) const
// �������������ָ���position������ָ��
{
	if (curPosition > position)
	{	// ��ǰλ����������λ��֮��,ֻ�ܴӱ�ͷ��ʼ����
		curPosition = 0;
		curPtr = head;
	}

	for (; curPosition < position; curPosition++)
		curPtr = curPtr->next;			// ����λ��position

	return curPtr;
}

template <class ElemType>
void LinkList<ElemType>::Init()
// �����������ʼ�����Ա�
{
	head = new Node<ElemType>;		// ����ͷָ��
	curPtr = head;	curPosition = 0;// ��ʼ����ǰλ��
	count = 0;						// ��ʼ��Ԫ�ظ���
}

template <class ElemType>
LinkList<ElemType>::LinkList()
// �������������һ��������
{
	Init();
}

template <class ElemType>
LinkList<ElemType>::~LinkList()
// ����������������Ա�
{
	Clear();			// ������Ա�
	delete head;		// �ͷ�ͷ�����ָ�ռ�
}

template <class ElemType>
int LinkList<ElemType>::Length() const
// ����������������Ա�Ԫ�ظ���
{
	return count;
}

template <class ElemType>
bool LinkList<ElemType>::Empty() const
// ��������������Ա�Ϊ�գ��򷵻�true�����򷵻�false
{
	return head->next == NULL;
}

template <class ElemType>
void LinkList<ElemType>::Clear()
// ���������������Ա�
{

	ElemType tmpElem;	// ��ʱԪ��ֵ
	while (Length() > 0)
	{	// ���Ա�ǿգ���ɾ����1��Ԫ��
		Delete(1, tmpElem);
	}
}

template <class ElemType>
void LinkList<ElemType>::Traverse(void(*visit)(const ElemType &)) const
// ������������ζ����Ա��ÿ��Ԫ�ص��ú���(*visit)
{
	for (Node<ElemType> *tmpPtr = head->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{	// ��tmpPtr����ָ��ÿ��Ԫ��
		(*visit)(tmpPtr->data);	// �����Ա��ÿ��Ԫ�ص��ú���(*visit)
	}
}

template <class ElemType>
int LinkList<ElemType>::GetCurPosition() const
// ������������ص�ǰλ��
{
	return curPosition;
}

template <class ElemType>
StatusCode LinkList<ElemType>::GetElem(int position, ElemType &e) const
// ��������������Ա���ڵ�position��Ԫ��ʱ����e������ֵ������ENTRY_FOUND,
//	���򷵻�NOT_PRESENT
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return NOT_PRESENT;				// Ԫ�ز�����
	}
	else
	{	// position�Ϸ�
		Node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);	// ȡ��ָ���position������ָ��	
		e = tmpPtr->data;				// ��e���ص�position��Ԫ�ص�ֵ
		return ENTRY_FOUND;
	}
}

template <class ElemType>
StatusCode LinkList<ElemType>::SetElem(int position, const ElemType &e)
// ��������������Ա�ĵ�position��λ�õ�Ԫ�ظ�ֵΪe,
//	position��ȡֵ��ΧΪ1��position��Length(),
//	position�Ϸ�ʱ����SUCCESS,���򷵻�RANGE_ERROR
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return RANGE_ERROR;
	}
	else
	{	// position�Ϸ�
		Node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position);	// ȡ��ָ���position������ָ��
		tmpPtr->data = e;				// ���õ�position��Ԫ�ص�ֵ
		return SUCCESS;
	}
}

template <class ElemType>
StatusCode LinkList<ElemType>::Delete(int position, ElemType &e)
// ���������ɾ�����Ա�ĵ�position��λ�õ�Ԫ��, ����e������ֵ,
//	position��ȡֵ��ΧΪ1��position��Length(),
//	position�Ϸ�ʱ����SUCCESS,���򷵻�RANGE_ERROR
{
	if (position < 1 || position > Length())
	{	// position��Χ��
		return RANGE_ERROR;
	}
	else
	{	// position�Ϸ�
		Node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);		// ȡ��ָ���position-1������ָ��
		Node<ElemType> *nextPtr = tmpPtr->next;	// nextPtrΪtmpPtr�ĺ��
		tmpPtr->next = nextPtr->next;			// ɾ�����
		e = nextPtr->data;						// ��e���ر�ɾ���Ԫ��ֵ	
		if (position == Length())
		{	// ɾ��β���,��ǰ����Ϊͷ���
			curPosition = 0;					// ���õ�ǰλ�õ����
			curPtr = head;						// ����ָ��ǰλ�õ�ָ��
		}
		else
		{	// ɾ����β���,��ǰ����Ϊ��position�����
			curPosition = position;				// ���õ�ǰλ�õ����
			curPtr = tmpPtr->next;				// ����ָ��ǰλ�õ�ָ��
		}
		count--;								// ɾ���ɹ���Ԫ�ظ�����1 
		delete nextPtr;							// �ͷű�ɾ���
		return SUCCESS;
	}
}

template <class ElemType>
StatusCode LinkList<ElemType>::Insert(int position, const ElemType &e)
// ��������������Ա�ĵ�position��λ��ǰ����Ԫ��e
//	position��ȡֵ��ΧΪ1��position��Length()+1
//	position�Ϸ�ʱ����SUCCESS, ���򷵻�RANGE_ERROR
{
	if (position < 1 || position > Length() + 1)
	{	// position��Χ��
		return RANGE_ERROR; // λ�ò��Ϸ�
	}
	else
	{	// position�Ϸ�
		Node<ElemType> *tmpPtr;
		tmpPtr = GetElemPtr(position - 1);	// ȡ��ָ���position-1������ָ��
		Node<ElemType> *newPtr;
		newPtr = new Node<ElemType>(e, tmpPtr->next);// �����½��
		tmpPtr->next = newPtr;				// ��tmpPtr���뵽������
		curPosition = position;				// ���õ�ǰλ�õ����
		curPtr = newPtr;					// ����ָ��ǰλ�õ�ָ��
		count++;							// ����ɹ���Ԫ�ظ�����1 
		return SUCCESS;
	}
}

template <class ElemType>
LinkList<ElemType>::LinkList(const LinkList<ElemType> &copy)
// ��������������Ա�copy���������Ա������ƹ��캯��ģ��
{
	int copyLength = copy.Length();		// copy�ĳ���
	ElemType e;
	Init();								// ��ʼ�����Ա�

	for (int curPosition = 1; curPosition <= copyLength; curPosition++)
	{	// ��������Ԫ��
		copy.GetElem(curPosition, e);	// ȡ����curPosition��Ԫ��
		Insert(Length() + 1, e);		// ��e���뵽��ǰ���Ա�
	}
}

template <class ElemType>
LinkList<ElemType> &LinkList<ElemType>::operator =(const LinkList<ElemType> &copy)
// ��������������Ա�copy��ֵ����ǰ���Ա������ظ�ֵ�����
{
	if (&copy != this)
	{
		int copyLength = copy.Length();		// copy�ĳ���
		ElemType e;
		Clear();							// ��յ�ǰ���Ա�

		for (int curPosition = 1; curPosition <= copyLength; curPosition++)
		{	// ��������Ԫ��
			copy.GetElem(curPosition, e);	// ȡ����curPosition��Ԫ��
			Insert(Length() + 1, e);		// ��e���뵽��ǰ���Ա�
		}
	}
	return *this;
}

#endif

