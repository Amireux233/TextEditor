#ifndef __NODE_H__
#define __NODE_H__

// �����ģ��
template <class ElemType>
struct Node
{
	// ���ݳ�Ա:
	ElemType data;				// ������
	Node<ElemType> *next;		// ָ����

								// ���캯��ģ��:
	Node();						// �޲����Ĺ��캯��ģ��
	Node(ElemType item, Node<ElemType> *link = NULL);	// ��֪����Ԫ��ֵ��ָ�뽨���ṹ
};

// �����ģ���ʵ�ֲ���
template<class ElemType>
Node<ElemType>::Node()
// �������������ָ����Ϊ�յĽ��
{
	next = NULL;
}

template<class ElemType>
Node<ElemType>::Node(ElemType item, Node<ElemType> *link)
// �������������һ��������Ϊitem��ָ����Ϊlink�Ľ��
{
	data = item;
	next = link;
}

#endif

